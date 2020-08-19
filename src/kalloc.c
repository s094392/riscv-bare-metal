#include "kalloc.h"
#include "memorylayout.h"
#include "memutils.h"
#include "riscv.h"
#include "stdint.h"
#include "uart.h"

#define PGUP(addr) (((addr) + PGSIZE - 1) & ~(PGSIZE - 1))
extern uint8_t end[];
struct run_t *freelist;

// construct the freelist from end of the text to PHYSTOP
void kinit() {
    uint8_t *p;
    for (p = (uint8_t *)PGUP((uint64_t)end); (uint64_t)p + PGSIZE <= PHYSTOP;
         p += PGSIZE) {
        kfree(p);
    }
}

void kfree(uint8_t *pa) {
    c_memset(pa, 1, PGSIZE);
    struct run_t *r = (struct run_t *)pa;
    r->next = freelist;
    freelist = r;
}

void *kalloc() {
    void *pa = freelist;
    freelist = freelist->next;
    return pa;
}
