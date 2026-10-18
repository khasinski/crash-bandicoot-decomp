/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
typedef struct {
    u8 gap0[0x3E];
    s16 field_3E;
    s16 field_40;
    s16 field_42;
    u8 gap44[0x90 - 0x44];
    s32 field_90;
    u32 field_94;
    u32 field_98;
    u8 gap9C[0xAC - 0x9C];
} SequenceState;
extern SequenceState *D_80060418[];
void func_8004CFB0(s32 arg0, s16 arg1, s16 arg2, u32 arg3) {
    s32 var_v1;
    s32 temp_v1;
    SequenceState *temp_a0;

    temp_a0 = &D_80060418[(s16)arg0][arg1];
    temp_v1 = temp_a0->field_90;
    if (temp_v1 & 4) return;
    if (temp_v1 & 0x100) return;
    if (arg2 == 0) return;
    {
        temp_a0->field_3E = arg2;
        temp_a0->field_94 = arg3;
        temp_a0->field_40 = arg2;
        var_v1 = arg2 < 0 ? -(s32)arg2 : (s32)arg2;
        temp_a0->field_98 = arg3;
        if (arg3 >= (u32) var_v1) {
            temp_a0->field_42 = (s16) (arg3 / (u32) var_v1);
            return;
        }
        temp_a0->field_42 = (s16) -(s16) ((u32) var_v1 / arg3);
    }
}
