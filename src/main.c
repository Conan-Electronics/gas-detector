#include <stdio.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "oled.h"

void main(void) {
    uart_init();
    uart_send_str_P(PSTR("Begin!"));
    oled_init();
    oled_clear();
    oled_on();
    for (int j = 0; j < 8; j++) {
        oled_start_draw(j * 16, j);
        for (int i = 0; i < 16; i++) {
            oled_draw(i % 2 == 0 ? 0x55 : 0xAA);
        }
        oled_finish_draw();
    }
    while (1) {
    }
}