#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */

extern u32 *D_800566F4;

s32 func_8002E060(s32 x, s32 y)
{
    if ((u32)x < 32 && (u32)y < 32 && (D_800566F4[y] & (0x80000000U >> x)) == 0) {
        return 1;
    }
    return 0;
}
