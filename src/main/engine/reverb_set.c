/* GCC_VERSION: 2.6.3 */
#include "common.h"
typedef struct {u32 mask;s32 mode;s16 depth_left,depth_right;s32 delay,feedback;} ReverbAttributes;
s32 func_80047208(ReverbAttributes *);
s32 func_80047BE8(ReverbAttributes *);
s32 func_80046EE0(s32);
s32 func_80030008(s32 mode,s16 left,s16 right,s32 delay,s32 feedback)
{
    ReverbAttributes attributes;
    attributes.mask=7;
    attributes.mode=mode|0x100;
    attributes.depth_left=left;
    attributes.depth_right=right;
    if((u32)(mode-7)<2) {
        attributes.delay=delay;
        attributes.feedback=feedback;
    }
    func_80047208(&attributes);
    func_80047BE8(&attributes);
    func_80046EE0(mode!=0);
    return 0;
}
