/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: r3000 */
#include "common.h"
#include "sdk/libspu/voice_attributes.h"
extern volatile u16 *D_800558E4;

s32 func_80048FB4(s32,s32,s32);
void func_800485E0(VoiceAttributes *arg0) {
    s32 temp_v0_3;
    u32 var_a0;
    s16 var_a1;
    u16 adsr1;
    u16 adsr2;
    s32 word_index;
    u16 left_bias;
    u16 right_bias;
    s32 temp_s2;
    s32 var_s1;
    s32 var_v1;
    u16 *temp_v0_2;
    u16 var_a2;
    u16 var_a3;
    u32 temp_v1_4;
    u32 temp_v1_5;
    volatile u16 *temp_v0;
    volatile u16 *temp_v1;
    volatile u16 *temp_v1_6;

    var_s1 = -1;
    for (var_v1 = 0; var_v1 < 24; var_v1++) {
        if ((1 << var_v1) & arg0->field_0) {
            var_s1 = var_v1;
            break;
        }
    }
    var_a1 = 0;
    if (var_s1 != -1) {
        temp_v1 = D_800558E4 + (var_s1 * 8);
        var_a2 = temp_v1[0];
        var_a3 = temp_v1[1];
        temp_s2 = var_s1 * 8;
        word_index = var_s1 * 2;
        if (var_a2 & 0x8000) {
            switch (var_a2 & 0xF000) {
            case 0x8000: var_a1 = 1; break;
            case 0x9000: var_a1 = 2; break;
            case 0xA000: var_a1 = 3; break;
            case 0xB000: var_a1 = 4; break;
            case 0xC000: var_a1 = 5; break;
            case 0xD000: var_a1 = 6; break;
            case 0xE000: var_a1 = 7; break;
            case 0xF000: var_a1 = 7; break;
            }
            var_a2 &= 0xFFF;
        }
        var_a0 = 0;
        if (var_a3 & 0x8000) {
            switch (var_a3 & 0xF000) {
            case 0x8000: var_a0 = 1; break;
            case 0x9000: var_a0 = 2; break;
            case 0xA000: var_a0 = 3; break;
            case 0xB000: var_a0 = 4; break;
            case 0xC000: var_a0 = 5; break;
            case 0xD000: var_a0 = 6; break;
            case 0xE000: var_a0 = 7; break;
            case 0xF000: var_a0 = 7; break;
            }
            var_a3 &= 0xFFF;
        }
        temp_v1_4 = var_a2 & 0xFFFF;
        if (temp_v1_4 < 0x4000U) {
            arg0->field_8 = var_a2;
        } else {
            left_bias = 0x8000;
            arg0->field_8 = (u16) (temp_v1_4 - (u16)left_bias);
        }
        temp_v1_5 = var_a3 & 0xFFFF;
        if (temp_v1_5 < 0x4000U) {
            arg0->field_A = var_a3;
        } else {
            right_bias = 0x8000;
            arg0->field_A = (u16) (temp_v1_5 - (u16)right_bias);
        }
        arg0->field_E = var_a0;
        arg0->field_C = var_a1;
        temp_v0 = D_800558E4 + word_index;
        arg0->field_10 = temp_v0[256];
        arg0->field_12 = temp_v0[257];
        arg0->field_14 = D_800558E4[temp_s2 + 2];
        temp_v0_2 = D_80055970 + var_s1;
        temp_v0_3 = func_80048FB4((u16) *temp_v0_2 >> 8, *(u8 *)temp_v0_2, arg0->field_14);
        if (temp_v0_3 >= 0) {
            arg0->field_16 = temp_v0_3;
        } else {
            arg0->field_16 = 0;
        }
        arg0->field_18 = (u16) D_80055970[var_s1];
        temp_v1_6 = D_800558E4 + temp_s2;
        arg0->field_1A = temp_v1_6[6];
        arg0->field_1C = (s32) (temp_v1_6[3] << D_80055908);
        arg0->field_20 = (s32) (temp_v1_6[7] << D_80055908);
        adsr1 = temp_v1_6[4];
        adsr2 = temp_v1_6[5];
        arg0->field_24 = (adsr1 & 0x80) ? 5 : 1;
        arg0->field_28 = (adsr2 & 0x300) ? 7 : ((adsr2 & 0x200) ? 5 : ((adsr2 & 0x100) ? 3 : 1));
        arg0->field_2C = (adsr2 & 0x20) ? 7 : 3;
        arg0->field_30 = (s16) (adsr1 >> 8);
        arg0->field_32 = (s16) ((u32) (adsr1 & 0xF0) >> 4);
        arg0->field_34 = (s16) ((adsr2 >> 6) & 0xFCFF);
        arg0->field_36 = (s16) (adsr2 & 0x1F);
        arg0->field_38 = (s16) (adsr1 & 0xF);
        arg0->field_3A = adsr1;
        arg0->field_3C = adsr2;
    }
}
