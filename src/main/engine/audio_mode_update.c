/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
#include "audio_channels.h"
/* GNU_AS_G: 8 */
void Midi_Control(AudioChannel *, u32, s32);
void SsSepSetVol();

extern AudioChannel D_80056ED0[];
extern s32 g_cur_map_level[];
extern s32 g_levels_unlocked[];

void Midi_TogglePlayback(s32 request) {
    s32 mode;

    if (D_8005665C >= 2) {
        mode = request >> 8;
        if (gp_card_chan == 3) {
            if ((mode <= 0) || (mode < 3) || (mode != gp_card_chan)) {
                Midi_Control(D_80056ED0, 1, 0);
                Midi_Control(D_80056ED0 - 1, 3, 0);
                D_8005666C = 0;
            } else {
                if ((g_levels_unlocked[0] != 0) || (g_cur_map_level[0] != 0)) {
                    D_8005666C = 0x3FFF;
                } else {
                    D_8005666C = 0;
                }
                Midi_Control(D_80056EBC, 2, 0);
                Midi_Control(D_80056EBC + 1, 0, 1);
            }
            SsSepSetVol(gp_midi_vol, D_80056ED0[0].channel, (s16) D_8005666C, (s16) D_8005666C);
        }
    }
}
