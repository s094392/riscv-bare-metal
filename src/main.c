#include <timer.h>

#include "kalloc.h"
#include "kvm.h"
#include "trap.h"
#include "uart.h"

int main() {
    uart_init();
    kinit();
    kviminit();
    kvminithart();
    print_s("Hello world!\n");
    timer_init();
    print_s("Raise exception to enable timer...\n");
    print_s("Back to user mode\n");
    while (1)
        ;
    return 0;
}
