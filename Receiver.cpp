#include <stdio.h>
#include "pico/stdlib.h"
#include <RF24.h>

RF24 radio(20, 17);
SPI spi;

const uint8_t address[] = "00001";

int main() {
    stdio_init_all();

    spi.begin(spi0, 18, 19, 16);

    if (!radio.begin(&spi)) {
        printf("Radio failed!\n");
        while (1);
    }

    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);

    radio.openReadingPipe(0, address);
    radio.startListening();

    while (true) {
        if (radio.available()) {
            int value;
            radio.read(&value, sizeof(value));

            printf("Received: %d\n", value);
        }
    }
}