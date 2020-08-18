#include "riscv.h"
#include "uart.h"
#define CLINT_BASE 0x2000000
#define MTIME (volatile unsigned long long int *)(CLINT_BASE + 0xbff8)
#define MTIMECMP (volatile unsigned long long int *)(CLINT_BASE + 0x4000)

void timer_init() {
    *MTIMECMP = *MTIME + 0xfffff * 5;
    uint64_t mie = r_mie();
    mie |= (1 << 7);
    w_mie(mie);
}
