/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "sdk/libspu/voice_attributes.h"

s32 _SpuSetVoiceAttr(VoiceAttributes *,s32,s32,s32);

void SpuSetVoiceAttr(VoiceAttributes *a) {_SpuSetVoiceAttr(a,0,0x17,0);}
