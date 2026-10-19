/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsSndSetDecres(s16 sequence,s16 channel,s16 value,u32 duration) {
    _SsSndSetVolData(sequence,channel,value,duration);
    g_ss_score_table[sequence][channel].field_90 |= 0x20;
    g_ss_score_table[sequence][channel].field_90 &= ~0x10;
}
