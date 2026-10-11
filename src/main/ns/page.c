#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Return an item span from adjacent offsets in a nonempty resource page. */

s32 func_80012C74(s32 *page, s32 index)
{
    s32 *entry;
    s32 result;
    if (!page[3]) {
        result = 0;
    } else {
        entry = page + index;
        result = entry[5] - entry[4];
    }
    return result;
}
