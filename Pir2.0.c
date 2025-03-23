#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos
#define PIR_PIN 20      // Pino do sensor PIR
#define BUZZER_PIN_1 10 // Pino do primeiro buzzer
#define BUZZER_PIN_2 21 // Pino do segundo buzzer
#define LED_PIN 13      // Pino do LED indicador

// Tempo que o buzzer e LED ficam ativados (em ms)
const uint TIME_ON = 1000;

// Frequência dos buzzers (em Hz)
const uint FREQUENCY_1 = 1000;  // Frequência do primeiro buzzer (1000 Hz)
const uint FREQUENCY_2 = 500;   // Frequência do segundo buzzer (500 Hz)

// Função para ativar o buzzer com frequência
void buzzer_on(uint pin, uint frequency) {
    uint time_on = 500000 / frequency;  // Calcula o tempo para alternar o estado (em microssegundos)
    for (int i = 0; i < frequency; i++) {
        gpio_put(pin, 1);  // Liga o buzzer
        sleep_us(time_on); // Aguarda metade do ciclo
        gpio_put(pin, 0);  // Desliga o buzzer
        sleep_us(time_on); // Aguarda a outra metade do ciclo
    }
}

int main() {
    stdio_init_all();

    // Configura os pinos
    gpio_init(PIR_PIN);
    gpio_set_dir(PIR_PIN, GPIO_IN);
    gpio_init(BUZZER_PIN_1);
    gpio_set_dir(BUZZER_PIN_1, GPIO_OUT);
    gpio_init(BUZZER_PIN_2);
    gpio_set_dir(BUZZER_PIN_2, GPIO_OUT);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("Sistema de Alarme com Sensor PIR, Buzzers e LED\n");

    while (1) {
        if (gpio_get(PIR_PIN)) { // Movimento detectado
            printf("Movimento detectado!\n");
            buzzer_on(BUZZER_PIN_1, FREQUENCY_1); // Gera o som do primeiro buzzer
            buzzer_on(BUZZER_PIN_2, FREQUENCY_2); // Gera o som do segundo buzzer
            gpio_put(LED_PIN, 1); // Acende o LED
            sleep_ms(TIME_ON); // Aguarda o tempo de ativação do alarme
            gpio_put(LED_PIN, 0); // Desliga o LED
        }

        sleep_ms(100); // Pequena pausa para evitar leituras muito rápidas
    }
}
