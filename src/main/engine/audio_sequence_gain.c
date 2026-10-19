/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
#include "audio_channels.h"
/* GNU_AS_G: 8 */
void SsSepSetVol();

void Midi_ResetSeqVol(s16 gain) {
    s16 channel;
    s32 scaled_gain;
    s32 index;

    D_80056648 = gain;
    index = D_8005665C >= 2;
    scaled_gain = gain >> 7;
    if (index < D_8005665C) {
        s32 volume = scaled_gain;
        do {
            channel = D_80056EBC[index].channel;
            SsSepSetVol(gp_midi_vol, channel, volume, volume);
            index += 1;
        } while (index < D_8005665C);
    }
}
