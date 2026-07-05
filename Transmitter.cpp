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

    while(!radio.begin(&spi)) {
        printf("Radio failed!\n");
        sleep_ms(1000);
    }
    radio.flush_rx();
    radio.flush_tx();
    while(!radio.isChipConnected()) 
    {
        printf("Chip not detected - check wiring!\n");
        sleep_ms(1000);
    }  


    radio.setPALevel(RF24_PA_HIGH);      // Use LOW for testing
    radio.setDataRate(RF24_250KBPS);    // Most reliable
    radio.setAutoAck(false);
    radio.setPayloadSize(sizeof(int));
    radio.openWritingPipe(address);
    radio.stopListening();

    for (int i = 0; i < 15; i++) {
        radio.printDetails();
        sleep_ms(1000);
    }
    int counter = 0;

    while (true) {
        bool ok = radio.write(&counter, sizeof(counter));

        printf("Sent %d : %s\n", counter, ok ? "OK" : "FAIL");

        counter++;
        sleep_ms(1000);
    }
}