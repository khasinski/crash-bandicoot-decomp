/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 bytes[0xAC];
} State;
extern State *D_80060418[];
s32 func_8004AEB8(s16,s16);
void func_8004AE44(s16 sequence,s16 channel,u8 value) {
    State *state=D_80060418[sequence]+channel;
    state->bytes[0x2C+state->bytes[0x12]]=value;
    *(s32 *)(state->bytes+0x88)=func_8004AEB8(sequence,channel);
}
