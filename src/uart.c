#include <stdint.h>

#include "uart.h"

static volatile uint8_t *uart;

void uart_init() {
    uart = (uint8_t *)(void *)NS16550A_UART0_CTRL_ADDR;
    uint32_t uart_freq = UART0_CLOCK_FREQ;
    uint32_t baud_rate = UART0_BAUD_RATE;
    uint32_t divisor = uart_freq / (16 * baud_rate);
    uart[UART_LCR] = UART_LCR_DLAB;
    uart[UART_DLL] = divisor & 0xff;
    uart[UART_DLM] = (divisor >> 8) & 0xff;
    uart[UART_LCR] = UART_LCR_PODD | UART_LCR_8BIT;
}

static int ns16550a_putchar(int ch) {
    while ((uart[UART_LSR] & UART_LSR_RI) == 0)
        ;
    return uart[UART_THR] = ch & 0xff;
}

void uart_send(char c) { ns16550a_putchar(c); }

void print_s(const char *s) {
    while (*s != '\0') {
        /* convert newline to carrige return + newline */
        if (*s == '\n') uart_send('\r');
        uart_send(*s++);
    }
}

void print_c(char c) { uart_send(c); }

void print_i(unsigned long int x) {
    if (x < 0) {
        print_c('-');
        x = -x;
    }
    if (x >= 10) print_i(x / 10);
    print_c(x % 10 + '0');
}

void print_h(unsigned long int d) {
    unsigned int n;
    int c;
    for (c = 28; c >= 0; c -= 4) {
        // get highest tetrad
        n = (d >> c) & 0xF;
        // 0-9 => '0'-'9', 10-15 => 'A'-'F'
        n += n > 9 ? 0x37 : 0x30;
        uart_send(n);
    }
}
