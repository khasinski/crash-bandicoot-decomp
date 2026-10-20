/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gte.h"

/* LIBGTE.A oko_02.o. Each library object's code is padded to 16 bytes (the pad
 * segments that follow it in configs/USA/main.yaml). */

void RotTrans(u32 *v0, u32 *v1, u32 *flag)
{
    u32 f;

    gte_mvmva_v0(v0);
    gte_stlvnl(v1);
    gte_getflag(f);
    *flag = f;
}
