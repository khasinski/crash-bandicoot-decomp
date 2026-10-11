#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Synchronise cached disc state while temporarily suppressing the callback. */
extern s32 func_8003E6D4(const char *, ...);
extern s32 func_80044640(s32, void *, s32, void *);
extern char D_800115B4[];
extern char D_800115C4[];
extern s32 D_800555A0;
extern s32 D_800555B0;
extern s32 D_800555B8;
extern s32 D_800558A8;
extern u8 D_800558AC[];

void func_80044B30(void) {
    s32 saved_callback;
    s32 poll_count;

    poll_count = 0;
    if (D_800558A8 < D_800555B8) {
        saved_callback = D_800555A0;
        D_800555A0 = 0;
        while (D_800555B0 & 0x10) {
            if ((poll_count++ & 0xFF) == 0) {
                func_8003E6D4(D_800115B4);
            }
            func_80044640(1, 0, 0, 0);
        }
        while (func_80044640(0x16, D_800558AC, 0, 0) != 0) {
            func_80044640(1, 0, 0, 0);
            func_8003E6D4(D_800115C4);
        }
        D_800555A0 = saved_callback;
        D_800558A8 = D_800555B8;
    }
}
