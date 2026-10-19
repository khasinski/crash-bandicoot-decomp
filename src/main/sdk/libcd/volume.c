#include "cd_audio.h"

/* GCC_VERSION: 2.6.3 */

/* Write the four CD stereo mixing coefficients. */

s32 CD_vol(u8 *arg0) {
    return CD_WriteVolumeRegisters(arg0);
}
