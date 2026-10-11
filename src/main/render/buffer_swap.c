/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
#include "render.h"
typedef struct { GpuDrawEnv env; u32 packet[16]; } Drawing;
s32 CORE_VSync(s32);
void *func_80040834(Drawing *);
void *func_80040A0C(GpuDisplayEnv *);
extern RenderBuffer *D_80058404[3];

void func_800172E8(void)
{
    RenderBuffer *swap;
    RenderBuffer **active = D_80058404;
    swap = D_80058404[1];
    *active = swap;
    D_80058404[1] = D_80058404[2];
    D_80058404[2] = swap;
    CORE_VSync(0);
    func_80040A0C((GpuDisplayEnv *)((u8 *)*active + 4));
    func_80040834((Drawing *)((u8 *)D_80058404[1] + 24));
}
