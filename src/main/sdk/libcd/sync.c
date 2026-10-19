#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Synchronise cached disc state while temporarily suppressing the callback. */
s32 puts(const char *, ...);
s32 CD_cw(s32, void *, s32, void *);

void CD_flush(void) {
    s32 saved_callback;
    s32 poll_count;

    poll_count = 0;
    if (D_800558A8 < D_800555B8) {
        saved_callback = g_cd_sync_cb;
        g_cd_sync_cb = 0;
        while (D_800555B0 & 0x10) {
            if ((poll_count++ & 0xFF) == 0) {
                puts(D_800115B4);
            }
            CD_cw(1, 0, 0, 0);
        }
        while (CD_cw(0x16, D_800558AC, 0, 0) != 0) {
            CD_cw(1, 0, 0, 0);
            puts(D_800115C4);
        }
        g_cd_sync_cb = saved_callback;
        D_800558A8 = D_800555B8;
    }
}
