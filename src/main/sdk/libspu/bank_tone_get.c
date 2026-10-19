/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s32 SpuVmVSetUp(s16, s16);                          /* extern */

typedef struct {
    u8 field_0;u8 field_1;u8 field_2;u8 field_3;u8 field_4;u8 field_5;u8 field_6;u8 field_7;u8 field_8;u8 field_9;u8 field_A;u8 field_B;u8 field_C;u8 field_D;
    u8 gapE[2];
    u16 field_10,field_12,field_14,field_16;
    u8 tail[8];
} ToneAttributes;

s32 SsUtGetVagAtr(s16 bank, s16 program, s32 tone, ToneAttributes *result) {
    s32 temp_v1;
    ToneAttributes *temp_v1_2;

    if (g_midi_tracks[bank] == 1) {
        SpuVmVSetUp(bank, program);
        temp_v1 = (s32) (((u32)tone + (g_spu_vm_cur_prog_tones * 0x10)) << 0x10) >> 0xB;
        result->field_0 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_0;
        result->field_1 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_1;
        result->field_2 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_2;
        result->field_3 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_3;
        result->field_4 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_4;
        result->field_5 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_5;
        result->field_7 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_7;
        result->field_6 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_6;
        result->field_8 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_8;
        result->field_9 = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_9;
        result->field_A = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_A;
        result->field_B = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_B;
        result->field_C = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_C;
        result->field_D = (u8) ((ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool))->field_D;
        temp_v1_2 = (ToneAttributes *)(temp_v1 + (u32)g_ns_vpage_pool);
        result->field_10 = (u16) temp_v1_2->field_10;
        result->field_12 = (u16) temp_v1_2->field_12;
        result->field_14 = (u16) temp_v1_2->field_14;
        result->field_16 = (u16) temp_v1_2->field_16;
        return 0;
    }
    return -1;
}
