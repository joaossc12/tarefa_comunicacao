#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "tarefa_comunicacao.pio.h"
#include "hardware/i2c.h"
#include "./includes/ssd1306.h"
#include "./includes/font.h"


#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define led_red 13
#define led_blue 12
#define led_green 11
#define led_matrix 7
#define button_a 5
#define button_b 6

volatile bool green_state = 0;
volatile bool blue_state = 0;
ssd1306_t ssd;

// Prototipação
void init_pinos();
void envio_matriz_led(PIO pio, uint sm, uint ref);
void apaga_matriz_led(PIO pio, uint sm);
static void callback_button(uint gpio, uint32_t events);

int main()
{   
    sleep_ms(5000);
    //PIO
    PIO pio = pio0;
    bool clk = set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &tafera_comunicacao_program);
    uint sm = pio_claim_unused_sm(pio, true);
    tafera_comunicacao_program_init(pio, sm, offset, led_matrix);

    //Interrupções
    init_pinos();
    gpio_set_irq_enabled_with_callback(button_a, GPIO_IRQ_EDGE_FALL, true, &callback_button);
    gpio_set_irq_enabled(button_b, GPIO_IRQ_EDGE_FALL, true);

    //Display
    i2c_init(I2C_PORT, 400 * 1000); //Frquencia de 400Khz
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    //ssd1306_t ssd; // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display
    ssd1306_fill(&ssd, false); //Apaga todos pixels
    ssd1306_send_data(&ssd); //Envia o comando

    //Exibição fixa da tela
    ssd1306_rect(&ssd, 3, 3, 122, 58, 1, 0); // Desenha um retângulo
    ssd1306_draw_string(&ssd, "Recebido:", 20, 10); // Desenha uma string
    ssd1306_draw_string(&ssd, "Led Azul:", 20, 30);    
    ssd1306_draw_string(&ssd, "Led Verde:", 20, 48); // Desenha uma string
    ssd1306_send_data(&ssd); // Atualiza o display

    apaga_matriz_led(pio, sm);
    //UART
    stdio_init_all();

    printf("AGUARDANDO CHAR: \n");
    while (true) {
            char c;
            c = getchar();
            printf("Recebido: '%c'\n", c);
            ssd1306_draw_char(&ssd,c, 93, 10);
            ssd1306_send_data(&ssd);
                switch (c)
                {
                case '0' ... '9':
                    envio_matriz_led(pio, sm, c - '0');
                    break;
                
                default:
                    break;
                }
            printf("AGUARDANDO NOVO CHAR: \n");
            
        
        sleep_ms(500);
    }
}

void init_pinos(){
  gpio_init(led_red);//inicializa o pino 13 do microcontrolador
  gpio_set_dir(led_red, GPIO_OUT);//configura o pino como saída
 
  gpio_init(led_blue);//inicializa o pino 12 do microcontrolador 
  gpio_set_dir(led_blue, GPIO_OUT);//configura o pino 12 como saída
 
  gpio_init(led_green); //inicializa o pino 11 do microcontrolador
  gpio_set_dir(led_green,GPIO_OUT); //configura o pino 11 como saída

  gpio_init(button_a);//inicializa o pino 5 do microcontrolador
  gpio_set_dir(button_a, GPIO_IN);//configura o pino como entrada
  gpio_pull_up(button_a); //Pull up pino 5

  gpio_init(button_b);//inicializa o pino 6 do microcontrolador
  gpio_set_dir(button_b, GPIO_IN);//configura o pino como entrada
  gpio_pull_up(button_b); //Pull up pino 6
}
void apaga_matriz_led(PIO pio, uint sm){
    for (int i = 0; i < 25; i++)
    {
        pio_sm_put_blocking(pio, sm, 0);}
}
void envio_matriz_led(PIO pio, uint sm, uint ref){
    uint32_t cor = 0x00333300; //cor roxa
    uint32_t numbers[10][25] = {{0, cor, cor, cor,0,0, cor, 0, cor, 0, 0, cor, 0, cor,0, 0, cor, 0, cor,0, 0, cor, cor, cor,0}, //Numero 0
                        {0, cor, cor, cor,0,0, 0, cor, 0, 0, 0, 0, cor, 0, 0, 0, cor, cor, 0, 0,0, 0, cor, 0, 0}, //Numero 1
                        {0, cor, cor, cor,0, 0, cor, 0, 0, 0, 0, cor, cor, cor, 0, 0, 0, 0, cor,0, 0, cor, cor, cor,0}, //Numero 2
                        {0, cor, cor, cor, 0, 0, 0, 0, cor, 0,0, cor, cor, cor, 0, 0, 0, 0, cor, 0, 0, cor, cor, cor, 0}, //Numero 3
                        {0, cor, 0, 0,0,0, 0, 0, cor, 0,0, cor, cor, cor,0,0, cor, 0, cor,0,0, cor, 0, cor,0}, //Numero 4
                        {0, cor, cor, cor,0,0, 0, 0, cor, 0,0, cor, cor, cor,0,0, cor, 0, 0,0,0, cor, cor, cor,0}, //Numero 5
                        {0, cor, cor, cor,0,0, cor, 0, cor, 0,0, cor, cor, cor,0,0, 0, 0, cor,0,0, cor, cor, cor,0}, //Numero 6
                        {0, cor, 0, 0,0, 0, 0, 0, cor, 0, 0, cor, 0, 0,0,0, 0, 0, cor,0,0, cor, cor, cor,0}, //Numero 7
                        {0, cor, cor, cor,0,0, cor, 0, cor, 0, 0, cor, cor, cor,0,0, cor, 0, cor,0,0, cor, cor, cor,0}, //Numero 8
                        {0, cor, cor, cor,0,0, 0, 0, cor, 0,0, cor, cor, cor,0,0, cor, 0, cor,0,0, cor, cor, cor,0} //Numero 9
                        };
        for (int i = 0; i < 25; i++)
        {
            pio_sm_put_blocking(pio, sm, numbers[ref][i]);
        }
}


static void callback_button(uint gpio, uint32_t events) {
    static absolute_time_t last_time_A = 0; // Tempo do último evento do botão A
    static absolute_time_t last_time_B = 0; // Tempo do último evento do botão B
    absolute_time_t now = get_absolute_time();

    if (gpio == button_a) { // Interrupção do botão A
        if (absolute_time_diff_us(last_time_A, now) > 200000) { // Debounce de 200ms
            gpio_put(led_green,!green_state);
            green_state = !green_state;
            printf("Estado do Led Verde %d \n",green_state);
            ssd1306_draw_char(&ssd,'0' + green_state, 100, 48);
            ssd1306_send_data(&ssd);
            last_time_A = now; // Atualiza o tempo do último evento do botão A
        }
    } else if (gpio == button_b) { // Interrupção do botão B
        if (absolute_time_diff_us(last_time_B, now) > 200000) { // Debounce de 200ms
            gpio_put(led_blue,!blue_state);
            blue_state = !blue_state;
            printf("Estado do Led Azul %d \n",blue_state);
            ssd1306_draw_char(&ssd,'0' + blue_state, 100, 30);
            ssd1306_send_data(&ssd);
            last_time_B = now; // Atualiza o tempo do último evento do botão B
        }
    }
}