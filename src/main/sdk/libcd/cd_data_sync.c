#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Forward the caller word to slot 04 of the API dispatch table, with index 3. */
s32 DMACallback(s32, s32);

s32 CdDataSync(s32 arg0)
{
    return DMACallback(3, arg0);
}
