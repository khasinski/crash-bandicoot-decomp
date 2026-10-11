#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Pack the palette coordinates into the GPU CLUT field. */


u16 func_8003F5DC(s32 x, s32 y)
{
    return ((y << 6) | ((x >> 4) & 0x3F)) & 0xFFFF;
}
