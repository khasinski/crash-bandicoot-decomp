#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* For entries matching the high-bit group ID, set bit 3 in the indexed state table. */

extern u16 D_8005E348[];
extern u32 D_8005FF58[];

void GOOL_TraverseObjectTreePreorder(u32 group)
{
    u16 *entry = D_8005E348;
    while (*entry) {
        if ((*entry >> 9) == group)
            D_8005FF58[*entry & 0x1FF] |= 8;
        entry++;
    }
}
