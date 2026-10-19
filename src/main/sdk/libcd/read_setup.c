#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Shared CD read state; retain the observed load after writing mode. */
s32 CD_sync(s32, s32);                              /* extern */
s32 CD_cw(s32, s32, s32, s32);                        /* extern */
s32 CD_read(void);                                /* extern */

#include "cd_read_state.h"

s32 cd_read_retry(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    g_cd_read_state.mode = arg2;
    temp_v1 = g_cd_read_state.mode & 0x30;
    switch (temp_v1) {                              /* irregular */
    case 0:
        g_cd_read_state.size = 0x200;
        break;
    case 32:
        g_cd_read_state.size = 0x249;
        break;
    default:
        g_cd_read_state.size = 0x246;
        break;
    }
    g_cd_read_state.count = arg0;
    g_cd_read_state.buffer = arg1;
    g_cd_read_state.state = 8;
    g_cd_read_state.word20 = g_cd_sync_cb;
    g_cd_read_state.word24 = D_800555A4;
    if (D_800555B0 & 0xE0) {
        CD_cw(9, 0, 0, 0);
    }
    CD_sync(0, 0);
    return -(CD_read() < 1);
}
