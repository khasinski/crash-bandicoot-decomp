#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Dispatch through slots at the offsets observed in the retail table.
 * Results describe the word left in v0; argument meanings remain unidentified.
 */
typedef s32 (*Callback)(void);
typedef void (*InterruptCallback)(void);
typedef InterruptCallback (*RegisterInterrupt)(s32, InterruptCallback);
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

s32 func_8003E6F4(void)
{
    return D_800549BC->slot0C();
}

InterruptCallback func_8003E724(s32 index, InterruptCallback callback)
{
    return D_800549BC->slot08(index, callback);
}

s32 func_8003E754(s32 arg0, s32 arg1)
{
    return D_800549BC->slot04(arg0, arg1);
}

s32 func_8003E784(s32 arg0)
{
    return D_800549BC->slot14(0, arg0);
}

s32 func_8003E7B8(s32 arg0, s32 arg1)
{
    return D_800549BC->slot14(arg0, arg1);
}

u16 *func_8003E7E8(void)
{
    return D_800549BC->slot10();
}

u16 *func_8003E818(void)
{
    return D_800549BC->slot18();
}
