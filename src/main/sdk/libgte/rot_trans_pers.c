/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gte.h"

/* LIBGTE.A oko_00.o. Each library object's code is padded to 16 bytes (the pad
 * segments that follow it in configs/USA/main.yaml). */

s32 RotTransPers(u32 *v0, u32 *sxy, u32 *p, u32 *flag)
{
    u32 f;
    s32 sz;

    gte_rtps_v0(v0);
    gte_stsxy2(*sxy);
    gte_swc2(*p, 8);
    gte_getflag(f);
    gte_getsz3(sz);
    *flag = f;
    return sz >> 2;
}
