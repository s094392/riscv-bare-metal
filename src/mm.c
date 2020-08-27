#include "kalloc.h"
#include "memorylayout.h"
#include "mm.h"
#include "riscv.h"
#include "uart.h"

#define PA2PFN(a) (a >> 12)
#define BASEPFN PA2PFN(KERNBASE)
#define TOPPFN PA2PFN(PHYSTOP)
struct page_t* page;

void pageinit(struct page_t* page) {
    page->counters = 0;
    page->order = 0;
}

void paginginit() {
    page = (struct page_t*)kalloc();
    int total_pages = (TOPPFN - BASEPFN);
    for (int i = 0; i < (sizeof(struct page_t) * total_pages) / PGSIZE; i++) {
        kalloc();
    }
    unsigned pfn = BASEPFN;
    for (; pfn < PA2PFN((int64_t)freelist); pfn++) {
        pageinit(&page[pfn - BASEPFN]);
        page[pfn - BASEPFN].counters = 1;
    }
    for (; pfn < PA2PFN(PHYSTOP); pfn++) {
        pageinit(&page[pfn - BASEPFN]);
        page[pfn - BASEPFN].counters = 0;
    }
}
