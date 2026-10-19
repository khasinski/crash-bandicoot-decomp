#include "common.h"
/* GCC_VERSION: 2.6.3 */


s32 CdReadyCallback(s32 arg0) {
    s32 temp_v0;

    temp_v0 = g_cd_ready_cb;
    g_cd_ready_cb = arg0;
    return temp_v0;
}
