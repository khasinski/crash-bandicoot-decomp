/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[0x2B];
    u8 field_2B;
    u8 gap2C[0x46 - 0x2C];
    s16 field_46;
    s16 field_48;
    u8 gap4A[0x74 - 0x4A];
    u16 field_74;
    u16 field_76;
    u8 gap78[0x90 - 0x78];
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;
extern SequenceState *D_80060418[];
s16 func_8004F998();
void func_8004B6D8(s16 sequence,s16 channel,u8 mode,s16 repeat) {
    SequenceState *state = &D_80060418[sequence][channel];
    state->field_90 &= ~0x200;
    D_80060418[sequence][channel].field_90 &= ~4;
    state->field_46 = repeat;
    if (mode==1) {
        D_80060418[sequence][channel].field_90 |= 1;
        state->field_48 = 0;
        state->field_2B = 1;
        func_8004F998((channel<<8)|sequence, state->field_74, state->field_76, 0);
    } else if (mode==0) {
        D_80060418[sequence][channel].field_90 |= 2;
    }
}
