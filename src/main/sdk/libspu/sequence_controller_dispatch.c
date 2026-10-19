/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef void (*ControllerCallback)(s16,s16,u8);
typedef void (*ResetCallback)(s16,s16);
typedef void (*EventCallback)();
extern ControllerCallback D_80058378;
extern ControllerCallback D_8005837C;
extern ControllerCallback D_80058380;
extern ControllerCallback D_80058384;
extern ControllerCallback D_80058388;
extern ControllerCallback D_8005838C;
extern ControllerCallback D_80058390;
extern ControllerCallback D_80058394;
extern ControllerCallback D_80058398;
extern ResetCallback D_8005839C;
s32 _SsReadDeltaValue(s16,s16);
void _SsGetSeqData(sequence,channel,controller)
s16 sequence,channel;
u8 controller;
{
    s32 channel_index=(s16)channel;
    s32 sequence_index=(s16)sequence;
    SequenceState *state=g_ss_score_table[sequence_index]+channel_index;
    u8 *cursor=state->field_4;
    u8 value;
    state->field_4=cursor+1;
    value=*cursor;
    switch(controller) {
    case 0: state->field_4C=value;state->field_88=_SsReadDeltaValue(sequence_index,channel_index);return;
    case 6: D_80058378(sequence_index,channel_index,value);goto done;
    case 7: D_8005837C(sequence_index,channel_index,value);goto done;
    case 10: D_80058380(sequence_index,channel_index,value);goto done;
    /* Controller 11 uses slot 9: 0x80058360 + 9 * 4 = 0x80058384. */
    case 11: ((ControllerCallback)g_Snd_FnTable[9])(sequence_index,channel_index,value);goto done;
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
    state->field_88=_SsReadDeltaValue(sequence,channel);
done:
    return;
}
