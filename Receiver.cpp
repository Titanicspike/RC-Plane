#include <stdio.h>
#include "pico/stdlib.h"
#include <RF24.h>

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


    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.setAutoAck(false);
    radio.setPayloadSize(sizeof(int));

    radio.openReadingPipe(0, address);
    radio.startListening();
    
    for (int i = 0; i < 15; i++) {
        radio.printDetails();
        sleep_ms(1000);
    }
    while (true) {
        if (radio.available()) {
            int value;
            radio.read(&value, sizeof(value));

            printf("Received: %d\n", value);
            
        }
        else
        {
            printf("No data available\n");
            sleep_ms(500);
        }
    }
}