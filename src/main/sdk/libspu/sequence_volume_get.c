/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
typedef struct {
    u8 gap00[0x74];
    u16 left;
    u16 right;
    u8 gap78[0xAC - 0x78];
} SequenceState;
extern s16 D_8005E56E;
extern SequenceState *D_80060418[];

s16 func_8004FF54(s16 arg0, u16 *arg1, u16 *arg2) {
    union { s32 channel; u16 *packed_id; } phase;
    SequenceState *temp_v0;

    phase.channel = (arg0 & 0xFF00) >> 8;
    temp_v0 = &D_80060418[arg0 & 255][phase.channel];
    phase.packed_id = (u16 *)&D_8005E56E;
    *phase.packed_id = arg0;
    *arg1 = temp_v0->left;
    *arg2 = temp_v0->right;
    return (s16)*phase.packed_id;
}
