/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"
s32 getintr(void);
typedef void (*CdCallback)(s32,void*);
extern volatile u8 *g_cd_reg0[];
extern volatile u8 g_cd_status[];
extern volatile u8 D_8005587D[];
void cd_callback(void) {
    s32 event;
    s32 pending;
    u8 bank;
    volatile u8 *ready_status;

    bank = *g_cd_reg0[0] & 3;
    ready_status=D_8005587D;
loop_1:
    pending = getintr();
    event = pending;
    if (pending != 0) {
        pending = event;
        if (event & 4) {
            if (D_800555A4[0] != NULL) {
                D_800555A4[0](ready_status[0], D_800571A0);
            }
            pending = event;
        }
        if (((pending & 2) != 0) && (g_cd_sync_cb[0] != NULL)) {
            g_cd_sync_cb[0](g_cd_status[0], D_80057198);
        }
        goto loop_1;
    }
    *g_cd_reg0[0] = bank;
}
