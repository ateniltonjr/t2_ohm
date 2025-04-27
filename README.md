![image](https://github.com/user-attachments/assets/f2a5c9b8-6208-4723-8f46-1d74be421827)
# Ohmímetro com Reconhecimento Automático do Código de Cores
## 📌 Sumário
Descrição do Projeto

Funcionalidades Implementadas

Esquema do Circuito

Esquema de Conexões

Como Compilar e Executar

Saída Esperada

Autor

Vídeo de Demonstração

## 👨‍💻 Autor
Atenilton Santos de Souza Júnior
Desenvolvedor do projeto de instrumentação eletrônica
GitHub [https://github.com/ateniltonjr](https://github.com/ateniltonjr)

## 🎥 Vídeo de Demonstração
Assista ao vídeo de demonstração
[Vídeo](#link)

## 📝 Descrição do Projeto
Este projeto implementa um ohmímetro inteligente baseado no microcontrolador RP2040 (BitDogLab) que mede resistências na faixa de 510Ω a 100kΩ (série E24 com 5% de tolerância) e identifica automaticamente o código de cores correspondente (3 primeiras faixas, sendo a quarta sempre dourada).

## ✨ Funcionalidades Implementadas
Sistema de medição preciso:

Utiliza resistor de referência de 10kΩ

Faixa de medição: 510Ω a 100kΩ

Leitura ADC com resolução de 12 bits (0-4095)

Processamento e exibição:

Cálculo do valor real da resistência

Aproximação para valor comercial mais próximo (série E24)

Identificação automática do código de cores (3 faixas)

Saídas de informação:

Display OLED SSD1306:

Valor do ADC (0-4095)

Valor real calculado

Valor aproximado (E24)

Representação gráfica das 3 faixas de cores

Monitor Serial:

Valor real calculado

Valor aproximado (E24)

Valor bruto do ADC

Matriz de LEDs WS2812B:

Visualização do código de cores (acionado pelo botão A)

Controles:

Botão A: Ativa visualização do código de cores na matriz de LEDs

Botão B: Coloca o RP2040 em modo BOOTSEL para programação

## 🛠️ Esquema do Circuito
[Conteúdo original...]

## 📋 Esquema de Conexões
Componente	Pino RP2040

OLED SDA	GPIO0

OLED SCL	GPIO1

Matriz LED	GPIO2

ADC (Resistor)	GPIO28

Botão A	GPIO3

Botão B	GPIO4


## 🚀 Como Compilar e Executar no VS Code
e
Pré-requisitos:

VS Code com extensão "Pico W-Go" ou "Cortex-Debug"

SDK do Raspberry Pi Pico instalado

Kit de ferramentas ARM GCC

Configuração do projeto:

bash

git clone https://github.com/ateniltonjr/t2_ohm.git

cd t2_ohm

mkdir build

cd build

cmake ..


Compilação:

Abra o projeto no VS Code

Pressione Ctrl+Shift+B para compilar

Ou execute no terminal:

bash

make -j4

Upload para a placa:

Mantenha pressionado o botão BOOTSEL enquanto conecta a placa via USB

Copie o arquivo ohmimetro.uf2 para a unidade RPI-RP2

Monitoramento Serial:

Conecte via terminal serial (115200 baud):

bash
minicom -o -D /dev/ttyACM0
ou use o monitor serial do VS Code

## 📊 Saída Esperada
Exemplo:

ADC: 2048

Valor Real: 9.95 kΩ

Aproximado: 10 kΩ

Cores: Marrom-Preto-Laranja

## Detalhes Adicionais:
O vídeo demonstra todo o fluxo de operação do sistema

Mostra a medição de diferentes resistores

Apresenta a visualização tanto no display quanto na matriz de LEDs

Inclui detalhes sobre a precisão das medições

## Como Contribuir:
Faça um fork do projeto

Crie sua branch (git checkout -b feature/nova-funcionalidade)

Commit suas mudanças (git commit -m 'Adiciona nova funcionalidade')

Push para a branch (git push origin feature/nova-funcionalidade)

Abra um Pull Request
