#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Slot 0x38 points to the raw GPU status reader in the retail dispatch table. */


u32 GetODE(void)
{
    return (u32)g_gpu_ctl->slot38() >> 31;
}
