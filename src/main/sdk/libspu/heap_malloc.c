/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u32 address;
    u32 size;
} SpuBlock;

extern s32 D_80055908;
extern s32 D_80055910;
extern s32 D_8005593C;
extern s32 D_80055940;
extern SpuBlock *D_80055944;
extern s32 D_80055954;
extern s32 D_80055958;

void func_80050964(void);

s32 func_8005115C(s32 size) {
    s32 i = 0;
    s32 found = -1;
    s32 rev_size;
    s32 temp;
    u32 temp_addr;
    u32 temp_size;
    u32 block_size;

    if (D_80055954 == 0) {
        rev_size = 0;
    } else {
        rev_size = (0x10000 - D_80055958) << D_80055908;
    }
    if (size & ~D_80055910) {
        temp = size + D_80055910;
    } else {
        temp = size;
    }
    size = temp >> D_80055908;
    size = size << D_80055908;
    if (D_80055944->address & 0x40000000) {
        found = 0;
    } else {
        func_80050964();
        for (; i < D_8005593C; i++) {
            if ((D_80055944[i].address & 0x40000000) ||
                ((D_80055944[i].address & 0x80000000) && (D_80055944[i].size >= (u32)size))) {
                found = i;
                break;
            }
        }
    }
    if (found == -1) {
        return -1;
    }
    if (D_80055944[found].address & 0x40000000) {
        if ((found < D_8005593C) && ((D_80055944[found].size - rev_size) >= (u32)size)) {
            D_80055940 = found + 1;
            D_80055944[D_80055940].address = ((D_80055944[found].address & 0x0FFFFFFF) + size) | 0x40000000;
            D_80055944[D_80055940].size = D_80055944[found].size - size;
            D_80055944[found].size = size;
            D_80055944[found].address &= 0x0FFFFFFF;
            func_80050964();
            return D_80055944[found].address;
        }
        return -1;
    }
    block_size = D_80055944[found].size;
    if ((u32)size < block_size) {
        if (D_80055940 < D_8005593C) {
            u32 new_addr = D_80055944[found].address + size;
            temp_addr = D_80055944[D_80055940].address;
            temp_size = D_80055944[D_80055940].size;
            D_80055944[D_80055940].address = new_addr | 0x80000000;
            D_80055944[D_80055940].size = block_size - size;
            D_80055944[D_80055940 + 1].address = temp_addr;
            D_80055944[D_80055940 + 1].size = temp_size;
            D_80055940++;
        }
    }
    D_80055944[found].size = size;
    D_80055944[found].address &= 0x0FFFFFFF;
    func_80050964();
    return D_80055944[found].address;
}
