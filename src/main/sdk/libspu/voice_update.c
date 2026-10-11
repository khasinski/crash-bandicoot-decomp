/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

#ifdef NON_MATCHING
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
    s16 temp_v1_2;
    s32 temp_a0_3;
    s32 temp_t6;
    s32 var_s5;
    s32 var_s6;
    s32 var_t2;
    s32 var_v0_2;
    s32 var_v0_3;
    u16 var_s4;
    u32 temp_a3;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 temp_v1_5;
    u32 var_a1;
    u32 var_lo;
    u32 var_t1;
    u8 temp_v1_3;
    u8 temp_v1_4;
    s32 scaled_velocity;
    s32 gain;
    s32 master_volume;
    u8 *program_table;
    State *temp_s2;

    var_s5 = arg3;
    var_s6 = 0;
    temp_a3 = arg0 << 0x10;
    var_s4 = arg4;
    temp_s2 = D_80060418[arg0 & 255] + (temp_a3 >> 24);
    func_80050728(arg1, arg2);
    D_8005E56E = arg0;
    if (var_s4 == 0) {
        var_s4 = 1;
    }
    if (!(var_s5 & 0xFFFF)) {
        var_s5 = 1;
    }
    var_t2 = var_s6;
    if ((u32)(var_t2 & 255) < D_8005E340) {
        s32 divisor127 = 127, divisor16129 = 16129;
        u32 divisor63 = 63;
        s16 *left_shadow = (s16 *)D_8005E588;
        s16 *right_shadow = left_shadow + 1;
        temp_t6 = arg2 * 0x10;
        var_v0_2 = var_t2 & 0xFF;
        do {
            if ((D_800572BA[var_v0_2].value == arg0) && (D_800572BE[var_v0_2].value == arg2) && (D_800572C2[var_v0_2].value == arg1)) {
                temp_v1_2 = temp_s2->gains[temp_s2->channel];
                if (temp_v1_2 != (var_s5 & 0xFFFF)) {
                    var_v0_3 = var_t2 & 0xFF;
                    if (temp_v1_2 == 0) {
                        temp_s2->gains[temp_s2->channel] = 1;
                        goto block_12;
                    }
                } else {
block_12:
                    var_v0_3 = var_t2 & 0xFF;
                }
                temp_a0_2 = D_800572C0[var_v0_3].value;
                program_table = D_8005CFCC;
                master_volume = D_8005CFDC[0x18];
                scaled_velocity = (D_800572B4[var_v0_3].value * (var_s5 & 65535)) / divisor127;
                gain = (scaled_velocity * ((master_volume << 14) - master_volume)) / divisor16129;
                gain = gain * program_table[temp_t6 + 1];
                temp_lo = ((u32)gain * D_8005CFE4[((temp_t6 + temp_a0_2) << 5) + 2]) / (u32)divisor16129;
                temp_lo_2 = (u32) (temp_lo * temp_s2->left) / (u32)divisor127;
                var_t1 = (u32) (temp_lo * temp_s2->right) / (u32)divisor127;
                temp_v1_3 = D_8005CFE4[(temp_a0_2 << 5) + 3];
                if (temp_v1_3 < 0x40U) {
                    var_t1 = (u32) (var_t1 * temp_v1_3) / divisor63;
                    var_a1 = temp_lo_2;
                } else {
                    var_a1 = (u32) (temp_lo_2 * (0x7F - temp_v1_3)) / divisor63;
                }
                temp_v1_4 = program_table[D_800572BE[var_t2 & 255].value * 16 + 4];
                if (temp_v1_4 < 0x40U) {
                    var_t1 = (u32) (var_t1 * temp_v1_4) / divisor63;
                } else {
                    var_a1 = (u32) (var_a1 * (0x7F - temp_v1_4)) / divisor63;
                }
                temp_v1_5 = var_s4 & 0xFF;
                if (temp_v1_5 < 0x40U) {
                    var_t1 = (u32) (var_t1 * temp_v1_5) / divisor63;
                } else {
                    var_a1 = (u32) (var_a1 * (0x7F - temp_v1_5)) / divisor63;
                }
                if (D_800583F8 == 1) {
                    if (var_a1 < var_t1) {
                        var_a1 = var_t1;
                    } else {
                        var_t1 = var_a1;
                    }
                }
                var_lo = var_a1 * var_a1;
                temp_a0_3 = var_t2 & 0xFF;
                left_shadow[temp_a0_3 * 8] = (s16) (var_lo / 16383U);
                right_shadow[temp_a0_3 * 8] = (s16) ((u32) (var_t1 * var_t1) / 16383U);
                var_s6 += 1;
                D_800577A4[temp_a0_3] = D_800577A4[temp_a0_3] | 3;
            }
            var_t2 += 1;
            var_v0_2 = var_t2 & 0xFF;
        } while ((u32) (var_t2 & 0xFF) < (u8) D_8005E340);
    }
    return var_s6;
}

#else

INCLUDE_ASM("asm/USA/main/nonmatchings/sdk/libspu/voice_update", func_800501A8);

#endif
