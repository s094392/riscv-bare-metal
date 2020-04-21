#include "encoding.h"
#include "trap.h"
#include "uart.h"

int main() {
    uart_init();
    print_s("Hello world!\n");
    print_s("Raise exception to enable timer...\n");
    asm volatile("ecall");
    print_s("Back to user mode\n");
    while (1)
        ;
    return 0;
}
