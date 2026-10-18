/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef struct {
    u8 gap00[4];
    u8 *field_4;
    u8 *field_8;
    u8 *field_C;
    u8 field_10;
    u8 gap11[5];
    u8 field_16;
    u8 gap17[0x27 - 0x17];
    u8 field_27;
    u8 field_28;
    u8 field_29;
    u8 field_2A;
    u8 gap2B[0x88 - 0x2B];
    s32 field_88;
    u8 gap8C[0xAC - 0x8C];
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
        state->field_16=value;
        state->field_27=1;
        state->field_88=func_8004AEB8(sequence,channel);
        state->field_C=state->field_4;
        break;
    case 30:
        state->field_16=value;
        if(state->field_28==0) {
            state->field_10=0;
            state->field_88=func_8004AEB8(sequence,channel);
        } else if(state->field_28<127) {
            state->field_28--;
            state->field_88=func_8004AEB8(sequence,channel);
            if(state->field_28!=0) {
                state->field_4=state->field_C;
            } else state->field_10=0;
        } else {
            func_8004AEB8(sequence,channel);
            state->field_88=0;
            state->field_4=state->field_C;
        }
        break;
    default:
        state->field_16=value;
        state->field_2A++;
        state->field_88=func_8004AEB8(sequence,channel);
        break;
    }
}
