#include <stdio.h>
#include "ui.h"
#include "assets.h"
#include "oled.h"

void ui_text2l(uint8_t x, uint8_t y, const uint8_t *lines, uint8_t width) {
    for (int j = 0; j < 2; j++) {
        oled_start_draw(x, j + y);
        for (int i = 0; i < width; i++) {
            oled_draw(pgm_read_byte(lines + j * width + i));
        }
        oled_finish_draw();
    }
}

void ui_text1l(uint8_t x, uint8_t y, const uint8_t *data, uint8_t width) {
    oled_start_draw(x, y);
    for (int i = 0; i < width; i++) {
        oled_draw(pgm_read_byte(data + i));
    }
    oled_finish_draw();
}

#define NUM_BUFFER_SIZE (22)
static char num_buffer[NUM_BUFFER_SIZE];

void ui_number(uint8_t x, uint8_t y, uint32_t data) {
    snprintf(num_buffer, NUM_BUFFER_SIZE, "%d", data);
    int pos = x;
    for (int i = 0; i < NUM_BUFFER_SIZE; i++) {
        if (num_buffer[i] == '\0') break;
        ui_text1l(pos, y, text_digits[num_buffer[i] - '0'], TEXT_DIGITS_WIDTH);
        pos += TEXT_DIGITS_WIDTH;
    }
}

void ui_progress(uint8_t x, uint8_t y, uint8_t width, uint32_t pos, uint32_t total) {
    uint8_t inner_width = width - 2 * 2;
    uint8_t fill = pos * inner_width / total;
    uint8_t empty = inner_width - fill;
    oled_start_draw(x, y);
    oled_draw(PB_BORDER);
    oled_draw(PB_EMPTY);
    for (int i = 0; i < fill; i++) {
        oled_draw(PB_FULL);
    }
    for (int i = 0; i < empty; i++) {
        oled_draw(PB_EMPTY);
    }
    oled_draw(PB_EMPTY);
    oled_draw(PB_BORDER);
}