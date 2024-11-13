#ifndef _TWI_H_
#define _TWI_H_

#include <stdint.h>

void oled_init();
void oled_clear();
void oled_off();
void oled_on();
void oled_start_draw(uint8_t x, uint8_t y);
void oled_draw(uint8_t data);
void oled_finish_draw();

#endif