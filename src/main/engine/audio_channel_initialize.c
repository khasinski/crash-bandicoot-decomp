/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"
void func_8004CD58();
extern s16 D_80056654;
extern s16 D_8005665C;
extern s32 D_8005666C;

void func_80031964(AudioChannel *record, s32 packed_volume, s32 channel) {
    if (D_8005665C >= 2 && channel == 1) {
        record->right_volume = (u16) D_8005666C;
        record->left_volume = (u16) D_8005666C;
    } else {
        record->left_volume = packed_volume >> 16;
        record->right_volume = packed_volume;
    }
    record->channel = channel;
    record->state = -1;
    func_8004CD58(D_80056654, (s16) channel, (s16) record->left_volume, (s16) record->right_volume);
}
