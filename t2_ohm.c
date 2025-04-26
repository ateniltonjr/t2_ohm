#include "ohmimetro.h"

int main() {
    stdio_init_all();
    button_interrupt();
    init_display();

    adc_init();
    adc_gpio_init(ADC_PIN);

    while (true) {
        realizar_medidas(str_x, str_y, cor1, cor2, cor3, &R_aproximado);
        atualizar_display(str_x, str_y, cor1, cor2, cor3, R_aproximado, cor);

        sleep_ms(700);
    }
}