/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

extern u8 D_800572B0[];
extern u8 D_800572C7[];

extern u8 *D_8005CFDC;



/* Retail caller passes a byte in a0 and the pitch in a1; a0 is unused here. */
void SpuVmKeyOnNow(u8 arg0, u16 arg1) {
    s32 master_volume;
    s16 shadow_index;
    u16 *left_destination, *right_destination;
    union { s32 signed_value; u32 unsigned_value; } gain;
    s32 var_a2_2;
    s32 var_a3_2;
    u16 temp_a1;
    u16 temp_v1_2;
    u32 var_a1;
    u32 var_a2;
    u32 var_a3;
    union { s32 signed_value; u32 unsigned_value; u8 *pointer; } squared;
    SequenceState *temp_a0;

    master_volume = D_8005CFDC[0x18];
    var_a3 = (s32)(D_8005E55C * ((master_volume << 14) - master_volume)) / 16129;
    gain.signed_value = (s32)var_a3 * D_8005E562;
    var_a2 = (u32)(gain.unsigned_value * D_8005E565) / 16129U;
    shadow_index = D_8005E572[0] * 8;
    temp_a0 = g_ss_score_table[D_8005E56E & 255] + ((u32)(D_8005E56E << 16) >> 24);
    var_a3 = var_a2;
    if ((s16) D_8005E56E != 0x21) {
        var_a3 = (u32) (var_a2 * temp_a0->field_74) / 127U;
        var_a2 = (u32) (var_a2 * temp_a0->field_76) / 127U;
    }
    if ((u8) D_8005E566 < 0x40U) {
        var_a2 = (u32) (var_a2 * D_8005E566) / 63U;
        var_a1 = var_a3;
    } else {
        var_a1 = (u32) (var_a3 * (0x7F - D_8005E566)) / 63U;
    }
    if ((u8) D_8005E563 < 0x40U) {
        var_a2 = (u32) (var_a2 * D_8005E563) / 63U;
    } else {
        var_a1 = (u32) (var_a1 * (0x7F - D_8005E563)) / 63U;
    }
    if ((u8) D_8005E55D < 0x40U) {
        var_a2 = (u32) (var_a2 * D_8005E55D) / 63U;
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
    squared.unsigned_value = (u32)(var_a1 * var_a1);
    var_a1 = (u32)squared.signed_value / 16383U;
    squared.unsigned_value = (u32)(var_a2 * var_a2);
    var_a2 = (u32)squared.signed_value / 16383U;
    squared.pointer = D_8005E58C;
    ((s16 *)D_8005E58C)[(u16)shadow_index] = arg1;
    left_destination = (u16 *)(squared.pointer - 4);
    left_destination += (u16)shadow_index;
    squared.pointer -= 2;
    right_destination = (u16 *)squared.pointer + (u16)shadow_index;
    *left_destination = var_a1;
    *right_destination = var_a2;
    g_card_ev_table[D_8005E572[0]] = g_card_ev_table[D_8005E572[0]] | 7;
    *(s16 *)(D_800572B0 + D_8005E572[0] * 0x34) = arg1;
    D_800572C7[D_8005E572[0] * 0x34] = 1;
    if (D_8005E572[0] < 0x10) {
        var_a3_2 = 1 << D_8005E572[0];
        var_a2_2 = 0;
    } else {
        var_a3_2 = 0;
        var_a2_2 = 1 << (D_8005E572[0] - 0x10);
    }
    if (D_8005E56C & 4) {
        D_8005725C = var_a3_2 | D_8005725C;
        D_80057264 = var_a2_2 | D_80057264;
    } else {
        D_8005725C &= ~var_a3_2;
        D_80057264 &= ~var_a2_2;
    }
    temp_v1_2 = var_a3_2 | D_8005724C;
    D_8005724C = temp_v1_2;
    temp_a1 = var_a2_2 | D_80057254;
    D_80057254 = temp_a1;
    D_80061A68 &= ~temp_v1_2;
    D_80061A70 &= ~temp_a1;
}
