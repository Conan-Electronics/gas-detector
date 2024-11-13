#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>

void uart_init();
void uart_send_char(char data);
void uart_send_str(const char* string);
void uart_send_str_P(PGM_P string);
char uart_get_char();
size_t uart_get_str(char* string, size_t size);

void uart_send_u8(uint8_t data);

#ifdef USE_STDIO
char* getsn(char* str, int size);
#endif

#endif