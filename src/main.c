#include <stdio.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "twi.h"

#define OLED_ADDR (0x3C)

void oled_send_command(uint8_t command) {
    twi_begin_send(OLED_ADDR);
    twi_send(0x00);  // command
    twi_send(command);
    twi_finish_send();
}

void oled_send_data(uint8_t data) {
    twi_begin_send(OLED_ADDR);
    twi_send(0x40);  // data
    twi_send(data);
    twi_finish_send();
}

void oled_init() {
    twi_init();
    oled_send_command(0xAE);
    oled_send_command(0xD5);
    oled_send_command(0x80);
    oled_send_command(0xA8);
    oled_send_command(0x3F);
    oled_send_command(0xD3);
    oled_send_command(0x00);

    oled_send_command(0x40);
    oled_send_command(0x8D);
    oled_send_command(0x14);
    oled_send_command(0x20);
    oled_send_command(0x00);
    oled_send_command(0xA0 | 0x1);
    oled_send_command(0xC8);
    oled_send_command(0xDA);
    oled_send_command(0x12);
    oled_send_command(0x81);
    oled_send_command(0xCF);
    oled_send_command(0xd9);
    oled_send_command(0xF1);
    oled_send_command(0xDB);
    oled_send_command(0x40);
    oled_send_command(0xA4);
    oled_send_command(0xA6);
}

void main(void) {
    uart_init();
    uart_send_str_P(PSTR("Begin!"));
    twi_init();
    // while (1) {
    // for (int i = 0; i < 127; i++) {
    uart_send_str_P(PSTR("\nStart: "));
    twi_begin_send(OLED_ADDR);
    uart_send_u8(TWSR);
    // if (TWSR != 0x20) {
    //     uart_send_str_P(PSTR("\nAddr: "));
    //     uart_send_u8(i);
    //     break;
    // }
    // uart_send_str_P(PSTR("\nFinish: "));
    // twi_finish_send();
    // uart_send_u8(TWSR);
    // }

    uart_send_str_P(PSTR("\nSend byte: "));
    twi_send(0);
    uart_send_u8(TWSR);
    uart_send_str_P(PSTR("\nFinish: "));
    twi_finish_send();
    uart_send_u8(TWSR);
    while (1) {
    }
}