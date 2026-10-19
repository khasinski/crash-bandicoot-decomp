/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
#include "common.h"

const char *CdComstr(s32 command)
{
    u32 index=command & 0xFF;
    const char *name;
    if(index<28)name=D_800555C4[index];else name=D_800113B4;
    return name;
}
const char *CdIntstr(s32 status)
{
    u32 index=status & 0xFF;
    const char *name;
    if(index<7)name=D_80055644[index];else name=D_800113B4;
    return name;
}
