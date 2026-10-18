/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

s32 func_80050728(s16,s16);
typedef struct { s16 value; u8 pad[50]; } VoiceWord;
extern VoiceWord D_800572B4[],D_800572BA[],D_800572BE[],D_800572C0[],D_800572C2[];
extern u8 D_800577A4[],D_8005E588[];
extern s16 D_800583F8,D_8005E56E;
extern u8 *D_8005CFCC,*D_8005CFDC,*D_8005CFE4;
extern u8 D_8005E340;
typedef struct { u8 before[18]; u8 channel; u8 pad[59]; s16 gains[16]; u8 gap[6]; u16 left, right; u8 tail[52]; } State;
extern State *D_80060418[];

s32 func_800501A8(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4) {
    s16 temp_a0_2;
    s32 var_s6;
    u8 var_t2;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 var_a1;
    u32 var_t1;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u32 temp_v1_5;
    s32 master_volume;
    State *temp_s2;

    var_s6 = 0;
    temp_s2 = D_80060418[arg0 & 255] + (((u32)(arg0 << 0x10)) >> 24);
    func_80050728(arg1, arg2);
    D_8005E56E = arg0;
    if (arg4 == 0) {
        arg4 = 1;
    }
    if (!(arg3 & 0xFFFF)) {
        arg3 = 1;
    }
    for (var_t2 = 0; var_t2 < D_8005E340; var_t2++) {
        if ((D_800572BA[var_t2].value == arg0) && (D_800572BE[var_t2].value == arg2) && (D_800572C2[var_t2].value == arg1)) {
            if ((temp_s2->gains[temp_s2->channel] != (arg3 & 0xFFFF)) && (temp_s2->gains[temp_s2->channel] == 0)) {
                temp_s2->gains[temp_s2->channel] = 1;
            }
            temp_lo = (D_800572B4[var_t2].value * (arg3 & 0xFFFF)) / 127;
            master_volume = D_8005CFDC[0x18];
            temp_lo_2 = ((s32)temp_lo * ((master_volume << 14) - master_volume)) / 16129;
            temp_lo = temp_lo_2 * D_8005CFCC[arg2 * 16 + 1];
            temp_a0_2 = D_800572C0[var_t2].value;
            temp_lo = ((u32)temp_lo * D_8005CFE4[((arg2 * 16 + temp_a0_2) << 5) + 2]) / 16129U;
            temp_lo_2 = (u32) (temp_lo * temp_s2->left) / 127U;
            var_t1 = (u32) (temp_lo * temp_s2->right) / 127U;
            temp_v1_3 = D_8005CFE4[(temp_a0_2 << 5) + 3];
            if (temp_v1_3 < 0x40U) {
                var_t1 = (u32) (var_t1 * temp_v1_3) / 63U;
                var_a1 = temp_lo_2;
            } else {
                var_a1 = (u32) (temp_lo_2 * (0x7F - temp_v1_3)) / 63U;
            }
            temp_v1_4 = D_8005CFCC[D_800572BE[var_t2].value * 16 + 4];
            if (temp_v1_4 < 0x40U) {
                var_t1 = (u32) (var_t1 * temp_v1_4) / 63U;
            } else {
                var_a1 = (u32) (var_a1 * (0x7F - temp_v1_4)) / 63U;
            }
            /* Retail keeps a dead var_t2 * 12 index in $v0 and holds temp_lo_2 in $t0 across the pan blocks. */
            {
                register s32 idx12 asm("$2") = var_t2 * 12;
                register u32 hold_t0 asm("$8") = temp_lo_2;
                asm volatile("" : : "r"(idx12), "r"(hold_t0), "r"(arg4));
                temp_v1_5 = arg4 & 0xFF;
            }
            if (temp_v1_5 < 0x40U) {
                var_t1 = (u32) (var_t1 * temp_v1_5) / 63U;
            } else {
                var_a1 = (u32) (var_a1 * (0x7F - temp_v1_5)) / 63U;
            }
            if (D_800583F8 == 1) {
                if (var_a1 < var_t1) {
                    var_a1 = var_t1;
                } else {
                    var_t1 = var_a1;
                }
            }
            var_a1 = (var_a1 * var_a1) / 16383U;
            var_t1 = (var_t1 * var_t1) / 16383U;
            *(s16 *)(D_8005E588 + var_t2 * 16) = var_a1;
            *(s16 *)(D_8005E588 + 2 + var_t2 * 16) = var_t1;
            var_s6 += 1;
            D_800577A4[var_t2] = D_800577A4[var_t2] | 3;
        }
    }
    return var_s6;
}
