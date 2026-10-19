#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Dispatch the display operation only when the pointed-to halfword is nonzero. */

#define CRASH_EXT_RENDER_DISPLAY
#include "render_externs.h"
#undef CRASH_EXT_RENDER_DISPLAY

void Gfx_UpdateMatrices2(void)
{
    if (*gp_level_entry)
        Gfx_UpdateCamMatrices();
}
