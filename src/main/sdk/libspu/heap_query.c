#include "common.h"
typedef struct {u32 address, size;} SpuBlock;

extern SpuBlock *D_80055944;
s32 func_80047120(u32 address) {
    u32 free_flag = 0x80000000;
    u32 end_flag = 0x40000000;
    u32 address_mask = 0x0fffffff;
    SpuBlock *block = D_80055944;
    while (1) {
        u32 base = block->address;
        if (!(base & free_flag)) {
            if (base & end_flag) break;
            base &= address_mask;
            if (base >= address || address < base + block->size) return 1;
        }
        block++;
    }
    return 0;
}

s32 func_80047190(u32 address) {
    SpuBlock *block = D_80055944;
    address <<= D_80055908;
    for (;;) {
        u32 base = block->address;
        if (!(base & 0x80000000)) {
            if (base & 0x40000000) break;
            base &= 0x0fffffff;
            if (base >= address || address < base + block->size) return 1;
        }
        block++;
    }
    return 0;
}
