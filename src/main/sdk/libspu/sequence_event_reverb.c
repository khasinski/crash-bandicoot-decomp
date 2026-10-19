/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsContPortamento(sequence,channel,value)
s16 sequence,channel;
u8 value;
{
    SequenceState *state=g_ss_score_table[(s16)sequence]+(s16)channel;
    if (value<0x40) SpuVmDamperOff(); else SpuVmDamperOn();
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
