#ifndef RESISTORES_H
#define RESISTORES_H

#define r510     510
#define r560     560
#define r620     620
#define r680     680
#define r720     720
#define r750     750
#define r820     820
#define r910     910
#define r1k      1000
#define r1k2     1200
#define r1k5     1500
#define r1k8     1800
#define r2k2     2200
#define r2k7     2700
#define r3k3     3300
#define r3k9     3900
#define r4k7     4700
#define r5k6     5600
#define r6k8     6800
#define r8k2     8200
#define r10k     10000
#define r12k     12000
#define r15k     15000
#define r18k     18000
#define r22k     22000
#define r27k     27000
#define r33k     33000
#define r39k     39000
#define r47k     47000
#define r56k     56000
#define r68k     68000
#define r82k     82000
#define r100k    100000

static const int resistores_comerciais[] = {
    r510, r560, r620, r680, r720, r750, r820, r910,
    r1k, r1k2, r1k5, r1k8, r2k2, r2k7, r3k3, r3k9,
    r4k7, r5k6, r6k8, r8k2, r10k, r12k, r15k, r18k,
    r22k, r27k, r33k, r39k, r47k, r56k, r68k, r82k, r100k
};

#define NUM_RESISTORES (sizeof(resistores_comerciais) / sizeof(resistores_comerciais[0]))

#define ADC_PIN 28 // GPIO para o voltímetro

int R_conhecido = 10000;   // Resistor de 10k ohm
float R_x = 0.0;           // Resistor desconhecido
float ADC_VREF = 3.31;     // Tensão de referência do ADC
int ADC_RESOLUTION = 4095; // Resolução do ADC (12 bits)

// Função para encontrar o resistor comercial mais próximo
int resistor_mais_proximo(float valor) {
    int mais_proximo = resistores_comerciais[0];
    float menor_diferenca = fabs(valor - mais_proximo);

    for (int i = 1; i < NUM_RESISTORES; i++) {
        float diferenca = fabs(valor - resistores_comerciais[i]);
        if (diferenca < menor_diferenca) {
            menor_diferenca = diferenca;
            mais_proximo = resistores_comerciais[i];
        }
    }
    return mais_proximo;
}

#endif // RESISTORES_H
