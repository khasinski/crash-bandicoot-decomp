/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0xAC];
} State;
typedef void (*SequenceCallback)(s16,s16,u8);
extern State *D_80060418[];
extern SequenceCallback D_80060498[][16];
s32 func_8004AEB8(s16,s16);
void func_8004A324(sequence,channel,value)
s16 sequence,channel;
u8 value;
{
    State *state=D_80060418[(s16)sequence]+(s16)channel;
    SequenceCallback callback;
    if (state->bytes[0x27]==1 && state->bytes[0x10]==0) {
        state->bytes[0x28]=value;
        state->bytes[0x10]=1;
    } else {
        if(state->bytes[0x16]==30) goto check_callback;
        if(state->bytes[0x16]==20) goto check_callback;
        state->bytes[0x15]=value;
        state->bytes[0x2A]++;
    }
check_callback:
    if (state->bytes[0x16]==40) {
        callback=D_80060498[(s16)sequence][(s16)channel];
        if(callback) callback(sequence,channel,value);
    }
    *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
}
