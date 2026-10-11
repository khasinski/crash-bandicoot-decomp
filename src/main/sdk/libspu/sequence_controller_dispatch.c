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
typedef void (*ControllerCallback)(s16,s16,u8);
typedef void (*ResetCallback)(s16,s16);
extern State *D_80060418[];
typedef void (*EventCallback)();
extern EventCallback D_80058360[];
extern ControllerCallback D_80058378,D_8005837C,D_80058380,D_80058384,D_80058388,D_8005838C,D_80058390,D_80058394,D_80058398;
extern ResetCallback D_8005839C;
s32 func_8004AEB8(s16,s16);
void func_8004A7E8(sequence,channel,controller)
s16 sequence,channel;
u8 controller;
{
    s32 channel_index=(s16)channel;
    s32 sequence_index=(s16)sequence;
    State *state=D_80060418[sequence_index]+channel_index;
    u8 *cursor=state->cursor;
    u8 value;
    state->cursor=cursor+1;
    value=*cursor;
    switch(controller) {
    case 0: state->value=value;state->ticks=func_8004AEB8(sequence_index,channel_index);return;
    case 6: D_80058378(sequence_index,channel_index,value);goto done;
    case 7: D_8005837C(sequence_index,channel_index,value);goto done;
    case 10: D_80058380(sequence_index,channel_index,value);goto done;
    /* Controller 11 uses slot 9: 0x80058360 + 9 * 4 = 0x80058384. */
    case 11: ((ControllerCallback)D_80058360[9])(sequence_index,channel_index,value);goto done;
    case 64: D_80058384(sequence_index,channel_index,value);goto done;
    case 91: D_80058398(sequence_index,channel_index,value);goto done;
    case 98: D_80058388(sequence_index,channel_index,value);goto done;
    case 99: D_8005838C(sequence_index,channel_index,value);goto done;
    case 100: D_80058390(sequence_index,channel_index,value);goto done;
    case 101: D_80058394(sequence_index,channel_index,value);goto done;
    case 121: goto reset;
    default: goto read_delta;
    }
reset:
    D_8005839C(sequence_index,channel_index);
    goto done;
read_delta:
    state->ticks=func_8004AEB8(sequence,channel);
done:
    return;
}
