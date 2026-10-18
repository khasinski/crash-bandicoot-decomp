/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
typedef struct {
    u8 gap00[4];
    u8 *field_4;
    u8 *field_8;
    u8 gap0C[0x2B - 0x0C];
    u8 field_2B;
    u8 gap2C[0x46 - 0x2C];
    s16 field_46;
    s16 field_48;
    u8 gap4A[0x90 - 0x4A];
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;
extern SequenceState *D_80060418[];
void func_8004AF70(s16 sequence, s16 channel) {
    SequenceState *state;
    state = &D_80060418[sequence][channel];
    state->field_46 = 1;
    state->field_48 = 0;
    D_80060418[sequence][channel].field_90 &= ~0x100;
    D_80060418[sequence][channel].field_90 &= ~8;
    D_80060418[sequence][channel].field_90 &= ~2;
    D_80060418[sequence][channel].field_90 &= ~4;
    D_80060418[sequence][channel].field_90 &= ~0x200;
    state->field_2B = 1;
    state->field_4 = state->field_8;
    D_80060418[sequence][channel].field_90 |= 1;
}
