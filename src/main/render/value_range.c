#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Select 0x11, 0x22 or 0x33 for the observed input ranges. */
s32 func_800175D0(s32 arg0)
{
    if (arg0 < 0) {
        arg0 = 0x22;
    } else if (arg0 < 0x13) {
        arg0 = 0x11;
    } else if (arg0 < 0x24) {
        arg0 = 0x22;
    } else if (arg0 < 0x35) {
        arg0 = 0x33;
    }
    return arg0;
}
