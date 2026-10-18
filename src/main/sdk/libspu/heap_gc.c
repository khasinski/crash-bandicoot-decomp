/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u32 address;
    u32 size;
} SpuBlock;

extern s32 D_80055940;
extern SpuBlock *D_80055944;

void func_80050964(void) {
    s32 i;
    s32 j;
    u32 temp_addr;
    u32 temp_size;

    for (i = 0; i <= D_80055940; ) {
        if (D_80055944[i].address & 0x80000000) {
            for (j = i + 1; ; j++) {
                if (D_80055944[j].address != 0x2FFFFFFF) {
                    goto found;
                }
            }
        found:
            if ((D_80055944[j].address & 0x80000000) &&
                ((D_80055944[j].address & 0x0FFFFFFF) == (D_80055944[i].address & 0x0FFFFFFF) + D_80055944[i].size)) {
                D_80055944[j].address = 0x2FFFFFFF;
                D_80055944[i].size += D_80055944[j].size;
                continue;
            }
        }
        i++;
    }
    for (i = 0; i <= D_80055940; i++) {
        if (D_80055944[i].size == 0) {
            D_80055944[i].address = 0x2FFFFFFF;
        }
    }
    for (i = 0; i <= D_80055940; i++) {
        if (D_80055944[i].address & 0x40000000) {
            break;
        }
        for (j = i + 1; j <= D_80055940; j++) {
            if (D_80055944[j].address & 0x40000000) {
                break;
            }
            if ((D_80055944[j].address & 0x0FFFFFFF) < (D_80055944[i].address & 0x0FFFFFFF)) {
                temp_addr = D_80055944[i].address;
                D_80055944[i].address = D_80055944[j].address;
                temp_size = D_80055944[i].size;
                D_80055944[i].size = D_80055944[j].size;
                D_80055944[j].address = temp_addr;
                D_80055944[j].size = temp_size;
            }
        }
    }
    for (i = 0; i <= D_80055940; i++) {
        if (D_80055944[i].address & 0x40000000) {
            break;
        }
        if (D_80055944[i].address == 0x2FFFFFFF) {
            D_80055944[i].address = D_80055944[D_80055940].address;
            D_80055944[i].size = D_80055944[D_80055940].size;
            D_80055940 = i;
            break;
        }
    }
    for (i = D_80055940 - 1; i >= 0; i--) {
        if (!(D_80055944[i].address & 0x80000000)) {
            break;
        }
        D_80055944[i].address = (D_80055944[i].address & 0x0FFFFFFF) | 0x40000000;
        D_80055944[i].size += D_80055944[D_80055940].size;
        D_80055940 = i;
    }
}
