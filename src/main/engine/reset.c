#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clear the two engine state words; their precise role is still unidentified. */

extern s32 gp_cur_pbak_frame;

void Pbak_Init(void)
{
    gp_cur_pbak_frame = 0;
    D_80061A30 = 0;
}

void Pbak_Kill(void)
{
}

void Pbak_Noop(void)
{
}
