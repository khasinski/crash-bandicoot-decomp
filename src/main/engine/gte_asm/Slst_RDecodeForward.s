.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Slst_RDecodeForward
    /* 23CA0 800334A0 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 23CA4 800334A4 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 23CA8 800334A8 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 23CAC 800334AC 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 23CB0 800334B0 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 23CB4 800334B4 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 23CB8 800334B8 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 23CBC 800334BC 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 23CC0 800334C0 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 23CC4 800334C4 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 23CC8 800334C8 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 23CCC 800334CC 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 23CD0 800334D0 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 23CD4 800334D4 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 23CD8 800334D8 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 23CDC 800334DC 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 23CE0 800334E0 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 23CE4 800334E4 FFFF1634 */  ori        $s6, $zero, 0xFFFF
    /* 23CE8 800334E8 03801F3C */  lui        $ra, %hi(.L80033748)
    /* 23CEC 800334EC 4837FF27 */  addiu      $ra, $ra, %lo(.L80033748)
    /* 23CF0 800334F0 21100000 */  addu       $v0, $zero, $zero
    /* 23CF4 800334F4 21680000 */  addu       $t5, $zero, $zero
    /* 23CF8 800334F8 08009024 */  addiu      $s0, $a0, 0x8
    /* 23CFC 800334FC 04008194 */  lhu        $at, 0x4($a0)
    /* 23D00 80033500 00000000 */  nop
    /* 23D04 80033504 40080100 */  sll        $at, $at, 1
    /* 23D08 80033508 04002124 */  addiu      $at, $at, 0x4
    /* 23D0C 8003350C 20E88100 */  add        $sp, $a0, $at /* handwritten instruction */
    /* 23D10 80033510 2178A003 */  addu       $t7, $sp, $zero
    /* 23D14 80033514 06008194 */  lhu        $at, 0x6($a0)
    /* 23D18 80033518 00000000 */  nop
    /* 23D1C 8003351C 40080100 */  sll        $at, $at, 1
    /* 23D20 80033520 04002124 */  addiu      $at, $at, 0x4
    /* 23D24 80033524 20F08100 */  add        $fp, $a0, $at /* handwritten instruction */
    /* 23D28 80033528 0400AE24 */  addiu      $t6, $a1, 0x4
    /* 23D2C 8003352C 0000BC94 */  lhu        $gp, 0x0($a1)
    /* 23D30 80033530 0400D124 */  addiu      $s1, $a2, 0x4
    /* 23D34 80033534 00000196 */  lhu        $at, 0x0($s0)
    /* 23D38 80033538 02001026 */  addiu      $s0, $s0, 0x2
    /* 23D3C 8003353C 2AC81D02 */  slt        $t9, $s0, $sp
    /* 23D40 80033540 08002013 */  beqz       $t9, .L80033564
    /* 23D44 80033544 21580000 */   addu      $t3, $zero, $zero
    /* 23D48 80033548 21C02000 */  addu       $t8, $at, $zero
    /* 23D4C 8003354C 05001613 */  beq        $t8, $s6, .L80033564
    /* 23D50 80033550 FF0F0933 */   andi      $t1, $t8, 0xFFF
    /* 23D54 80033554 00F00B33 */  andi       $t3, $t8, 0xF000
    /* 23D58 80033558 025B0B00 */  srl        $t3, $t3, 12
    /* 23D5C 8003355C 02000104 */  bgez       $zero, .L80033568
    /* 23D60 80033560 01006B25 */   addiu     $t3, $t3, 0x1
  .L80033564:
    /* 23D64 80033564 004A1600 */  sll        $t1, $s6, 8
  .L80033568:
    /* 23D68 80033568 03006019 */  blez       $t3, .L80033578
    /* 23D6C 8003356C 00000000 */   nop
    /* 23D70 80033570 00001896 */  lhu        $t8, 0x0($s0)
    /* 23D74 80033574 02001026 */  addiu      $s0, $s0, 0x2
  .L80033578:
    /* 23D78 80033578 0000E195 */  lhu        $at, 0x0($t7)
    /* 23D7C 8003357C 0200EF25 */  addiu      $t7, $t7, 0x2
    /* 23D80 80033580 2AC8FE01 */  slt        $t9, $t7, $fp
    /* 23D84 80033584 08002013 */  beqz       $t9, .L800335A8
    /* 23D88 80033588 21500000 */   addu      $t2, $zero, $zero
    /* 23D8C 8003358C 21B82000 */  addu       $s7, $at, $zero
    /* 23D90 80033590 0500F612 */  beq        $s7, $s6, .L800335A8
    /* 23D94 80033594 FF0FE832 */   andi      $t0, $s7, 0xFFF
    /* 23D98 80033598 00F0EA32 */  andi       $t2, $s7, 0xF000
    /* 23D9C 8003359C 02530A00 */  srl        $t2, $t2, 12
    /* 23DA0 800335A0 02000104 */  bgez       $zero, .L800335AC
    /* 23DA4 800335A4 01004A25 */   addiu     $t2, $t2, 0x1
  .L800335A8:
    /* 23DA8 800335A8 00421600 */  sll        $t0, $s6, 8
  .L800335AC:
    /* 23DAC 800335AC 03004019 */  blez       $t2, .L800335BC
    /* 23DB0 800335B0 00000000 */   nop
    /* 23DB4 800335B4 0000F795 */  lhu        $s7, 0x0($t7)
    /* 23DB8 800335B8 0200EF25 */  addiu      $t7, $t7, 0x2
  .L800335BC:
    /* 23DBC 800335BC 21180000 */  addu       $v1, $zero, $zero
  .L800335C0:
    /* 23DC0 800335C0 2A087C00 */  slt        $at, $v1, $gp
    /* 23DC4 800335C4 2A380B00 */  slt        $a3, $zero, $t3
    /* 23DC8 800335C8 24082700 */  and        $at, $at, $a3
    /* 23DCC 800335CC 22002010 */  beqz       $at, .L80033658
    /* 23DD0 800335D0 FFFF2121 */   addi      $at, $t1, -0x1 /* handwritten instruction */
    /* 23DD4 800335D4 22082300 */  sub        $at, $at, $v1 /* handwritten instruction */
    /* 23DD8 800335D8 1F002014 */  bnez       $at, .L80033658
    /* 23DDC 800335DC 00000000 */   nop
    /* 23DE0 800335E0 FFFF6B21 */  addi       $t3, $t3, -0x1 /* handwritten instruction */
    /* 23DE4 800335E4 0100AD25 */  addiu      $t5, $t5, 0x1
    /* 23DE8 800335E8 01006324 */  addiu      $v1, $v1, 0x1
    /* 23DEC 800335EC 0200CE25 */  addiu      $t6, $t6, 0x2
    /* 23DF0 800335F0 06006019 */  blez       $t3, .L8003360C
    /* 23DF4 800335F4 00000000 */   nop
    /* 23DF8 800335F8 00001896 */  lhu        $t8, 0x0($s0)
    /* 23DFC 800335FC 02001026 */  addiu      $s0, $s0, 0x2
    /* 23E00 80033600 C20B1800 */  srl        $at, $t8, 15
    /* 23E04 80033604 50000104 */  bgez       $zero, .L80033748
    /* 23E08 80033608 20482101 */   add       $t1, $t1, $at /* handwritten instruction */
  .L8003360C:
    /* 23E0C 8003360C 00000196 */  lhu        $at, 0x0($s0)
    /* 23E10 80033610 02001026 */  addiu      $s0, $s0, 0x2
    /* 23E14 80033614 2AC81D02 */  slt        $t9, $s0, $sp
    /* 23E18 80033618 08002013 */  beqz       $t9, .L8003363C
    /* 23E1C 8003361C 21580000 */   addu      $t3, $zero, $zero
    /* 23E20 80033620 21C02000 */  addu       $t8, $at, $zero
    /* 23E24 80033624 05001613 */  beq        $t8, $s6, .L8003363C
    /* 23E28 80033628 FF0F0933 */   andi      $t1, $t8, 0xFFF
    /* 23E2C 8003362C 00F00B33 */  andi       $t3, $t8, 0xF000
    /* 23E30 80033630 025B0B00 */  srl        $t3, $t3, 12
    /* 23E34 80033634 02000104 */  bgez       $zero, .L80033640
    /* 23E38 80033638 01006B25 */   addiu     $t3, $t3, 0x1
  .L8003363C:
    /* 23E3C 8003363C 004A1600 */  sll        $t1, $s6, 8
  .L80033640:
    /* 23E40 80033640 41006019 */  blez       $t3, .L80033748
    /* 23E44 80033644 00000000 */   nop
    /* 23E48 80033648 00001896 */  lhu        $t8, 0x0($s0)
    /* 23E4C 8003364C 02001026 */  addiu      $s0, $s0, 0x2
    /* 23E50 80033650 3D000104 */  bgez       $zero, .L80033748
    /* 23E54 80033654 00000000 */   nop
  .L80033658:
    /* 23E58 80033658 22004019 */  blez       $t2, .L800336E4
    /* 23E5C 8003365C 20080D01 */   add       $at, $t0, $t5 /* handwritten instruction */
    /* 23E60 80033660 22082300 */  sub        $at, $at, $v1 /* handwritten instruction */
    /* 23E64 80033664 1F002014 */  bnez       $at, .L800336E4
    /* 23E68 80033668 FF7FE132 */   andi      $at, $s7, 0x7FFF
    /* 23E6C 8003366C 000021A6 */  sh         $at, 0x0($s1)
    /* 23E70 80033670 02003126 */  addiu      $s1, $s1, 0x2
    /* 23E74 80033674 01004224 */  addiu      $v0, $v0, 0x1
    /* 23E78 80033678 FFFF4A21 */  addi       $t2, $t2, -0x1 /* handwritten instruction */
    /* 23E7C 8003367C 06004019 */  blez       $t2, .L80033698
    /* 23E80 80033680 00000000 */   nop
    /* 23E84 80033684 0000F795 */  lhu        $s7, 0x0($t7)
    /* 23E88 80033688 0200EF25 */  addiu      $t7, $t7, 0x2
    /* 23E8C 8003368C C20B1700 */  srl        $at, $s7, 15
    /* 23E90 80033690 2D000104 */  bgez       $zero, .L80033748
    /* 23E94 80033694 20400101 */   add       $t0, $t0, $at /* handwritten instruction */
  .L80033698:
    /* 23E98 80033698 0000E195 */  lhu        $at, 0x0($t7)
    /* 23E9C 8003369C 0200EF25 */  addiu      $t7, $t7, 0x2
    /* 23EA0 800336A0 2AC8FE01 */  slt        $t9, $t7, $fp
    /* 23EA4 800336A4 08002013 */  beqz       $t9, .L800336C8
    /* 23EA8 800336A8 21500000 */   addu      $t2, $zero, $zero
    /* 23EAC 800336AC 21B82000 */  addu       $s7, $at, $zero
    /* 23EB0 800336B0 0500F612 */  beq        $s7, $s6, .L800336C8
    /* 23EB4 800336B4 FF0FE832 */   andi      $t0, $s7, 0xFFF
    /* 23EB8 800336B8 00F0EA32 */  andi       $t2, $s7, 0xF000
    /* 23EBC 800336BC 02530A00 */  srl        $t2, $t2, 12
    /* 23EC0 800336C0 02000104 */  bgez       $zero, .L800336CC
    /* 23EC4 800336C4 01004A25 */   addiu     $t2, $t2, 0x1
  .L800336C8:
    /* 23EC8 800336C8 00421600 */  sll        $t0, $s6, 8
  .L800336CC:
    /* 23ECC 800336CC 1E004019 */  blez       $t2, .L80033748
    /* 23ED0 800336D0 00000000 */   nop
    /* 23ED4 800336D4 0000F795 */  lhu        $s7, 0x0($t7)
    /* 23ED8 800336D8 0200EF25 */  addiu      $t7, $t7, 0x2
    /* 23EDC 800336DC 1A000104 */  bgez       $zero, .L80033748
    /* 23EE0 800336E0 00000000 */   nop
  .L800336E4:
    /* 23EE4 800336E4 2A087C00 */  slt        $at, $v1, $gp
    /* 23EE8 800336E8 17002010 */  beqz       $at, .L80033748
    /* 23EEC 800336EC 22082301 */   sub       $at, $t1, $v1 /* handwritten instruction */
    /* 23EF0 800336F0 FFFF2120 */  addi       $at, $at, -0x1 /* handwritten instruction */
    /* 23EF4 800336F4 20380D01 */  add        $a3, $t0, $t5 /* handwritten instruction */
    /* 23EF8 800336F8 2238E300 */  sub        $a3, $a3, $v1 /* handwritten instruction */
    /* 23EFC 800336FC 2AC82700 */  slt        $t9, $at, $a3
    /* 23F00 80033700 02002017 */  bnez       $t9, .L8003370C
    /* 23F04 80033704 00000000 */   nop
    /* 23F08 80033708 2108E000 */  addu       $at, $a3, $zero
  .L8003370C:
    /* 23F0C 8003370C 22388303 */  sub        $a3, $gp, $v1 /* handwritten instruction */
    /* 23F10 80033710 FFFFE720 */  addi       $a3, $a3, -0x1 /* handwritten instruction */
    /* 23F14 80033714 2AC82700 */  slt        $t9, $at, $a3
    /* 23F18 80033718 02002017 */  bnez       $t9, .L80033724
    /* 23F1C 8003371C 00000000 */   nop
    /* 23F20 80033720 2108E000 */  addu       $at, $a3, $zero
  .L80033724:
    /* 23F24 80033724 02002728 */  slti       $a3, $at, 0x2
    /* 23F28 80033728 5A01E010 */  beqz       $a3, .L80033C94
    /* 23F2C 8003372C 00000000 */   nop
    /* 23F30 80033730 0000C195 */  lhu        $at, 0x0($t6)
    /* 23F34 80033734 0200CE25 */  addiu      $t6, $t6, 0x2
    /* 23F38 80033738 000021A6 */  sh         $at, 0x0($s1)
    /* 23F3C 8003373C 02003126 */  addiu      $s1, $s1, 0x2
    /* 23F40 80033740 01004224 */  addiu      $v0, $v0, 0x1
    /* 23F44 80033744 01006324 */  addiu      $v1, $v1, 0x1
  .L80033748:
    /* 23F48 80033748 2A087C00 */  slt        $at, $v1, $gp
    /* 23F4C 8003374C 2A380A00 */  slt        $a3, $zero, $t2
    /* 23F50 80033750 25082700 */  or         $at, $at, $a3
    /* 23F54 80033754 2A380B00 */  slt        $a3, $zero, $t3
    /* 23F58 80033758 25082700 */  or         $at, $at, $a3
    /* 23F5C 8003375C 98FF2014 */  bnez       $at, .L800335C0
    /* 23F60 80033760 00000000 */   nop
    /* 23F64 80033764 06008194 */  lhu        $at, 0x6($a0)
    /* 23F68 80033768 00000000 */  nop
    /* 23F6C 8003376C 40080100 */  sll        $at, $at, 1
    /* 23F70 80033770 04002124 */  addiu      $at, $at, 0x4
    /* 23F74 80033774 20708100 */  add        $t6, $a0, $at /* handwritten instruction */
    /* 23F78 80033778 00008194 */  lhu        $at, 0x0($a0)
    /* 23F7C 8003377C 00000000 */  nop
    /* 23F80 80033780 40080100 */  sll        $at, $at, 1
    /* 23F84 80033784 04002124 */  addiu      $at, $at, 0x4
    /* 23F88 80033788 20788100 */  add        $t7, $a0, $at /* handwritten instruction */
  .L8003378C:
    /* 23F8C 8003378C 2A38CF01 */  slt        $a3, $t6, $t7
    /* 23F90 80033790 2500E010 */  beqz       $a3, .L80033828
    /* 23F94 80033794 00000000 */   nop
    /* 23F98 80033798 0000C195 */  lhu        $at, 0x0($t6)
    /* 23F9C 8003379C 0200CE25 */  addiu      $t6, $t6, 0x2
    /* 23FA0 800337A0 21003610 */  beq        $at, $s6, .L80033828
    /* 23FA4 800337A4 00802730 */   andi      $a3, $at, 0x8000
    /* 23FA8 800337A8 0400E010 */  beqz       $a3, .L800337BC
    /* 23FAC 800337AC 00783330 */   andi      $s3, $at, 0x7800
    /* 23FB0 800337B0 C29A1300 */  srl        $s3, $s3, 11
    /* 23FB4 800337B4 0E000104 */  bgez       $zero, .L800337F0
    /* 23FB8 800337B8 FF073430 */   andi      $s4, $at, 0x7FF
  .L800337BC:
    /* 23FBC 800337BC 00C02730 */  andi       $a3, $at, 0xC000
    /* 23FC0 800337C0 00401924 */  addiu      $t9, $zero, 0x4000
    /* 23FC4 800337C4 0600F914 */  bne        $a3, $t9, .L800337E0
    /* 23FC8 800337C8 1F003330 */   andi      $s3, $at, 0x1F
    /* 23FCC 800337CC 10007326 */  addiu      $s3, $s3, 0x10
    /* 23FD0 800337D0 E03F2730 */  andi       $a3, $at, 0x3FE0
    /* 23FD4 800337D4 42390700 */  srl        $a3, $a3, 5
    /* 23FD8 800337D8 05000104 */  bgez       $zero, .L800337F0
    /* 23FDC 800337DC 21A08702 */   addu      $s4, $s4, $a3
  .L800337E0:
    /* 23FE0 800337E0 FF0F3430 */  andi       $s4, $at, 0xFFF
    /* 23FE4 800337E4 0000C195 */  lhu        $at, 0x0($t6)
    /* 23FE8 800337E8 0200CE25 */  addiu      $t6, $t6, 0x2
    /* 23FEC 800337EC FF0F3330 */  andi       $s3, $at, 0xFFF
  .L800337F0:
    /* 23FF0 800337F0 21C88002 */  addu       $t9, $s4, $zero
    /* 23FF4 800337F4 01007326 */  addiu      $s3, $s3, 0x1
    /* 23FF8 800337F8 21987402 */  addu       $s3, $s3, $s4
    /* 23FFC 800337FC 40981300 */  sll        $s3, $s3, 1
    /* 24000 80033800 40A01400 */  sll        $s4, $s4, 1
    /* 24004 80033804 0400C124 */  addiu      $at, $a2, 0x4
    /* 24008 80033808 21A08102 */  addu       $s4, $s4, $at
    /* 2400C 8003380C 21986102 */  addu       $s3, $s3, $at
    /* 24010 80033810 00008196 */  lhu        $at, 0x0($s4)
    /* 24014 80033814 00006796 */  lhu        $a3, 0x0($s3)
    /* 24018 80033818 000061A6 */  sh         $at, 0x0($s3)
    /* 2401C 8003381C 000087A6 */  sh         $a3, 0x0($s4)
    /* 24020 80033820 DAFF0104 */  bgez       $zero, .L8003378C
    /* 24024 80033824 21A02003 */   addu      $s4, $t9, $zero
  .L80033828:
    /* 24028 80033828 0000C2A4 */  sh         $v0, 0x0($a2)
    /* 2402C 8003382C 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 24030 80033830 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 24034 80033834 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 24038 80033838 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2403C 8003383C 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 24040 80033840 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 24044 80033844 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 24048 80033848 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2404C 8003384C 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 24050 80033850 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 24054 80033854 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 24058 80033858 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2405C 8003385C 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 24060 80033860 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 24064 80033864 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 24068 80033868 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2406C 8003386C 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 24070 80033870 0800E003 */  jr         $ra
    /* 24074 80033874 00000000 */   nop
endlabel Slst_RDecodeForward
