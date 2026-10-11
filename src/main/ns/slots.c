#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clear the halfword at offset 0x30 for a slot with stride 0x2C. */

void func_800164F8(u8 *table, s32 index)
{
    s16 *field = (s16 *)(table + index * 0x2C + 0x30);
    if (*field)
        *field = 0;
}
