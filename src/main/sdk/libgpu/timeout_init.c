#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Establish the GPU operation timeout and reset its polling counter. */
extern s32 CORE_VSync(s32);
extern s32 D_80054B84;
extern s32 D_80054B88;
void func_80042864(void)
{
    D_80054B84 = CORE_VSync(-1) + 240;
    D_80054B88 = 0;
}
