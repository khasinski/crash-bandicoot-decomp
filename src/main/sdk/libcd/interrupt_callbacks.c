/* GCC_VERSION: 2.6.3 */
/* ASPSX_VERSION: 2.21 */
/* GNU_AS_G: 0 */
#include "common.h"
extern s32 func_80043BA8(void);
typedef void (*CdCallback)(s32,void*);
extern CdCallback D_800555A0[],D_800555A4[];
extern volatile u8 *D_80055864[];
extern volatile u8 D_8005587C[],D_8005587D[];
extern u8 D_800571A0[],D_80057198[];
void func_80045B24(void) {
    s32 event;
    s32 pending;
    u8 bank;
    volatile u8 *ready_status;

    bank = *D_80055864[0] & 3;
    ready_status=D_8005587D;
loop_1:
    pending = func_80043BA8();
    event = pending;
    if (pending != 0) {
        pending = event;
        if (event & 4) {
            if (D_800555A4[0] != NULL) {
                D_800555A4[0](ready_status[0], D_800571A0);
            }
            pending = event;
        }
        if (((pending & 2) != 0) && (D_800555A0[0] != NULL)) {
            D_800555A0[0](D_8005587C[0], D_80057198);
        }
        goto loop_1;
    }
    *D_80055864[0] = bank;
}
