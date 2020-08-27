#include <timer.h>

#include "kalloc.h"
#include "kvm.h"
#include "mm.h"
#include "trap.h"
#include "uart.h"

int main() {
    uart_init();
    kinit();
    kvminit();
    kvminithart();
    paginginit();
    print_s("Hello world!\n");
    print_s("Raise exception to enable timer...\n");
    print_s("Back to user mode\n");
    while (1)
        ;
    return 0;
}
