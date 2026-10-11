/* GCC_VERSION: 2.6.3 */
#include "common.h"

s32 func_80045518(void *, s32, s32);

s32 func_800439A4(s32 count, void *buffer, s32 mode)
{
    s32 retries = 3;
    do {
        if (func_80045518(buffer, count, mode) != 0) {
            retries--;
        } else {
            return 1;
        }
    } while (retries != -1);
    return 0;
}
