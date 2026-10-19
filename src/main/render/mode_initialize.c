/* GCC_VERSION: 2.6.3 */
#include "render.h"


void SetColorMatrix(s16 *);
void SetBackColor(s32,s32,s32);
void SetGeomOffset(s32,s32);
void SetGeomScreen(s32);
/* Preserve unknown projection modes; reset the GTE matrix and camera words. */
void Gfx_InitMatrices(void)
{
    s32 mode;
    s32 distance;
    RenderProjectionState *projection;
    s16 *matrix;
    D_80057288=0;D_80057284=0;D_80057280=0;
    mode=g_ns_page_pool->word114;
    switch(mode) {
    case 30: distance=960;break;
    case 37: distance=800;break;
    case 55: distance=500;break;
    case 60: distance=460;break;
    case 90: distance=288;break;
    default:goto preserve_distance;
    }
    g_view_proj.distance=distance;
preserve_distance:
    projection=(RenderProjectionState *)&g_view_proj;
    SetGeomScreen(projection->distance);
    SetGeomOffset(0,0);
    D_800578B4=4096;D_800578B0=0;D_800578B2=0;
    D_800578C4=0;D_800578C8=0;D_800578CC=0;
    matrix=projection->matrix;
    *matrix=512;
    D_800578DA=512;D_800578E0=512;D_800578D6=512;
    D_800578DC=512;D_800578E2=512;D_800578D8=512;
    D_800578DE=512;D_800578E4=512;
    SetBackColor(0,0,0);
    SetColorMatrix(matrix);
    Gfx_ResetCam(((RenderCameraPrefix *)((u8 *)projection
        - CRASH_OFFSETOF(RenderCameraPrefix, projection)))->transform);
    ((RenderCameraPrefix *)((u8 *)projection
        - CRASH_OFFSETOF(RenderCameraPrefix, projection)))->transform[0]=0;
    D_80057868=0;D_8005786C=0x1F400;
    D_80057870=0;D_80057874=0;D_80057878=0;
    D_80057888[0]=0;D_8005788C[0]=0xE1000;D_80057890[0]=0x5DC000;
    D_800578AC=0;D_8006193C[0]=0;g_item_pool1[0]=0;
}
