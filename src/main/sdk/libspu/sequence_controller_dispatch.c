/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef void (*ControllerCallback)(s16,s16,u8);
typedef void (*SeqResetCallback)(s16,s16);
typedef void (*EventCallback)();
extern ControllerCallback g_ss_cc_data_entry;
extern ControllerCallback g_ss_cc_main_vol;
extern ControllerCallback g_ss_cc_panpot;
extern ControllerCallback g_ss_cc_damper;
extern ControllerCallback g_ss_cc_nrpn_lsb;
extern ControllerCallback g_ss_cc_nrpn_msb;
extern ControllerCallback g_ss_cc_rpn_lsb;
extern ControllerCallback g_ss_cc_rpn_msb;
extern ControllerCallback g_ss_cc_reverb;
extern SeqResetCallback g_ss_cc_reset_all;
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
    case 6: g_ss_cc_data_entry(sequence_index,channel_index,value);goto done;
    case 7: g_ss_cc_main_vol(sequence_index,channel_index,value);goto done;
    case 10: g_ss_cc_panpot(sequence_index,channel_index,value);goto done;
    /* Controller 11 uses slot 9: 0x80058360 + 9 * 4 = 0x80058384. */
    case 11: ((ControllerCallback)g_Snd_FnTable[9])(sequence_index,channel_index,value);goto done;
    case 64: g_ss_cc_damper(sequence_index,channel_index,value);goto done;
    case 91: g_ss_cc_reverb(sequence_index,channel_index,value);goto done;
    case 98: g_ss_cc_nrpn_lsb(sequence_index,channel_index,value);goto done;
    case 99: g_ss_cc_nrpn_msb(sequence_index,channel_index,value);goto done;
    case 100: g_ss_cc_rpn_lsb(sequence_index,channel_index,value);goto done;
    case 101: g_ss_cc_rpn_msb(sequence_index,channel_index,value);goto done;
    case 121: goto reset;
    default: goto read_delta;
    }
reset:
    g_ss_cc_reset_all(sequence_index,channel_index);
    goto done;
read_delta:
    state->field_88=_SsReadDeltaValue(sequence,channel);
done:
    return;
}
