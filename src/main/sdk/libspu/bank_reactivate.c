/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void func_8004DDA8(s32);
extern u8 D_8005E578[];
s32 func_80050C64(s32 requested)
{
    s16 index;
    if ((u16)requested < 17) {
        index = requested;
        if (D_8005E578[index] == 2) {
            func_8004DDA8(0);
            D_8005E578[index] = 1;
            return index;
        }
    }
    return -1;
}
