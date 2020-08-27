#ifndef MM_H
#define MM_H
#include "stdint.h"
struct page_t {
    uint8_t order;
    uint8_t counters;
};

extern struct page_t* page;

void paginginit();
#endif
