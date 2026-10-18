/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[0x74];
    s16 left;
    s16 right;
    u8 gap78[0xAC - 0x78];
} SequenceState;
extern SequenceState *D_80060418[];
extern s16 D_8005E56E;
s32 func_8004FFC0(s32 selector) {
    s32 channel=(selector&0xFF00)>>8;
    SequenceState *state=&D_80060418[selector&0xFF][channel];
    D_8005E56E=selector;
    return state->left;
}
s32 func_80050010(s32 selector) {
    s32 channel=(selector&0xFF00)>>8;
    SequenceState *state=&D_80060418[selector&0xFF][channel];
    D_8005E56E=selector;
    return state->right;
}
