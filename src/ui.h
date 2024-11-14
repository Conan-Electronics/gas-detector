#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

void ui_text2l(uint8_t x, uint8_t y, const uint8_t *lines, uint8_t width);
void ui_text1l(uint8_t x, uint8_t y, const uint8_t *data, uint8_t width);
void ui_number(uint8_t x, uint8_t y, uint32_t data);
void ui_progress(uint8_t x, uint8_t y, uint8_t width, uint32_t pos, uint32_t total);

#endif