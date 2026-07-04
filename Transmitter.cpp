#include <stdio.h>
#include "pico/stdlib.h"
#include <RF24.h>
#include <stdint.h>

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

    radio.setPALevel(RF24_PA_LOW);      // Use LOW for testing
    radio.setDataRate(RF24_250KBPS);    // Most reliable
    radio.openWritingPipe(address);
    radio.stopListening();

    int counter = 0;

    while (true) {
        bool ok = radio.write(&counter, sizeof(counter));

        printf("Sent %d : %s\n", counter, ok ? "OK" : "FAIL");

        counter++;
        sleep_ms(1000);
    }
}