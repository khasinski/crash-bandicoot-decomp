/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0x4C];
    s16 vab_id;
    s16 gains[16];
    u8 gap6E[0x88 - 0x6E];
    s32 ticks;
    u8 gap8C[0xAC - 0x8C];
} State;
extern State *D_80060418[];
/* This SDK call passes promoted words, including the packed selector. */
s32 func_800501A8();
s32 func_8004AEB8(s16,s16);
void func_8004A128(s16 sequence,s16 channel,u8 value) {
    State *state=D_80060418[sequence]+channel;
    s32 index=state->bytes[0x12];
    u8 *slot=state->bytes+index;
    func_800501A8((channel<<8)|sequence,state->vab_id,slot[0x2C],state->gains[index],value);
    slot[0x17]=value;
    state->ticks=func_8004AEB8(sequence,channel);
}
