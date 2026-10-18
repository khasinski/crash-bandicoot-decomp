#include "common.h"

/* GCC_VERSION: 2.6.3 */

void *BIOS_MemCpy(void *, void *, s32);

/* Copy the complete cached environment into the caller's buffer. */
void *func_800409D4(void *out)
{
    BIOS_MemCpy(out, D_80054A7C, 0x5C);
    return out;
}
