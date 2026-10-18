/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0x88];
    s32 ticks;
    u8 gap8C[0xAC - 0x8C];
} State;
extern State *D_80060418[];
s32 func_8004AEB8(s16,s16);
void func_8004A594(s16 sequence,s16 channel,u8 value) {
    State *state=D_80060418[sequence]+channel;
    state->bytes[0x13]=value;
    state->bytes[0x29]++;
    state->ticks=func_8004AEB8(sequence,channel);
}
void func_8004A608(s16 sequence,s16 channel,u8 value) {
    State *state=D_80060418[sequence]+channel;
    state->bytes[0x14]=value;
    state->bytes[0x29]++;
    state->ticks=func_8004AEB8(sequence,channel);
}
