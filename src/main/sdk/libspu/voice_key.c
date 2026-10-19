#include "common.h"

/* GCC_VERSION: 2.5.7 */

void SpuSetKey(s32 arg0, u32 arg1) {
    u32 var_v0;
    u32 temp_a1;
    u16 low;
    u32 temp_a3;

    temp_a1 = arg1 & 0xFFFFFF;
    temp_a3 = temp_a1 >> 0x10;
    low = temp_a1;
    if (arg0 != 0) {
        if (arg0 == 1) {
            var_v0 = temp_a1 | D_800559A4;
            g_spu_RXX[0xC4] = low;
            g_spu_RXX[0xC5] = (s16) temp_a3;
            goto block_4;
        }
    } else {
        g_spu_RXX[0xC6] = low;
        g_spu_RXX[0xC7] = (s16) temp_a3;
        var_v0 = ~temp_a1 & D_800559A4;
block_4:
        D_800559A4 = var_v0;
    }
}
