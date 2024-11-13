#include "oled.h"
#include "twi.h"

#define OLED_ADDR (0x3C)

static void oled_send_command(uint8_t command) {
    twi_begin_send(OLED_ADDR);
    twi_send(0x00);  // command
    twi_send(command);
    twi_finish_send();
}

static void oled_send_data(uint8_t data) {
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
    // oled_send_command(0xAF);
}

void oled_clear() {
    for (uint8_t y = 0; y < 8; y++) {
        oled_send_command(0x00 | 2);
        oled_send_command(0x10);
        oled_send_command(0xB0 | y);
        twi_begin_send(OLED_ADDR);
        twi_send(0x40);
        for (uint16_t i = 0; i < 128; i++) {
            twi_send(0x00);
        }
        twi_finish_send();
    }
}

void oled_off() {
    oled_send_command(0xAE);
}

void oled_on() {
    oled_send_command(0xAF);
}

void oled_start_draw(uint8_t x, uint8_t y) {
    x += 2;
    oled_send_command(0x00 | (x & 0xF));
    oled_send_command(0x10 | (x >> 4));
    oled_send_command(0xB0 | y);
    twi_begin_send(OLED_ADDR);
    twi_send(0x40);
}

void oled_draw(uint8_t data) {
    twi_send(data);
}

void oled_finish_draw() {
    twi_finish_send();
}