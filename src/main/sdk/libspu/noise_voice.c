/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

extern volatile u16 *D_80056270;
extern u16 D_8005724C;
extern u16 D_80057254;
extern u16 D_8005725C;
extern u16 D_80057264;
typedef struct { s16 pitch; u8 pad[50]; } VoicePitch;
extern VoicePitch D_800572B0[];
typedef struct { u8 flags; u8 pad[51]; } VoiceFlags;
extern VoiceFlags D_800572C7[];
extern u8 D_800577A4[];
extern s16 D_800583F8;
extern u8 D_8005E340;
extern u8 D_8005E55A;
extern u8 D_8005E55D;
extern u8 D_8005E562;
extern u8 D_8005E563;
extern u8 D_8005E565;
extern u8 D_8005E566;
extern u8 D_8005E568;
extern u8 D_8005E56C;
extern u16 D_8005E56E;
extern u8 D_8005E588[];
typedef struct { u8 bytes[172]; } State;
extern State *D_80060418[];
extern u16 D_80061A68;
extern u16 D_80061A70;

void func_8004EBDC(s32 arg0) {
    s32 dummy;
    s32 *unused_ptr = &dummy;
    s16 var_a1_2;
    s16 var_a2_2;
    s16 var_a3;
    s32 temp_v1_2;
    u16 temp_a0_2;
    u16 temp_v0_2;
    u32 temp_a0;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 var_a1;
    u32 var_a2;
    s32 left_scale, right_scale;
    u16 control;
    u32 packed_id;
    State *temp_v1;

    packed_id = D_8005E56E;
    temp_v1 = D_80060418[packed_id & 255] + (packed_id >> 8);
    left_scale = *(u16 *)(temp_v1->bytes + 0x74);
    temp_lo = (u32)(((left_scale << 7) + left_scale) * D_8005E562) / 127U;
    right_scale = *(u16 *)(temp_v1->bytes + 0x76);
    temp_lo_2 = (u32)(((right_scale << 7) + right_scale) * D_8005E562) / 127U;
    temp_lo = (temp_lo * D_8005E565) / 127U;
    temp_lo_2 = (temp_lo_2 * D_8005E565) / 127U;
    control = D_80056270[0x1AA / 2];
    if ((u8) D_8005E566 < 0x40U) {
        var_a2 = (u32) (temp_lo_2 * D_8005E566) / 63U;
        var_a1 = temp_lo;
    } else {
        var_a2 = temp_lo_2;
        var_a1 = (u32) (temp_lo * (0x7F - D_8005E566)) / 63U;
    }
    if ((u8) D_8005E563 < 0x40U) {
        var_a2 = (u32) (var_a2 * D_8005E563) / 63U;
    } else {
        var_a1 = (u32) (var_a1 * (0x7F - D_8005E563)) / 63U;
    }
    if ((u8) D_8005E55D < 0x40U) {
        var_a2 = (u32) (D_8005E55D * var_a2) / 63U;
    } else {
        var_a1 = (u32) (var_a1 * (0x7F - D_8005E55D)) / 63U;
    }
    if (D_800583F8 == 1) {
        if (var_a1 < var_a2) {
            var_a1 = var_a2;
        } else {
            var_a2 = var_a1;
        }
    }
    control &= 0xC0FF;
    control |= ((D_8005E55A - D_8005E568) & 0x3F) << 8;
    D_80056270[0x1AA / 2] = control;
    temp_a0 = arg0 & 0xFF;
    temp_v1_2 = temp_a0 * 0x10;
    *(s16 *)(D_8005E588 + 2 + temp_v1_2) = (s16) var_a2;
    *(s16 *)(D_8005E588 + temp_v1_2) = (s16) var_a1;
    D_800577A4[temp_a0] = D_800577A4[temp_a0] | 3;
    if (temp_a0 < 0x10U) {
        var_a3 = 1 << temp_a0;
        var_a2_2 = 0;
    } else {
        var_a3 = 0;
        var_a2_2 = 1 << (temp_a0 - 0x10);
    }
    D_800572B0[arg0 & 0xFF].pitch = 0xA;
    var_a1_2 = 0;
    if (D_8005E340 != 0) {
        do {
            D_800572C7[var_a1_2].flags &= 1;
            var_a1_2++;
        } while (var_a1_2 < D_8005E340);
    }
    D_800572C7[arg0 & 0xFF].flags = 2;
    temp_v0_2 = var_a3 | D_8005724C;
    D_8005724C = temp_v0_2;
    temp_a0_2 = var_a2_2 | D_80057254;
    D_80057254 = temp_a0_2;
    D_80061A68 &= ~temp_v0_2;
    D_80061A70 &= ~temp_a0_2;
    if (D_8005E56C & 4) {
        D_8005725C |= var_a3;
        D_80057264 |= var_a2_2;
    } else {
        D_8005725C &= ~var_a3;
        D_80057264 &= ~var_a2_2;
    }
    D_80056270[0x194 / 2] = var_a3;
    D_80056270[0x196 / 2] = var_a2_2;
}
