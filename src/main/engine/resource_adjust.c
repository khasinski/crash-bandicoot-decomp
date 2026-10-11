#include "common.h"

/* GCC_VERSION: 2.6.3 */

s32 func_80015118(s32 *resource, s32 argument, s32 count);
s32 func_80015458(s32 *resource, s32 count);

/* Invalid handles are ignored; nonpositive counts use the release path. */
s32 func_80031B60(s32 *resource, s32 argument, s32 count)
{
    s32 result;

    if (*resource == 0x6396347F) {
        result = 0;
    } else if (count <= 0) {
        func_80015458(resource, -count);
        result = 0;
    } else {
        result = func_80015118(resource, argument, count);
    }
    return result;
}
