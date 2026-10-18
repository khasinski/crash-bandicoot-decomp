/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
#include "audio_channels.h"
/* GNU_AS_G: 8 */
void func_80031A40(AudioChannel *, u32, s32);
void func_8004CD58();

extern AudioChannel D_80056ED0[];
extern s32 D_80061914[];
extern s32 D_80061918[];

void func_800313C4(s32 request) {
    s32 mode;

    if (D_8005665C >= 2) {
        mode = request >> 8;
        if (D_800566C0 == 3) {
            if ((mode <= 0) || (mode < 3) || (mode != D_800566C0)) {
                func_80031A40(D_80056ED0, 1, 0);
                func_80031A40(D_80056ED0 - 1, 3, 0);
                D_8005666C = 0;
            } else {
                if ((D_80061918[0] != 0) || (D_80061914[0] != 0)) {
                    D_8005666C = 0x3FFF;
                } else {
                    D_8005666C = 0;
                }
                func_80031A40(D_80056EBC, 2, 0);
                func_80031A40(D_80056EBC + 1, 0, 1);
            }
            func_8004CD58(D_80056654, D_80056ED0[0].channel, (s16) D_8005666C, (s16) D_8005666C);
        }
    }
}
