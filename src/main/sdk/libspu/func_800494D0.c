/* GCC_VERSION: 2.5.7 */
#include "common.h"

void _SsSndSetCres(s16,s16,s16,u32);

void SsSeqSetCrescendo(s16 a,s16 b,s32 c) {_SsSndSetCres(a,0,b,c);}
