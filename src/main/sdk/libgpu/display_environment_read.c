#include "common.h"

/* GCC_VERSION: 2.6.3 */

extern void *BIOS_MemCpy(void *, void *, s32);
extern u8 D_80054AD8[0x14];

/* Copy the complete cached environment into the caller's buffer. */
void *func_80040EBC(void *out)
{
    BIOS_MemCpy(out, D_80054AD8, 0x14);
    return out;
}
