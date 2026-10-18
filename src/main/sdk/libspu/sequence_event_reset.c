/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0x4E];
    s16 gains[16];
    u8 gap6E[0x88 - 0x6E];
    s32 ticks;
    u8 gap8C[0xAC - 0x8C];
} State;
extern State *D_80060418[];
s32 func_8004AEB8(s16,s16);
s32 func_8004D478(void);
void func_8004D65C(void);
void func_8004A67C(s16 sequence,s16 channel) {
    State *state=D_80060418[sequence]+channel;
    func_8004D478();
    func_8004D65C();
    state->bytes[0x2C+state->bytes[0x12]]=state->bytes[0x12];
    state->bytes[0x13]=0;
    state->bytes[0x14]=0;
    state->gains[state->bytes[0x12]]=127;
    state->bytes[0x17+state->bytes[0x12]]=64;
    state->ticks=func_8004AEB8(sequence,channel);
}
