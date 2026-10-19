/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"
void SsSepSetVol();

void Midi_SeqInit(AudioChannel *record, s32 packed_volume, s32 channel) {
    if (D_8005665C >= 2 && channel == 1) {
        record->right_volume = (u16) D_8005666C;
        record->left_volume = (u16) D_8005666C;
    } else {
        record->left_volume = packed_volume >> 16;
        record->right_volume = packed_volume;
    }
    record->channel = channel;
    record->state = -1;
    SsSepSetVol(gp_midi_vol, (s16) channel, (s16) record->left_volume, (s16) record->right_volume);
}
