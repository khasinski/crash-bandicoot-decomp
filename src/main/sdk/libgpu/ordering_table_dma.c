#include "common.h"

/* GCC_VERSION: 2.6.3 */
void func_80042864(void);
s32 func_80042898(void);
extern volatile u32 *D_80054B50, *D_80054B54, *D_80054B58, *D_80054B5C;
s32 func_800416E4(u32 *table, s32 count)
{
    *D_80054B5C |= 0x08000000;
    *D_80054B58 = 0;
    *D_80054B50 = (u32)(table - 1 + count);
    *D_80054B54 = count;
    *D_80054B58 = 0x11000002;
    func_80042864();
    while (*D_80054B58 & 0x01000000) {
        if (func_80042898()) return -1;
    }
    return count;
}
