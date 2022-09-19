
#pragma once

#include <string.h>
#include <stdint.h>

/*
	Taken from: https://github.com/tylov/STC/blob/master/include/stc/ccommon.h
	It's MIT licensed
*/

#define _c_ROTL(x, k) (x << (k) | x >> (8*sizeof(x) - (k)))

static inline uint64_t c_fasthash(const void* key, size_t len) {
    const uint8_t *x = (const uint8_t*) key;
    uint64_t u8, h = 1; size_t n = len >> 3;
    uint32_t u4;
    while (n--) {
        memcpy(&u8, x, 8), x += 8;
        h += (_c_ROTL(u8, 26) ^ u8)*0xc6a4a7935bd1e99d;
    }
    switch (len &= 7) {
        case 0: return h;
        case 4: memcpy(&u4, x, 4);
                return h + u4*0xc6a4a7935bd1e99d;
    }
    h += *x++;
    while (--len) h = (h << 10) - h + *x++;
    return _c_ROTL(h, 26) ^ h;
}
