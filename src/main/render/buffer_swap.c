/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
#include "render.h"
s32 VSync(s32);
void *PutDispEnv(GpuDisplayEnv *);

void Gpu_SwapBuffers(void)
{
    RenderBuffer *swap;
    RenderBuffer **active = g_db_cur;
    swap = g_db_cur[1];
    *active = swap;
    g_db_cur[1] = g_db_cur[2];
    g_db_cur[2] = swap;
    VSync(0);
    PutDispEnv(&(*active)->display);
    PutDrawEnv(&g_db_cur[1]->drawing);
}
