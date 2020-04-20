#include "uart.h"

void handle_trap(uintptr_t mcause, uintptr_t mepc) {
    unsigned long int stat;
    print_s("trap!\n");

    print_s("Register mcause is: 0x");
    print_h(mcause);
    print_s("\n");

    print_s("Register mepc is: 0x");
    print_h(mepc);
    print_s("\n");

    asm volatile("csrr %0, mstatus" : "=r"(stat));
    print_s("Register mstatus is: 0x");
    print_h(stat);
    print_s("\n");

    asm volatile("test:");
    asm volatile("csrr t0, mepc");
    asm volatile("addi t0, t0, 0x4");
    asm volatile("csrw mepc, t0");
}
