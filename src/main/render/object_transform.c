#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Pass the object and its field at 0x80 to the transform routine. */

void func_800294B0(void *, void *, s32);

void func_8002967C(u8 *object, s32 arg)
{
    func_800294B0(object + 0x80, object, arg);
}
