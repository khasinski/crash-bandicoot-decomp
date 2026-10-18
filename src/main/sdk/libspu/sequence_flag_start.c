/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[0x90];
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;
extern SequenceState *D_80060418[];
void func_8004B5E0(s16 sequence,s16 channel) {
    SequenceState *state = &D_80060418[sequence][channel];
    u32 word = state->field_90;
    if (!(word&0x204)) {
        if (!(word&0x100)) {
            state->field_90 = word&~2;
            D_80060418[sequence][channel].field_90 |= 8;
            D_80060418[sequence][channel].field_90 |= 1;
        }
    }
}
