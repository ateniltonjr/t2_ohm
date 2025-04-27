/*
*             ___________________________________________
*            |                                           |
*            |  PROJETO: DualControl Matrix              |
*            |                                           |
*            |  ► Controle simultâneo de:                |
*            |    - Matriz LED 5x5 (WS2812B)             |
*            |    - Display OLED 128x64 (SSD1306)        |
*            |                                           |
*            |  ► Funcionalidades:                       |
*            |    - Joystick analógico para navegação    |
*            |    - Modos RGB com ajuste PWM             |
*            |    - Feedback sonoro via buzzer           |
*            |                                           |
*            |  ► Tecnologias:                           |
*            |    - RP2040 (BitDogLab)                   |
*            |    - Protocolos: I2C, UART, ADC, PWM, PIO |
*            |                                           |
*            |  AUTOR: Atenilton Santos de Souza Júnior  |
*            |___________________________________________|
*/

#include "lib_principal/ohmimetro.h"

 // Eventos dos botões
void eventos_botoes() 
{
     if(botaoA_pressionado) {
        botaoA_pressionado = false;
        estado_botao_A = !estado_botao_A;
        
        if(estado_botao_A) {
            atualizar_matriz_leds(cor1, cor2, cor3);
        } else {
            desliga();
        }
    }
    
    if(botaoB_pressionado) {
        botaoB_pressionado = false;
        reset_usb_boot(0, 0);
    }

    realizar_medidas(str_x, str_y, cor1, cor2, cor3, &R_aproximado);
    atualizar_display(str_x, str_y, cor1, cor2, cor3, R_aproximado, cor);
}

int main() {
    stdio_init_all();
    iniciar_botoes();
    init_display();
    controle(PINO_MATRIZ);

    adc_init();
    adc_gpio_init(ADC_PIN);

    gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, &debounceA);
    gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &debounceA);

    while (true) 
    { 
        tight_loop_contents(); //Reduz o consumo da CPU
        eventos_botoes();
        sleep_ms(100); // Reduzi o tempo de sleep para melhor responsividade
    }
}