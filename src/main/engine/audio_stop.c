#include "common.h"
#include "audio_channels.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
void SsSepClose(s16);                               /* extern */
void SsSepPause(s16, s16);                          /* extern */
void SsSepPlay(s16, s16, s16, s16);                /* extern */
void SsSepReplay(s16, s16);                          /* extern */
void SsSepStop(s16, s16);                          /* extern */
void SsSepSetVol(s16, s16, s16, s16);                /* extern */
void SsVabClose(s16);                               /* extern */

/* Export the real small-common channel identifier. */
asm(".globl D_80056658");
s16 D_80056658;

void Midi_Close(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        SsSepClose(arg0);
    }
    if ((arg1 != 0) && (D_80056658 != -1)) {
        SsVabClose(D_80056658);
    }
}

s32 Midi_Control(AudioChannel *record, s32 action, s32 arg) {
    s32 i;

    if (record != NULL) {
        switch (action) {
        case 0:
            record->state = 1;
            SsSepPlay(gp_midi_vol, record->channel, 1, (s16)arg);
            break;
        case 1:
            record->state = 2;
            SsSepStop(gp_midi_vol, record->channel);
            break;
        case 2:
            record->state = 0;
            SsSepPause(gp_midi_vol, record->channel);
            break;
        case 3:
            record->state = 1;
            SsSepReplay(gp_midi_vol, record->channel);
            break;
        case 4:
            record->left_volume = arg >> 16;
            record->right_volume = arg;
            for (i = (D_8005665C >= 2); i < D_8005665C; i++) {
                SsSepSetVol(gp_midi_vol, record->channel, record->left_volume, record->right_volume);
            }
            break;
        }
    }
}
