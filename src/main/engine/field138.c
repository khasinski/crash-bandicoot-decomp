/* GCC_VERSION: 2.6.3 */
#include "gool.h"
typedef GoolRuntimeObject Object;
extern s32 D_80052CA4[];
void func_80027A08(Object *object,s32 index,s32 fallback) {
    s32 bias = (object->flags120 & 0x10) ? 0 : 24;
    if (index >= 0) object->offset138 = bias + D_80052CA4[index];
    else object->offset138 = bias + fallback;
}
