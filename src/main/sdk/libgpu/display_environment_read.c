#include "common.h"

/* GCC_VERSION: 2.6.3 */

extern u8 g_gpu_cur_dispenv[0x14];

/* Copy the complete cached environment into the caller's buffer. */
void *GetDispEnv(void *out)
{
    BIOS_MemCpy(out, g_gpu_cur_dispenv, 0x14);
    return out;
}
