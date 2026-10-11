/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0xAC];
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
    *(s16 *)(state->bytes+0x4E + 2*state->bytes[0x12])=127;
    state->bytes[0x17+state->bytes[0x12]]=64;
    *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
}
