#ifndef _TWI_H_
#define _TWI_H_

#include <stdint.h>

void twi_init();
void twi_begin_send(uint8_t address);
void twi_send(uint8_t data);
void twi_finish_send();

#endif