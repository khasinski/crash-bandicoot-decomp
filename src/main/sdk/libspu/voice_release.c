/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

typedef struct { s16 value; u8 pad[50]; } VoiceWord;
typedef struct { u8 value; u8 pad[51]; } VoiceByte;

extern VoiceWord D_800572AC[];
extern VoiceWord D_800572B0[];
extern VoiceByte D_800572C7[];

void SpuVmKeyOffNow(void) {
    u16 voice;
    s32 var_a3;
    s32 var_a2;
    u16 temp_a0;
    u16 temp_a1;

    voice = D_8005E572[0];
    if (voice < 0x10) {
        var_a3 = 1 << voice;
        var_a2 = 0;
    } else {
        var_a3 = 0;
        var_a2 = 1 << (voice - 0x10);
    }
    D_800572C7[voice].value = 0;
    D_800572B0[voice].value = 0;
    D_800572AC[voice].value = 0;
    temp_a0 = var_a3 | D_80061A68;
    D_80061A68 = temp_a0;
    temp_a1 = var_a2 | D_80061A70;
    D_80061A70 = temp_a1;
    D_8005724C &= ~temp_a0;
    D_80057254 &= ~temp_a1;
}
