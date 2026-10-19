.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformWorldsDark2
    /* 27DEC 800375EC 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 27DF0 800375F0 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 27DF4 800375F4 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 27DF8 800375F8 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 27DFC 800375FC 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 27E00 80037600 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 27E04 80037604 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 27E08 80037608 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 27E0C 8003760C 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 27E10 80037610 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 27E14 80037614 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 27E18 80037618 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 27E1C 8003761C 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 27E20 80037620 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 27E24 80037624 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 27E28 80037628 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 27E2C 8003762C 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 27E30 80037630 1000AF8F */  lw         $t7, 0x10($sp)
    /* 27E34 80037634 1400BF8F */  lw         $ra, 0x14($sp)
    /* 27E38 80037638 0000EB8D */  lw         $t3, 0x0($t7)
    /* 27E3C 8003763C 801F1C3C */  lui        $gp, (0x1F8000E4 >> 16)
    /* 27E40 80037640 E00087AF */  sw         $a3, 0xE0($gp) /* Failed to symbolize address 0x1F8000E0 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27E44 80037644 E4009FAF */  sw         $ra, 0xE4($gp) /* Failed to symbolize address 0x1F8000E4 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27E48 80037648 60000F34 */  ori        $t7, $zero, 0x60
    /* 27E4C 8003764C 00008D8C */  lw         $t5, 0x0($a0)
    /* 27E50 80037650 02008A24 */  addiu      $t2, $a0, 0x2
    /* 27E54 80037654 21504D01 */  addu       $t2, $t2, $t5
    /* 27E58 80037658 21504D01 */  addu       $t2, $t2, $t5
    /* 27E5C 8003765C FFFF0C34 */  ori        $t4, $zero, 0xFFFF
    /* 27E60 80037660 00004195 */  lhu        $at, 0x0($t2)
    /* 27E64 80037664 80300600 */  sll        $a2, $a2, 2
    /* 27E68 80037668 FC1F0334 */  ori        $v1, $zero, 0x1FFC
  .L8003766C:
    /* 27E6C 8003766C FEFF4A25 */  addiu      $t2, $t2, -0x2
    /* 27E70 80037670 02F30100 */  srl        $fp, $at, 12
    /* 27E74 80037674 1000CC13 */  beq        $fp, $t4, .L800376B8
    /* 27E78 80037678 FF0F2130 */   andi      $at, $at, 0xFFF
    /* 27E7C 8003767C 2160C003 */  addu       $t4, $fp, $zero
    /* 27E80 80037680 80F90C00 */  sll        $ra, $t4, 6
    /* 27E84 80037684 801F023C */  lui        $v0, (0x1F800100 >> 16)
    /* 27E88 80037688 00014234 */  ori        $v0, $v0, (0x1F800100 & 0xFFFF)
    /* 27E8C 8003768C 21105F00 */  addu       $v0, $v0, $ra
    /* 27E90 80037690 04005D8C */  lw         $sp, 0x4($v0)
    /* 27E94 80037694 08005E8C */  lw         $fp, 0x8($v0)
    /* 27E98 80037698 0C005F8C */  lw         $ra, 0xC($v0)
    /* 27E9C 8003769C 0028DD48 */  ctc2       $sp, $5 /* handwritten instruction */
    /* 27EA0 800376A0 0030DE48 */  ctc2       $fp, $6 /* handwritten instruction */
    /* 27EA4 800376A4 0038DF48 */  ctc2       $ra, $7 /* handwritten instruction */
    /* 27EA8 800376A8 1400578C */  lw         $s7, 0x14($v0)
    /* 27EAC 800376AC 1800588C */  lw         $t8, 0x18($v0)
    /* 27EB0 800376B0 1C00598C */  lw         $t9, 0x1C($v0)
    /* 27EB4 800376B4 20004724 */  addiu      $a3, $v0, 0x20
  .L800376B8:
    /* 27EB8 800376B8 C0080100 */  sll        $at, $at, 3
    /* 27EBC 800376BC 2148E102 */  addu       $t1, $s7, $at
    /* 27EC0 800376C0 0000218D */  lw         $at, 0x0($t1)
    /* 27EC4 800376C4 0400298D */  lw         $t1, 0x4($t1)
    /* 27EC8 800376C8 00130100 */  sll        $v0, $at, 12
    /* 27ECC 800376CC FF003D31 */  andi       $sp, $t1, 0xFF
    /* 27ED0 800376D0 25105D00 */  or         $v0, $v0, $sp
    /* 27ED4 800376D4 42840900 */  srl        $s0, $t1, 17
    /* 27ED8 800376D8 F87F1032 */  andi       $s0, $s0, 0x7FF8
    /* 27EDC 800376DC 21801802 */  addu       $s0, $s0, $t8
    /* 27EE0 800376E0 42890900 */  srl        $s1, $t1, 5
    /* 27EE4 800376E4 F87F3132 */  andi       $s1, $s1, 0x7FF8
    /* 27EE8 800376E8 21883802 */  addu       $s1, $s1, $t8
    /* 27EEC 800376EC 42940100 */  srl        $s2, $at, 17
    /* 27EF0 800376F0 F87F5232 */  andi       $s2, $s2, 0x7FF8
    /* 27EF4 800376F4 21905802 */  addu       $s2, $s2, $t8
    /* 27EF8 800376F8 0000138E */  lw         $s3, 0x0($s0)
    /* 27EFC 800376FC 0400108E */  lw         $s0, 0x4($s0)
    /* 27F00 80037700 0000348E */  lw         $s4, 0x0($s1)
    /* 27F04 80037704 0400318E */  lw         $s1, 0x4($s1)
    /* 27F08 80037708 0000558E */  lw         $s5, 0x0($s2)
    /* 27F0C 8003770C 0400528E */  lw         $s2, 0x4($s2)
    /* 27F10 80037710 F8FF013C */  lui        $at, (0xFFF8FFF8 >> 16)
    /* 27F14 80037714 F8FF2134 */  ori        $at, $at, (0xFFF8FFF8 & 0xFFFF)
    /* 27F18 80037718 24E80102 */  and        $sp, $s0, $at
    /* 27F1C 8003771C 24F02102 */  and        $fp, $s1, $at
    /* 27F20 80037720 24F84102 */  and        $ra, $s2, $at
    /* 27F24 80037724 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 27F28 80037728 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 27F2C 8003772C 00209F48 */  mtc2       $ra, $4 /* handwritten instruction */
    /* 27F30 80037730 801F093C */  lui        $t1, (0x1F800300 >> 16)
    /* 27F34 80037734 00032935 */  ori        $t1, $t1, (0x1F800300 & 0xFFFF)
    /* 27F38 80037738 00090C00 */  sll        $at, $t4, 4
    /* 27F3C 8003773C 21482101 */  addu       $t1, $t1, $at
    /* 27F40 80037740 00002E8D */  lw         $t6, 0x0($t1)
    /* 27F44 80037744 000C1D00 */  sll        $at, $sp, 16
    /* 27F48 80037748 030C0100 */  sra        $at, $at, 16
    /* 27F4C 8003774C 2170C101 */  addu       $t6, $t6, $at
    /* 27F50 80037750 4800818F */  lw         $at, 0x48($gp) /* Failed to symbolize address 0x1F800048 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27F54 80037754 00000000 */  nop
    /* 27F58 80037758 2308C101 */  subu       $at, $t6, $at
    /* 27F5C 8003775C 02002104 */  bgez       $at, .L80037768
    /* 27F60 80037760 00000000 */   nop
    /* 27F64 80037764 23080100 */  negu       $at, $at
  .L80037768:
    /* 27F68 80037768 21200100 */  addu       $a0, $zero, $at
    /* 27F6C 8003776C 04002E8D */  lw         $t6, 0x4($t1)
    /* 27F70 80037770 030C1D00 */  sra        $at, $sp, 16
    /* 27F74 80037774 2170C101 */  addu       $t6, $t6, $at
    /* 27F78 80037778 4C00818F */  lw         $at, 0x4C($gp) /* Failed to symbolize address 0x1F80004C for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27F7C 8003777C 00000000 */  nop
    /* 27F80 80037780 2308C101 */  subu       $at, $t6, $at
    /* 27F84 80037784 02002104 */  bgez       $at, .L80037790
    /* 27F88 80037788 00000000 */   nop
    /* 27F8C 8003778C 23080100 */  negu       $at, $at
  .L80037790:
    /* 27F90 80037790 21208100 */  addu       $a0, $a0, $at
    /* 27F94 80037794 00002E8D */  lw         $t6, 0x0($t1)
    /* 27F98 80037798 000C1E00 */  sll        $at, $fp, 16
    /* 27F9C 8003779C 030C0100 */  sra        $at, $at, 16
    /* 27FA0 800377A0 2170C101 */  addu       $t6, $t6, $at
    /* 27FA4 800377A4 4800818F */  lw         $at, 0x48($gp) /* Failed to symbolize address 0x1F800048 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27FA8 800377A8 00000000 */  nop
    /* 27FAC 800377AC 2308C101 */  subu       $at, $t6, $at
    /* 27FB0 800377B0 02002104 */  bgez       $at, .L800377BC
    /* 27FB4 800377B4 00000000 */   nop
    /* 27FB8 800377B8 23080100 */  negu       $at, $at
  .L800377BC:
    /* 27FBC 800377BC 21400100 */  addu       $t0, $zero, $at
    /* 27FC0 800377C0 04002E8D */  lw         $t6, 0x4($t1)
    /* 27FC4 800377C4 030C1E00 */  sra        $at, $fp, 16
    /* 27FC8 800377C8 2170C101 */  addu       $t6, $t6, $at
    /* 27FCC 800377CC 4C00818F */  lw         $at, 0x4C($gp) /* Failed to symbolize address 0x1F80004C for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27FD0 800377D0 00000000 */  nop
    /* 27FD4 800377D4 2308C101 */  subu       $at, $t6, $at
    /* 27FD8 800377D8 02002104 */  bgez       $at, .L800377E4
    /* 27FDC 800377DC 00000000 */   nop
    /* 27FE0 800377E0 23080100 */  negu       $at, $at
  .L800377E4:
    /* 27FE4 800377E4 21400101 */  addu       $t0, $t0, $at
    /* 27FE8 800377E8 00002E8D */  lw         $t6, 0x0($t1)
    /* 27FEC 800377EC 000C1F00 */  sll        $at, $ra, 16
    /* 27FF0 800377F0 030C0100 */  sra        $at, $at, 16
    /* 27FF4 800377F4 2170C101 */  addu       $t6, $t6, $at
    /* 27FF8 800377F8 4800818F */  lw         $at, 0x48($gp) /* Failed to symbolize address 0x1F800048 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 27FFC 800377FC 00000000 */  nop
    /* 28000 80037800 2308C101 */  subu       $at, $t6, $at
    /* 28004 80037804 02002104 */  bgez       $at, .L80037810
    /* 28008 80037808 00000000 */   nop
    /* 2800C 8003780C 23080100 */  negu       $at, $at
  .L80037810:
    /* 28010 80037810 21B00100 */  addu       $s6, $zero, $at
    /* 28014 80037814 04002E8D */  lw         $t6, 0x4($t1)
    /* 28018 80037818 030C1F00 */  sra        $at, $ra, 16
    /* 2801C 8003781C 2170C101 */  addu       $t6, $t6, $at
    /* 28020 80037820 4C00818F */  lw         $at, 0x4C($gp) /* Failed to symbolize address 0x1F80004C for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28024 80037824 00000000 */  nop
    /* 28028 80037828 2308C101 */  subu       $at, $t6, $at
    /* 2802C 8003782C 02002104 */  bgez       $at, .L80037838
    /* 28030 80037830 00000000 */   nop
    /* 28034 80037834 23080100 */  negu       $at, $at
  .L80037838:
    /* 28038 80037838 21B0C102 */  addu       $s6, $s6, $at
    /* 2803C 8003783C 0700013C */  lui        $at, (0x70006 >> 16)
    /* 28040 80037840 06002134 */  ori        $at, $at, (0x70006 & 0xFFFF)
    /* 28044 80037844 02EE1300 */  srl        $sp, $s3, 24
    /* 28048 80037848 C0E81D00 */  sll        $sp, $sp, 3
    /* 2804C 8003784C 24700102 */  and        $t6, $s0, $at
    /* 28050 80037850 804A0E00 */  sll        $t1, $t6, 10
    /* 28054 80037854 25E8A903 */  or         $sp, $sp, $t1
    /* 28058 80037858 C2480E00 */  srl        $t1, $t6, 3
    /* 2805C 8003785C 25E8A903 */  or         $sp, $sp, $t1
    /* 28060 80037860 02F61400 */  srl        $fp, $s4, 24
    /* 28064 80037864 C0F01E00 */  sll        $fp, $fp, 3
    /* 28068 80037868 24702102 */  and        $t6, $s1, $at
    /* 2806C 8003786C 804A0E00 */  sll        $t1, $t6, 10
    /* 28070 80037870 25F0C903 */  or         $fp, $fp, $t1
    /* 28074 80037874 C2480E00 */  srl        $t1, $t6, 3
    /* 28078 80037878 25F0C903 */  or         $fp, $fp, $t1
    /* 2807C 8003787C 02FE1500 */  srl        $ra, $s5, 24
    /* 28080 80037880 C0F81F00 */  sll        $ra, $ra, 3
    /* 28084 80037884 24704102 */  and        $t6, $s2, $at
    /* 28088 80037888 804A0E00 */  sll        $t1, $t6, 10
    /* 2808C 8003788C 25F8E903 */  or         $ra, $ra, $t1
    /* 28090 80037890 C2480E00 */  srl        $t1, $t6, 3
    /* 28094 80037894 25F8E903 */  or         $ra, $ra, $t1
    /* 28098 80037898 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 2809C 8003789C 00189E48 */  mtc2       $fp, $3 /* handwritten instruction */
    /* 280A0 800378A0 00289F48 */  mtc2       $ra, $5 /* handwritten instruction */
    /* 280A4 800378A4 801F093C */  lui        $t1, (0x1F800300 >> 16)
    /* 280A8 800378A8 00032935 */  ori        $t1, $t1, (0x1F800300 & 0xFFFF)
    /* 280AC 800378AC 00090C00 */  sll        $at, $t4, 4
    /* 280B0 800378B0 21482101 */  addu       $t1, $t1, $at
    /* 280B4 800378B4 08002E8D */  lw         $t6, 0x8($t1)
    /* 280B8 800378B8 000C1D00 */  sll        $at, $sp, 16
    /* 280BC 800378BC 030C0100 */  sra        $at, $at, 16
    /* 280C0 800378C0 2170C101 */  addu       $t6, $t6, $at
    /* 280C4 800378C4 5000818F */  lw         $at, 0x50($gp) /* Failed to symbolize address 0x1F800050 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 280C8 800378C8 00000000 */  nop
    /* 280CC 800378CC 2308C101 */  subu       $at, $t6, $at
    /* 280D0 800378D0 02002104 */  bgez       $at, .L800378DC
    /* 280D4 800378D4 00000000 */   nop
    /* 280D8 800378D8 23080100 */  negu       $at, $at
  .L800378DC:
    /* 280DC 800378DC 21208100 */  addu       $a0, $a0, $at
    /* 280E0 800378E0 54008E8F */  lw         $t6, 0x54($gp) /* Failed to symbolize address 0x1F800054 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 280E4 800378E4 5800818F */  lw         $at, 0x58($gp) /* Failed to symbolize address 0x1F800058 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 280E8 800378E8 06E8C401 */  srlv       $sp, $a0, $t6
    /* 280EC 800378EC 21709D00 */  addu       $t6, $a0, $sp
    /* 280F0 800378F0 06E82400 */  srlv       $sp, $a0, $at
    /* 280F4 800378F4 2320DD01 */  subu       $a0, $t6, $sp
    /* 280F8 800378F8 01000132 */  andi       $at, $s0, 0x1
    /* 280FC 800378FC 03002010 */  beqz       $at, .L8003790C
    /* 28100 80037900 5C008E8F */   lw        $t6, 0x5C($gp) /* Failed to symbolize address 0x1F80005C for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28104 80037904 00000000 */  nop
    /* 28108 80037908 60008E8F */  lw         $t6, 0x60($gp) /* Failed to symbolize address 0x1F800060 for %gp_rel. Make sure this address is within the recognized valid address space. */
  .L8003790C:
    /* 2810C 8003790C 00000000 */  nop
    /* 28110 80037910 21208E00 */  addu       $a0, $a0, $t6
    /* 28114 80037914 00109D28 */  slti       $sp, $a0, 0x1000
    /* 28118 80037918 0300A017 */  bnez       $sp, .L80037928
    /* 2811C 8003791C 00000000 */   nop
    /* 28120 80037920 04000104 */  bgez       $zero, .L80037934
    /* 28124 80037924 FF0F0434 */   ori       $a0, $zero, 0xFFF
  .L80037928:
    /* 28128 80037928 02008104 */  bgez       $a0, .L80037934
    /* 2812C 8003792C 00000000 */   nop
    /* 28130 80037930 25200000 */  or         $a0, $zero, $zero
  .L80037934:
    /* 28134 80037934 00408448 */  mtc2       $a0, $8 /* handwritten instruction */
    /* 28138 80037938 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 2813C 8003793C 00000000 */  nop
    /* 28140 80037940 00000000 */  nop
    /* 28144 80037944 1000784A */  dpcs
    /* 28148 80037948 00000000 */  nop
    /* 2814C 8003794C 00000000 */  nop
    /* 28150 80037950 00B01348 */  mfc2       $s3, $22 /* handwritten instruction */
    /* 28154 80037954 08002E8D */  lw         $t6, 0x8($t1)
    /* 28158 80037958 000C1E00 */  sll        $at, $fp, 16
    /* 2815C 8003795C 030C0100 */  sra        $at, $at, 16
    /* 28160 80037960 2170C101 */  addu       $t6, $t6, $at
    /* 28164 80037964 5000818F */  lw         $at, 0x50($gp) /* Failed to symbolize address 0x1F800050 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28168 80037968 00000000 */  nop
    /* 2816C 8003796C 2308C101 */  subu       $at, $t6, $at
    /* 28170 80037970 02002104 */  bgez       $at, .L8003797C
    /* 28174 80037974 00000000 */   nop
    /* 28178 80037978 23080100 */  negu       $at, $at
  .L8003797C:
    /* 2817C 8003797C 21400101 */  addu       $t0, $t0, $at
    /* 28180 80037980 54008E8F */  lw         $t6, 0x54($gp) /* Failed to symbolize address 0x1F800054 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28184 80037984 5800818F */  lw         $at, 0x58($gp) /* Failed to symbolize address 0x1F800058 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28188 80037988 06E8C801 */  srlv       $sp, $t0, $t6
    /* 2818C 8003798C 21701D01 */  addu       $t6, $t0, $sp
    /* 28190 80037990 06E82800 */  srlv       $sp, $t0, $at
    /* 28194 80037994 2340DD01 */  subu       $t0, $t6, $sp
    /* 28198 80037998 01002132 */  andi       $at, $s1, 0x1
    /* 2819C 8003799C 03002010 */  beqz       $at, .L800379AC
    /* 281A0 800379A0 5C008E8F */   lw        $t6, 0x5C($gp) /* Failed to symbolize address 0x1F80005C for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 281A4 800379A4 00000000 */  nop
    /* 281A8 800379A8 60008E8F */  lw         $t6, 0x60($gp) /* Failed to symbolize address 0x1F800060 for %gp_rel. Make sure this address is within the recognized valid address space. */
  .L800379AC:
    /* 281AC 800379AC 00000000 */  nop
    /* 281B0 800379B0 21400E01 */  addu       $t0, $t0, $t6
    /* 281B4 800379B4 00101D29 */  slti       $sp, $t0, 0x1000
    /* 281B8 800379B8 0300A017 */  bnez       $sp, .L800379C8
    /* 281BC 800379BC 00000000 */   nop
    /* 281C0 800379C0 04000104 */  bgez       $zero, .L800379D4
    /* 281C4 800379C4 FF0F0834 */   ori       $t0, $zero, 0xFFF
  .L800379C8:
    /* 281C8 800379C8 02000105 */  bgez       $t0, .L800379D4
    /* 281CC 800379CC 00000000 */   nop
    /* 281D0 800379D0 25400000 */  or         $t0, $zero, $zero
  .L800379D4:
    /* 281D4 800379D4 00408848 */  mtc2       $t0, $8 /* handwritten instruction */
    /* 281D8 800379D8 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 281DC 800379DC 00000000 */  nop
    /* 281E0 800379E0 00000000 */  nop
    /* 281E4 800379E4 1000784A */  dpcs
    /* 281E8 800379E8 00000000 */  nop
    /* 281EC 800379EC 00000000 */  nop
    /* 281F0 800379F0 00B01448 */  mfc2       $s4, $22 /* handwritten instruction */
    /* 281F4 800379F4 08002E8D */  lw         $t6, 0x8($t1)
    /* 281F8 800379F8 000C1F00 */  sll        $at, $ra, 16
    /* 281FC 800379FC 030C0100 */  sra        $at, $at, 16
    /* 28200 80037A00 2170C101 */  addu       $t6, $t6, $at
    /* 28204 80037A04 5000818F */  lw         $at, 0x50($gp) /* Failed to symbolize address 0x1F800050 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28208 80037A08 00000000 */  nop
    /* 2820C 80037A0C 2308C101 */  subu       $at, $t6, $at
    /* 28210 80037A10 02002104 */  bgez       $at, .L80037A1C
    /* 28214 80037A14 00000000 */   nop
    /* 28218 80037A18 23080100 */  negu       $at, $at
  .L80037A1C:
    /* 2821C 80037A1C 21B0C102 */  addu       $s6, $s6, $at
    /* 28220 80037A20 54008E8F */  lw         $t6, 0x54($gp) /* Failed to symbolize address 0x1F800054 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28224 80037A24 5800818F */  lw         $at, 0x58($gp) /* Failed to symbolize address 0x1F800058 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28228 80037A28 06E8D601 */  srlv       $sp, $s6, $t6
    /* 2822C 80037A2C 2170DD02 */  addu       $t6, $s6, $sp
    /* 28230 80037A30 06E83600 */  srlv       $sp, $s6, $at
    /* 28234 80037A34 23B0DD01 */  subu       $s6, $t6, $sp
    /* 28238 80037A38 01004132 */  andi       $at, $s2, 0x1
    /* 2823C 80037A3C 03002010 */  beqz       $at, .L80037A4C
    /* 28240 80037A40 5C008E8F */   lw        $t6, 0x5C($gp) /* Failed to symbolize address 0x1F80005C for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 28244 80037A44 00000000 */  nop
    /* 28248 80037A48 60008E8F */  lw         $t6, 0x60($gp) /* Failed to symbolize address 0x1F800060 for %gp_rel. Make sure this address is within the recognized valid address space. */
  .L80037A4C:
    /* 2824C 80037A4C 00000000 */  nop
    /* 28250 80037A50 21B0CE02 */  addu       $s6, $s6, $t6
    /* 28254 80037A54 0010DD2A */  slti       $sp, $s6, 0x1000
    /* 28258 80037A58 0300A017 */  bnez       $sp, .L80037A68
    /* 2825C 80037A5C 00000000 */   nop
    /* 28260 80037A60 04000104 */  bgez       $zero, .L80037A74
    /* 28264 80037A64 FF0F1634 */   ori       $s6, $zero, 0xFFF
  .L80037A68:
    /* 28268 80037A68 0200C106 */  bgez       $s6, .L80037A74
    /* 2826C 80037A6C 00000000 */   nop
    /* 28270 80037A70 25B00000 */  or         $s6, $zero, $zero
  .L80037A74:
    /* 28274 80037A74 00409648 */  mtc2       $s6, $8 /* handwritten instruction */
    /* 28278 80037A78 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 2827C 80037A7C 00000000 */  nop
    /* 28280 80037A80 00000000 */  nop
    /* 28284 80037A84 1000784A */  dpcs
    /* 28288 80037A88 00000000 */  nop
    /* 2828C 80037A8C 00000000 */  nop
    /* 28290 80037A90 00B01548 */  mfc2       $s5, $22 /* handwritten instruction */
    /* 28294 80037A94 02F50200 */  srl        $fp, $v0, 20
    /* 28298 80037A98 3000284A */  rtpt
    /* 2829C 80037A9C 80F01E00 */  sll        $fp, $fp, 2
    /* 282A0 80037AA0 21703E03 */  addu       $t6, $t9, $fp
    /* 282A4 80037AA4 0000C98D */  lw         $t1, 0x0($t6)
    /* 282A8 80037AA8 0034123C */  lui        $s2, (0x34000000 >> 16)
    /* 282AC 80037AAC 024E0900 */  srl        $t1, $t1, 24
    /* 282B0 80037AB0 FF001E3C */  lui        $fp, (0xFFFFFF >> 16)
    /* 282B4 80037AB4 FFFFDE37 */  ori        $fp, $fp, (0xFFFFFF & 0xFFFF)
    /* 282B8 80037AB8 80003D31 */  andi       $sp, $t1, 0x80
    /* 282BC 80037ABC 6500A013 */  beqz       $sp, .L80037C54
    /* 282C0 80037AC0 24987E02 */   and       $s3, $s3, $fp
    /* 282C4 80037AC4 08006CE9 */  swc2       $12, 0x8($t3)
    /* 282C8 80037AC8 14006DE9 */  swc2       $13, 0x14($t3)
    /* 282CC 80037ACC 20006EE9 */  swc2       $14, 0x20($t3)
    /* 282D0 80037AD0 24F02F01 */  and        $fp, $t1, $t7
    /* 282D4 80037AD4 0300CF13 */  beq        $fp, $t7, .L80037AE4
    /* 282D8 80037AD8 25987202 */   or        $s3, $s3, $s2
    /* 282DC 80037ADC 00021F3C */  lui        $ra, (0x2000000 >> 16)
    /* 282E0 80037AE0 25987F02 */  or         $s3, $s3, $ra
  .L80037AE4:
    /* 282E4 80037AE4 040073AD */  sw         $s3, 0x4($t3)
    /* 282E8 80037AE8 100074AD */  sw         $s4, 0x10($t3)
    /* 282EC 80037AEC 1C0075AD */  sw         $s5, 0x1C($t3)
    /* 282F0 80037AF0 C2FB0200 */  srl        $ra, $v0, 15
    /* 282F4 80037AF4 1C00FF33 */  andi       $ra, $ra, 0x1C
    /* 282F8 80037AF8 2108E703 */  addu       $at, $ra, $a3
    /* 282FC 80037AFC 1E005F30 */  andi       $ra, $v0, 0x1E
    /* 28300 80037B00 0B00E013 */  beqz       $ra, .L80037B30
    /* 28304 80037B04 42E90200 */   srl       $sp, $v0, 5
    /* 28308 80037B08 E0009E8F */  lw         $fp, 0xE0($gp) /* Failed to symbolize address 0x1F8000E0 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 2830C 80037B0C 0700BD33 */  andi       $sp, $sp, 0x7
    /* 28310 80037B10 06F0BE03 */  srlv       $fp, $fp, $sp
    /* 28314 80037B14 02EB0200 */  srl        $sp, $v0, 12
    /* 28318 80037B18 1F00BD33 */  andi       $sp, $sp, 0x1F
    /* 2831C 80037B1C 21E8DD03 */  addu       $sp, $fp, $sp
    /* 28320 80037B20 0100FE37 */  ori        $fp, $ra, 0x1
    /* 28324 80037B24 24E8BE03 */  and        $sp, $sp, $fp
    /* 28328 80037B28 80E81D00 */  sll        $sp, $sp, 2
    /* 2832C 80037B2C 2170AE03 */  addu       $t6, $sp, $t6
  .L80037B30:
    /* 28330 80037B30 0400D38D */  lw         $s3, 0x4($t6)
    /* 28334 80037B34 0000348C */  lw         $s4, 0x0($at)
    /* 28338 80037B38 E4009E8F */  lw         $fp, 0xE4($gp) /* Failed to symbolize address 0x1F8000E4 for %gp_rel. Make sure this address is within the recognized valid address space. */
    /* 2833C 80037B3C 82ED1300 */  srl        $sp, $s3, 22
    /* 28340 80037B40 C0E81D00 */  sll        $sp, $sp, 3
    /* 28344 80037B44 2170DD03 */  addu       $t6, $fp, $sp
    /* 28348 80037B48 0000D08D */  lw         $s0, 0x0($t6)
    /* 2834C 80037B4C 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 28350 80037B50 02AD1300 */  srl        $s5, $s3, 20
    /* 28354 80037B54 0300B532 */  andi       $s5, $s5, 0x3
    /* 28358 80037B58 C0E91500 */  sll        $sp, $s5, 7
    /* 2835C 80037B5C 1C009E32 */  andi       $fp, $s4, 0x1C
    /* 28360 80037B60 25E8BE03 */  or         $sp, $sp, $fp
    /* 28364 80037B64 82F41300 */  srl        $fp, $s3, 18
    /* 28368 80037B68 0300DE33 */  andi       $fp, $fp, 0x3
    /* 2836C 80037B6C 25E8BE03 */  or         $sp, $sp, $fp
    /* 28370 80037B70 60003E31 */  andi       $fp, $t1, 0x60
    /* 28374 80037B74 25E8BE03 */  or         $sp, $sp, $fp
    /* 28378 80037B78 00EC1D00 */  sll        $sp, $sp, 16
    /* 2837C 80037B7C 1F007E32 */  andi       $fp, $s3, 0x1F
    /* 28380 80037B80 80F01E00 */  sll        $fp, $fp, 2
    /* 28384 80037B84 80009F32 */  andi       $ra, $s4, 0x80
    /* 28388 80037B88 25F0DF03 */  or         $fp, $fp, $ra
    /* 2838C 80037B8C 00FA1E00 */  sll        $ra, $fp, 8
    /* 28390 80037B90 82F21300 */  srl        $fp, $s3, 10
    /* 28394 80037B94 F800DE33 */  andi       $fp, $fp, 0xF8
    /* 28398 80037B98 06F0BE02 */  srlv       $fp, $fp, $s5
    /* 2839C 80037B9C 25A8DF03 */  or         $s5, $fp, $ra
    /* 283A0 80037BA0 02F41000 */  srl        $fp, $s0, 16
    /* 283A4 80037BA4 21F0D503 */  addu       $fp, $fp, $s5
    /* 283A8 80037BA8 25F8BE03 */  or         $ra, $sp, $fp
    /* 283AC 80037BAC 0F003D31 */  andi       $sp, $t1, 0xF
    /* 283B0 80037BB0 C01F7E32 */  andi       $fp, $s3, 0x1FC0
    /* 283B4 80037BB4 25E8BE03 */  or         $sp, $sp, $fp
    /* 283B8 80037BB8 02F11400 */  srl        $fp, $s4, 4
    /* 283BC 80037BBC F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 283C0 80037BC0 25E8BE03 */  or         $sp, $sp, $fp
    /* 283C4 80037BC4 00EC1D00 */  sll        $sp, $sp, 16
    /* 283C8 80037BC8 FFFF1E32 */  andi       $fp, $s0, 0xFFFF
    /* 283CC 80037BCC 21F0D503 */  addu       $fp, $fp, $s5
    /* 283D0 80037BD0 25F0BE03 */  or         $fp, $sp, $fp
    /* 283D4 80037BD4 2170D501 */  addu       $t6, $t6, $s5
    /* 283D8 80037BD8 0C007EAD */  sw         $fp, 0xC($t3)
    /* 283DC 80037BDC 18007FAD */  sw         $ra, 0x18($t3)
    /* 283E0 80037BE0 24006EA5 */  sh         $t6, 0x24($t3)
    /* 283E4 80037BE4 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 283E8 80037BE8 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 283EC 80037BEC 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 283F0 80037BF0 21E8BE03 */  addu       $sp, $sp, $fp
    /* 283F4 80037BF4 21E8BF03 */  addu       $sp, $sp, $ra
    /* 283F8 80037BF8 42E91D00 */  srl        $sp, $sp, 5
    /* 283FC 80037BFC 80E81D00 */  sll        $sp, $sp, 2
    /* 28400 80037C00 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 28404 80037C04 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 28408 80037C08 2AF0A303 */  slt        $fp, $sp, $v1
    /* 2840C 80037C0C 0600C013 */  beqz       $fp, .L80037C28
    /* 28410 80037C10 2170A300 */   addu      $t6, $a1, $v1
    /* 28414 80037C14 2118A003 */  addu       $v1, $sp, $zero
    /* 28418 80037C18 03006104 */  bgez       $v1, .L80037C28
    /* 2841C 80037C1C 2170A300 */   addu      $t6, $a1, $v1
    /* 28420 80037C20 21180000 */  addu       $v1, $zero, $zero
    /* 28424 80037C24 2170A300 */  addu       $t6, $a1, $v1
  .L80037C28:
    /* 28428 80037C28 0000DD8D */  lw         $sp, 0x0($t6)
    /* 2842C 80037C2C FF001E3C */  lui        $fp, (0xFFFFFF >> 16)
    /* 28430 80037C30 FFFFDE37 */  ori        $fp, $fp, (0xFFFFFF & 0xFFFF)
    /* 28434 80037C34 24F07E01 */  and        $fp, $t3, $fp
    /* 28438 80037C38 0000DEAD */  sw         $fp, 0x0($t6)
    /* 2843C 80037C3C 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 28440 80037C40 25E8BF03 */  or         $sp, $sp, $ra
    /* 28444 80037C44 00007DAD */  sw         $sp, 0x0($t3)
    /* 28448 80037C48 28006B25 */  addiu      $t3, $t3, 0x28
    /* 2844C 80037C4C 23000104 */  bgez       $zero, .L80037CDC
    /* 28450 80037C50 00000000 */   nop
  .L80037C54:
    /* 28454 80037C54 08006CE9 */  swc2       $12, 0x8($t3)
    /* 28458 80037C58 10006DE9 */  swc2       $13, 0x10($t3)
    /* 2845C 80037C5C 18006EE9 */  swc2       $14, 0x18($t3)
    /* 28460 80037C60 0030123C */  lui        $s2, (0x30000000 >> 16)
    /* 28464 80037C64 25987202 */  or         $s3, $s3, $s2
    /* 28468 80037C68 040073AD */  sw         $s3, 0x4($t3)
    /* 2846C 80037C6C 0C0074AD */  sw         $s4, 0xC($t3)
    /* 28470 80037C70 140075AD */  sw         $s5, 0x14($t3)
    /* 28474 80037C74 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 28478 80037C78 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 2847C 80037C7C 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 28480 80037C80 21E8BE03 */  addu       $sp, $sp, $fp
    /* 28484 80037C84 21E8BF03 */  addu       $sp, $sp, $ra
    /* 28488 80037C88 42E91D00 */  srl        $sp, $sp, 5
    /* 2848C 80037C8C 80E81D00 */  sll        $sp, $sp, 2
    /* 28490 80037C90 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 28494 80037C94 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 28498 80037C98 2AF0A303 */  slt        $fp, $sp, $v1
    /* 2849C 80037C9C 0600C013 */  beqz       $fp, .L80037CB8
    /* 284A0 80037CA0 2170A300 */   addu      $t6, $a1, $v1
    /* 284A4 80037CA4 2118A003 */  addu       $v1, $sp, $zero
    /* 284A8 80037CA8 03006104 */  bgez       $v1, .L80037CB8
    /* 284AC 80037CAC 2170A300 */   addu      $t6, $a1, $v1
    /* 284B0 80037CB0 21180000 */  addu       $v1, $zero, $zero
    /* 284B4 80037CB4 2170A300 */  addu       $t6, $a1, $v1
  .L80037CB8:
    /* 284B8 80037CB8 0000DD8D */  lw         $sp, 0x0($t6)
    /* 284BC 80037CBC FF001E3C */  lui        $fp, (0xFFFFFF >> 16)
    /* 284C0 80037CC0 FFFFDE37 */  ori        $fp, $fp, (0xFFFFFF & 0xFFFF)
    /* 284C4 80037CC4 24F07E01 */  and        $fp, $t3, $fp
    /* 284C8 80037CC8 0000DEAD */  sw         $fp, 0x0($t6)
    /* 284CC 80037CCC 00061E3C */  lui        $fp, (0x6000000 >> 16)
    /* 284D0 80037CD0 25E8BE03 */  or         $sp, $sp, $fp
    /* 284D4 80037CD4 00007DAD */  sw         $sp, 0x0($t3)
    /* 284D8 80037CD8 1C006B25 */  addiu      $t3, $t3, 0x1C
  .L80037CDC:
    /* 284DC 80037CDC FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 284E0 80037CE0 62FEA015 */  bnez       $t5, .L8003766C
    /* 284E4 80037CE4 00004195 */   lhu       $at, 0x0($t2)
    /* 284E8 80037CE8 00000000 */  nop
    /* 284EC 80037CEC 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 284F0 80037CF0 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 284F4 80037CF4 00000000 */  nop
    /* 284F8 80037CF8 1000A18F */  lw         $at, 0x10($sp)
    /* 284FC 80037CFC 00000000 */  nop
    /* 28500 80037D00 00002BAC */  sw         $t3, 0x0($at)
    /* 28504 80037D04 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 28508 80037D08 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2850C 80037D0C 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 28510 80037D10 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 28514 80037D14 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 28518 80037D18 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2851C 80037D1C 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 28520 80037D20 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 28524 80037D24 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 28528 80037D28 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2852C 80037D2C 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 28530 80037D30 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 28534 80037D34 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 28538 80037D38 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2853C 80037D3C 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 28540 80037D40 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 28544 80037D44 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 28548 80037D48 0800E003 */  jr         $ra
    /* 2854C 80037D4C 00000000 */   nop
endlabel Gte_RTransformWorldsDark2
