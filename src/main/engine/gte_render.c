#include "common.h"

/*
 * Handwritten GTE polygon/SVTX/background rendering pipeline (0x800334A0..0x8003A94C).
 * See docs/ASM_AND_GTE_POLICY.md for details on the custom register ABI and
 * the 4-byte embedded counter word at 0x80034520.
 */

HANDWRITTEN_ASM("src/main/engine/gte_asm", Slst_RDecodeForward);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Slst_RDecodeBackward);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RMemcpy_0);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RMemcpy_1);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RMemcpy_2);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RMemcpy_3);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RMemcpy_4);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RMemcpy);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gpu_RResetOT_0);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gpu_RResetOT_1);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gpu_RResetOT_2);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gpu_RResetOT_3);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gpu_RResetOT_4);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gpu_RResetOT);

/* The following assembly label contains a writable counter word, not an
 * ABI function. Retain its original address while typing this data access. */
void RIncTickCount(void)
{
    engine_counter[0]++;
}

HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034520);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RSqrMagnitude2);
HANDWRITTEN_ASM("src/main/engine/gte_asm", RSqrMagnitude3);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformSvtx);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformCvtx);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RProjectBound);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RExtendBound3);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RExtendBound2);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorlds);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorldsFog);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorldsRipple);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorldsLightning);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorldsDark);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorldsDarkLoop);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformWorldsDark2);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Solid_RZoneQueryOctree);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Solid_RPlotQueryWalls);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Solid_RPlotWallEntry);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Solid_RPlotWall);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Solid_RFindFloorY);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Solid_RFindCeilY);
HANDWRITTEN_ASM("src/main/engine/gte_asm", sin);
HANDWRITTEN_ASM("src/main/engine/gte_asm", cos);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003913C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RCalcObjectMatrices);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RCalcSpriteRotMatrix);
HANDWRITTEN_ASM("src/main/engine/gte_asm", Gte_RTransformSprite);
