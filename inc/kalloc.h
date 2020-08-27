#ifndef KALLOC_H
#define KALLOC_H

#include "stdint.h"
struct run_t {
    struct run_t* next;
};

extern struct run_t* freelist;

void kinit();
void kfree(uint8_t* pa);
void* kalloc();
#endif
