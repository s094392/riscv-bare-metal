#include "stdint.h"
struct run_t {
    struct run_t* next;
};

void kinit();
void kfree(uint8_t* pa);
