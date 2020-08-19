#include "memutils.h"
#include "stdint.h"

void *c_memset(void *dst, int c, uint32_t n) {
    char *cdst = (char *)dst;
    int i;
    for (i = 0; i < n; i++) {
        cdst[i] = c;
    }
    return dst;
}
