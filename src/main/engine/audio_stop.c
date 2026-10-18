#include "common.h"
#include "audio_channels.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
void func_80049404(s16);                               /* extern */
void func_8004B544(s16, s16);                          /* extern */
void func_8004B5A8(s16, s16, s16, s16);                /* extern */
void func_8004B6AC(s16, s16);                          /* extern */
void func_8004C964(s16, s16);                          /* extern */
void func_8004CD58(s16, s16, s16, s16);                /* extern */
void func_80050868(s16);                               /* extern */

/* Export the real small-common channel identifier. */
asm(".globl D_80056658");
s16 D_80056658;

void func_800319DC(s16 arg0, s32 arg1) {
    if (arg0 != -1) {
        func_80049404(arg0);
    }
    if ((arg1 != 0) && (D_80056658 != -1)) {
        func_80050868(D_80056658);
    }
}

s32 func_80031A40(AudioChannel *record, s32 action, s32 arg) {
    s32 i;

    if (record != NULL) {
        switch (action) {
        case 0:
            record->state = 1;
            func_8004B5A8(D_80056654, record->channel, 1, (s16)arg);
            break;
        case 1:
            record->state = 2;
            func_8004C964(D_80056654, record->channel);
            break;
        case 2:
            record->state = 0;
            func_8004B544(D_80056654, record->channel);
            break;
        case 3:
            record->state = 1;
            func_8004B6AC(D_80056654, record->channel);
            break;
        case 4:
            record->left_volume = arg >> 16;
            record->right_volume = arg;
            for (i = (D_8005665C >= 2); i < D_8005665C; i++) {
                func_8004CD58(D_80056654, record->channel, record->left_volume, record->right_volume);
            }
            break;
        }
    }
}
