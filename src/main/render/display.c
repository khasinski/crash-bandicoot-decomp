#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Dispatch the display operation only when the pointed-to halfword is nonzero. */

extern u16 *gp_level_entry;
void Gfx_UpdateCamMatrices(void);

void Gfx_UpdateMatrices2(void)
{
    if (*gp_level_entry)
        Gfx_UpdateCamMatrices();
}
