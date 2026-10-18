/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"
void func_8004CB6C(s32);
void func_8004CD58();
u8 func_800507EC(s32);
extern s16 D_80056648;

extern s32 D_80056710[];
extern s32 D_80061914[];
extern s32 D_80061918[];

void func_80031244(void) {
    s16 channel;
    s32 scaled_gain;
    s32 index;
    s32 voice_limit;
    u32 gain;

    func_8004CB6C(1);
    index = D_8005665C >= 2;
    gain = ((u32)D_80061918[0] * 0x3FFFU) >> 8;
    D_80056648 = (s16) gain;
    scaled_gain = (s32) (gain << 0x10) >> 0x17;
    if (index < D_8005665C) {
        s32 volume = scaled_gain;
        do {
            channel = D_80056EBC[index].channel;
            func_8004CD58(D_80056654, channel, volume, volume);
            index += 1;
        } while (index < D_8005665C);
    }
    D_80056650 = 0x6396347F;
    D_800566C0 = 0;
    D_80056654 = -1;
    D_80056658 = -1;
    if (D_80061918[0] == 0) {
        voice_limit = 8;
    } else if (D_80061914[0] == 0) {
        voice_limit = 20;
    } else {
        switch (D_80056710[0]) {
        case 0x3:
            voice_limit = 0xB;
            break;
        case 0x5:
        case 0xC:
        case 0x15:
            voice_limit = 0xD;
            break;
        case 0x6:
        case 0x7:
            voice_limit = 0xE;
            break;
        case 0x1F:
        case 0x22:
        case 0x2E:
            voice_limit = 0xF;
            break;
        case 0xE:
        case 0x13:
            voice_limit = 0x11;
            break;
        case 0x8:
        case 0x11:
        case 0x14:
        case 0x16:
        case 0x1E:
        case 0x24:
        case 0x28:
        case 0x2A:
        case 0x33:
            voice_limit = 0x12;
            break;
        case 0xA:
            voice_limit = 0x15;
            break;
        default:
            voice_limit = 0x10;
            break;
        }
    }
    D_80056668 = voice_limit;
    func_800507EC(*(u8 *)&D_80056668);
}
