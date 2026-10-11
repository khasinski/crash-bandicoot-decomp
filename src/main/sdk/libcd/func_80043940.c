#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Forward the caller word to slot 04 of the API dispatch table, with index 3. */
extern s32 func_8003E754(s32, s32);

s32 func_80043940(s32 arg0)
{
    return func_8003E754(3, arg0);
}
