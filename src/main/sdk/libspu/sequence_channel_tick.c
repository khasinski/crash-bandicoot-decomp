/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
void func_8004C4D4(s16,s16);
extern u8 *D_80060418[];
void func_8004C3C8(s16 arg0, s16 arg1) {
    s16 temp_v0;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = (arg1 * 0xAC) + D_80060418[arg0];
    temp_v0 = *(s16 *)(temp_s1 + 0x70);
    temp_v1 = *(s32 *)(temp_s1 + 0x88);
    temp_a1 = temp_v1 - temp_v0;
    if (temp_a1 > 0) {
        temp_v1_2 = *(s16 *)(temp_s1 + 0x6E);
        if (temp_v1_2 > 0) {
            *(s16 *)(temp_s1 + 0x6E) = (s16) (temp_v1_2 - 1);
            return;
        }
        if (temp_v1_2 == 0) {
            *(s16 *)(temp_s1 + 0x6E) = temp_v0;
            var_v0 = *(s32 *)(temp_s1 + 0x88) - 1;
            goto block_10;
        }
        *(s32 *)(temp_s1 + 0x88) = temp_a1;
        return;
    }
    if (temp_v0 >= temp_v1) {
        var_s0 = temp_v1;
        do {
loop_8:
            func_8004C4D4(arg0, arg1);
            temp_v0_2 = *(s32 *)(temp_s1 + 0x88);
            if (temp_v0_2 == 0) {
                goto loop_8;
            }
            temp_v1_3 = *(s16 *)(temp_s1 + 0x70);
            var_s0 += temp_v0_2;
        } while (var_s0 < temp_v1_3);
        var_v0 = var_s0 - temp_v1_3;
block_10:
        *(s32 *)(temp_s1 + 0x88) = var_v0;
    }
}
