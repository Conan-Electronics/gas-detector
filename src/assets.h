#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <stdint.h>
#include <avr/pgmspace.h>

#define TEXT_HEATING_WIDTH (70)
const uint8_t text_heating[TEXT_HEATING_WIDTH * 2] PROGMEM;

#define TEXT_CALIBRATING_WIDTH (91)
const uint8_t text_calibrating[TEXT_CALIBRATING_WIDTH * 2] PROGMEM;

#define TEXT_DIGITS_WIDTH (6)
const uint8_t text_digits[10][TEXT_DIGITS_WIDTH] PROGMEM;

#define TEXT_MAX_WIDTH (21)
const uint8_t text_max[TEXT_MAX_WIDTH] PROGMEM;

#define TEXT_WARN_WIDTH (8)
const uint8_t text_warn[TEXT_WARN_WIDTH] PROGMEM;

#define PB_BORDER (0b11111110)
#define PB_EMPTY (0b10000010)
#define PB_FULL (0b10111010)

#endif
