#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clear the two engine state words; their precise role is still unidentified. */

extern s32 D_80056704;
extern s32 D_80061A30;

void func_8002E8A4(void)
{
    D_80056704 = 0;
    D_80061A30 = 0;
}

void func_8002E8BC(void)
{
}

void func_8002E8C4(void)
{
}
