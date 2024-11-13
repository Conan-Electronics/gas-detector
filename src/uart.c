#include <avr/io.h>
#include "uart.h"

// baud rate 9600 and F_CPU=16MHz
#define UBRR_VALUE 103
#define PUTTY_FIX
// #define USE_STDIO

void uart_send_char(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_send_str(const char* string) {
    while (*string != '\0') {
        if (*string == '\n') {
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = '\r';
        }
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = *string;
        string++;
    }
}

void uart_send_str_P(PGM_P string) {
    char data;
    while ((data = pgm_read_byte(string)) != '\0') {
        if (data == '\n') {
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = '\r';
        }
        while (!(UCSR0A & (1 << UDRE0)));
        UDR0 = data;
        string++;
    }
}

void uart_send_u8(uint8_t data) {
    uint8_t out, started = 0;

    out = data / 100;
    if (out > 0) {
        uart_send_char('0' + out);
        started = 1;
    }
    data -= out * 100;

    out = data / 10;
    if (started || out > 0) {
        uart_send_char('0' + out);
        started = 1;
    }
    data -= out * 10;

    if (started || data > 0) {
        uart_send_char('0' + data);
    }
}

void uart_send_i8(int8_t data) {
    if (data < 0) {
        uart_send_char('-');
        data = -data;
    }
    uart_send_u8(data);
}

char uart_get_char() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

size_t uart_get_str(char* string, size_t size) {
    uint8_t readed = 0;
    char data = '\0';
    while (readed < size && data != '\r' && data != '\n') {
        while (!(UCSR0A & (1 << RXC0)));
        *string = data = UDR0;
        string++;
        readed++;
    }
    *string = '\0';
    return readed;
}

#ifdef USE_STDIO

#include <stdio.h>

static int uart_stream_send(char data, FILE* stream) {
    if (data == '\n') uart_stream_send('\r', stream);
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
    return 0;
}

static int uart_stream_get(FILE* stream) {
    while (!(UCSR0A & (1 << RXC0)));
#ifdef PUTTYFIX
    uint8_t data = UDR0;
    if (data == '\r') return '\n';
    return data;
#else
    return UDR0;
#endif
}

static FILE uartio = FDEV_SETUP_STREAM(uart_stream_send, uart_stream_get, _FDEV_SETUP_RW);

char* getsn(char* str, int size) {
    // Mix of gets anf fgets
    char* cp;
    int c;

    if ((stdin->flags & __SRD) == 0 || size <= 0)
        return NULL;

    for (c = 0, cp = str; c != '\n' && c != '\r' && size > 0; size--, cp++) {
        if ((c = getchar()) == EOF)
            return NULL;
        *cp = (char)c;
    }
    *--cp = '\0';

    return str;
}

#endif

void uart_init() {
    UBRR0L = UBRR_VALUE & 0xFF;
    UBRR0H = UBRR_VALUE >> 8;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0A &= ~(1 << U2X0);

#ifdef USE_STDIO
    stdout = &uartio;
    stdin = &uartio;
#endif
}
