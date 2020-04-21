#include "encoding.h"
#include "uart.h"
#define CLINT_BASE 0x2000000
#define MTIME (volatile unsigned long long int*)(CLINT_BASE + 0xbff8)
#define MTIMECMP (volatile unsigned long long int*)(CLINT_BASE + 0x4000)

int count = 0;

void handle_interrupt(uint64_t mcause) {
    unsigned long long int mie;
    asm volatile("testa:");
    if ((mcause << 1 >> 1) == 0x7) {
        print_s("Timer Interrupt: ");
        print_i(++count);
        print_s("\n");

        *MTIMECMP = *MTIME + 0xfffff * 5;

        asm volatile("csrr %0, mie" : "=r"(mie));
    } else {
        print_s("Unknown interrupt: ");
        print_i(mcause << 1 >> 1);
        print_s("\n");
        while (1)
            ;
    }
}

void handle_exception(uint64_t mcause) {
    unsigned long long int mie, mstatus;

    if (mcause == 0x8) {
        asm volatile("csrr %0, mstatus" : "=r"(mstatus));
        print_s("Register mstatus is: 0x");
        print_h(mstatus);
        print_s("\n");

        *MTIMECMP = *MTIME + 0xfffff * 5;

        asm volatile("csrr %0, mie" : "=r"(mie));
        mie |= (1 << 7);
        asm volatile("csrw mie, %0" : "=r"(mie));
    } else {
        print_s("Unknown exception: ");
        print_i(mcause << 1 >> 1);
        print_s("\n");
        while (1)
            ;
    }
}

void handle_trap() {
    uint64_t mcause, mepc;
    asm volatile("csrr %0, mcause" : "=r"(mcause));
    asm volatile("csrr %0, mepc" : "=r"(mepc));

    if (mcause >> 63) {
        handle_interrupt(mcause);
    } else {
        handle_exception(mcause);
        asm volatile("csrr t0, mepc");
        asm volatile("addi t0, t0, 0x4");
        asm volatile("csrw mepc, t0");
    }
}
