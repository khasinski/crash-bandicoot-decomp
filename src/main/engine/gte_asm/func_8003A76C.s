.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_8003A76C
    /* 2AF6C 8003A76C 1000A88F */  lw         $t0, 0x10($sp)
    /* 2AF70 8003A770 1400A98F */  lw         $t1, 0x14($sp)
    /* 2AF74 8003A774 1800AA8F */  lw         $t2, 0x18($sp)
    /* 2AF78 8003A778 80400800 */  sll        $t0, $t0, 2
    /* 2AF7C 8003A77C 23080700 */  negu       $at, $a3
    /* 2AF80 8003A780 FFFFEE30 */  andi       $t6, $a3, 0xFFFF
    /* 2AF84 8003A784 FFFF2D30 */  andi       $t5, $at, 0xFFFF
    /* 2AF88 8003A788 00640700 */  sll        $t4, $a3, 16
    /* 2AF8C 8003A78C 007C0100 */  sll        $t7, $at, 16
    /* 2AF90 8003A790 2508AC01 */  or         $at, $t5, $t4
    /* 2AF94 8003A794 2510CC01 */  or         $v0, $t6, $t4
    /* 2AF98 8003A798 2518AF01 */  or         $v1, $t5, $t7
    /* 2AF9C 8003A79C 2578CF01 */  or         $t7, $t6, $t7
    /* 2AFA0 8003A7A0 0000278D */  lw         $a3, 0x0($t1)
    /* 2AFA4 8003A7A4 0000AC8C */  lw         $t4, 0x0($a1)
    /* 2AFA8 8003A7A8 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 2AFAC 8003A7AC 00088048 */  mtc2       $zero, $1 /* handwritten instruction */
    /* 2AFB0 8003A7B0 00108248 */  mtc2       $v0, $2 /* handwritten instruction */
    /* 2AFB4 8003A7B4 00188048 */  mtc2       $zero, $3 /* handwritten instruction */
    /* 2AFB8 8003A7B8 00208348 */  mtc2       $v1, $4 /* handwritten instruction */
    /* 2AFBC 8003A7BC 00288048 */  mtc2       $zero, $5 /* handwritten instruction */
    /* 2AFC0 8003A7C0 026E0C00 */  srl        $t5, $t4, 24
    /* 2AFC4 8003A7C4 3000284A */  rtpt
    /* 2AFC8 8003A7C8 00F84148 */  cfc2       $at, $31 /* handwritten instruction */
    /* 2AFCC 8003A7CC 00000000 */  nop
    /* 2AFD0 8003A7D0 5C002004 */  bltz       $at, .L8003A944
    /* 2AFD4 8003A7D4 00008F48 */   mtc2      $t7, $0 /* handwritten instruction */
    /* 2AFD8 8003A7D8 00088048 */  mtc2       $zero, $1 /* handwritten instruction */
    /* 2AFDC 8003A7DC 0800ECE8 */  swc2       $12, 0x8($a3)
    /* 2AFE0 8003A7E0 1000EDE8 */  swc2       $13, 0x10($a3)
    /* 2AFE4 8003A7E4 1800EEE8 */  swc2       $14, 0x18($a3)
    /* 2AFE8 8003A7E8 00880F48 */  mfc2       $t7, $17 /* handwritten instruction */
    /* 2AFEC 8003A7EC 00900248 */  mfc2       $v0, $18 /* handwritten instruction */
    /* 2AFF0 8003A7F0 00980348 */  mfc2       $v1, $19 /* handwritten instruction */
    /* 2AFF4 8003A7F4 2178E201 */  addu       $t7, $t7, $v0
    /* 2AFF8 8003A7F8 2178E301 */  addu       $t7, $t7, $v1
    /* 2AFFC 8003A7FC 42790F00 */  srl        $t7, $t7, 5
    /* 2B000 8003A800 80780F00 */  sll        $t7, $t7, 2
    /* 2B004 8003A804 0100184A */  rtps
    /* 2B008 8003A808 00F84148 */  cfc2       $at, $31 /* handwritten instruction */
    /* 2B00C 8003A80C 00000000 */  nop
    /* 2B010 8003A810 4C002004 */  bltz       $at, .L8003A944
    /* 2B014 8003A814 00000000 */   nop
    /* 2B018 8003A818 2000EEE8 */  swc2       $14, 0x20($a3)
    /* 2B01C 8003A81C FF00033C */  lui        $v1, (0xFFFFFF >> 16)
    /* 2B020 8003A820 FFFF6334 */  ori        $v1, $v1, (0xFFFFFF & 0xFFFF)
    /* 2B024 8003A824 24088301 */  and        $at, $t4, $v1
    /* 2B028 8003A828 002C033C */  lui        $v1, (0x2C000000 >> 16)
    /* 2B02C 8003A82C 25082300 */  or         $at, $at, $v1
    /* 2B030 8003A830 60000334 */  ori        $v1, $zero, 0x60
    /* 2B034 8003A834 2410A301 */  and        $v0, $t5, $v1
    /* 2B038 8003A838 03004310 */  beq        $v0, $v1, .L8003A848
    /* 2B03C 8003A83C 0400AB8C */   lw        $t3, 0x4($a1)
    /* 2B040 8003A840 0002033C */  lui        $v1, (0x2000000 >> 16)
    /* 2B044 8003A844 25082300 */  or         $at, $at, $v1
  .L8003A848:
    /* 2B048 8003A848 0400E1AC */  sw         $at, 0x4($a3)
    /* 2B04C 8003A84C 022D0B00 */  srl        $a1, $t3, 20
    /* 2B050 8003A850 820D0B00 */  srl        $at, $t3, 22
    /* 2B054 8003A854 C0080100 */  sll        $at, $at, 3
    /* 2B058 8003A858 21704101 */  addu       $t6, $t2, $at
    /* 2B05C 8003A85C 0000CA8D */  lw         $t2, 0x0($t6)
    /* 2B060 8003A860 0400CE8D */  lw         $t6, 0x4($t6)
    /* 2B064 8003A864 0300A530 */  andi       $a1, $a1, 0x3
    /* 2B068 8003A868 C0090500 */  sll        $at, $a1, 7
    /* 2B06C 8003A86C 1C00C330 */  andi       $v1, $a2, 0x1C
    /* 2B070 8003A870 25082300 */  or         $at, $at, $v1
    /* 2B074 8003A874 821C0B00 */  srl        $v1, $t3, 18
    /* 2B078 8003A878 03006330 */  andi       $v1, $v1, 0x3
    /* 2B07C 8003A87C 25082300 */  or         $at, $at, $v1
    /* 2B080 8003A880 6000A331 */  andi       $v1, $t5, 0x60
    /* 2B084 8003A884 25082300 */  or         $at, $at, $v1
    /* 2B088 8003A888 000C0100 */  sll        $at, $at, 16
    /* 2B08C 8003A88C 1F006231 */  andi       $v0, $t3, 0x1F
    /* 2B090 8003A890 80100200 */  sll        $v0, $v0, 2
    /* 2B094 8003A894 8000C330 */  andi       $v1, $a2, 0x80
    /* 2B098 8003A898 25104300 */  or         $v0, $v0, $v1
    /* 2B09C 8003A89C 001A0200 */  sll        $v1, $v0, 8
    /* 2B0A0 8003A8A0 82120B00 */  srl        $v0, $t3, 10
    /* 2B0A4 8003A8A4 F8004230 */  andi       $v0, $v0, 0xF8
    /* 2B0A8 8003A8A8 0610A200 */  srlv       $v0, $v0, $a1
    /* 2B0AC 8003A8AC 25284300 */  or         $a1, $v0, $v1
    /* 2B0B0 8003A8B0 02140A00 */  srl        $v0, $t2, 16
    /* 2B0B4 8003A8B4 21104500 */  addu       $v0, $v0, $a1
    /* 2B0B8 8003A8B8 25182200 */  or         $v1, $at, $v0
    /* 2B0BC 8003A8BC 0F00A131 */  andi       $at, $t5, 0xF
    /* 2B0C0 8003A8C0 C01F6231 */  andi       $v0, $t3, 0x1FC0
    /* 2B0C4 8003A8C4 25082200 */  or         $at, $at, $v0
    /* 2B0C8 8003A8C8 02110600 */  srl        $v0, $a2, 4
    /* 2B0CC 8003A8CC F0FF4230 */  andi       $v0, $v0, 0xFFF0
    /* 2B0D0 8003A8D0 25082200 */  or         $at, $at, $v0
    /* 2B0D4 8003A8D4 000C0100 */  sll        $at, $at, 16
    /* 2B0D8 8003A8D8 FFFF4231 */  andi       $v0, $t2, 0xFFFF
    /* 2B0DC 8003A8DC 21104500 */  addu       $v0, $v0, $a1
    /* 2B0E0 8003A8E0 25102200 */  or         $v0, $at, $v0
    /* 2B0E4 8003A8E4 FFFFC131 */  andi       $at, $t6, 0xFFFF
    /* 2B0E8 8003A8E8 21082500 */  addu       $at, $at, $a1
    /* 2B0EC 8003A8EC 02740E00 */  srl        $t6, $t6, 16
    /* 2B0F0 8003A8F0 2170C501 */  addu       $t6, $t6, $a1
    /* 2B0F4 8003A8F4 0C00E2AC */  sw         $v0, 0xC($a3)
    /* 2B0F8 8003A8F8 1400E3AC */  sw         $v1, 0x14($a3)
    /* 2B0FC 8003A8FC 1C00E1A4 */  sh         $at, 0x1C($a3)
    /* 2B100 8003A900 2400EEA4 */  sh         $t6, 0x24($a3)
    /* 2B104 8003A904 22780F01 */  sub        $t7, $t0, $t7 /* handwritten instruction */
    /* 2B108 8003A908 FC1FE331 */  andi       $v1, $t7, 0x1FFC
    /* 2B10C 8003A90C 2A786F00 */  slt        $t7, $v1, $t7
    /* 2B110 8003A910 0200E011 */  beqz       $t7, .L8003A91C
    /* 2B114 8003A914 21188300 */   addu      $v1, $a0, $v1
    /* 2B118 8003A918 FC1F8324 */  addiu      $v1, $a0, 0x1FFC
  .L8003A91C:
    /* 2B11C 8003A91C 0000618C */  lw         $at, 0x0($v1)
    /* 2B120 8003A920 FF00043C */  lui        $a0, (0xFFFFFF >> 16)
    /* 2B124 8003A924 FFFF8434 */  ori        $a0, $a0, (0xFFFFFF & 0xFFFF)
    /* 2B128 8003A928 2410E400 */  and        $v0, $a3, $a0
    /* 2B12C 8003A92C 000062AC */  sw         $v0, 0x0($v1)
    /* 2B130 8003A930 0009033C */  lui        $v1, (0x9000000 >> 16)
    /* 2B134 8003A934 25082300 */  or         $at, $at, $v1
    /* 2B138 8003A938 0000E1AC */  sw         $at, 0x0($a3)
    /* 2B13C 8003A93C 2800E124 */  addiu      $at, $a3, 0x28
    /* 2B140 8003A940 000021AD */  sw         $at, 0x0($t1)
  .L8003A944:
    /* 2B144 8003A944 0800E003 */  jr         $ra
    /* 2B148 8003A948 00000000 */   nop
endlabel func_8003A76C
