/* GCC_VERSION: 2.5.7 */
#include "common.h"

void _SsSndSetPauseMode(s16,s16);

void SsSeqPause(s16 a) {_SsSndSetPauseMode(a,0);}
