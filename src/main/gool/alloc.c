#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Free the two allocation tables and update the fixed-point value from the current resource. */


extern void *g_player;
extern s32 *g_ns_page_pool;

void GOOL_FreeAllocTable(void)
{
    LIBC_Free(g_objects);
    LIBC_Free(g_player);
}

s32 Gool_InitLid(void)
{
    s32 *entry = g_ns_page_pool;
    g_cur_display_flags[0] = entry[1] << 8;
    if (!entry[0])
        return -0xE;
    return -0xFF;
}
