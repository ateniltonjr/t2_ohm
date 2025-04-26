#ifndef OHMIMETRO_H
#define OHMIMETRO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "lib/font.h"
#include "lib/resistores.h"
#include "lib/bootsel.h"
#include "lib/display.h"

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
    exibir_codigo_cores(*R_aproximado);

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

#endif