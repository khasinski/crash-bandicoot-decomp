/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
typedef struct {u32 mask;s32 mode;s16 depth_left,depth_right;s32 delay,feedback;} ReverbAttributes;
extern ReverbAttributes g_spu_reverb_attr;
void SsUtSetReverbDepth(s16 left, s16 right) {
    s32 depth;
    depth = (left * 0x7FFF) / 127;
    g_spu_reverb_attr.mask = 6;
    g_spu_reverb_attr.depth_left = depth;
    g_spu_reverb_attr.depth_right = (right * 0x7FFF) / 127;
    SpuSetReverbModeParam(&g_spu_reverb_attr);
}
