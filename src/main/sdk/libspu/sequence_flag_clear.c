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
/* The packed selector is passed as a word by this SDK caller. */
void func_80050060();
void func_8004C300(s16 sequence,s16 channel)
{
    SequenceState *state = &D_80060418[sequence][channel];
    func_80050060((channel<<8)|sequence);
    state->field_2B = 0;
    D_80060418[sequence][channel].field_90 &= ~2;
}
