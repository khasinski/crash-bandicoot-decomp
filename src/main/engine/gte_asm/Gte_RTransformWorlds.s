.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformWorlds
    /* 25C38 80035438 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 25C3C 8003543C 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 25C40 80035440 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 25C44 80035444 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 25C48 80035448 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 25C4C 8003544C 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 25C50 80035450 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 25C54 80035454 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 25C58 80035458 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 25C5C 8003545C 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 25C60 80035460 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 25C64 80035464 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 25C68 80035468 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 25C6C 8003546C 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 25C70 80035470 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 25C74 80035474 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 25C78 80035478 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 25C7C 8003547C 1000AF8F */  lw         $t7, 0x10($sp)
    /* 25C80 80035480 1400B68F */  lw         $s6, 0x14($sp)
    /* 25C84 80035484 0000EB8D */  lw         $t3, 0x0($t7)
    /* 25C88 80035488 801F1D3C */  lui        $sp, (0x1F8000E0 >> 16)
    /* 25C8C 8003548C E000BD37 */  ori        $sp, $sp, (0x1F8000E0 & 0xFFFF)
    /* 25C90 80035490 0000A7AF */  sw         $a3, 0x0($sp)
    /* 25C94 80035494 FF001C3C */  lui        $gp, (0xFFFFFF >> 16)
    /* 25C98 80035498 FFFF9C37 */  ori        $gp, $gp, (0xFFFFFF & 0xFFFF)
    /* 25C9C 8003549C 60000F34 */  ori        $t7, $zero, 0x60
    /* 25CA0 800354A0 801F083C */  lui        $t0, (0x1F800100 >> 16)
    /* 25CA4 800354A4 00010835 */  ori        $t0, $t0, (0x1F800100 & 0xFFFF)
    /* 25CA8 800354A8 00008D8C */  lw         $t5, 0x0($a0)
    /* 25CAC 800354AC 02008A24 */  addiu      $t2, $a0, 0x2
    /* 25CB0 800354B0 21504D01 */  addu       $t2, $t2, $t5
    /* 25CB4 800354B4 21504D01 */  addu       $t2, $t2, $t5
    /* 25CB8 800354B8 FFFF0C34 */  ori        $t4, $zero, 0xFFFF
    /* 25CBC 800354BC 0002043C */  lui        $a0, (0x2000000 >> 16)
    /* 25CC0 800354C0 00004195 */  lhu        $at, 0x0($t2)
    /* 25CC4 800354C4 80300600 */  sll        $a2, $a2, 2
    /* 25CC8 800354C8 FC1F0334 */  ori        $v1, $zero, 0x1FFC
  .L800354CC:
    /* 25CCC 800354CC FEFF4A25 */  addiu      $t2, $t2, -0x2
    /* 25CD0 800354D0 02F30100 */  srl        $fp, $at, 12
    /* 25CD4 800354D4 0E00CC13 */  beq        $fp, $t4, .L80035510
    /* 25CD8 800354D8 FF0F2130 */   andi      $at, $at, 0xFFF
    /* 25CDC 800354DC 2160C003 */  addu       $t4, $fp, $zero
    /* 25CE0 800354E0 80F90C00 */  sll        $ra, $t4, 6
    /* 25CE4 800354E4 2110E803 */  addu       $v0, $ra, $t0
    /* 25CE8 800354E8 04005D8C */  lw         $sp, 0x4($v0)
    /* 25CEC 800354EC 08005E8C */  lw         $fp, 0x8($v0)
    /* 25CF0 800354F0 0C005F8C */  lw         $ra, 0xC($v0)
    /* 25CF4 800354F4 0028DD48 */  ctc2       $sp, $5 /* handwritten instruction */
    /* 25CF8 800354F8 0030DE48 */  ctc2       $fp, $6 /* handwritten instruction */
    /* 25CFC 800354FC 0038DF48 */  ctc2       $ra, $7 /* handwritten instruction */
    /* 25D00 80035500 1400578C */  lw         $s7, 0x14($v0)
    /* 25D04 80035504 1800588C */  lw         $t8, 0x18($v0)
    /* 25D08 80035508 1C00598C */  lw         $t9, 0x1C($v0)
    /* 25D0C 8003550C 20004724 */  addiu      $a3, $v0, 0x20
  .L80035510:
    /* 25D10 80035510 C0080100 */  sll        $at, $at, 3
    /* 25D14 80035514 2148E102 */  addu       $t1, $s7, $at
    /* 25D18 80035518 0000218D */  lw         $at, 0x0($t1)
    /* 25D1C 8003551C 0400298D */  lw         $t1, 0x4($t1)
    /* 25D20 80035520 00130100 */  sll        $v0, $at, 12
    /* 25D24 80035524 FF003D31 */  andi       $sp, $t1, 0xFF
    /* 25D28 80035528 25105D00 */  or         $v0, $v0, $sp
    /* 25D2C 8003552C 42840900 */  srl        $s0, $t1, 17
    /* 25D30 80035530 F87F1032 */  andi       $s0, $s0, 0x7FF8
    /* 25D34 80035534 21801802 */  addu       $s0, $s0, $t8
    /* 25D38 80035538 42890900 */  srl        $s1, $t1, 5
    /* 25D3C 8003553C F87F3132 */  andi       $s1, $s1, 0x7FF8
    /* 25D40 80035540 21883802 */  addu       $s1, $s1, $t8
    /* 25D44 80035544 42940100 */  srl        $s2, $at, 17
    /* 25D48 80035548 F87F5232 */  andi       $s2, $s2, 0x7FF8
    /* 25D4C 8003554C 21905802 */  addu       $s2, $s2, $t8
    /* 25D50 80035550 0000138E */  lw         $s3, 0x0($s0)
    /* 25D54 80035554 0400108E */  lw         $s0, 0x4($s0)
    /* 25D58 80035558 0000348E */  lw         $s4, 0x0($s1)
    /* 25D5C 8003555C 0400318E */  lw         $s1, 0x4($s1)
    /* 25D60 80035560 0000558E */  lw         $s5, 0x0($s2)
    /* 25D64 80035564 0400528E */  lw         $s2, 0x4($s2)
    /* 25D68 80035568 F8FF013C */  lui        $at, (0xFFF8FFF8 >> 16)
    /* 25D6C 8003556C F8FF2134 */  ori        $at, $at, (0xFFF8FFF8 & 0xFFFF)
    /* 25D70 80035570 24E80102 */  and        $sp, $s0, $at
    /* 25D74 80035574 24F02102 */  and        $fp, $s1, $at
    /* 25D78 80035578 24F84102 */  and        $ra, $s2, $at
    /* 25D7C 8003557C 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 25D80 80035580 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 25D84 80035584 00209F48 */  mtc2       $ra, $4 /* handwritten instruction */
    /* 25D88 80035588 0700013C */  lui        $at, (0x70006 >> 16)
    /* 25D8C 8003558C 06002134 */  ori        $at, $at, (0x70006 & 0xFFFF)
    /* 25D90 80035590 02EE1300 */  srl        $sp, $s3, 24
    /* 25D94 80035594 C0E81D00 */  sll        $sp, $sp, 3
    /* 25D98 80035598 24800102 */  and        $s0, $s0, $at
    /* 25D9C 8003559C 804A1000 */  sll        $t1, $s0, 10
    /* 25DA0 800355A0 25E8A903 */  or         $sp, $sp, $t1
    /* 25DA4 800355A4 C2481000 */  srl        $t1, $s0, 3
    /* 25DA8 800355A8 25E8A903 */  or         $sp, $sp, $t1
    /* 25DAC 800355AC 02F61400 */  srl        $fp, $s4, 24
    /* 25DB0 800355B0 C0F01E00 */  sll        $fp, $fp, 3
    /* 25DB4 800355B4 24882102 */  and        $s1, $s1, $at
    /* 25DB8 800355B8 804A1100 */  sll        $t1, $s1, 10
    /* 25DBC 800355BC 25F0C903 */  or         $fp, $fp, $t1
    /* 25DC0 800355C0 C2481100 */  srl        $t1, $s1, 3
    /* 25DC4 800355C4 25F0C903 */  or         $fp, $fp, $t1
    /* 25DC8 800355C8 02FE1500 */  srl        $ra, $s5, 24
    /* 25DCC 800355CC C0F81F00 */  sll        $ra, $ra, 3
    /* 25DD0 800355D0 24904102 */  and        $s2, $s2, $at
    /* 25DD4 800355D4 804A1200 */  sll        $t1, $s2, 10
    /* 25DD8 800355D8 25F8E903 */  or         $ra, $ra, $t1
    /* 25DDC 800355DC C2481200 */  srl        $t1, $s2, 3
    /* 25DE0 800355E0 25F8E903 */  or         $ra, $ra, $t1
    /* 25DE4 800355E4 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 25DE8 800355E8 00189E48 */  mtc2       $fp, $3 /* handwritten instruction */
    /* 25DEC 800355EC 00289F48 */  mtc2       $ra, $5 /* handwritten instruction */
    /* 25DF0 800355F0 02F50200 */  srl        $fp, $v0, 20
    /* 25DF4 800355F4 00000000 */  nop
    /* 25DF8 800355F8 3000284A */  rtpt
    /* 25DFC 800355FC 80F01E00 */  sll        $fp, $fp, 2
    /* 25E00 80035600 21703E03 */  addu       $t6, $t9, $fp
    /* 25E04 80035604 0000C98D */  lw         $t1, 0x0($t6)
    /* 25E08 80035608 0034123C */  lui        $s2, (0x34000000 >> 16)
    /* 25E0C 8003560C 024E0900 */  srl        $t1, $t1, 24
    /* 25E10 80035610 80003D31 */  andi       $sp, $t1, 0x80
    /* 25E14 80035614 6300A013 */  beqz       $sp, .L800357A4
    /* 25E18 80035618 24987C02 */   and       $s3, $s3, $gp
    /* 25E1C 8003561C 08006CE9 */  swc2       $12, 0x8($t3)
    /* 25E20 80035620 14006DE9 */  swc2       $13, 0x14($t3)
    /* 25E24 80035624 20006EE9 */  swc2       $14, 0x20($t3)
    /* 25E28 80035628 24F02F01 */  and        $fp, $t1, $t7
    /* 25E2C 8003562C 0200CF13 */  beq        $fp, $t7, .L80035638
    /* 25E30 80035630 25987202 */   or        $s3, $s3, $s2
    /* 25E34 80035634 25986402 */  or         $s3, $s3, $a0
  .L80035638:
    /* 25E38 80035638 040073AD */  sw         $s3, 0x4($t3)
    /* 25E3C 8003563C 100074AD */  sw         $s4, 0x10($t3)
    /* 25E40 80035640 1C0075AD */  sw         $s5, 0x1C($t3)
    /* 25E44 80035644 C2FB0200 */  srl        $ra, $v0, 15
    /* 25E48 80035648 1C00FF33 */  andi       $ra, $ra, 0x1C
    /* 25E4C 8003564C 2108E703 */  addu       $at, $ra, $a3
    /* 25E50 80035650 1E005F30 */  andi       $ra, $v0, 0x1E
    /* 25E54 80035654 0D00E013 */  beqz       $ra, .L8003568C
    /* 25E58 80035658 42E90200 */   srl       $sp, $v0, 5
    /* 25E5C 8003565C 801F1E3C */  lui        $fp, (0x1F8000E0 >> 16)
    /* 25E60 80035660 E000DE37 */  ori        $fp, $fp, (0x1F8000E0 & 0xFFFF)
    /* 25E64 80035664 0000DE8F */  lw         $fp, 0x0($fp)
    /* 25E68 80035668 0700BD33 */  andi       $sp, $sp, 0x7
    /* 25E6C 8003566C 06F0BE03 */  srlv       $fp, $fp, $sp
    /* 25E70 80035670 02EB0200 */  srl        $sp, $v0, 12
    /* 25E74 80035674 1F00BD33 */  andi       $sp, $sp, 0x1F
    /* 25E78 80035678 21E8DD03 */  addu       $sp, $fp, $sp
    /* 25E7C 8003567C 0100FE37 */  ori        $fp, $ra, 0x1
    /* 25E80 80035680 24E8BE03 */  and        $sp, $sp, $fp
    /* 25E84 80035684 80E81D00 */  sll        $sp, $sp, 2
    /* 25E88 80035688 2170AE03 */  addu       $t6, $sp, $t6
  .L8003568C:
    /* 25E8C 8003568C 0400D38D */  lw         $s3, 0x4($t6)
    /* 25E90 80035690 0000348C */  lw         $s4, 0x0($at)
    /* 25E94 80035694 82ED1300 */  srl        $sp, $s3, 22
    /* 25E98 80035698 C0E81D00 */  sll        $sp, $sp, 3
    /* 25E9C 8003569C 2170DD02 */  addu       $t6, $s6, $sp
    /* 25EA0 800356A0 0000D08D */  lw         $s0, 0x0($t6)
    /* 25EA4 800356A4 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 25EA8 800356A8 02AD1300 */  srl        $s5, $s3, 20
    /* 25EAC 800356AC 0300B532 */  andi       $s5, $s5, 0x3
    /* 25EB0 800356B0 C0E91500 */  sll        $sp, $s5, 7
    /* 25EB4 800356B4 1C009E32 */  andi       $fp, $s4, 0x1C
    /* 25EB8 800356B8 25E8BE03 */  or         $sp, $sp, $fp
    /* 25EBC 800356BC 82F41300 */  srl        $fp, $s3, 18
    /* 25EC0 800356C0 0300DE33 */  andi       $fp, $fp, 0x3
    /* 25EC4 800356C4 25E8BE03 */  or         $sp, $sp, $fp
    /* 25EC8 800356C8 60003E31 */  andi       $fp, $t1, 0x60
    /* 25ECC 800356CC 25E8BE03 */  or         $sp, $sp, $fp
    /* 25ED0 800356D0 00EC1D00 */  sll        $sp, $sp, 16
    /* 25ED4 800356D4 1F007E32 */  andi       $fp, $s3, 0x1F
    /* 25ED8 800356D8 80F01E00 */  sll        $fp, $fp, 2
    /* 25EDC 800356DC 80009F32 */  andi       $ra, $s4, 0x80
    /* 25EE0 800356E0 25F0DF03 */  or         $fp, $fp, $ra
    /* 25EE4 800356E4 00FA1E00 */  sll        $ra, $fp, 8
    /* 25EE8 800356E8 82F21300 */  srl        $fp, $s3, 10
    /* 25EEC 800356EC F800DE33 */  andi       $fp, $fp, 0xF8
    /* 25EF0 800356F0 06F0BE02 */  srlv       $fp, $fp, $s5
    /* 25EF4 800356F4 25A8DF03 */  or         $s5, $fp, $ra
    /* 25EF8 800356F8 02F41000 */  srl        $fp, $s0, 16
    /* 25EFC 800356FC 21F0D503 */  addu       $fp, $fp, $s5
    /* 25F00 80035700 25F8BE03 */  or         $ra, $sp, $fp
    /* 25F04 80035704 0F003D31 */  andi       $sp, $t1, 0xF
    /* 25F08 80035708 C01F7E32 */  andi       $fp, $s3, 0x1FC0
    /* 25F0C 8003570C 25E8BE03 */  or         $sp, $sp, $fp
    /* 25F10 80035710 02F11400 */  srl        $fp, $s4, 4
    /* 25F14 80035714 F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 25F18 80035718 25E8BE03 */  or         $sp, $sp, $fp
    /* 25F1C 8003571C 00EC1D00 */  sll        $sp, $sp, 16
    /* 25F20 80035720 FFFF1E32 */  andi       $fp, $s0, 0xFFFF
    /* 25F24 80035724 21F0D503 */  addu       $fp, $fp, $s5
    /* 25F28 80035728 25F0BE03 */  or         $fp, $sp, $fp
    /* 25F2C 8003572C 2170D501 */  addu       $t6, $t6, $s5
    /* 25F30 80035730 0C007EAD */  sw         $fp, 0xC($t3)
    /* 25F34 80035734 18007FAD */  sw         $ra, 0x18($t3)
    /* 25F38 80035738 24006EA5 */  sh         $t6, 0x24($t3)
    /* 25F3C 8003573C 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 25F40 80035740 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 25F44 80035744 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 25F48 80035748 21E8BE03 */  addu       $sp, $sp, $fp
    /* 25F4C 8003574C 21E8BF03 */  addu       $sp, $sp, $ra
    /* 25F50 80035750 42E91D00 */  srl        $sp, $sp, 5
    /* 25F54 80035754 80E81D00 */  sll        $sp, $sp, 2
    /* 25F58 80035758 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 25F5C 8003575C FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 25F60 80035760 2AF0A303 */  slt        $fp, $sp, $v1
    /* 25F64 80035764 0600C013 */  beqz       $fp, .L80035780
    /* 25F68 80035768 2170A300 */   addu      $t6, $a1, $v1
    /* 25F6C 8003576C 2118A003 */  addu       $v1, $sp, $zero
    /* 25F70 80035770 03006104 */  bgez       $v1, .L80035780
    /* 25F74 80035774 2170A300 */   addu      $t6, $a1, $v1
    /* 25F78 80035778 21180000 */  addu       $v1, $zero, $zero
    /* 25F7C 8003577C 2170A300 */  addu       $t6, $a1, $v1
  .L80035780:
    /* 25F80 80035780 0000DD8D */  lw         $sp, 0x0($t6)
    /* 25F84 80035784 24F07C01 */  and        $fp, $t3, $gp
    /* 25F88 80035788 0000DEAD */  sw         $fp, 0x0($t6)
    /* 25F8C 8003578C 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 25F90 80035790 25E8BF03 */  or         $sp, $sp, $ra
    /* 25F94 80035794 00007DAD */  sw         $sp, 0x0($t3)
    /* 25F98 80035798 28006B25 */  addiu      $t3, $t3, 0x28
    /* 25F9C 8003579C 21000104 */  bgez       $zero, .L80035824
    /* 25FA0 800357A0 00000000 */   nop
  .L800357A4:
    /* 25FA4 800357A4 08006CE9 */  swc2       $12, 0x8($t3)
    /* 25FA8 800357A8 10006DE9 */  swc2       $13, 0x10($t3)
    /* 25FAC 800357AC 18006EE9 */  swc2       $14, 0x18($t3)
    /* 25FB0 800357B0 0030123C */  lui        $s2, (0x30000000 >> 16)
    /* 25FB4 800357B4 25987202 */  or         $s3, $s3, $s2
    /* 25FB8 800357B8 040073AD */  sw         $s3, 0x4($t3)
    /* 25FBC 800357BC 0C0074AD */  sw         $s4, 0xC($t3)
    /* 25FC0 800357C0 140075AD */  sw         $s5, 0x14($t3)
    /* 25FC4 800357C4 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 25FC8 800357C8 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 25FCC 800357CC 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 25FD0 800357D0 21E8BE03 */  addu       $sp, $sp, $fp
    /* 25FD4 800357D4 21E8BF03 */  addu       $sp, $sp, $ra
    /* 25FD8 800357D8 42E91D00 */  srl        $sp, $sp, 5
    /* 25FDC 800357DC 80E81D00 */  sll        $sp, $sp, 2
    /* 25FE0 800357E0 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 25FE4 800357E4 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 25FE8 800357E8 2AF0A303 */  slt        $fp, $sp, $v1
    /* 25FEC 800357EC 0600C013 */  beqz       $fp, .L80035808
    /* 25FF0 800357F0 2170A300 */   addu      $t6, $a1, $v1
    /* 25FF4 800357F4 2118A003 */  addu       $v1, $sp, $zero
    /* 25FF8 800357F8 03006104 */  bgez       $v1, .L80035808
    /* 25FFC 800357FC 2170A300 */   addu      $t6, $a1, $v1
    /* 26000 80035800 21180000 */  addu       $v1, $zero, $zero
    /* 26004 80035804 2170A300 */  addu       $t6, $a1, $v1
  .L80035808:
    /* 26008 80035808 0000DD8D */  lw         $sp, 0x0($t6)
    /* 2600C 8003580C 24F07C01 */  and        $fp, $t3, $gp
    /* 26010 80035810 0000DEAD */  sw         $fp, 0x0($t6)
    /* 26014 80035814 00061E3C */  lui        $fp, (0x6000000 >> 16)
    /* 26018 80035818 25E8BE03 */  or         $sp, $sp, $fp
    /* 2601C 8003581C 00007DAD */  sw         $sp, 0x0($t3)
    /* 26020 80035820 1C006B25 */  addiu      $t3, $t3, 0x1C
  .L80035824:
    /* 26024 80035824 FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 26028 80035828 28FFA015 */  bnez       $t5, .L800354CC
    /* 2602C 8003582C 00004195 */   lhu       $at, 0x0($t2)
    /* 26030 80035830 00000000 */  nop
    /* 26034 80035834 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 26038 80035838 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2603C 8003583C 00000000 */  nop
    /* 26040 80035840 1000A18F */  lw         $at, 0x10($sp)
    /* 26044 80035844 00000000 */  nop
    /* 26048 80035848 00002BAC */  sw         $t3, 0x0($at)
    /* 2604C 8003584C 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 26050 80035850 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 26054 80035854 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 26058 80035858 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2605C 8003585C 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 26060 80035860 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 26064 80035864 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 26068 80035868 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2606C 8003586C 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 26070 80035870 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 26074 80035874 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 26078 80035878 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2607C 8003587C 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 26080 80035880 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 26084 80035884 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 26088 80035888 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2608C 8003588C 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 26090 80035890 0800E003 */  jr         $ra
    /* 26094 80035894 00000000 */   nop
endlabel Gte_RTransformWorlds
