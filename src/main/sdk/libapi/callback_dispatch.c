#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Dispatch through slots at the offsets observed in the retail table.
 * Results describe the word left in v0; argument meanings remain unidentified.
 */
typedef s32 (*Callback)(void);
typedef void (*IrqHandler)(void);
typedef IrqHandler (*RegisterInterrupt)(s32, IrqHandler);
typedef s32 (*Exchange)(s32, s32);
typedef u16 *(*StateCallback)(void);

typedef struct {
    u32 word00;
    Exchange slot04;
    RegisterInterrupt slot08;
    Callback slot0C;
    StateCallback slot10;
    Exchange slot14;
    StateCallback slot18;
} Dispatch;

extern Dispatch *D_800549BC;

s32 ResetCallback(void)
{
    return D_800549BC->slot0C();
}

IrqHandler InterruptCallback(s32 index, IrqHandler callback)
{
    return D_800549BC->slot08(index, callback);
}

s32 DMACallback(s32 arg0, s32 arg1)
{
    return D_800549BC->slot04(arg0, arg1);
}

s32 VSyncCallback(s32 arg0)
{
    return D_800549BC->slot14(0, arg0);
}

s32 VSyncCallbacks(s32 arg0, s32 arg1)
{
    return D_800549BC->slot14(arg0, arg1);
}

u16 *StopCallback(void)
{
    return D_800549BC->slot10();
}

u16 *RestartCallback(void)
{
    return D_800549BC->slot18();
}
