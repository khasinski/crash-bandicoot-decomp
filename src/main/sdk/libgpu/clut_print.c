#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Decode CLUT coordinates for the diagnostic callback. */


void DumpClut(s32 arg0) {
    g_gpu_ot_status(D_800110B0, (arg0 & 0x3F) * 0x10, (u32) (arg0 & 0xFFFF) >> 6);
}
