#ifndef KVM_H
#define KVM_H
#include "riscv.h"
#include "stdint.h"
typedef uint64_t pde_t;

void kvminit();
void kvmmap(uint64_t va, uint64_t pa, uint64_t sz, int perm);
void mappages(pagetable_t pagetable, uint64_t va, uint64_t size, uint64_t pa,
              int perm);
pte_t *walk(pagetable_t pagetable, uint64_t va, int alloc);
void kvminithart();
#endif
