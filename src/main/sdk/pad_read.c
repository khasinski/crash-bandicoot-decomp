#include "common.h"
/* GCC_VERSION: 2.6.3 */

s32 PadRead(void) {
    PAD_dr();
    return ~g_pad_mode_state;
}
