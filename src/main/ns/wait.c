#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Set the wait flag and service pending resource operations until the counter reaches zero. */

extern s32 D_8005CFA8;
extern s32 D_8005CFC0;
extern void func_800134C8(s32);

void func_80013748(void)
{
    D_8005CFC0 = 1;
    while (D_8005CFA8 != 0)
        func_800134C8(-1);
}
