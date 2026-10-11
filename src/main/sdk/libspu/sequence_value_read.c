/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[4];
    u8 *cursor;
    u8 gap08[0x44];
    s16 value;
    u8 gap4E[0x3A];
    s32 ticks;
    u8 gap8C[0x20];
} State;
extern State *D_80060418[];
s32 func_8004AEB8(s16,s16);
void func_80049BA0(s16 sequence,s16 channel)
{
    State *state=D_80060418[sequence]+channel;
    u8 *cursor=state->cursor;
    state->cursor=cursor+1;
    state->value=*cursor;
    state->ticks=func_8004AEB8(sequence,channel);
}
