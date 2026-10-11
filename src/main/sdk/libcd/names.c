/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
#include "common.h"
extern const char *D_800555C4[];
extern const char *D_80055644[];
extern const char D_800113B4[];
const char *func_80043428(s32 command)
{
    u32 index=command & 0xFF;
    const char *name;
    if(index<28)name=D_800555C4[index];else name=D_800113B4;
    return name;
}
const char *func_80043460(s32 status)
{
    u32 index=status & 0xFF;
    const char *name;
    if(index<7)name=D_80055644[index];else name=D_800113B4;
    return name;
}
