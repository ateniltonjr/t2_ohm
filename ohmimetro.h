#ifndef OHMIMETRO_H
#define OHMIMETRO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "lib/font.h"
#include "lib/resistores.h"
#include "lib/display.h"
#include "lib/matrixws.h"
#include "pico/bootrom.h"

#define botaoA 5
#define botaoB 6

void iniciar_botoes() 
{
    gpio_init(botaoA);
    gpio_set_dir(botaoA, GPIO_IN);
    gpio_pull_up(botaoA);

    gpio_init(botaoB);
    gpio_set_dir(botaoB, GPIO_IN);
    gpio_pull_up(botaoB);

}

char str_x[5];
char str_y[10];
char cor1[10], cor2[10], cor3[10];
int R_aproximado;

bool cor = true;

// Função para realizar as medições e cálculos
void realizar_medidas(char *str_x, char *str_y, char *cor1, char *cor2, char *cor3, int *R_aproximado) {
    adc_select_input(2);

    float soma = 0.0f;
    for (int i = 0; i < 500; i++) {
        soma += adc_read();
        sleep_ms(1);
    }
    float media = soma / 500.0f;

    R_x = (R_conhecido * media) / (ADC_RESOLUTION - media);

    sprintf(str_x, "%1.0f", media);  // valor médio ADC
    *R_aproximado = resistor_mais_proximo(R_x);
    sprintf(str_y, "%.0f", R_x);      // valor da resistência medida (sem "Ohms")

    printf("resistencia medida: %.2f Ohms, aproximada: %d Ohms, media ADC: %.2f\n", R_x, *R_aproximado, media);

    // Determinar as cores do resistor
    int digito1, digito2, multiplicador;
    int ordem = 0;
    int temp = *R_aproximado;
    while (temp >= 100) {
        temp /= 10;
        ordem++;
    }
    digito1 = temp / 10;
    digito2 = temp % 10;
    multiplicador = ordem;

    strcpy(cor1, cores[digito1]);
    strcpy(cor2, cores[digito2]);
    strcpy(cor3, cores[multiplicador]);
}

// Função para atualizar o display
void atualizar_display(const char *str_x, const char *str_y, const char *cor1, const char *cor2, const char *cor3, int R_aproximado, bool cor) {
    ssd1306_fill(&ssd, !cor); // limpa fundo

    // Parte de cima: Códigos de cor
    ssd1306_draw_string(&ssd, cor1, 8, 4);
    ssd1306_draw_string(&ssd, cor2, 8, 14);
    ssd1306_draw_string(&ssd, cor3, 8, 24);

    ssd1306_draw_string(&ssd, "Codigo", 78, 4);
    ssd1306_draw_string(&ssd, "de", 78, 14);
    ssd1306_draw_string(&ssd, "Cores", 78, 24);

    // Linha separadora
    ssd1306_line(&ssd, 3, 34, 123, 34, cor);

    // Parte de baixo: Valores
    ssd1306_draw_string(&ssd, "ADC:", 5, 38);
    ssd1306_draw_string(&ssd, str_x, 50, 38); // Valor médio ADC

    ssd1306_draw_string(&ssd, "Med:", 5, 46);
    ssd1306_draw_string(&ssd, str_y, 50, 46); // Valor resistência medida

    char str_aprox[10];
    sprintf(str_aprox, "%d", R_aproximado);
    ssd1306_draw_string(&ssd, "Aprox:", 5, 54);
    ssd1306_draw_string(&ssd, str_aprox, 50, 54); // Valor comercial aproximado

    ssd1306_send_data(&ssd); // Atualiza tela
}

// Função para acender os trrês primeiros LEDs com as cores do resistor
void atualizar_matriz_leds(const char *cor1, const char *cor2, const char *cor3) {

    // Função auxiliar interna para mapear nomes de cor para valores RGB
    uint8_t rr = 0, gg = 0, bb = 0;
    uint8_t fator_brilho = 10;  // Fator para reduzir o brilho para 25%

    // LED 0: primeira cor
    if (strcmp(cor1, "Preto") == 0)         { rr = 0; gg = 0; bb = 0; }
    else if (strcmp(cor1, "Marrom") == 0)   { rr = 139; gg = 69; bb = 19; }
    else if (strcmp(cor1, "Vermelho") == 0) { rr = 255; gg = 0; bb = 0; }
    else if (strcmp(cor1, "Laranja") == 0)  { rr = 255; gg = 165; bb = 0; }
    else if (strcmp(cor1, "Amarelo") == 0)  { rr = 255; gg = 255; bb = 0; }
    else if (strcmp(cor1, "Verde") == 0)    { rr = 0; gg = 255; bb = 0; }
    else if (strcmp(cor1, "Azul") == 0)     { rr = 0; gg = 0; bb = 255; }
    else if (strcmp(cor1, "Violeta") == 0)  { rr = 138; gg = 43; bb = 226; }
    else if (strcmp(cor1, "Cinza") == 0)    { rr = 128; gg = 128; bb = 128; }
    else if (strcmp(cor1, "Branco") == 0)   { rr = 255; gg = 255; bb = 255; }

    // Reduzir o brilho proporcionalmente
    rr /= fator_brilho;
    gg /= fator_brilho;
    bb /= fator_brilho;

    cores_matriz(22, rr, gg, bb);

    // LED 1: segunda cor
    if (strcmp(cor2, "Preto") == 0)         { rr = 0; gg = 0; bb = 0; }
    else if (strcmp(cor2, "Marrom") == 0)   { rr = 139; gg = 69; bb = 19; }
    else if (strcmp(cor2, "Vermelho") == 0) { rr = 255; gg = 0; bb = 0; }
    else if (strcmp(cor2, "Laranja") == 0)  { rr = 255; gg = 165; bb = 0; }
    else if (strcmp(cor2, "Amarelo") == 0)  { rr = 255; gg = 255; bb = 0; }
    else if (strcmp(cor2, "Verde") == 0)    { rr = 0; gg = 255; bb = 0; }
    else if (strcmp(cor2, "Azul") == 0)     { rr = 0; gg = 0; bb = 255; }
    else if (strcmp(cor2, "Violeta") == 0)  { rr = 138; gg = 43; bb = 226; }
    else if (strcmp(cor2, "Cinza") == 0)    { rr = 128; gg = 128; bb = 128; }
    else if (strcmp(cor2, "Branco") == 0)   { rr = 255; gg = 255; bb = 255; }

    // Reduzir o brilho proporcionalmente
    rr /= fator_brilho;
    gg /= fator_brilho;
    bb /= fator_brilho;

    cores_matriz(17, rr, gg, bb);

    // LED 2: terceira cor
    if (strcmp(cor3, "Preto") == 0)         { rr = 0; gg = 0; bb = 0; }
    else if (strcmp(cor3, "Marrom") == 0)   { rr = 139; gg = 69; bb = 19; }
    else if (strcmp(cor3, "Vermelho") == 0) { rr = 255; gg = 0; bb = 0; }
    else if (strcmp(cor3, "Laranja") == 0)  { rr = 255; gg = 165; bb = 0; }
    else if (strcmp(cor3, "Amarelo") == 0)  { rr = 255; gg = 255; bb = 0; }
    else if (strcmp(cor3, "Verde") == 0)    { rr = 0; gg = 255; bb = 0; }
    else if (strcmp(cor3, "Azul") == 0)     { rr = 0; gg = 0; bb = 255; }
    else if (strcmp(cor3, "Violeta") == 0)  { rr = 138; gg = 43; bb = 226; }
    else if (strcmp(cor3, "Cinza") == 0)    { rr = 128; gg = 128; bb = 128; }
    else if (strcmp(cor3, "Branco") == 0)   { rr = 255; gg = 255; bb = 255; }

    // Reduzir o brilho proporcionalmente
    rr /= fator_brilho;
    gg /= fator_brilho;
    bb /= fator_brilho;

    cores_matriz(12, rr, gg, bb);

    bf();
}

#define debounce_delay 300
volatile uint32_t last_interrupt_time = 0;
volatile bool botaoA_pressionado = false;
volatile bool botaoB_pressionado = false;
bool estado_botao_A = false;

void debounceA(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    
    if(current_time - last_interrupt_time < debounce_delay) 
    {
        return; // Ignora pulsos muito próximos
    }
    
    last_interrupt_time = current_time;
    
    if(gpio == botaoA) 
    {
        botaoA_pressionado = true;
    }
    else if(gpio == botaoB) 
    {
        botaoB_pressionado = true;
    }
}

#endif