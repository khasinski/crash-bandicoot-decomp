/* GCC_VERSION: 2.6.3 */
#include "common.h"

s32 func_80044640(s32, u8 *, u8 *, s32);
s32 func_80044B30(void);
s32 func_800440EC(s32, u8 *);
extern s32 D_80055520[32];
typedef void (*CdCallback)(s32, u8 *);
extern CdCallback D_800555A0;
extern u8 D_800555B0;

s32 func_80043520(u8 command, u8 *params, u8 *result) {
    s32 retries = 3;
    s32 code = command & 0xff;
    s32 *table = D_80055520;
    CdCallback saved_callback = D_800555A0;
    s32 *command_flags = &table[code];
    s32 status = 0;
    do {
        if ((code == 0x10) && !(D_800555B0 & 0x20)) {
            retries--;
            func_80044B30();
        } else {
            if (code != 1) {
                D_800555A0 = 0;
                func_80044B30();
                if (params && *command_flags && func_80044640(2, params, result, 0)) goto retry;
                D_800555A0 = saved_callback;
            }
            if (!func_80044640(command, params, result, 0)) goto done;
retry:
            retries--;
        }
    } while (retries != -1);
    D_800555A0 = saved_callback;
    status = -1;
done:
    return status + 1;
}

s32 func_80043668(u8 command, u8 *params) {
    s32 retries = 3;
    s32 code = command & 0xff;
    s32 *table = D_80055520;
    CdCallback saved_callback = D_800555A0;
    s32 *command_flags = &table[code];
    s32 status = 0;
    do {
        if ((code == 0x10) && !(D_800555B0 & 0x20)) {
            retries--;
            func_80044B30();
        } else {
            if (code != 1) {
                D_800555A0 = 0;
                func_80044B30();
                if (params && *command_flags && func_80044640(2, params, NULL, 0)) goto retry;
                D_800555A0 = saved_callback;
            }
            if (!func_80044640(command, params, NULL, 1)) goto done;
retry:
            retries--;
        }
    } while (retries != -1);
    D_800555A0 = saved_callback;
    status = -1;
done:
    return status + 1;
}

s32 func_800437A4(u8 command, u8 *params, u8 *result) {
    s32 retries = 3;
    s32 code = command & 0xff;
    s32 *table = D_80055520;
    CdCallback saved_callback = D_800555A0;
    s32 *command_flags = &table[code];
    s32 status;
    s32 success;
    do {
        if (code == 0x10 && !(D_800555B0 & 0x20)) {
            retries--;
            func_80044B30();
            status = -1;
        } else {
            if (code != 1) {
                D_800555A0 = 0;
                func_80044B30();
                if (params && *command_flags && func_80044640(2,params,result,0)) goto retry;
                D_800555A0 = saved_callback;
            }
            if (func_80044640(command,params,result,0) == 0) {
                status = 0;
                goto done;
            }
retry:
            retries--;
            status = -1;
        }
    /* Retry paths set status to -1, the exhausted-counter sentinel. */
    } while (retries != status);
    D_800555A0 = saved_callback;
done:
    if (status == 0) success = func_800440EC(0,result) == 2;
    else success = 0;
    return success;
}
