#define UART0DR (volatile unsigned char*)0x10010000

void uart_send(char c) { *UART0DR = c; }

void print_s(const char* s) {
    while (*s != '\0') {
        /* convert newline to carrige return + newline */
        if (*s == '\n') uart_send('\r');
        uart_send(*s++);
    }
}

void print_c(char c) { uart_send(c); }

void print_i(int x) {
    if (x < 0) {
        print_c('-');
        x = -x;
    }
    if (x >= 10) print_i(x / 10);
    print_c(x % 10 + '0');
}

int main() {
    char s[20] = "Hello world!\n";
    print_s(s);
    return 0;
}
