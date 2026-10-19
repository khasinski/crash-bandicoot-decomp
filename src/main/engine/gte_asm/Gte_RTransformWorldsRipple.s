.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformWorldsRipple
    /* 26610 80035E10 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 26614 80035E14 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 26618 80035E18 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2661C 80035E1C 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 26620 80035E20 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 26624 80035E24 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 26628 80035E28 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2662C 80035E2C 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 26630 80035E30 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 26634 80035E34 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 26638 80035E38 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2663C 80035E3C 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 26640 80035E40 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 26644 80035E44 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 26648 80035E48 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2664C 80035E4C 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 26650 80035E50 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 26654 80035E54 1000AF8F */  lw         $t7, 0x10($sp)
    /* 26658 80035E58 1400B68F */  lw         $s6, 0x14($sp)
    /* 2665C 80035E5C 0000EB8D */  lw         $t3, 0x0($t7)
    /* 26660 80035E60 801F1D3C */  lui        $sp, (0x1F8000E0 >> 16)
    /* 26664 80035E64 E000BD37 */  ori        $sp, $sp, (0x1F8000E0 & 0xFFFF)
    /* 26668 80035E68 0000A7AF */  sw         $a3, 0x0($sp)
    /* 2666C 80035E6C FF001C3C */  lui        $gp, (0xFFFFFF >> 16)
    /* 26670 80035E70 FFFF9C37 */  ori        $gp, $gp, (0xFFFFFF & 0xFFFF)
    /* 26674 80035E74 60000F34 */  ori        $t7, $zero, 0x60
    /* 26678 80035E78 801F083C */  lui        $t0, (0x1F800100 >> 16)
    /* 2667C 80035E7C 00010835 */  ori        $t0, $t0, (0x1F800100 & 0xFFFF)
    /* 26680 80035E80 00008D8C */  lw         $t5, 0x0($a0)
    /* 26684 80035E84 02008A24 */  addiu      $t2, $a0, 0x2
    /* 26688 80035E88 21504D01 */  addu       $t2, $t2, $t5
    /* 2668C 80035E8C 21504D01 */  addu       $t2, $t2, $t5
    /* 26690 80035E90 FFFF0C34 */  ori        $t4, $zero, 0xFFFF
    /* 26694 80035E94 0002043C */  lui        $a0, (0x2000000 >> 16)
    /* 26698 80035E98 00004195 */  lhu        $at, 0x0($t2)
    /* 2669C 80035E9C 80300600 */  sll        $a2, $a2, 2
    /* 266A0 80035EA0 FC1F0334 */  ori        $v1, $zero, 0x1FFC
  .L80035EA4:
    /* 266A4 80035EA4 FEFF4A25 */  addiu      $t2, $t2, -0x2
    /* 266A8 80035EA8 02F30100 */  srl        $fp, $at, 12
    /* 266AC 80035EAC 0E00CC13 */  beq        $fp, $t4, .L80035EE8
    /* 266B0 80035EB0 FF0F2130 */   andi      $at, $at, 0xFFF
    /* 266B4 80035EB4 2160C003 */  addu       $t4, $fp, $zero
    /* 266B8 80035EB8 80F90C00 */  sll        $ra, $t4, 6
    /* 266BC 80035EBC 2110E803 */  addu       $v0, $ra, $t0
    /* 266C0 80035EC0 04005D8C */  lw         $sp, 0x4($v0)
    /* 266C4 80035EC4 08005E8C */  lw         $fp, 0x8($v0)
    /* 266C8 80035EC8 0C005F8C */  lw         $ra, 0xC($v0)
    /* 266CC 80035ECC 0028DD48 */  ctc2       $sp, $5 /* handwritten instruction */
    /* 266D0 80035ED0 0030DE48 */  ctc2       $fp, $6 /* handwritten instruction */
    /* 266D4 80035ED4 0038DF48 */  ctc2       $ra, $7 /* handwritten instruction */
    /* 266D8 80035ED8 1400578C */  lw         $s7, 0x14($v0)
    /* 266DC 80035EDC 1800588C */  lw         $t8, 0x18($v0)
    /* 266E0 80035EE0 1C00598C */  lw         $t9, 0x1C($v0)
    /* 266E4 80035EE4 20004724 */  addiu      $a3, $v0, 0x20
  .L80035EE8:
    /* 266E8 80035EE8 C0080100 */  sll        $at, $at, 3
    /* 266EC 80035EEC 2148E102 */  addu       $t1, $s7, $at
    /* 266F0 80035EF0 0000218D */  lw         $at, 0x0($t1)
    /* 266F4 80035EF4 0400298D */  lw         $t1, 0x4($t1)
    /* 266F8 80035EF8 00130100 */  sll        $v0, $at, 12
    /* 266FC 80035EFC FF003D31 */  andi       $sp, $t1, 0xFF
    /* 26700 80035F00 25105D00 */  or         $v0, $v0, $sp
    /* 26704 80035F04 42840900 */  srl        $s0, $t1, 17
    /* 26708 80035F08 F87F1032 */  andi       $s0, $s0, 0x7FF8
    /* 2670C 80035F0C 21801802 */  addu       $s0, $s0, $t8
    /* 26710 80035F10 42890900 */  srl        $s1, $t1, 5
    /* 26714 80035F14 F87F3132 */  andi       $s1, $s1, 0x7FF8
    /* 26718 80035F18 21883802 */  addu       $s1, $s1, $t8
    /* 2671C 80035F1C 42940100 */  srl        $s2, $at, 17
    /* 26720 80035F20 F87F5232 */  andi       $s2, $s2, 0x7FF8
    /* 26724 80035F24 21905802 */  addu       $s2, $s2, $t8
    /* 26728 80035F28 0000138E */  lw         $s3, 0x0($s0)
    /* 2672C 80035F2C 0400108E */  lw         $s0, 0x4($s0)
    /* 26730 80035F30 0000348E */  lw         $s4, 0x0($s1)
    /* 26734 80035F34 0400318E */  lw         $s1, 0x4($s1)
    /* 26738 80035F38 0000558E */  lw         $s5, 0x0($s2)
    /* 2673C 80035F3C 0400528E */  lw         $s2, 0x4($s2)
    /* 26740 80035F40 F8FF013C */  lui        $at, (0xFFF8FFF8 >> 16)
    /* 26744 80035F44 F8FF2134 */  ori        $at, $at, (0xFFF8FFF8 & 0xFFFF)
    /* 26748 80035F48 801F1F3C */  lui        $ra, (0x1F800048 >> 16)
    /* 2674C 80035F4C 4800FF37 */  ori        $ra, $ra, (0x1F800048 & 0xFFFF)
    /* 26750 80035F50 01001D32 */  andi       $sp, $s0, 0x1
    /* 26754 80035F54 1000A013 */  beqz       $sp, .L80035F98
    /* 26758 80035F58 24E80102 */   and       $sp, $s0, $at
    /* 2675C 80035F5C C2F41D00 */  srl        $fp, $sp, 19
    /* 26760 80035F60 F8FFA933 */  andi       $t1, $sp, 0xFFF8
    /* 26764 80035F64 C2480900 */  srl        $t1, $t1, 3
    /* 26768 80035F68 21F0C903 */  addu       $fp, $fp, $t1
    /* 2676C 80035F6C 0F00DE33 */  andi       $fp, $fp, 0xF
    /* 26770 80035F70 80F01E00 */  sll        $fp, $fp, 2
    /* 26774 80035F74 2148DF03 */  addu       $t1, $fp, $ra
    /* 26778 80035F78 00003E8D */  lw         $fp, 0x0($t1)
    /* 2677C 80035F7C 00000000 */  nop
    /* 26780 80035F80 034C1D00 */  sra        $t1, $sp, 16
    /* 26784 80035F84 21483E01 */  addu       $t1, $t1, $fp
    /* 26788 80035F88 004C0900 */  sll        $t1, $t1, 16
    /* 2678C 80035F8C 00F41000 */  sll        $fp, $s0, 16
    /* 26790 80035F90 02F41E00 */  srl        $fp, $fp, 16
    /* 26794 80035F94 25E8C903 */  or         $sp, $fp, $t1
  .L80035F98:
    /* 26798 80035F98 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 2679C 80035F9C 01003D32 */  andi       $sp, $s1, 0x1
    /* 267A0 80035FA0 1000A013 */  beqz       $sp, .L80035FE4
    /* 267A4 80035FA4 24E82102 */   and       $sp, $s1, $at
    /* 267A8 80035FA8 C2F41D00 */  srl        $fp, $sp, 19
    /* 267AC 80035FAC F8FFA933 */  andi       $t1, $sp, 0xFFF8
    /* 267B0 80035FB0 C2480900 */  srl        $t1, $t1, 3
    /* 267B4 80035FB4 21F0C903 */  addu       $fp, $fp, $t1
    /* 267B8 80035FB8 0F00DE33 */  andi       $fp, $fp, 0xF
    /* 267BC 80035FBC 80F01E00 */  sll        $fp, $fp, 2
    /* 267C0 80035FC0 2148DF03 */  addu       $t1, $fp, $ra
    /* 267C4 80035FC4 00003E8D */  lw         $fp, 0x0($t1)
    /* 267C8 80035FC8 00000000 */  nop
    /* 267CC 80035FCC 034C1D00 */  sra        $t1, $sp, 16
    /* 267D0 80035FD0 21483E01 */  addu       $t1, $t1, $fp
    /* 267D4 80035FD4 004C0900 */  sll        $t1, $t1, 16
    /* 267D8 80035FD8 00F41100 */  sll        $fp, $s1, 16
    /* 267DC 80035FDC 02F41E00 */  srl        $fp, $fp, 16
    /* 267E0 80035FE0 25E8C903 */  or         $sp, $fp, $t1
  .L80035FE4:
    /* 267E4 80035FE4 00109D48 */  mtc2       $sp, $2 /* handwritten instruction */
    /* 267E8 80035FE8 01005D32 */  andi       $sp, $s2, 0x1
    /* 267EC 80035FEC 1000A013 */  beqz       $sp, .L80036030
    /* 267F0 80035FF0 24E84102 */   and       $sp, $s2, $at
    /* 267F4 80035FF4 C2F41D00 */  srl        $fp, $sp, 19
    /* 267F8 80035FF8 F8FFA933 */  andi       $t1, $sp, 0xFFF8
    /* 267FC 80035FFC C2480900 */  srl        $t1, $t1, 3
    /* 26800 80036000 21F0C903 */  addu       $fp, $fp, $t1
    /* 26804 80036004 0F00DE33 */  andi       $fp, $fp, 0xF
    /* 26808 80036008 80F01E00 */  sll        $fp, $fp, 2
    /* 2680C 8003600C 2148DF03 */  addu       $t1, $fp, $ra
    /* 26810 80036010 00003E8D */  lw         $fp, 0x0($t1)
    /* 26814 80036014 00000000 */  nop
    /* 26818 80036018 034C1D00 */  sra        $t1, $sp, 16
    /* 2681C 8003601C 21483E01 */  addu       $t1, $t1, $fp
    /* 26820 80036020 004C0900 */  sll        $t1, $t1, 16
    /* 26824 80036024 00F41200 */  sll        $fp, $s2, 16
    /* 26828 80036028 02F41E00 */  srl        $fp, $fp, 16
    /* 2682C 8003602C 25E8C903 */  or         $sp, $fp, $t1
  .L80036030:
    /* 26830 80036030 00209D48 */  mtc2       $sp, $4 /* handwritten instruction */
    /* 26834 80036034 0700013C */  lui        $at, (0x70006 >> 16)
    /* 26838 80036038 06002134 */  ori        $at, $at, (0x70006 & 0xFFFF)
    /* 2683C 8003603C 02EE1300 */  srl        $sp, $s3, 24
    /* 26840 80036040 C0E81D00 */  sll        $sp, $sp, 3
    /* 26844 80036044 24800102 */  and        $s0, $s0, $at
    /* 26848 80036048 804A1000 */  sll        $t1, $s0, 10
    /* 2684C 8003604C 25E8A903 */  or         $sp, $sp, $t1
    /* 26850 80036050 C2481000 */  srl        $t1, $s0, 3
    /* 26854 80036054 25E8A903 */  or         $sp, $sp, $t1
    /* 26858 80036058 02F61400 */  srl        $fp, $s4, 24
    /* 2685C 8003605C C0F01E00 */  sll        $fp, $fp, 3
    /* 26860 80036060 24882102 */  and        $s1, $s1, $at
    /* 26864 80036064 804A1100 */  sll        $t1, $s1, 10
    /* 26868 80036068 25F0C903 */  or         $fp, $fp, $t1
    /* 2686C 8003606C C2481100 */  srl        $t1, $s1, 3
    /* 26870 80036070 25F0C903 */  or         $fp, $fp, $t1
    /* 26874 80036074 02FE1500 */  srl        $ra, $s5, 24
    /* 26878 80036078 C0F81F00 */  sll        $ra, $ra, 3
    /* 2687C 8003607C 24904102 */  and        $s2, $s2, $at
    /* 26880 80036080 804A1200 */  sll        $t1, $s2, 10
    /* 26884 80036084 25F8E903 */  or         $ra, $ra, $t1
    /* 26888 80036088 C2481200 */  srl        $t1, $s2, 3
    /* 2688C 8003608C 25F8E903 */  or         $ra, $ra, $t1
    /* 26890 80036090 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 26894 80036094 00189E48 */  mtc2       $fp, $3 /* handwritten instruction */
    /* 26898 80036098 00289F48 */  mtc2       $ra, $5 /* handwritten instruction */
    /* 2689C 8003609C 02F50200 */  srl        $fp, $v0, 20
    /* 268A0 800360A0 3000284A */  rtpt
    /* 268A4 800360A4 80F01E00 */  sll        $fp, $fp, 2
    /* 268A8 800360A8 21703E03 */  addu       $t6, $t9, $fp
    /* 268AC 800360AC 0000C98D */  lw         $t1, 0x0($t6)
    /* 268B0 800360B0 0034123C */  lui        $s2, (0x34000000 >> 16)
    /* 268B4 800360B4 024E0900 */  srl        $t1, $t1, 24
    /* 268B8 800360B8 80003D31 */  andi       $sp, $t1, 0x80
    /* 268BC 800360BC 6300A013 */  beqz       $sp, .L8003624C
    /* 268C0 800360C0 24987C02 */   and       $s3, $s3, $gp
    /* 268C4 800360C4 08006CE9 */  swc2       $12, 0x8($t3)
    /* 268C8 800360C8 14006DE9 */  swc2       $13, 0x14($t3)
    /* 268CC 800360CC 20006EE9 */  swc2       $14, 0x20($t3)
    /* 268D0 800360D0 24F02F01 */  and        $fp, $t1, $t7
    /* 268D4 800360D4 0200CF13 */  beq        $fp, $t7, .L800360E0
    /* 268D8 800360D8 25987202 */   or        $s3, $s3, $s2
    /* 268DC 800360DC 25986402 */  or         $s3, $s3, $a0
  .L800360E0:
    /* 268E0 800360E0 040073AD */  sw         $s3, 0x4($t3)
    /* 268E4 800360E4 100074AD */  sw         $s4, 0x10($t3)
    /* 268E8 800360E8 1C0075AD */  sw         $s5, 0x1C($t3)
    /* 268EC 800360EC C2FB0200 */  srl        $ra, $v0, 15
    /* 268F0 800360F0 1C00FF33 */  andi       $ra, $ra, 0x1C
    /* 268F4 800360F4 2108E703 */  addu       $at, $ra, $a3
    /* 268F8 800360F8 1E005F30 */  andi       $ra, $v0, 0x1E
    /* 268FC 800360FC 0D00E013 */  beqz       $ra, .L80036134
    /* 26900 80036100 42E90200 */   srl       $sp, $v0, 5
    /* 26904 80036104 801F1E3C */  lui        $fp, (0x1F8000E0 >> 16)
    /* 26908 80036108 E000DE37 */  ori        $fp, $fp, (0x1F8000E0 & 0xFFFF)
    /* 2690C 8003610C 0000DE8F */  lw         $fp, 0x0($fp)
    /* 26910 80036110 0700BD33 */  andi       $sp, $sp, 0x7
    /* 26914 80036114 06F0BE03 */  srlv       $fp, $fp, $sp
    /* 26918 80036118 02EB0200 */  srl        $sp, $v0, 12
    /* 2691C 8003611C 1F00BD33 */  andi       $sp, $sp, 0x1F
    /* 26920 80036120 21E8DD03 */  addu       $sp, $fp, $sp
    /* 26924 80036124 0100FE37 */  ori        $fp, $ra, 0x1
    /* 26928 80036128 24E8BE03 */  and        $sp, $sp, $fp
    /* 2692C 8003612C 80E81D00 */  sll        $sp, $sp, 2
    /* 26930 80036130 2170AE03 */  addu       $t6, $sp, $t6
  .L80036134:
    /* 26934 80036134 0400D38D */  lw         $s3, 0x4($t6)
    /* 26938 80036138 0000348C */  lw         $s4, 0x0($at)
    /* 2693C 8003613C 82ED1300 */  srl        $sp, $s3, 22
    /* 26940 80036140 C0E81D00 */  sll        $sp, $sp, 3
    /* 26944 80036144 2170DD02 */  addu       $t6, $s6, $sp
    /* 26948 80036148 0000D08D */  lw         $s0, 0x0($t6)
    /* 2694C 8003614C 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 26950 80036150 02AD1300 */  srl        $s5, $s3, 20
    /* 26954 80036154 0300B532 */  andi       $s5, $s5, 0x3
    /* 26958 80036158 C0E91500 */  sll        $sp, $s5, 7
    /* 2695C 8003615C 1C009E32 */  andi       $fp, $s4, 0x1C
    /* 26960 80036160 25E8BE03 */  or         $sp, $sp, $fp
    /* 26964 80036164 82F41300 */  srl        $fp, $s3, 18
    /* 26968 80036168 0300DE33 */  andi       $fp, $fp, 0x3
    /* 2696C 8003616C 25E8BE03 */  or         $sp, $sp, $fp
    /* 26970 80036170 60003E31 */  andi       $fp, $t1, 0x60
    /* 26974 80036174 25E8BE03 */  or         $sp, $sp, $fp
    /* 26978 80036178 00EC1D00 */  sll        $sp, $sp, 16
    /* 2697C 8003617C 1F007E32 */  andi       $fp, $s3, 0x1F
    /* 26980 80036180 80F01E00 */  sll        $fp, $fp, 2
    /* 26984 80036184 80009F32 */  andi       $ra, $s4, 0x80
    /* 26988 80036188 25F0DF03 */  or         $fp, $fp, $ra
    /* 2698C 8003618C 00FA1E00 */  sll        $ra, $fp, 8
    /* 26990 80036190 82F21300 */  srl        $fp, $s3, 10
    /* 26994 80036194 F800DE33 */  andi       $fp, $fp, 0xF8
    /* 26998 80036198 06F0BE02 */  srlv       $fp, $fp, $s5
    /* 2699C 8003619C 25A8DF03 */  or         $s5, $fp, $ra
    /* 269A0 800361A0 02F41000 */  srl        $fp, $s0, 16
    /* 269A4 800361A4 21F0D503 */  addu       $fp, $fp, $s5
    /* 269A8 800361A8 25F8BE03 */  or         $ra, $sp, $fp
    /* 269AC 800361AC 0F003D31 */  andi       $sp, $t1, 0xF
    /* 269B0 800361B0 C01F7E32 */  andi       $fp, $s3, 0x1FC0
    /* 269B4 800361B4 25E8BE03 */  or         $sp, $sp, $fp
    /* 269B8 800361B8 02F11400 */  srl        $fp, $s4, 4
    /* 269BC 800361BC F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 269C0 800361C0 25E8BE03 */  or         $sp, $sp, $fp
    /* 269C4 800361C4 00EC1D00 */  sll        $sp, $sp, 16
    /* 269C8 800361C8 FFFF1E32 */  andi       $fp, $s0, 0xFFFF
    /* 269CC 800361CC 21F0D503 */  addu       $fp, $fp, $s5
    /* 269D0 800361D0 25F0BE03 */  or         $fp, $sp, $fp
    /* 269D4 800361D4 2170D501 */  addu       $t6, $t6, $s5
    /* 269D8 800361D8 0C007EAD */  sw         $fp, 0xC($t3)
    /* 269DC 800361DC 18007FAD */  sw         $ra, 0x18($t3)
    /* 269E0 800361E0 24006EA5 */  sh         $t6, 0x24($t3)
    /* 269E4 800361E4 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 269E8 800361E8 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 269EC 800361EC 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 269F0 800361F0 21E8BE03 */  addu       $sp, $sp, $fp
    /* 269F4 800361F4 21E8BF03 */  addu       $sp, $sp, $ra
    /* 269F8 800361F8 42E91D00 */  srl        $sp, $sp, 5
    /* 269FC 800361FC 80E81D00 */  sll        $sp, $sp, 2
    /* 26A00 80036200 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 26A04 80036204 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 26A08 80036208 2AF0A303 */  slt        $fp, $sp, $v1
    /* 26A0C 8003620C 0600C013 */  beqz       $fp, .L80036228
    /* 26A10 80036210 2170A300 */   addu      $t6, $a1, $v1
    /* 26A14 80036214 2118A003 */  addu       $v1, $sp, $zero
    /* 26A18 80036218 03006104 */  bgez       $v1, .L80036228
    /* 26A1C 8003621C 2170A300 */   addu      $t6, $a1, $v1
    /* 26A20 80036220 21180000 */  addu       $v1, $zero, $zero
    /* 26A24 80036224 2170A300 */  addu       $t6, $a1, $v1
  .L80036228:
    /* 26A28 80036228 0000DD8D */  lw         $sp, 0x0($t6)
    /* 26A2C 8003622C 24F07C01 */  and        $fp, $t3, $gp
    /* 26A30 80036230 0000DEAD */  sw         $fp, 0x0($t6)
    /* 26A34 80036234 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 26A38 80036238 25E8BF03 */  or         $sp, $sp, $ra
    /* 26A3C 8003623C 00007DAD */  sw         $sp, 0x0($t3)
    /* 26A40 80036240 28006B25 */  addiu      $t3, $t3, 0x28
    /* 26A44 80036244 21000104 */  bgez       $zero, .L800362CC
    /* 26A48 80036248 00000000 */   nop
  .L8003624C:
    /* 26A4C 8003624C 08006CE9 */  swc2       $12, 0x8($t3)
    /* 26A50 80036250 10006DE9 */  swc2       $13, 0x10($t3)
    /* 26A54 80036254 18006EE9 */  swc2       $14, 0x18($t3)
    /* 26A58 80036258 0030123C */  lui        $s2, (0x30000000 >> 16)
    /* 26A5C 8003625C 25987202 */  or         $s3, $s3, $s2
    /* 26A60 80036260 040073AD */  sw         $s3, 0x4($t3)
    /* 26A64 80036264 0C0074AD */  sw         $s4, 0xC($t3)
    /* 26A68 80036268 140075AD */  sw         $s5, 0x14($t3)
    /* 26A6C 8003626C 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 26A70 80036270 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 26A74 80036274 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 26A78 80036278 21E8BE03 */  addu       $sp, $sp, $fp
    /* 26A7C 8003627C 21E8BF03 */  addu       $sp, $sp, $ra
    /* 26A80 80036280 42E91D00 */  srl        $sp, $sp, 5
    /* 26A84 80036284 80E81D00 */  sll        $sp, $sp, 2
    /* 26A88 80036288 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 26A8C 8003628C FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 26A90 80036290 2AF0A303 */  slt        $fp, $sp, $v1
    /* 26A94 80036294 0600C013 */  beqz       $fp, .L800362B0
    /* 26A98 80036298 2170A300 */   addu      $t6, $a1, $v1
    /* 26A9C 8003629C 2118A003 */  addu       $v1, $sp, $zero
    /* 26AA0 800362A0 03006104 */  bgez       $v1, .L800362B0
    /* 26AA4 800362A4 2170A300 */   addu      $t6, $a1, $v1
    /* 26AA8 800362A8 21180000 */  addu       $v1, $zero, $zero
    /* 26AAC 800362AC 2170A300 */  addu       $t6, $a1, $v1
  .L800362B0:
    /* 26AB0 800362B0 0000DD8D */  lw         $sp, 0x0($t6)
    /* 26AB4 800362B4 24F07C01 */  and        $fp, $t3, $gp
    /* 26AB8 800362B8 0000DEAD */  sw         $fp, 0x0($t6)
    /* 26ABC 800362BC 00061E3C */  lui        $fp, (0x6000000 >> 16)
    /* 26AC0 800362C0 25E8BE03 */  or         $sp, $sp, $fp
    /* 26AC4 800362C4 00007DAD */  sw         $sp, 0x0($t3)
    /* 26AC8 800362C8 1C006B25 */  addiu      $t3, $t3, 0x1C
  .L800362CC:
    /* 26ACC 800362CC FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 26AD0 800362D0 F4FEA015 */  bnez       $t5, .L80035EA4
    /* 26AD4 800362D4 00004195 */   lhu       $at, 0x0($t2)
    /* 26AD8 800362D8 00000000 */  nop
    /* 26ADC 800362DC 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 26AE0 800362E0 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 26AE4 800362E4 00000000 */  nop
    /* 26AE8 800362E8 1000A18F */  lw         $at, 0x10($sp)
    /* 26AEC 800362EC 00000000 */  nop
    /* 26AF0 800362F0 00002BAC */  sw         $t3, 0x0($at)
    /* 26AF4 800362F4 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 26AF8 800362F8 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 26AFC 800362FC 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 26B00 80036300 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 26B04 80036304 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 26B08 80036308 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 26B0C 8003630C 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 26B10 80036310 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 26B14 80036314 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 26B18 80036318 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 26B1C 8003631C 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 26B20 80036320 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 26B24 80036324 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 26B28 80036328 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 26B2C 8003632C 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 26B30 80036330 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 26B34 80036334 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 26B38 80036338 0800E003 */  jr         $ra
    /* 26B3C 8003633C 00000000 */   nop
endlabel Gte_RTransformWorldsRipple
