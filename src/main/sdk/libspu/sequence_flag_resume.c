/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[0x2B];
    u8 field_2B;
    u8 gap2C[0x90 - 0x2C];
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;
extern SequenceState *D_80060418[];
void func_8004C764(s16 sequence,s16 channel) {
    SequenceState *state = &D_80060418[sequence][channel];
    state->field_2B = 1;
    D_80060418[sequence][channel].field_90 &= ~8;
}
