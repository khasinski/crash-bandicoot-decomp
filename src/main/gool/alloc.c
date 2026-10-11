#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Free the two allocation tables and update the fixed-point value from the current resource. */

extern void LIBC_Free(void *);
extern void *D_80060DB4;
extern void *D_80060DB0;
extern s32 *D_8005C53C;
extern s32 D_8006188C;

void GOOL_FreeAllocTable(void)
{
    LIBC_Free(D_80060DB4);
    LIBC_Free(D_80060DB0);
}

s32 func_8001AC60(void)
{
    s32 *entry = D_8005C53C;
    D_8006188C = entry[1] << 8;
    if (!entry[0])
        return -0xE;
    return -0xFF;
}
