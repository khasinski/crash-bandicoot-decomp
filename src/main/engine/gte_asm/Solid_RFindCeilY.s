.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Solid_RFindCeilY
    /* 295F8 80038DF8 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 295FC 80038DFC 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 29600 80038E00 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 29604 80038E04 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 29608 80038E08 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2960C 80038E0C 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 29610 80038E10 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 29614 80038E14 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 29618 80038E18 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2961C 80038E1C 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 29620 80038E20 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 29624 80038E24 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 29628 80038E28 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2962C 80038E2C 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 29630 80038E30 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 29634 80038E34 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 29638 80038E38 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2963C 80038E3C 1000A88F */  lw         $t0, 0x10($sp)
    /* 29640 80038E40 1400A98F */  lw         $t1, 0x14($sp)
    /* 29644 80038E44 1800AA8F */  lw         $t2, 0x18($sp)
    /* 29648 80038E48 0000DD8C */  lw         $sp, 0x0($a2)
    /* 2964C 80038E4C 0400DE8C */  lw         $fp, 0x4($a2)
    /* 29650 80038E50 0800DF8C */  lw         $ra, 0x8($a2)
    /* 29654 80038E54 0000EE8C */  lw         $t6, 0x0($a3)
    /* 29658 80038E58 0400EF8C */  lw         $t7, 0x4($a3)
    /* 2965C 80038E5C 0800F08C */  lw         $s0, 0x8($a3)
    /* 29660 80038E60 0C00F18C */  lw         $s1, 0xC($a3)
    /* 29664 80038E64 1000F28C */  lw         $s2, 0x10($a3)
    /* 29668 80038E68 1400F38C */  lw         $s3, 0x14($a3)
    /* 2966C 80038E6C 21380000 */  addu       $a3, $zero, $zero
    /* 29670 80038E70 21300000 */  addu       $a2, $zero, $zero
    /* 29674 80038E74 FFFF0825 */  addiu      $t0, $t0, -0x1
    /* 29678 80038E78 40400800 */  sll        $t0, $t0, 1
    /* 2967C 80038E7C FFFF2925 */  addiu      $t1, $t1, -0x1
    /* 29680 80038E80 40480900 */  sll        $t1, $t1, 1
  .L80038E84:
    /* 29684 80038E84 0000A18C */  lw         $at, 0x0($a1)
    /* 29688 80038E88 0400A28C */  lw         $v0, 0x4($a1)
    /* 2968C 80038E8C FFFF1C34 */  ori        $gp, $zero, 0xFFFF
    /* 29690 80038E90 24183C00 */  and        $v1, $at, $gp
    /* 29694 80038E94 46007C10 */  beq        $v1, $gp, .L80038FB0
    /* 29698 80038E98 00000000 */   nop
    /* 2969C 80038E9C 0E006014 */  bnez       $v1, .L80038ED8
    /* 296A0 80038EA0 00000000 */   nop
    /* 296A4 80038EA4 02A40100 */  srl        $s4, $at, 16
    /* 296A8 80038EA8 00A21400 */  sll        $s4, $s4, 8
    /* 296AC 80038EAC FFFF5530 */  andi       $s5, $v0, 0xFFFF
    /* 296B0 80038EB0 00AA1500 */  sll        $s5, $s5, 8
    /* 296B4 80038EB4 02B40200 */  srl        $s6, $v0, 16
    /* 296B8 80038EB8 00B21600 */  sll        $s6, $s6, 8
    /* 296BC 80038EBC 0800A18C */  lw         $at, 0x8($a1)
    /* 296C0 80038EC0 0C00A28C */  lw         $v0, 0xC($a1)
    /* 296C4 80038EC4 02BC0100 */  srl        $s7, $at, 16
    /* 296C8 80038EC8 FFFF5830 */  andi       $t8, $v0, 0xFFFF
    /* 296CC 80038ECC 02CC0200 */  srl        $t9, $v0, 16
    /* 296D0 80038ED0 ECFF0104 */  bgez       $zero, .L80038E84
    /* 296D4 80038ED4 1000A524 */   addiu     $a1, $a1, 0x10
  .L80038ED8:
    /* 296D8 80038ED8 F8FF2330 */  andi       $v1, $at, 0xFFF8
    /* 296DC 80038EDC 82180300 */  srl        $v1, $v1, 2
    /* 296E0 80038EE0 01006334 */  ori        $v1, $v1, 0x1
    /* 296E4 80038EE4 0E007C30 */  andi       $gp, $v1, 0xE
    /* 296E8 80038EE8 03008813 */  beq        $gp, $t0, .L80038EF8
    /* 296EC 80038EEC 00000000 */   nop
    /* 296F0 80038EF0 2D008917 */  bne        $gp, $t1, .L80038FA8
    /* 296F4 80038EF4 00000000 */   nop
  .L80038EF8:
    /* 296F8 80038EF8 07003C30 */  andi       $gp, $at, 0x7
    /* 296FC 80038EFC 025C0100 */  srl        $t3, $at, 16
    /* 29700 80038F00 FFFF4C30 */  andi       $t4, $v0, 0xFFFF
    /* 29704 80038F04 026C0200 */  srl        $t5, $v0, 16
    /* 29708 80038F08 005C0B00 */  sll        $t3, $t3, 16
    /* 2970C 80038F0C 035B0B00 */  sra        $t3, $t3, 12
    /* 29710 80038F10 00640C00 */  sll        $t4, $t4, 16
    /* 29714 80038F14 03630C00 */  sra        $t4, $t4, 12
    /* 29718 80038F18 006C0D00 */  sll        $t5, $t5, 16
    /* 2971C 80038F1C 036B0D00 */  sra        $t5, $t5, 12
    /* 29720 80038F20 2158AB03 */  addu       $t3, $sp, $t3
    /* 29724 80038F24 2160CC03 */  addu       $t4, $fp, $t4
    /* 29728 80038F28 2168ED03 */  addu       $t5, $ra, $t5
    /* 2972C 80038F2C 21108001 */  addu       $v0, $t4, $zero
    /* 29730 80038F30 2A082B02 */  slt        $at, $s1, $t3
    /* 29734 80038F34 1C002014 */  bnez       $at, .L80038FA8
    /* 29738 80038F38 2A084C02 */   slt       $at, $s2, $t4
    /* 2973C 80038F3C 1A002014 */  bnez       $at, .L80038FA8
    /* 29740 80038F40 2A086D02 */   slt       $at, $s3, $t5
    /* 29744 80038F44 18002014 */  bnez       $at, .L80038FA8
    /* 29748 80038F48 2A08FC02 */   slt       $at, $s7, $gp
    /* 2974C 80038F4C 02002014 */  bnez       $at, .L80038F58
    /* 29750 80038F50 0608F402 */   srlv      $at, $s4, $s7
    /* 29754 80038F54 06089403 */  srlv       $at, $s4, $gp
  .L80038F58:
    /* 29758 80038F58 21586101 */  addu       $t3, $t3, $at
    /* 2975C 80038F5C 2A081C03 */  slt        $at, $t8, $gp
    /* 29760 80038F60 02002014 */  bnez       $at, .L80038F6C
    /* 29764 80038F64 06081503 */   srlv      $at, $s5, $t8
    /* 29768 80038F68 06089503 */  srlv       $at, $s5, $gp
  .L80038F6C:
    /* 2976C 80038F6C 21608101 */  addu       $t4, $t4, $at
    /* 29770 80038F70 2A083C03 */  slt        $at, $t9, $gp
    /* 29774 80038F74 02002014 */  bnez       $at, .L80038F80
    /* 29778 80038F78 06083603 */   srlv      $at, $s6, $t9
    /* 2977C 80038F7C 06089603 */  srlv       $at, $s6, $gp
  .L80038F80:
    /* 29780 80038F80 2168A101 */  addu       $t5, $t5, $at
    /* 29784 80038F84 2A086E01 */  slt        $at, $t3, $t6
    /* 29788 80038F88 07002014 */  bnez       $at, .L80038FA8
    /* 2978C 80038F8C 2A088F01 */   slt       $at, $t4, $t7
    /* 29790 80038F90 05002014 */  bnez       $at, .L80038FA8
    /* 29794 80038F94 2A08B001 */   slt       $at, $t5, $s0
    /* 29798 80038F98 03002014 */  bnez       $at, .L80038FA8
    /* 2979C 80038F9C 00000000 */   nop
    /* 297A0 80038FA0 0100C624 */  addiu      $a2, $a2, 0x1
    /* 297A4 80038FA4 2138E200 */  addu       $a3, $a3, $v0
  .L80038FA8:
    /* 297A8 80038FA8 B6FF0104 */  bgez       $zero, .L80038E84
    /* 297AC 80038FAC 0800A524 */   addiu     $a1, $a1, 0x8
  .L80038FB0:
    /* 297B0 80038FB0 1600C010 */  beqz       $a2, .L8003900C
    /* 297B4 80038FB4 00000000 */   nop
    /* 297B8 80038FB8 1A00E600 */  div        $zero, $a3, $a2
    /* 297BC 80038FBC 12100000 */  mflo       $v0
    /* 297C0 80038FC0 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 297C4 80038FC4 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 297C8 80038FC8 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 297CC 80038FCC 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 297D0 80038FD0 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 297D4 80038FD4 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 297D8 80038FD8 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 297DC 80038FDC 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 297E0 80038FE0 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 297E4 80038FE4 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 297E8 80038FE8 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 297EC 80038FEC 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 297F0 80038FF0 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 297F4 80038FF4 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 297F8 80038FF8 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 297FC 80038FFC 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 29800 80039000 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 29804 80039004 0800E003 */  jr         $ra
    /* 29808 80039008 00000000 */   nop
  .L8003900C:
    /* 2980C 8003900C 21104001 */  addu       $v0, $t2, $zero
    /* 29810 80039010 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 29814 80039014 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 29818 80039018 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2981C 8003901C 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 29820 80039020 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 29824 80039024 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 29828 80039028 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2982C 8003902C 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 29830 80039030 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 29834 80039034 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 29838 80039038 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2983C 8003903C 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 29840 80039040 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 29844 80039044 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 29848 80039048 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2984C 8003904C 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 29850 80039050 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 29854 80039054 0800E003 */  jr         $ra
    /* 29858 80039058 00000000 */   nop
endlabel Solid_RFindCeilY
