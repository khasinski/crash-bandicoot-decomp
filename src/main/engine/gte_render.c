#include "common.h"

/*
 * Handwritten GTE polygon/SVTX/background rendering pipeline (0x800334A0..0x8003A94C).
 * See docs/ASM_AND_GTE_POLICY.md for details on the custom register ABI and
 * the 4-byte embedded counter word at 0x80034520.
 */

HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800334A0);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033878);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033F18);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033F38);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033F58);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033F78);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033F98);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80033FBC);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034230);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034250);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034270);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034290);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800342B0);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800342D8);

/* The following assembly label contains a writable counter word, not an
 * ABI function. Retain its original address while typing this data access. */
extern u32 func_80034520[];
void func_80034504(void)
{
    func_80034520[0]++;
}

HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034520);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034524);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034580);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003460C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80034B08);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800351C8);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80035370);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800353B0);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80035438);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80035898);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80035E10);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80036340);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80036BF4);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80036D9C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800375EC);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80037D50);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003864C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003899C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800389A8);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80038AC4);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80038DF8);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003905C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_800390D0);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003913C);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_80039BD4);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003A144);
HANDWRITTEN_ASM("src/main/engine/gte_asm", func_8003A76C);
