#include "common.h"

/*
 * Handwritten GTE polygon/SVTX/background rendering pipeline (0x800334A0..0x8003A94C).
 * See docs/ASM_AND_GTE_POLICY.md for details on the custom register ABI and
 * the 4-byte embedded counter word at 0x80034520.
 */

HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Slst_RDecodeForward);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Slst_RDecodeBackward);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RMemcpy_0);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RMemcpy_1);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RMemcpy_2);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RMemcpy_3);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RMemcpy_4);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RMemcpy);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gpu_RResetOT_0);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gpu_RResetOT_1);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gpu_RResetOT_2);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gpu_RResetOT_3);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gpu_RResetOT_4);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gpu_RResetOT);

/* The following assembly label contains a writable counter word, not an
 * ABI function. Retain its original address while typing this data access. */
void RIncTickCount(void)
{
    engine_counter[0]++;
}

HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", g_rcnt_ticks);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RSqrMagnitude2);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", RSqrMagnitude3);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformSvtx);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformCvtx);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RProjectBound);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RExtendBound3);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RExtendBound2);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorlds);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorldsFog);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorldsRipple);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorldsLightning);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorldsDark);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorldsDarkLoop);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformWorldsDark2);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Solid_RZoneQueryOctree);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Solid_RPlotQueryWalls);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Solid_RPlotWallEntry);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Solid_RPlotWall);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Solid_RFindFloorY);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Solid_RFindCeilY);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", sin);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", cos);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RCalcObjectRotMatrix);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RCalcObjectMatrices);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RCalcSpriteRotMatrix);
HANDWRITTEN_ASM("asm/USA/main/nonmatchings/engine/gte_render", Gte_RTransformSprite);
