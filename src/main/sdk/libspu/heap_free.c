/* GCC_VERSION: 2.6.3 */
#include "common.h"

typedef struct {
    u32 address;
    u32 size;
} SpuBlock;

void func_80050964(void);
extern s32 D_8005593C;
extern SpuBlock *D_80055944;

void func_800508E8(u32 address)
{
    s32 i;

    for (i = 0; i < D_8005593C; i++) {
        if (D_80055944[i].address & 0x40000000) {
            break;
        }
        if (D_80055944[i].address == address) {
            D_80055944[i].address = address | 0x80000000;
            break;
        }
    }
    func_80050964();
}
