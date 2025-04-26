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

int main() {
    stdio_init_all();
    button_interrupt();
    init_display();

    adc_init();
    adc_gpio_init(ADC_PIN);

    char str_x[5];
    char str_y[6]; // 6 para garantir espaço se for até "100000"

    bool cor = true;
    while (true) {
        adc_select_input(2);

        float soma = 0.0f;
        for (int i = 0; i < 500; i++) {
            soma += adc_read();
            sleep_ms(1);
        }
        float media = soma / 500.0f;

        R_x = (R_conhecido * media) / (ADC_RESOLUTION - media);

        sprintf(str_x, "%1.0f", media);
        int R_aproximado = resistor_mais_proximo(R_x);
        sprintf(str_y, "%1.0f", R_x);   // Converte o float em string

        printf("resistencia medida: %.2f Ohms, aproximada: %d Ohms, media ADC: %.2f\n", R_x, R_aproximado, media);

        ssd1306_fill(&ssd, !cor);
        ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor);
        ssd1306_line(&ssd, 3, 25, 123, 25, cor);
        ssd1306_line(&ssd, 3, 37, 123, 37, cor);
        ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 6);
        ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 16);
        ssd1306_draw_string(&ssd, "  Ohmimetro", 10, 28);
        ssd1306_draw_string(&ssd, "ADC", 13, 41);
        ssd1306_draw_string(&ssd, "Resisten.", 50, 41);
        ssd1306_line(&ssd, 44, 37, 44, 60, cor);
        ssd1306_draw_string(&ssd, str_x, 8, 52);
        ssd1306_draw_string(&ssd, str_y, 59, 52);
        ssd1306_send_data(&ssd);

        sleep_ms(700);
    }
}
