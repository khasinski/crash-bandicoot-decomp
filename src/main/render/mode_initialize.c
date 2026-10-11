/* GCC_VERSION: 2.6.3 */
#include "render.h"
extern s32 D_80057280,D_80057284,D_80057288;
extern s32 D_80057868,D_8005786C,D_80057870,D_80057874,D_80057878;
extern s32 D_80057888,D_8005788C,D_80057890,D_800578AC;
extern s16 D_800578B0,D_800578B2,D_800578B4;
extern s32 D_800578C4,D_800578C8,D_800578CC;
extern s16 D_800578D6,D_800578D8,D_800578DA,D_800578DC,D_800578DE;
extern s16 D_800578E0,D_800578E2,D_800578E4;
extern s32 D_8006193C,D_80061940;
void func_80042EFC(s16 *);
void func_80042F6C(s32,s32,s32);
void func_80042F8C(s32,s32);
void func_80042FAC(s32);
/* Preserve unknown projection modes; reset the GTE matrix and camera words. */
void func_80017790(void)
{
    s32 mode;
    s32 distance;
    RenderProjectionState *projection;
    s16 *matrix;
    D_80057288=0;D_80057284=0;D_80057280=0;
    mode=D_8005C53C->word114;
    switch(mode) {
    case 30: distance=960;break;
    case 37: distance=800;break;
    case 55: distance=500;break;
    case 60: distance=460;break;
    case 90: distance=288;break;
    default:goto preserve_distance;
    }
    D_800578D0.distance=distance;
preserve_distance:
    projection=(RenderProjectionState *)&D_800578D0;
    func_80042FAC(projection->distance);
    func_80042F8C(0,0);
    D_800578B4=4096;D_800578B0=0;D_800578B2=0;
    D_800578C4=0;D_800578C8=0;D_800578CC=0;
    matrix=projection->matrix;
    *matrix=512;
    D_800578DA=512;D_800578E0=512;D_800578D6=512;
    D_800578DC=512;D_800578E2=512;D_800578D8=512;
    D_800578DE=512;D_800578E4=512;
    func_80042F6C(0,0,0);
    func_80042EFC(matrix);
    func_800180A0(((RenderCameraPrefix *)((u8 *)projection
        - CRASH_OFFSETOF(RenderCameraPrefix, projection)))->transform);
    ((RenderCameraPrefix *)((u8 *)projection
        - CRASH_OFFSETOF(RenderCameraPrefix, projection)))->transform[0]=0;
    D_80057868=0;D_8005786C=0x1F400;
    D_80057870=0;D_80057874=0;D_80057878=0;
    D_80057888=0;D_8005788C=0xE1000;D_80057890=0x5DC000;
    D_800578AC=0;D_8006193C=0;D_80061940=0;
}
