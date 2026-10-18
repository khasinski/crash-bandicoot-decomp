/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[4];
    u8 *cursor;
    u8 gap08[0x4C - 0x08];
    s16 vab_id;
    u8 gap4E[0x88 - 0x4E];
    s32 ticks;
    u8 gap8C[0xAC - 0x8C];
} State;
extern State *D_80060418[];
s32 func_8004AEB8(s16,s16);
s32 func_8004F8AC();
void func_8004A740(s16 sequence,s16 channel) {
    State *state=D_80060418[sequence]+channel;
    u8 *bytes=(u8 *)state;
    u8 *cursor=state->cursor;
    u8 value;
    state->cursor=cursor+1;
    value=*cursor;
    func_8004F8AC((channel<<8)|sequence,state->vab_id,bytes[0x2C+bytes[0x12]],value);
    state->ticks=func_8004AEB8(sequence,channel);
}
