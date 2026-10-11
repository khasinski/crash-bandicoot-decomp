/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0xAC];
} State;
extern State *D_80060418[];
s32 func_8004AEB8(s16,s16);
void func_8004A44C(sequence,channel,value)
s16 sequence,channel;
u8 value;
{
    State *state=D_80060418[sequence]+channel;
    switch(value) {
    case 20:
        state->bytes[0x16]=value;
        state->bytes[0x27]=1;
        *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
        *(u8 **)(state->bytes+0x0C)=*(u8 **)(state->bytes+4);
        break;
    case 30:
        state->bytes[0x16]=value;
        if(state->bytes[0x28]==0) {
            state->bytes[0x10]=0;
            *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
        } else if(state->bytes[0x28]<127) {
            state->bytes[0x28]--;
            *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
            if(state->bytes[0x28]!=0) {
                *(u8 **)(state->bytes+4)=*(u8 **)(state->bytes+0x0C);
            } else state->bytes[0x10]=0;
        } else {
            func_8004AEB8(sequence,channel);
            *(s32 *)(state->bytes+0x88)=0;
            *(u8 **)(state->bytes+4)=*(u8 **)(state->bytes+0x0C);
        }
        break;
    default:
        state->bytes[0x16]=value;
        state->bytes[0x2A]++;
        *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
        break;
    }
}
