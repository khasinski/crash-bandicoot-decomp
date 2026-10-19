/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
s32 SpuVmKeyOn();
s32 SpuVmKeyOff();
void _SsNoteOn(s16 sequence,s16 channel,u8 note,u8 velocity) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    s32 index=state->field_12;
    u8 *slot=&state->field_0+index;
    u8 parameter=slot[0x17];
    u16 volume=velocity;
    if (!((state->field_AA>>index)&1)) {
        if (state->field_74!=0) {
            if(velocity!=0) {
                SpuVmKeyOn((channel<<8)|sequence,state->field_4C,slot[0x2C],note,volume,parameter);
                state->field_A8=volume;
            } else {
                SpuVmKeyOff((channel<<8)|sequence,state->field_4C,slot[0x2C],note);
            }
        }
    }
}
