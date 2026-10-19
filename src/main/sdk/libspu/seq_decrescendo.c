/* GCC_VERSION: 2.5.7 */
#include "common.h"

void _SsSndSetDecres(s16,s16,s16,u32);

void SsSeqSetDecrescendo(s16 a,s16 b,s32 c) {_SsSndSetDecres(a,0,b,c);}
