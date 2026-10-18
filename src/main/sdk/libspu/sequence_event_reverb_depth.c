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
void func_8004D3BC(s16,s16);
void func_8004A298(s16 sequence,s16 channel,u8 value) {
    State *state=D_80060418[sequence]+channel;
    s16 depth=value;
    func_8004D3BC(depth,depth);
    state->ticks=func_8004AEB8(sequence,channel);
}
