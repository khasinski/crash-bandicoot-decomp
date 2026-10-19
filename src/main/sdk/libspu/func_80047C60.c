/* GCC_VERSION: 2.6.3 */
#include "common.h"

void _SpuSetAnyVoice(s32,s32,s32,s32);

void SpuSetReverbVoice(s32 a,s32 b) {_SpuSetAnyVoice(a,b,0xcc,0xcd);}
