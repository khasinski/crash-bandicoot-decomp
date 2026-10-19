/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
typedef struct {u32 mask;s32 mode;s16 depth_left,depth_right;s32 delay,feedback;} ReverbAttributes;
s32 SpuSetReverbModeParam(ReverbAttributes *);
extern ReverbAttributes D_8005778C;
void SsUtSetReverbDepth(s16 left, s16 right) {
    s32 depth;
    depth = (left * 0x7FFF) / 127;
    D_8005778C.mask = 6;
    D_8005778C.depth_left = depth;
    D_8005778C.depth_right = (right * 0x7FFF) / 127;
    SpuSetReverbModeParam(&D_8005778C);
}
