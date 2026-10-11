/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s32 func_80050728(s16, s16);                          /* extern */
extern u8 *D_8005CFE4;
extern u8 D_8005E55F;
extern u8 D_8005E578[];

typedef struct {
    u8 field_0;u8 field_1;u8 field_2;u8 field_3;u8 field_4;u8 field_5;u8 field_6;u8 field_7;u8 field_8;u8 field_9;u8 field_A;u8 field_B;u8 field_C;u8 field_D;
    u8 gapE[2];
    u16 field_10,field_12,field_14,field_16;
    u8 tail[8];
} ToneAttributes;

s32 func_8004D184(s16 bank, s16 program, s32 tone, ToneAttributes *result) {
    s32 temp_v1;
    ToneAttributes *temp_v1_2;

    if (D_8005E578[bank] == 1) {
        func_80050728(bank, program);
        temp_v1 = (s32) (((u32)tone + (D_8005E55F * 0x10)) << 0x10) >> 0xB;
        result->field_0 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_0;
        result->field_1 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_1;
        result->field_2 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_2;
        result->field_3 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_3;
        result->field_4 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_4;
        result->field_5 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_5;
        result->field_7 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_7;
        result->field_6 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_6;
        result->field_8 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_8;
        result->field_9 = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_9;
        result->field_A = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_A;
        result->field_B = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_B;
        result->field_C = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_C;
        result->field_D = (u8) ((ToneAttributes *)(temp_v1 + (u32)D_8005CFE4))->field_D;
        temp_v1_2 = (ToneAttributes *)(temp_v1 + (u32)D_8005CFE4);
        result->field_10 = (u16) temp_v1_2->field_10;
        result->field_12 = (u16) temp_v1_2->field_12;
        result->field_14 = (u16) temp_v1_2->field_14;
        result->field_16 = (u16) temp_v1_2->field_16;
        return 0;
    }
    return -1;
}
