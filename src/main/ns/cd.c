#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Call the CD routine with the inverted flag; report success only for a zero result. */

extern s32 func_80043984(s32, s32);

s32 func_8001381C(s32 enabled)
{
    s32 result = func_80043984(enabled == 0, 0);
    if (result < 0)
        return 0;
    return result == 0;
}
