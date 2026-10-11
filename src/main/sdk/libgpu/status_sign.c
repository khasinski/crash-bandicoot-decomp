#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Slot 0x38 points to the raw GPU status reader in the retail dispatch table. */
typedef struct {
    u8 pad00[0x38];
    s32 (*slot38)(void);
} GpuDispatch;

extern GpuDispatch *D_80054A64;

u32 func_80040EF4(void)
{
    return (u32)D_80054A64->slot38() >> 31;
}
