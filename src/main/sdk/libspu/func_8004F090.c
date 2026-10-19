/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
typedef struct {
    u8 gap00[0x194];
    u16 voice_off_lo;
    u16 voice_off_hi;
} SpuPorts;
extern SpuPorts *g_snd_tempo;
extern u8 D_800572B0[];
extern u8 D_800572C7[];
void vmNoiseOff(s32 arg0) {
    s32 offset;
    SpuPorts *ports;
    offset = (arg0 & 0xFF) * 0x34;
    D_800572C7[offset] = 0;
    ports = g_snd_tempo;
    *(u16 *)(D_800572B0 + offset) = 0;
    ports->voice_off_lo = 0;
    ports->voice_off_hi = 0;
}
