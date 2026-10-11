/* GCC_VERSION: 2.6.3 */
#include "common.h"
typedef struct {
    u32 mask;
    s32 mode;
    s16 depth_left,depth_right;
    s32 delay,feedback;
} ReverbAttributes;
s32 func_80047208(ReverbAttributes *);
s32 func_80046EE0(s32);
void func_8002FFC0(void) {
    ReverbAttributes attributes;
    attributes.mask = 7;
    attributes.mode = 0;
    attributes.depth_left = 0;
    attributes.depth_right = 0;
    func_80047208(&attributes);
    func_80046EE0(0);
}
