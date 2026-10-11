/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
extern u8 *D_80060418[];
void func_8004CFB0(s32 arg0, s16 arg1, s16 arg2, u32 arg3) {
    s32 var_v1;
    s32 temp_v1;
    u8 *temp_a0;

    temp_a0 = (arg1 * 0xAC) + D_80060418[(s16)arg0];
    temp_v1 = *(s32 *)(temp_a0 + 0x90);
    if (temp_v1 & 4) return;
    if (temp_v1 & 0x100) return;
    if (arg2 == 0) return;
    {
        *(s16 *)(temp_a0 + 0x3E) = arg2;
        *(u32 *)(temp_a0 + 0x94) = arg3;
        *(s16 *)(temp_a0 + 0x40) = arg2;
        var_v1 = arg2 < 0 ? -(s32)arg2 : (s32)arg2;
        *(u32 *)(temp_a0 + 0x98) = arg3;
        if (arg3 >= (u32) var_v1) {
            *(s16 *)(temp_a0 + 0x42) = (s16) (arg3 / (u32) var_v1);
            return;
        }
        *(s16 *)(temp_a0 + 0x42) = (s16) -(s16) ((u32) var_v1 / arg3);
    }
}
