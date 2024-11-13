#include "twi.h"
#include "uart.h"

void twi_init() {
    // TWBR = 0x0C;
    TWBR = 0x48;
    // TWCR = (1 << TWEN) | _BV(TWIE) | _BV(TWEA);
}

void twi_begin_send(uint8_t address) {
    while (1) {
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        while (!(TWCR & (1 << TWINT)));
        twi_send(address << 1);
        if (TWSR == 0x18) return;
        twi_finish_send();
    }
}

void twi_send(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void twi_finish_send() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}