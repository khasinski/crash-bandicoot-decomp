/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

s32 func_8004EA24(void) {
    s32 temp_v0;
    s32 semitone_index;
    s32 quotient;
    s32 remainder;
    s32 temp_v1;
    u32 note;
    u16 var_v1;
    u32 var_v1_2;
    s32 var_a0;

    var_a0 = D_8005E569;
    note = (u32)D_8005E55A + 0x3C;
    temp_v1 = note - D_8005E568;
    if ((s32) var_a0 < 0) {
        var_a0 += 7;
    }
    quotient = temp_v1 / 12;
    remainder = temp_v1 % 12;
    var_v1_2 = (u32)var_a0 >> 3;
    if (var_v1_2 >= 0x10U) {
        var_v1_2 = 0xF;
    }
    semitone_index = remainder * 0x10;
    semitone_index += var_v1_2 & 0xFFFF;
    var_v1 = D_80056278[semitone_index];
    temp_v0 = quotient - 5;
    if (temp_v0 > 0) {
        var_v1 <<= temp_v0;
    } else if (temp_v0 < 0) {
        var_v1 = (u16) ((s32) (var_v1 & 0xFFFF) >> -temp_v0);
    }
    return var_v1 & 0xFFFF;
}
