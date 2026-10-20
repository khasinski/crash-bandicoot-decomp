/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gte.h"

/* LIBGTE.A fgo_06.o. Each library object's code is padded to 16 bytes (the pad
 * segments that follow it in configs/USA/main.yaml). */

void SetGeomScreen(s32 h)
{
    gte_ctc2(h, 26);
}
