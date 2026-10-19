#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clear callback state and install the CD interrupt handler. */

extern s32 g_cd_read_state[10];

void CD_init(void) {
    s32 *var_v1;
    s32 var_v0;

    var_v1 = g_cd_read_state;
    var_v0 = 9;
    g_cd_ready_cb = 0;
    g_cd_sync_cb = 0;
    g_cd_read_buf_ptr = 0;
    g_cd_read_sectors = 0;
    do {
        *var_v1 = 0;
        var_v0 -= 1;
        var_v1++;
    } while (var_v0 != -1);
    ResetCallback();
    InterruptCallback(2, &cd_callback);
}
