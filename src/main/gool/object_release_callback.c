#include "gool.h"

/* GCC_VERSION: 2.6.3 */
typedef GoolRuntimeObject Object;
extern s32 D_80057918;
extern s32 func_8001CDD0(Object *,s32);
extern void func_80024040(s32,Object *,s32,s32,s32);
s32 func_8001D11C(Object *arg0, s32 arg1) {
    s32 temp_s1;

    if (arg0->kind != 0) {
        temp_s1 = arg0->entry;
        if ((temp_s1 == arg1) && !(arg0->flagsCC & 0x01000000) && !(arg0->flags120 & 0x40000) && ((func_80024040(0, arg0, 0x1A00, 0, 0), (arg0->entry == temp_s1)) || (D_80057918 == -1))) {
            return func_8001CDD0(arg0, 0);
        }
        /* Duplicate return node #8. Try simplifying control flow for better match */
        return -0xFF;
    }
    return -0xFF;
}
