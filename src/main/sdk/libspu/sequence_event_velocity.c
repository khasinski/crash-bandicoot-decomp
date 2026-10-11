/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0xAC];
} State;
extern State *D_80060418[];
/* This SDK call passes promoted words, including the packed selector. */
s32 func_800501A8();
s32 func_8004AEB8(s16,s16);
void func_8004A060(s16 sequence,s16 channel,u8 velocity) {
    State *state=D_80060418[sequence]+channel;
    s32 index=state->bytes[0x12];
    func_800501A8((channel<<8)|sequence,*(s16 *)(state->bytes+0x4C),state->bytes[0x2C+index],velocity,state->bytes[0x17+index]);
    *(s16 *)(state->bytes+0x4E + index*2)=velocity;
    *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
}
