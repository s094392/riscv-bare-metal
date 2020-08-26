#include "kalloc.h"
#include "kvm.h"
#include "memorylayout.h"
#include "memutils.h"
#include "riscv.h"
#include "stdint.h"

extern uint8_t end[];
pagetable_t k_pagetable;

void kviminit() {
    k_pagetable = (pagetable_t)kalloc();
    c_memset(k_pagetable, 0, PGSIZE);

    // uart registers
    kvmmap(UART0, UART0, PGSIZE, PTE_R | PTE_W);

    // virtio mmio disk interface
    kvmmap(VIRTIO0, VIRTIO0, PGSIZE, PTE_R | PTE_W);

    // CLINT
    kvmmap(CLINT, CLINT, 0x10000, PTE_R | PTE_W);

    // PLIC
    kvmmap(PLIC, PLIC, 0x400000, PTE_R | PTE_W);

    // map kernel text executable and read-only.
    kvmmap(KERNBASE, KERNBASE, PGSIZE * 30, PTE_W | PTE_R | PTE_X);
}

void kvmmap(uint64_t va, uint64_t pa, uint64_t sz, int perm) {
    mappages(k_pagetable, va, sz, pa, perm);
}

void mappages(pagetable_t pagetable, uint64_t va, uint64_t size, uint64_t pa,
              int perm) {
    uint64_t a, last;
    pte_t *pte;
    a = PGROUNDDOWN(va);
    last = PGROUNDDOWN(va + size - 1);
    for (; a != last + PGSIZE; a += PGSIZE, pa += PGSIZE) {
        pte = walk(pagetable, a, 1);
        *pte = PA2PTE(pa) | perm | PTE_V;
    }
}

pte_t *walk(pagetable_t pagetable, uint64_t va, int alloc) {
    for (int level = 2; level > 0; level--) {
        pte_t *pte = &pagetable[PX(level, va)];
        if (*pte & PTE_V) {
            pagetable = (pagetable_t)PTE2PA(*pte);
        } else {
            if (!alloc || (pagetable = (pde_t *)kalloc()) == 0) return 0;
            c_memset(pagetable, 0, PGSIZE);
            *pte = PA2PTE(pagetable) | PTE_V;
        }
    }
    return &pagetable[PX(0, va)];
}

void kvminithart() {
    w_satp(MAKE_SATP(k_pagetable));
    //    sfence_vma();
}
