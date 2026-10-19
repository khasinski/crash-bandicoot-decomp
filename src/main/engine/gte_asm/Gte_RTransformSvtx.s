.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformSvtx
    /* 24E0C 8003460C 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 24E10 80034610 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 24E14 80034614 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 24E18 80034618 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 24E1C 8003461C 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 24E20 80034620 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 24E24 80034624 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 24E28 80034628 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 24E2C 8003462C 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 24E30 80034630 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 24E34 80034634 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 24E38 80034638 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 24E3C 8003463C 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 24E40 80034640 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 24E44 80034644 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 24E48 80034648 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 24E4C 8003464C 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 24E50 80034650 1000A88F */  lw         $t0, 0x10($sp)
    /* 24E54 80034654 1400A98F */  lw         $t1, 0x14($sp)
    /* 24E58 80034658 1800AA8F */  lw         $t2, 0x18($sp)
    /* 24E5C 8003465C 1C00B78F */  lw         $s7, 0x1C($sp)
    /* 24E60 80034660 2000AF8F */  lw         $t7, 0x20($sp)
    /* 24E64 80034664 80480900 */  sll        $t1, $t1, 2
    /* 24E68 80034668 FF00193C */  lui        $t9, (0xFFFFFF >> 16)
    /* 24E6C 8003466C FFFF3937 */  ori        $t9, $t9, (0xFFFFFF & 0xFFFF)
    /* 24E70 80034670 60001834 */  ori        $t8, $zero, 0x60
    /* 24E74 80034674 00061C3C */  lui        $gp, (0x6000000 >> 16)
    /* 24E78 80034678 0800818C */  lw         $at, 0x8($a0)
    /* 24E7C 8003467C 0C00828C */  lw         $v0, 0xC($a0)
    /* 24E80 80034680 1000838C */  lw         $v1, 0x10($a0)
    /* 24E84 80034684 80FF2124 */  addiu      $at, $at, -0x80
    /* 24E88 80034688 80FF4224 */  addiu      $v0, $v0, -0x80
    /* 24E8C 8003468C 80FF6324 */  addiu      $v1, $v1, -0x80
    /* 24E90 80034690 38008B24 */  addiu      $t3, $a0, 0x38
    /* 24E94 80034694 1400EC24 */  addiu      $t4, $a3, 0x14
    /* 24E98 80034698 0000ED8C */  lw         $t5, 0x0($a3)
    /* 24E9C 8003469C 0000478D */  lw         $a3, 0x0($t2)
  .L800346A0:
    /* 24EA0 800346A0 0000DD8C */  lw         $sp, 0x0($a2)
    /* 24EA4 800346A4 0400DE8C */  lw         $fp, 0x4($a2)
    /* 24EA8 800346A8 00000000 */  nop
    /* 24EAC 800346AC FFFFBF33 */  andi       $ra, $sp, 0xFFFF
    /* 24EB0 800346B0 21807F01 */  addu       $s0, $t3, $ra
    /* 24EB4 800346B4 02FC1D00 */  srl        $ra, $sp, 16
    /* 24EB8 800346B8 21887F01 */  addu       $s1, $t3, $ra
    /* 24EBC 800346BC FFFFDF33 */  andi       $ra, $fp, 0xFFFF
    /* 24EC0 800346C0 21907F01 */  addu       $s2, $t3, $ra
    /* 24EC4 800346C4 02FC1E00 */  srl        $ra, $fp, 16
    /* 24EC8 800346C8 0080EA33 */  andi       $t2, $ra, 0x8000
    /* 24ECC 800346CC FF7FFF33 */  andi       $ra, $ra, 0x7FFF
    /* 24ED0 800346D0 80F81F00 */  sll        $ra, $ra, 2
    /* 24ED4 800346D4 21709F01 */  addu       $t6, $t4, $ra
    /* 24ED8 800346D8 00001696 */  lhu        $s6, 0x0($s0)
    /* 24EDC 800346DC 02001396 */  lhu        $s3, 0x2($s0)
    /* 24EE0 800346E0 02F21600 */  srl        $fp, $s6, 8
    /* 24EE4 800346E4 21F0C203 */  addu       $fp, $fp, $v0
    /* 24EE8 800346E8 80F41E00 */  sll        $fp, $fp, 18
    /* 24EEC 800346EC FF00DD32 */  andi       $sp, $s6, 0xFF
    /* 24EF0 800346F0 21E8A103 */  addu       $sp, $sp, $at
    /* 24EF4 800346F4 80E81D00 */  sll        $sp, $sp, 2
    /* 24EF8 800346F8 FFFFBD33 */  andi       $sp, $sp, 0xFFFF
    /* 24EFC 800346FC 25F0DD03 */  or         $fp, $fp, $sp
    /* 24F00 80034700 00009E48 */  mtc2       $fp, $0 /* handwritten instruction */
    /* 24F04 80034704 FF007D32 */  andi       $sp, $s3, 0xFF
    /* 24F08 80034708 21E8A303 */  addu       $sp, $sp, $v1
    /* 24F0C 8003470C 80E81D00 */  sll        $sp, $sp, 2
    /* 24F10 80034710 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 24F14 80034714 00003696 */  lhu        $s6, 0x0($s1)
    /* 24F18 80034718 02003496 */  lhu        $s4, 0x2($s1)
    /* 24F1C 8003471C 02F21600 */  srl        $fp, $s6, 8
    /* 24F20 80034720 21F0C203 */  addu       $fp, $fp, $v0
    /* 24F24 80034724 80F41E00 */  sll        $fp, $fp, 18
    /* 24F28 80034728 FF00DD32 */  andi       $sp, $s6, 0xFF
    /* 24F2C 8003472C 21E8A103 */  addu       $sp, $sp, $at
    /* 24F30 80034730 80E81D00 */  sll        $sp, $sp, 2
    /* 24F34 80034734 FFFFBD33 */  andi       $sp, $sp, 0xFFFF
    /* 24F38 80034738 25F0DD03 */  or         $fp, $fp, $sp
    /* 24F3C 8003473C 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 24F40 80034740 FF009D32 */  andi       $sp, $s4, 0xFF
    /* 24F44 80034744 21E8A303 */  addu       $sp, $sp, $v1
    /* 24F48 80034748 80E81D00 */  sll        $sp, $sp, 2
    /* 24F4C 8003474C 00189D48 */  mtc2       $sp, $3 /* handwritten instruction */
    /* 24F50 80034750 00005696 */  lhu        $s6, 0x0($s2)
    /* 24F54 80034754 02005596 */  lhu        $s5, 0x2($s2)
    /* 24F58 80034758 02F21600 */  srl        $fp, $s6, 8
    /* 24F5C 8003475C 21F0C203 */  addu       $fp, $fp, $v0
    /* 24F60 80034760 80F41E00 */  sll        $fp, $fp, 18
    /* 24F64 80034764 FF00DD32 */  andi       $sp, $s6, 0xFF
    /* 24F68 80034768 21E8A103 */  addu       $sp, $sp, $at
    /* 24F6C 8003476C 80E81D00 */  sll        $sp, $sp, 2
    /* 24F70 80034770 FFFFBD33 */  andi       $sp, $sp, 0xFFFF
    /* 24F74 80034774 25F0DD03 */  or         $fp, $fp, $sp
    /* 24F78 80034778 00209E48 */  mtc2       $fp, $4 /* handwritten instruction */
    /* 24F7C 8003477C FF00BD32 */  andi       $sp, $s5, 0xFF
    /* 24F80 80034780 21E8A303 */  addu       $sp, $sp, $v1
    /* 24F84 80034784 80E81D00 */  sll        $sp, $sp, 2
    /* 24F88 80034788 00289D48 */  mtc2       $sp, $5 /* handwritten instruction */
    /* 24F8C 8003478C 0000C48D */  lw         $a0, 0x0($t6)
    /* 24F90 80034790 3000284A */  rtpt
    /* 24F94 80034794 00F85D48 */  cfc2       $sp, $31 /* handwritten instruction */
    /* 24F98 80034798 00308448 */  mtc2       $a0, $6 /* handwritten instruction */
    /* 24F9C 8003479C BE00A007 */  bltz       $sp, .L80034A98
    /* 24FA0 800347A0 02B60400 */   srl       $s6, $a0, 24
    /* 24FA4 800347A4 1000DD32 */  andi       $sp, $s6, 0x10
    /* 24FA8 800347A8 0800A017 */  bnez       $sp, .L800347CC
    /* 24FAC 800347AC 00000000 */   nop
    /* 24FB0 800347B0 0600404B */  nclip
    /* 24FB4 800347B4 00C01D48 */  mfc2       $sp, $24 /* handwritten instruction */
    /* 24FB8 800347B8 00000000 */  nop
    /* 24FBC 800347BC B600A013 */  beqz       $sp, .L80034A98
    /* 24FC0 800347C0 26E8A803 */   xor       $sp, $sp, $t0
    /* 24FC4 800347C4 B400A007 */  bltz       $sp, .L80034A98
    /* 24FC8 800347C8 00000000 */   nop
  .L800347CC:
    /* 24FCC 800347CC 06004011 */  beqz       $t2, .L800347E8
    /* 24FD0 800347D0 00000000 */   nop
    /* 24FD4 800347D4 00A08448 */  mtc2       $a0, $20 /* handwritten instruction */
    /* 24FD8 800347D8 00A88448 */  mtc2       $a0, $21 /* handwritten instruction */
    /* 24FDC 800347DC 00B08448 */  mtc2       $a0, $22 /* handwritten instruction */
    /* 24FE0 800347E0 18000104 */  bgez       $zero, .L80034844
    /* 24FE4 800347E4 00000000 */   nop
  .L800347E8:
    /* 24FE8 800347E8 04001096 */  lhu        $s0, 0x4($s0)
    /* 24FEC 800347EC 04003196 */  lhu        $s1, 0x4($s1)
    /* 24FF0 800347F0 04005296 */  lhu        $s2, 0x4($s2)
    /* 24FF4 800347F4 00FF7D32 */  andi       $sp, $s3, 0xFF00
    /* 24FF8 800347F8 00F61000 */  sll        $fp, $s0, 24
    /* 24FFC 800347FC 25E8BE03 */  or         $sp, $sp, $fp
    /* 25000 80034800 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 25004 80034804 00FF1D32 */  andi       $sp, $s0, 0xFF00
    /* 25008 80034808 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 2500C 8003480C 00FF9D32 */  andi       $sp, $s4, 0xFF00
    /* 25010 80034810 00F61100 */  sll        $fp, $s1, 24
    /* 25014 80034814 25E8BE03 */  or         $sp, $sp, $fp
    /* 25018 80034818 00109D48 */  mtc2       $sp, $2 /* handwritten instruction */
    /* 2501C 8003481C 00FF3D32 */  andi       $sp, $s1, 0xFF00
    /* 25020 80034820 00189D48 */  mtc2       $sp, $3 /* handwritten instruction */
    /* 25024 80034824 00FFBD32 */  andi       $sp, $s5, 0xFF00
    /* 25028 80034828 00F61200 */  sll        $fp, $s2, 24
    /* 2502C 8003482C 25E8BE03 */  or         $sp, $sp, $fp
    /* 25030 80034830 00209D48 */  mtc2       $sp, $4 /* handwritten instruction */
    /* 25034 80034834 00FF5D32 */  andi       $sp, $s2, 0xFF00
    /* 25038 80034838 00289D48 */  mtc2       $sp, $5 /* handwritten instruction */
    /* 2503C 8003483C 00000000 */  nop
    /* 25040 80034840 3F04184B */  ncct
  .L80034844:
    /* 25044 80034844 8000DD32 */  andi       $sp, $s6, 0x80
    /* 25048 80034848 6300A013 */  beqz       $sp, .L800349D8
    /* 2504C 8003484C 00000000 */   nop
    /* 25050 80034850 0800ECE8 */  swc2       $12, 0x8($a3)
    /* 25054 80034854 1400EDE8 */  swc2       $13, 0x14($a3)
    /* 25058 80034858 2000EEE8 */  swc2       $14, 0x20($a3)
    /* 2505C 8003485C 00A01D48 */  mfc2       $sp, $20 /* handwritten instruction */
    /* 25060 80034860 1000F5E8 */  swc2       $21, 0x10($a3)
    /* 25064 80034864 1C00F6E8 */  swc2       $22, 0x1C($a3)
    /* 25068 80034868 24E8B903 */  and        $sp, $sp, $t9
    /* 2506C 8003486C 00341E3C */  lui        $fp, (0x34000000 >> 16)
    /* 25070 80034870 25E8BE03 */  or         $sp, $sp, $fp
    /* 25074 80034874 24F0D802 */  and        $fp, $s6, $t8
    /* 25078 80034878 0300D813 */  beq        $fp, $t8, .L80034888
    /* 2507C 8003487C 0800D08D */   lw        $s0, 0x8($t6)
    /* 25080 80034880 00021F3C */  lui        $ra, (0x2000000 >> 16)
    /* 25084 80034884 25E8BF03 */  or         $sp, $sp, $ra
  .L80034888:
    /* 25088 80034888 0400FDAC */  sw         $sp, 0x4($a3)
    /* 2508C 8003488C 0400DD8D */  lw         $sp, 0x4($t6)
    /* 25090 80034890 02951000 */  srl        $s2, $s0, 20
    /* 25094 80034894 0000B18F */  lw         $s1, 0x0($sp)
    /* 25098 80034898 82ED1000 */  srl        $sp, $s0, 22
    /* 2509C 8003489C C0E81D00 */  sll        $sp, $sp, 3
    /* 250A0 800348A0 2170FD02 */  addu       $t6, $s7, $sp
    /* 250A4 800348A4 0000D38D */  lw         $s3, 0x0($t6)
    /* 250A8 800348A8 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 250AC 800348AC 03005232 */  andi       $s2, $s2, 0x3
    /* 250B0 800348B0 C0E91200 */  sll        $sp, $s2, 7
    /* 250B4 800348B4 1C003F32 */  andi       $ra, $s1, 0x1C
    /* 250B8 800348B8 25E8BF03 */  or         $sp, $sp, $ra
    /* 250BC 800348BC 82FC1000 */  srl        $ra, $s0, 18
    /* 250C0 800348C0 0300FF33 */  andi       $ra, $ra, 0x3
    /* 250C4 800348C4 25E8BF03 */  or         $sp, $sp, $ra
    /* 250C8 800348C8 6000DF32 */  andi       $ra, $s6, 0x60
    /* 250CC 800348CC 25E8BF03 */  or         $sp, $sp, $ra
    /* 250D0 800348D0 00EC1D00 */  sll        $sp, $sp, 16
    /* 250D4 800348D4 1F001E32 */  andi       $fp, $s0, 0x1F
    /* 250D8 800348D8 80F01E00 */  sll        $fp, $fp, 2
    /* 250DC 800348DC 80003F32 */  andi       $ra, $s1, 0x80
    /* 250E0 800348E0 25F0DF03 */  or         $fp, $fp, $ra
    /* 250E4 800348E4 00FA1E00 */  sll        $ra, $fp, 8
    /* 250E8 800348E8 82F21000 */  srl        $fp, $s0, 10
    /* 250EC 800348EC F800DE33 */  andi       $fp, $fp, 0xF8
    /* 250F0 800348F0 06F05E02 */  srlv       $fp, $fp, $s2
    /* 250F4 800348F4 2590DF03 */  or         $s2, $fp, $ra
    /* 250F8 800348F8 02F41300 */  srl        $fp, $s3, 16
    /* 250FC 800348FC 21F0D203 */  addu       $fp, $fp, $s2
    /* 25100 80034900 25F8BE03 */  or         $ra, $sp, $fp
    /* 25104 80034904 0F00DD32 */  andi       $sp, $s6, 0xF
    /* 25108 80034908 C01F1E32 */  andi       $fp, $s0, 0x1FC0
    /* 2510C 8003490C 25E8BE03 */  or         $sp, $sp, $fp
    /* 25110 80034910 02F11100 */  srl        $fp, $s1, 4
    /* 25114 80034914 F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 25118 80034918 25E8BE03 */  or         $sp, $sp, $fp
    /* 2511C 8003491C 00EC1D00 */  sll        $sp, $sp, 16
    /* 25120 80034920 FFFF7E32 */  andi       $fp, $s3, 0xFFFF
    /* 25124 80034924 21F0D203 */  addu       $fp, $fp, $s2
    /* 25128 80034928 25F0BE03 */  or         $fp, $sp, $fp
    /* 2512C 8003492C 2170D201 */  addu       $t6, $t6, $s2
    /* 25130 80034930 0C00FEAC */  sw         $fp, 0xC($a3)
    /* 25134 80034934 1800FFAC */  sw         $ra, 0x18($a3)
    /* 25138 80034938 2400EEA4 */  sh         $t6, 0x24($a3)
    /* 2513C 8003493C 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 25140 80034940 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 25144 80034944 1500E011 */  beqz       $t7, .L8003499C
    /* 25148 80034948 00981F48 */   mfc2      $ra, $19 /* handwritten instruction */
    /* 2514C 8003494C 2AB0BE03 */  slt        $s6, $sp, $fp
    /* 25150 80034950 0200C012 */  beqz       $s6, .L8003495C
    /* 25154 80034954 21A0A003 */   addu      $s4, $sp, $zero
    /* 25158 80034958 21A0C003 */  addu       $s4, $fp, $zero
  .L8003495C:
    /* 2515C 8003495C 2AB09F02 */  slt        $s6, $s4, $ra
    /* 25160 80034960 0200C012 */  beqz       $s6, .L8003496C
    /* 25164 80034964 00000000 */   nop
    /* 25168 80034968 21A0E003 */  addu       $s4, $ra, $zero
  .L8003496C:
    /* 2516C 8003496C 2AB0DD03 */  slt        $s6, $fp, $sp
    /* 25170 80034970 0200C012 */  beqz       $s6, .L8003497C
    /* 25174 80034974 21E8A003 */   addu      $sp, $sp, $zero
    /* 25178 80034978 21E8C003 */  addu       $sp, $fp, $zero
  .L8003497C:
    /* 2517C 8003497C 2AB0FD03 */  slt        $s6, $ra, $sp
    /* 25180 80034980 0200C012 */  beqz       $s6, .L8003498C
    /* 25184 80034984 00000000 */   nop
    /* 25188 80034988 21E8E003 */  addu       $sp, $ra, $zero
  .L8003498C:
    /* 2518C 8003498C 21E8B403 */  addu       $sp, $sp, $s4
    /* 25190 80034990 42F01D00 */  srl        $fp, $sp, 1
    /* 25194 80034994 03000104 */  bgez       $zero, .L800349A4
    /* 25198 80034998 21E8BE03 */   addu      $sp, $sp, $fp
  .L8003499C:
    /* 2519C 8003499C 21E8BE03 */  addu       $sp, $sp, $fp
    /* 251A0 800349A0 21E8BF03 */  addu       $sp, $sp, $ra
  .L800349A4:
    /* 251A4 800349A4 42E91D00 */  srl        $sp, $sp, 5
    /* 251A8 800349A8 80E81D00 */  sll        $sp, $sp, 2
    /* 251AC 800349AC 22E83D01 */  sub        $sp, $t1, $sp /* handwritten instruction */
    /* 251B0 800349B0 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 251B4 800349B4 2170BD00 */  addu       $t6, $a1, $sp
    /* 251B8 800349B8 0000DD8D */  lw         $sp, 0x0($t6)
    /* 251BC 800349BC 24F0F900 */  and        $fp, $a3, $t9
    /* 251C0 800349C0 0000DEAD */  sw         $fp, 0x0($t6)
    /* 251C4 800349C4 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 251C8 800349C8 25E8BF03 */  or         $sp, $sp, $ra
    /* 251CC 800349CC 0000FDAC */  sw         $sp, 0x0($a3)
    /* 251D0 800349D0 31000104 */  bgez       $zero, .L80034A98
    /* 251D4 800349D4 2800E724 */   addiu     $a3, $a3, 0x28
  .L800349D8:
    /* 251D8 800349D8 0800ECE8 */  swc2       $12, 0x8($a3)
    /* 251DC 800349DC 1000EDE8 */  swc2       $13, 0x10($a3)
    /* 251E0 800349E0 1800EEE8 */  swc2       $14, 0x18($a3)
    /* 251E4 800349E4 00A01D48 */  mfc2       $sp, $20 /* handwritten instruction */
    /* 251E8 800349E8 0C00F5E8 */  swc2       $21, 0xC($a3)
    /* 251EC 800349EC 1400F6E8 */  swc2       $22, 0x14($a3)
    /* 251F0 800349F0 24E8B903 */  and        $sp, $sp, $t9
    /* 251F4 800349F4 00301F3C */  lui        $ra, (0x30000000 >> 16)
    /* 251F8 800349F8 25E8BF03 */  or         $sp, $sp, $ra
    /* 251FC 800349FC 0400FDAC */  sw         $sp, 0x4($a3)
    /* 25200 80034A00 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 25204 80034A04 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 25208 80034A08 1500E011 */  beqz       $t7, .L80034A60
    /* 2520C 80034A0C 00981F48 */   mfc2      $ra, $19 /* handwritten instruction */
    /* 25210 80034A10 2AB0BE03 */  slt        $s6, $sp, $fp
    /* 25214 80034A14 0200C012 */  beqz       $s6, .L80034A20
    /* 25218 80034A18 21A0A003 */   addu      $s4, $sp, $zero
    /* 2521C 80034A1C 21A0C003 */  addu       $s4, $fp, $zero
  .L80034A20:
    /* 25220 80034A20 2AB09F02 */  slt        $s6, $s4, $ra
    /* 25224 80034A24 0200C012 */  beqz       $s6, .L80034A30
    /* 25228 80034A28 00000000 */   nop
    /* 2522C 80034A2C 21A0E003 */  addu       $s4, $ra, $zero
  .L80034A30:
    /* 25230 80034A30 2AB0DD03 */  slt        $s6, $fp, $sp
    /* 25234 80034A34 0200C012 */  beqz       $s6, .L80034A40
    /* 25238 80034A38 21E8A003 */   addu      $sp, $sp, $zero
    /* 2523C 80034A3C 21E8C003 */  addu       $sp, $fp, $zero
  .L80034A40:
    /* 25240 80034A40 2AB0FD03 */  slt        $s6, $ra, $sp
    /* 25244 80034A44 0200C012 */  beqz       $s6, .L80034A50
    /* 25248 80034A48 00000000 */   nop
    /* 2524C 80034A4C 21E8E003 */  addu       $sp, $ra, $zero
  .L80034A50:
    /* 25250 80034A50 21E8B403 */  addu       $sp, $sp, $s4
    /* 25254 80034A54 42F01D00 */  srl        $fp, $sp, 1
    /* 25258 80034A58 03000104 */  bgez       $zero, .L80034A68
    /* 2525C 80034A5C 21E8BE03 */   addu      $sp, $sp, $fp
  .L80034A60:
    /* 25260 80034A60 21E8BE03 */  addu       $sp, $sp, $fp
    /* 25264 80034A64 21E8BF03 */  addu       $sp, $sp, $ra
  .L80034A68:
    /* 25268 80034A68 C2E81D00 */  srl        $sp, $sp, 3
    /* 2526C 80034A6C 22E83D01 */  sub        $sp, $t1, $sp /* handwritten instruction */
    /* 25270 80034A70 0200A107 */  bgez       $sp, .L80034A7C
    /* 25274 80034A74 FC1FBD33 */   andi      $sp, $sp, 0x1FFC
    /* 25278 80034A78 25E80000 */  or         $sp, $zero, $zero
  .L80034A7C:
    /* 2527C 80034A7C 2170BD00 */  addu       $t6, $a1, $sp
    /* 25280 80034A80 0000DD8D */  lw         $sp, 0x0($t6)
    /* 25284 80034A84 24F0F900 */  and        $fp, $a3, $t9
    /* 25288 80034A88 0000DEAD */  sw         $fp, 0x0($t6)
    /* 2528C 80034A8C 25E8BC03 */  or         $sp, $sp, $gp
    /* 25290 80034A90 0000FDAC */  sw         $sp, 0x0($a3)
    /* 25294 80034A94 1C00E724 */  addiu      $a3, $a3, 0x1C
  .L80034A98:
    /* 25298 80034A98 FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 2529C 80034A9C 00FFA015 */  bnez       $t5, .L800346A0
    /* 252A0 80034AA0 0800C624 */   addiu     $a2, $a2, 0x8
    /* 252A4 80034AA4 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 252A8 80034AA8 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 252AC 80034AAC 00000000 */  nop
    /* 252B0 80034AB0 1800A18F */  lw         $at, 0x18($sp)
    /* 252B4 80034AB4 00000000 */  nop
    /* 252B8 80034AB8 000027AC */  sw         $a3, 0x0($at)
    /* 252BC 80034ABC 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 252C0 80034AC0 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 252C4 80034AC4 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 252C8 80034AC8 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 252CC 80034ACC 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 252D0 80034AD0 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 252D4 80034AD4 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 252D8 80034AD8 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 252DC 80034ADC 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 252E0 80034AE0 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 252E4 80034AE4 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 252E8 80034AE8 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 252EC 80034AEC 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 252F0 80034AF0 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 252F4 80034AF4 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 252F8 80034AF8 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 252FC 80034AFC 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 25300 80034B00 0800E003 */  jr         $ra
    /* 25304 80034B04 00000000 */   nop
endlabel Gte_RTransformSvtx
