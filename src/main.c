#include <stdio.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "oled.h"
#include "assets.h"
#include "ui.h"
#include <util/delay.h>

void main(void) {
    uart_init();
    uart_send_str_P(PSTR("Begin!"));
    oled_init();
    oled_clear();
    oled_on();
    ui_text2l((128 - TEXT_HEATING_WIDTH) / 2, 0, text_heating, TEXT_HEATING_WIDTH);
    ui_text2l((128 - TEXT_CALIBRATING_WIDTH) / 2, 2, text_calibrating, TEXT_CALIBRATING_WIDTH);
    ui_number(10, 5, 10894);
    ui_text1l(50, 5, text_max, TEXT_MAX_WIDTH);
    ui_text1l(100, 5, text_warn, TEXT_WARN_WIDTH);
    ui_progress(1, 6, 126, 0, 122);
    int pr = 0;
    while (1) {
        if (pr <= 122) {
            ui_progress(1, 6, 126, pr, 122);
            pr++;
            _delay_ms(60000 / 122);
        }
    }
}