/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
#include "render.h"
s32 VSync(s32);
void *func_80040A0C(GpuDisplayEnv *);

void func_800172E8(void)
{
    RenderBuffer *swap;
    RenderBuffer **active = D_80058404;
    swap = D_80058404[1];
    *active = swap;
    D_80058404[1] = D_80058404[2];
    D_80058404[2] = swap;
    VSync(0);
    func_80040A0C(&(*active)->display);
    func_80040834(&D_80058404[1]->drawing);
}
