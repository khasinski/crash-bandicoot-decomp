/* GCC_VERSION: 2.5.7 */
#include "common.h"

void Snd_SetPlayMode(s16,s16,u8,s16);

void SsSeqPlay(s16 a,u8 b,s16 c) {Snd_SetPlayMode(a,0,b,c);}
