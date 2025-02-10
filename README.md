# Projeto: Uso de SDK com Raspberry Pi Pico W e Kit BitDogLab

## 📌 Descrição

Este projeto utiliza a **Raspberry Pi Pico W** em conjunto com o **Kit de Desenvolvimento BitDogLab** para controle de uma matriz de LEDs, interação com botões e exibição de informações em um **display OLED SSD1306** via comunicação **I2C**. Além disso, permite o recebimento de caracteres via **UART** para acionar padrões na matriz de LEDs.

## 🎯 Objetivos

✔ - Implementar comunicação via **I2C** e **UART** para controle de periféricos.
✔ - Utilizar o **Pico SDK** para programação em **C**.
✔ - Trabalhar com interrupções para capturar eventos dos botões.

## 📺 Demonstração

- **Execução na Placa BitDogLab:** 
- **Vídeo** [Youtube](https://youtube.com/shorts/05vVg3j3qGU)

## 🛠 Tecnologia Utilizada

### 🔹 **Software**
- **Linguagem de Programação:** C
- **IDE:** Visual Studio Code
- **SDK:** Pico SDK
- **Simulador:** Wokwi
- **Controle de Versão:** Git
- **Plataforma de Hospedagem:** GitHub

### 🔹 **Hardware**
- **Placa de Desenvolvimento:** BitDogLab
- **Display OLED:** SSD1306 (I2C)
- **Matriz de LEDs:** WS2812 (PIO)
- **Botões:** Push buttons

## 📂 Estrutura do Projeto

```
pico_project/
│── build/                  # Arquivos compilados (gerado pelo CMake)
│── includes/               # Cabeçalhos das funções
│   ├── font.h
│   ├── ssd1306.h
│
│── src/                    # Implementação das funções
│   ├── ssd1306.c
│
│── CMakeLists.txt          # Configuração do CMake
│── pico_sdk_import.cmake   # Importação do SDK do Pico
│── README.md               # Documentação do projeto
│── wokwi.toml              # Configuração do simulador Wokwi
│── diagram.json            # Arquivo de configuração do circuito
│── tarefa_comunicacao.c    # Código principal do projeto
│── tarefa_comunicacao.pio  # Código de configuração de PIO
```

## 🎮 Funcionalidades

- **Botão A** Alterna o estado do LED Verde e exibe no display OLED.
- **Botão B** Alterna o estado do LED Azul e exibe no display OLED.
- **Recebimento via UART** Aciona padrões na matriz de LEDs de acordo com o número recebido.

## 📡 Protocolos Utilizados

- **I2C:** Comunicação entre o Raspberry Pi Pico W e o display OLED SSD1306.
- **UART:** Comunicação serial para recebimento de caracteres e controle da matriz de LEDs.

## 📝 Como Executar o Projeto

1️⃣ **Clone o repositório:**
```sh
 git clone https://github.com/joaossc12/tarefa_comunicacao
 cd tarefa_comunicacao
```

2️⃣ **Compile o projeto:**
```sh
 mkdir build && cd build
 cmake ..
 make
```

3️⃣ **Carregue o código na sua Raspberry Pi Pico W** e teste as funcionalidades.

