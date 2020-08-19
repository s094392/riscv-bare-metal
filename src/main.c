#include <timer.h>

#include "kalloc.h"
#include "trap.h"
#include "uart.h"

int main() {
    uart_init();
    kinit();
    print_s("Hello world!\n");
    timer_init();
    print_s("Raise exception to enable timer...\n");
    print_s("Back to user mode\n");
    while (1)
        ;
    return 0;
}
