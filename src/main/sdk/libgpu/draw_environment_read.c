#include "common.h"

/* GCC_VERSION: 2.6.3 */

void *BIOS_MemCpy(void *, void *, s32);

/* Copy the complete cached environment into the caller's buffer. */
void *GetDrawEnv(void *out)
{
    BIOS_MemCpy(out, g_gpu_cur_drawenv, 0x5C);
    return out;
}
