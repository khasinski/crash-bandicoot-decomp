/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s16 func_8004FF54(s16, u16 *, u16 *);
typedef struct {
    u8 gap00[0x78];
    u16 field_78;
    u16 field_7A;
    u8 gap7C[0x90 - 0x7C];
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;
extern SequenceState *D_80060418[];
void func_8004B44C(s16 sequence, s16 channel) {
    SequenceState *state = &D_80060418[sequence][channel];
    func_8004FF54((channel << 8) | sequence, &state->field_78, &state->field_7A);
    D_80060418[sequence][channel].field_90 &= ~1;
    D_80060418[sequence][channel].field_90 &= ~8;
    D_80060418[sequence][channel].field_90 |= 2;
}
