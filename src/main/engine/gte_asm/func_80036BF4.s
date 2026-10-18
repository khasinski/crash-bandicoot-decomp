.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_80036BF4
    /* 273F4 80036BF4 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 273F8 80036BF8 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 273FC 80036BFC 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 27400 80036C00 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 27404 80036C04 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 27408 80036C08 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2740C 80036C0C 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 27410 80036C10 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 27414 80036C14 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 27418 80036C18 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2741C 80036C1C 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 27420 80036C20 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 27424 80036C24 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 27428 80036C28 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2742C 80036C2C 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 27430 80036C30 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 27434 80036C34 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 27438 80036C38 1000AF8F */  lw         $t7, 0x10($sp)
    /* 2743C 80036C3C 1400B68F */  lw         $s6, 0x14($sp)
    /* 27440 80036C40 1800A18F */  lw         $at, 0x18($sp)
    /* 27444 80036C44 1C00BF8F */  lw         $ra, 0x1C($sp)
    /* 27448 80036C48 0000EB8D */  lw         $t3, 0x0($t7)
    /* 2744C 80036C4C 801F1D3C */  lui        $sp, (0x1F8000E0 >> 16)
    /* 27450 80036C50 E000BD37 */  ori        $sp, $sp, (0x1F8000E0 & 0xFFFF)
    /* 27454 80036C54 0000A7AF */  sw         $a3, 0x0($sp)
    /* 27458 80036C58 00A85348 */  cfc2       $s3, $21 /* handwritten instruction */
    /* 2745C 80036C5C 00B05448 */  cfc2       $s4, $22 /* handwritten instruction */
    /* 27460 80036C60 00B85548 */  cfc2       $s5, $23 /* handwritten instruction */
    /* 27464 80036C64 0400B3AF */  sw         $s3, 0x4($sp)
    /* 27468 80036C68 0800B4AF */  sw         $s4, 0x8($sp)
    /* 2746C 80036C6C 0C00B5AF */  sw         $s5, 0xC($sp)
    /* 27470 80036C70 FF001C3C */  lui        $gp, (0xFFFFFF >> 16)
    /* 27474 80036C74 FFFF9C37 */  ori        $gp, $gp, (0xFFFFFF & 0xFFFF)
    /* 27478 80036C78 60000F34 */  ori        $t7, $zero, 0x60
    /* 2747C 80036C7C 801F083C */  lui        $t0, (0x1F800100 >> 16)
    /* 27480 80036C80 00010835 */  ori        $t0, $t0, (0x1F800100 & 0xFFFF)
    /* 27484 80036C84 00008D8C */  lw         $t5, 0x0($a0)
    /* 27488 80036C88 02008A24 */  addiu      $t2, $a0, 0x2
    /* 2748C 80036C8C 21504D01 */  addu       $t2, $t2, $t5
    /* 27490 80036C90 21504D01 */  addu       $t2, $t2, $t5
    /* 27494 80036C94 FFFF0C34 */  ori        $t4, $zero, 0xFFFF
    /* 27498 80036C98 21382000 */  addu       $a3, $at, $zero
    /* 2749C 80036C9C 2120E003 */  addu       $a0, $ra, $zero
    /* 274A0 80036CA0 00004195 */  lhu        $at, 0x0($t2)
    /* 274A4 80036CA4 80300600 */  sll        $a2, $a2, 2
    /* 274A8 80036CA8 FC1F0334 */  ori        $v1, $zero, 0x1FFC
  .L80036CAC:
    /* 274AC 80036CAC FEFF4A25 */  addiu      $t2, $t2, -0x2
    /* 274B0 80036CB0 02F30100 */  srl        $fp, $at, 12
    /* 274B4 80036CB4 0D00CC13 */  beq        $fp, $t4, .L80036CEC
    /* 274B8 80036CB8 FF0F2130 */   andi      $at, $at, 0xFFF
    /* 274BC 80036CBC 2160C003 */  addu       $t4, $fp, $zero
    /* 274C0 80036CC0 80F90C00 */  sll        $ra, $t4, 6
    /* 274C4 80036CC4 2110E803 */  addu       $v0, $ra, $t0
    /* 274C8 80036CC8 04005D8C */  lw         $sp, 0x4($v0)
    /* 274CC 80036CCC 08005E8C */  lw         $fp, 0x8($v0)
    /* 274D0 80036CD0 0C005F8C */  lw         $ra, 0xC($v0)
    /* 274D4 80036CD4 0028DD48 */  ctc2       $sp, $5 /* handwritten instruction */
    /* 274D8 80036CD8 0030DE48 */  ctc2       $fp, $6 /* handwritten instruction */
    /* 274DC 80036CDC 0038DF48 */  ctc2       $ra, $7 /* handwritten instruction */
    /* 274E0 80036CE0 1400578C */  lw         $s7, 0x14($v0)
    /* 274E4 80036CE4 1800588C */  lw         $t8, 0x18($v0)
    /* 274E8 80036CE8 1C00598C */  lw         $t9, 0x1C($v0)
  .L80036CEC:
    /* 274EC 80036CEC C0080100 */  sll        $at, $at, 3
    /* 274F0 80036CF0 2148E102 */  addu       $t1, $s7, $at
    /* 274F4 80036CF4 0000218D */  lw         $at, 0x0($t1)
    /* 274F8 80036CF8 0400298D */  lw         $t1, 0x4($t1)
    /* 274FC 80036CFC 00130100 */  sll        $v0, $at, 12
    /* 27500 80036D00 FF003D31 */  andi       $sp, $t1, 0xFF
    /* 27504 80036D04 25105D00 */  or         $v0, $v0, $sp
    /* 27508 80036D08 42840900 */  srl        $s0, $t1, 17
    /* 2750C 80036D0C F87F1032 */  andi       $s0, $s0, 0x7FF8
    /* 27510 80036D10 21801802 */  addu       $s0, $s0, $t8
    /* 27514 80036D14 42890900 */  srl        $s1, $t1, 5
    /* 27518 80036D18 F87F3132 */  andi       $s1, $s1, 0x7FF8
    /* 2751C 80036D1C 21883802 */  addu       $s1, $s1, $t8
    /* 27520 80036D20 42940100 */  srl        $s2, $at, 17
    /* 27524 80036D24 F87F5232 */  andi       $s2, $s2, 0x7FF8
    /* 27528 80036D28 21905802 */  addu       $s2, $s2, $t8
    /* 2752C 80036D2C 0000138E */  lw         $s3, 0x0($s0)
    /* 27530 80036D30 0400108E */  lw         $s0, 0x4($s0)
    /* 27534 80036D34 0000348E */  lw         $s4, 0x0($s1)
    /* 27538 80036D38 0400318E */  lw         $s1, 0x4($s1)
    /* 2753C 80036D3C 0000558E */  lw         $s5, 0x0($s2)
    /* 27540 80036D40 0400528E */  lw         $s2, 0x4($s2)
    /* 27544 80036D44 801F093C */  lui        $t1, (0x1F800048 >> 16)
    /* 27548 80036D48 48002935 */  ori        $t1, $t1, (0x1F800048 & 0xFFFF)
    /* 2754C 80036D4C 00003D8D */  lw         $sp, 0x0($t1)
    /* 27550 80036D50 04003E8D */  lw         $fp, 0x4($t1)
    /* 27554 80036D54 08003F8D */  lw         $ra, 0x8($t1)
    /* 27558 80036D58 0C0028C9 */  lwc2       $8, 0xC($t1)
    /* 2755C 80036D5C 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 27560 80036D60 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 27564 80036D64 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 27568 80036D68 01001D32 */  andi       $sp, $s0, 0x1
    /* 2756C 80036D6C 01003F32 */  andi       $ra, $s1, 0x1
    /* 27570 80036D70 40F81F00 */  sll        $ra, $ra, 1
    /* 27574 80036D74 25E8BF03 */  or         $sp, $sp, $ra
    /* 27578 80036D78 01005F32 */  andi       $ra, $s2, 0x1
    /* 2757C 80036D7C 80F81F00 */  sll        $ra, $ra, 2
    /* 27580 80036D80 25E8BF03 */  or         $sp, $sp, $ra
    /* 27584 80036D84 03801F3C */  lui        $ra, %hi(func_80036D9C)
    /* 27588 80036D88 9C6DFF27 */  addiu      $ra, $ra, %lo(func_80036D9C)
    /* 2758C 80036D8C C0E91D00 */  sll        $sp, $sp, 7
    /* 27590 80036D90 21F8FD03 */  addu       $ra, $ra, $sp
    /* 27594 80036D94 0800E003 */  jr         $ra
    /* 27598 80036D98 27F08003 */   not       $fp, $gp
endlabel func_80036BF4
