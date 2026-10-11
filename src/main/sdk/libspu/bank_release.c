/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

void func_800508E8(u32);
extern u8 D_8005E578[];
extern u32 D_80060CF0[];
extern u16 D_80060CE8;

void func_80050868(s32 requested)
{
    s16 index;
    if ((u16)requested < 16) {
        index = requested;
        if (D_8005E578[index] == 1) {
            func_800508E8(D_80060CF0[index]);
            D_8005E578[index] = 0;
            D_80060CE8--;
        }
    }
}
