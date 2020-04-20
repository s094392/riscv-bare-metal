#include "encoding.h"
#include "trap.h"
#include "uart.h"

int main() {
    uart_init();
    print_s("Hello world!\n");
    asm volatile("ecall");
    asm volatile("back:");
    print_s("Back to main\n");
    while (1)
        ;
    return 0;
}
