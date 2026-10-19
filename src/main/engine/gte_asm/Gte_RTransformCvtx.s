.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformCvtx
    /* 25308 80034B08 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 2530C 80034B0C 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 25310 80034B10 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 25314 80034B14 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 25318 80034B18 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2531C 80034B1C 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 25320 80034B20 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 25324 80034B24 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 25328 80034B28 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2532C 80034B2C 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 25330 80034B30 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 25334 80034B34 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 25338 80034B38 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2533C 80034B3C 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 25340 80034B40 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 25344 80034B44 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 25348 80034B48 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2534C 80034B4C 1000A88F */  lw         $t0, 0x10($sp)
    /* 25350 80034B50 1400A98F */  lw         $t1, 0x14($sp)
    /* 25354 80034B54 1800AA8F */  lw         $t2, 0x18($sp)
    /* 25358 80034B58 1C00B78F */  lw         $s7, 0x1C($sp)
    /* 2535C 80034B5C 2000BE8F */  lw         $fp, 0x20($sp)
    /* 25360 80034B60 801F013C */  lui        $at, (0x1F8000E0 >> 16)
    /* 25364 80034B64 E0002134 */  ori        $at, $at, (0x1F8000E0 & 0xFFFF)
    /* 25368 80034B68 0C003EAC */  sw         $fp, 0xC($at)
    /* 2536C 80034B6C FF001F34 */  ori        $ra, $zero, 0xFF
    /* 25370 80034B70 06F0DF03 */  srlv       $fp, $ra, $fp
    /* 25374 80034B74 00FA1E00 */  sll        $ra, $fp, 8
    /* 25378 80034B78 25F0FE03 */  or         $fp, $ra, $fp
    /* 2537C 80034B7C 00FA1F00 */  sll        $ra, $ra, 8
    /* 25380 80034B80 25F0FE03 */  or         $fp, $ra, $fp
    /* 25384 80034B84 10003EAC */  sw         $fp, 0x10($at)
    /* 25388 80034B88 00A85D48 */  cfc2       $sp, $21 /* handwritten instruction */
    /* 2538C 80034B8C 00B05E48 */  cfc2       $fp, $22 /* handwritten instruction */
    /* 25390 80034B90 00B85F48 */  cfc2       $ra, $23 /* handwritten instruction */
    /* 25394 80034B94 00003DAC */  sw         $sp, 0x0($at)
    /* 25398 80034B98 04003EAC */  sw         $fp, 0x4($at)
    /* 2539C 80034B9C 08003FAC */  sw         $ra, 0x8($at)
    /* 253A0 80034BA0 80480900 */  sll        $t1, $t1, 2
    /* 253A4 80034BA4 FF00193C */  lui        $t9, (0xFFFFFF >> 16)
    /* 253A8 80034BA8 FFFF3937 */  ori        $t9, $t9, (0xFFFFFF & 0xFFFF)
    /* 253AC 80034BAC 60001834 */  ori        $t8, $zero, 0x60
    /* 253B0 80034BB0 00061C3C */  lui        $gp, (0x6000000 >> 16)
    /* 253B4 80034BB4 0800818C */  lw         $at, 0x8($a0)
    /* 253B8 80034BB8 0C00828C */  lw         $v0, 0xC($a0)
    /* 253BC 80034BBC 1000838C */  lw         $v1, 0x10($a0)
    /* 253C0 80034BC0 80FF2124 */  addiu      $at, $at, -0x80
    /* 253C4 80034BC4 80FF4224 */  addiu      $v0, $v0, -0x80
    /* 253C8 80034BC8 80FF6324 */  addiu      $v1, $v1, -0x80
    /* 253CC 80034BCC 38008B24 */  addiu      $t3, $a0, 0x38
    /* 253D0 80034BD0 1400EC24 */  addiu      $t4, $a3, 0x14
    /* 253D4 80034BD4 0000ED8C */  lw         $t5, 0x0($a3)
    /* 253D8 80034BD8 0000478D */  lw         $a3, 0x0($t2)
  .L80034BDC:
    /* 253DC 80034BDC 21780000 */  addu       $t7, $zero, $zero
    /* 253E0 80034BE0 0000DD8C */  lw         $sp, 0x0($a2)
    /* 253E4 80034BE4 0400DE8C */  lw         $fp, 0x4($a2)
    /* 253E8 80034BE8 FFFFBF33 */  andi       $ra, $sp, 0xFFFF
    /* 253EC 80034BEC 21807F01 */  addu       $s0, $t3, $ra
    /* 253F0 80034BF0 02FC1D00 */  srl        $ra, $sp, 16
    /* 253F4 80034BF4 21887F01 */  addu       $s1, $t3, $ra
    /* 253F8 80034BF8 FFFFDF33 */  andi       $ra, $fp, 0xFFFF
    /* 253FC 80034BFC 21907F01 */  addu       $s2, $t3, $ra
    /* 25400 80034C00 02FC1E00 */  srl        $ra, $fp, 16
    /* 25404 80034C04 FF7FFF33 */  andi       $ra, $ra, 0x7FFF
    /* 25408 80034C08 80F81F00 */  sll        $ra, $ra, 2
    /* 2540C 80034C0C 21709F01 */  addu       $t6, $t4, $ra
    /* 25410 80034C10 00001696 */  lhu        $s6, 0x0($s0)
    /* 25414 80034C14 02001396 */  lhu        $s3, 0x2($s0)
    /* 25418 80034C18 02F21600 */  srl        $fp, $s6, 8
    /* 2541C 80034C1C 21F0C203 */  addu       $fp, $fp, $v0
    /* 25420 80034C20 80F41E00 */  sll        $fp, $fp, 18
    /* 25424 80034C24 FF00DD32 */  andi       $sp, $s6, 0xFF
    /* 25428 80034C28 21E8A103 */  addu       $sp, $sp, $at
    /* 2542C 80034C2C 80E81D00 */  sll        $sp, $sp, 2
    /* 25430 80034C30 FFFFBD33 */  andi       $sp, $sp, 0xFFFF
    /* 25434 80034C34 25F0DD03 */  or         $fp, $fp, $sp
    /* 25438 80034C38 00009E48 */  mtc2       $fp, $0 /* handwritten instruction */
    /* 2543C 80034C3C FF007D32 */  andi       $sp, $s3, 0xFF
    /* 25440 80034C40 21E8A303 */  addu       $sp, $sp, $v1
    /* 25444 80034C44 80E81D00 */  sll        $sp, $sp, 2
    /* 25448 80034C48 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 2544C 80034C4C 00003696 */  lhu        $s6, 0x0($s1)
    /* 25450 80034C50 02003496 */  lhu        $s4, 0x2($s1)
    /* 25454 80034C54 02F21600 */  srl        $fp, $s6, 8
    /* 25458 80034C58 21F0C203 */  addu       $fp, $fp, $v0
    /* 2545C 80034C5C 80F41E00 */  sll        $fp, $fp, 18
    /* 25460 80034C60 FF00DD32 */  andi       $sp, $s6, 0xFF
    /* 25464 80034C64 21E8A103 */  addu       $sp, $sp, $at
    /* 25468 80034C68 80E81D00 */  sll        $sp, $sp, 2
    /* 2546C 80034C6C FFFFBD33 */  andi       $sp, $sp, 0xFFFF
    /* 25470 80034C70 25F0DD03 */  or         $fp, $fp, $sp
    /* 25474 80034C74 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 25478 80034C78 FF009D32 */  andi       $sp, $s4, 0xFF
    /* 2547C 80034C7C 21E8A303 */  addu       $sp, $sp, $v1
    /* 25480 80034C80 80E81D00 */  sll        $sp, $sp, 2
    /* 25484 80034C84 00189D48 */  mtc2       $sp, $3 /* handwritten instruction */
    /* 25488 80034C88 00005696 */  lhu        $s6, 0x0($s2)
    /* 2548C 80034C8C 02005596 */  lhu        $s5, 0x2($s2)
    /* 25490 80034C90 02F21600 */  srl        $fp, $s6, 8
    /* 25494 80034C94 21F0C203 */  addu       $fp, $fp, $v0
    /* 25498 80034C98 80F41E00 */  sll        $fp, $fp, 18
    /* 2549C 80034C9C FF00DD32 */  andi       $sp, $s6, 0xFF
    /* 254A0 80034CA0 21E8A103 */  addu       $sp, $sp, $at
    /* 254A4 80034CA4 80E81D00 */  sll        $sp, $sp, 2
    /* 254A8 80034CA8 FFFFBD33 */  andi       $sp, $sp, 0xFFFF
    /* 254AC 80034CAC 25F0DD03 */  or         $fp, $fp, $sp
    /* 254B0 80034CB0 00209E48 */  mtc2       $fp, $4 /* handwritten instruction */
    /* 254B4 80034CB4 FF00BD32 */  andi       $sp, $s5, 0xFF
    /* 254B8 80034CB8 21E8A303 */  addu       $sp, $sp, $v1
    /* 254BC 80034CBC 80E81D00 */  sll        $sp, $sp, 2
    /* 254C0 80034CC0 00289D48 */  mtc2       $sp, $5 /* handwritten instruction */
    /* 254C4 80034CC4 0000C48D */  lw         $a0, 0x0($t6)
    /* 254C8 80034CC8 00000000 */  nop
    /* 254CC 80034CCC 3000284A */  rtpt
    /* 254D0 80034CD0 00F85D48 */  cfc2       $sp, $31 /* handwritten instruction */
    /* 254D4 80034CD4 00000000 */  nop
    /* 254D8 80034CD8 0901A007 */  bltz       $sp, .L80035100
    /* 254DC 80034CDC 02B60400 */   srl       $s6, $a0, 24
    /* 254E0 80034CE0 1000DD32 */  andi       $sp, $s6, 0x10
    /* 254E4 80034CE4 2A01A017 */  bnez       $sp, .L80035190
    /* 254E8 80034CE8 00000000 */   nop
    /* 254EC 80034CEC 0600404B */  nclip
    /* 254F0 80034CF0 00C01D48 */  mfc2       $sp, $24 /* handwritten instruction */
    /* 254F4 80034CF4 00000000 */  nop
    /* 254F8 80034CF8 0101A013 */  beqz       $sp, .L80035100
    /* 254FC 80034CFC 26E8A803 */   xor       $sp, $sp, $t0
    /* 25500 80034D00 FF00A007 */  bltz       $sp, .L80035100
    /* 25504 80034D04 00000000 */   nop
  .L80034D08:
    /* 25508 80034D08 04001096 */  lhu        $s0, 0x4($s0)
    /* 2550C 80034D0C 04003196 */  lhu        $s1, 0x4($s1)
    /* 25510 80034D10 04005296 */  lhu        $s2, 0x4($s2)
    /* 25514 80034D14 FF009D30 */  andi       $sp, $a0, 0xFF
    /* 25518 80034D18 8000BE2F */  sltiu      $fp, $sp, 0x80
    /* 2551C 80034D1C 0700C013 */  beqz       $fp, .L80034D3C
    /* 25520 80034D20 00000000 */   nop
    /* 25524 80034D24 00A8C048 */  ctc2       $zero, $21 /* handwritten instruction */
    /* 25528 80034D28 00B0C048 */  ctc2       $zero, $22 /* handwritten instruction */
    /* 2552C 80034D2C 00B8C048 */  ctc2       $zero, $23 /* handwritten instruction */
    /* 25530 80034D30 7F001E34 */  ori        $fp, $zero, 0x7F
    /* 25534 80034D34 06000104 */  bgez       $zero, .L80034D50
    /* 25538 80034D38 23E8DD03 */   subu      $sp, $fp, $sp
  .L80034D3C:
    /* 2553C 80034D3C F00F1E34 */  ori        $fp, $zero, 0xFF0
    /* 25540 80034D40 00A8DE48 */  ctc2       $fp, $21 /* handwritten instruction */
    /* 25544 80034D44 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 25548 80034D48 00B8DE48 */  ctc2       $fp, $23 /* handwritten instruction */
    /* 2554C 80034D4C 80FFBD27 */  addiu      $sp, $sp, -0x80
  .L80034D50:
    /* 25550 80034D50 40E91D00 */  sll        $sp, $sp, 5
    /* 25554 80034D54 00409D48 */  mtc2       $sp, $8 /* handwritten instruction */
    /* 25558 80034D58 029A1300 */  srl        $s3, $s3, 8
    /* 2555C 80034D5C 02A21400 */  srl        $s4, $s4, 8
    /* 25560 80034D60 02AA1500 */  srl        $s5, $s5, 8
    /* 25564 80034D64 00F21400 */  sll        $fp, $s4, 8
    /* 25568 80034D68 25E87E02 */  or         $sp, $s3, $fp
    /* 2556C 80034D6C 00F41500 */  sll        $fp, $s5, 16
    /* 25570 80034D70 25E8BE03 */  or         $sp, $sp, $fp
    /* 25574 80034D74 00309D48 */  mtc2       $sp, $6 /* handwritten instruction */
    /* 25578 80034D78 00000000 */  nop
    /* 2557C 80034D7C 00000000 */  nop
    /* 25580 80034D80 1000784A */  dpcs
    /* 25584 80034D84 00000000 */  nop
    /* 25588 80034D88 00000000 */  nop
    /* 2558C 80034D8C 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 25590 80034D90 00000000 */  nop
    /* 25594 80034D94 00000000 */  nop
    /* 25598 80034D98 FF00B333 */  andi       $s3, $sp, 0xFF
    /* 2559C 80034D9C 02A21D00 */  srl        $s4, $sp, 8
    /* 255A0 80034DA0 FF009432 */  andi       $s4, $s4, 0xFF
    /* 255A4 80034DA4 02AC1D00 */  srl        $s5, $sp, 16
    /* 255A8 80034DA8 FF00B532 */  andi       $s5, $s5, 0xFF
    /* 255AC 80034DAC 02EA0400 */  srl        $sp, $a0, 8
    /* 255B0 80034DB0 FF00BD33 */  andi       $sp, $sp, 0xFF
    /* 255B4 80034DB4 8000BE2F */  sltiu      $fp, $sp, 0x80
    /* 255B8 80034DB8 0700C013 */  beqz       $fp, .L80034DD8
    /* 255BC 80034DBC 00000000 */   nop
    /* 255C0 80034DC0 00A8C048 */  ctc2       $zero, $21 /* handwritten instruction */
    /* 255C4 80034DC4 00B0C048 */  ctc2       $zero, $22 /* handwritten instruction */
    /* 255C8 80034DC8 00B8C048 */  ctc2       $zero, $23 /* handwritten instruction */
    /* 255CC 80034DCC 7F001E34 */  ori        $fp, $zero, 0x7F
    /* 255D0 80034DD0 06000104 */  bgez       $zero, .L80034DEC
    /* 255D4 80034DD4 23E8DD03 */   subu      $sp, $fp, $sp
  .L80034DD8:
    /* 255D8 80034DD8 F00F1E34 */  ori        $fp, $zero, 0xFF0
    /* 255DC 80034DDC 00A8DE48 */  ctc2       $fp, $21 /* handwritten instruction */
    /* 255E0 80034DE0 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 255E4 80034DE4 00B8DE48 */  ctc2       $fp, $23 /* handwritten instruction */
    /* 255E8 80034DE8 80FFBD27 */  addiu      $sp, $sp, -0x80
  .L80034DEC:
    /* 255EC 80034DEC 40E91D00 */  sll        $sp, $sp, 5
    /* 255F0 80034DF0 00409D48 */  mtc2       $sp, $8 /* handwritten instruction */
    /* 255F4 80034DF4 FF001D32 */  andi       $sp, $s0, 0xFF
    /* 255F8 80034DF8 FF003E32 */  andi       $fp, $s1, 0xFF
    /* 255FC 80034DFC 00F21E00 */  sll        $fp, $fp, 8
    /* 25600 80034E00 FF005F32 */  andi       $ra, $s2, 0xFF
    /* 25604 80034E04 00FC1F00 */  sll        $ra, $ra, 16
    /* 25608 80034E08 25E8BE03 */  or         $sp, $sp, $fp
    /* 2560C 80034E0C 25E8BF03 */  or         $sp, $sp, $ra
    /* 25610 80034E10 00309D48 */  mtc2       $sp, $6 /* handwritten instruction */
    /* 25614 80034E14 00000000 */  nop
    /* 25618 80034E18 00000000 */  nop
    /* 2561C 80034E1C 1000784A */  dpcs
    /* 25620 80034E20 00000000 */  nop
    /* 25624 80034E24 00000000 */  nop
    /* 25628 80034E28 02EA1000 */  srl        $sp, $s0, 8
    /* 2562C 80034E2C 00FF3E32 */  andi       $fp, $s1, 0xFF00
    /* 25630 80034E30 00FF5F32 */  andi       $ra, $s2, 0xFF00
    /* 25634 80034E34 00FA1F00 */  sll        $ra, $ra, 8
    /* 25638 80034E38 25E8BE03 */  or         $sp, $sp, $fp
    /* 2563C 80034E3C 25E8BF03 */  or         $sp, $sp, $ra
    /* 25640 80034E40 00309D48 */  mtc2       $sp, $6 /* handwritten instruction */
    /* 25644 80034E44 00B01048 */  mfc2       $s0, $22 /* handwritten instruction */
    /* 25648 80034E48 00000000 */  nop
    /* 2564C 80034E4C 00000000 */  nop
    /* 25650 80034E50 00FF1132 */  andi       $s1, $s0, 0xFF00
    /* 25654 80034E54 02921000 */  srl        $s2, $s0, 8
    /* 25658 80034E58 00FF5232 */  andi       $s2, $s2, 0xFF00
    /* 2565C 80034E5C 00821000 */  sll        $s0, $s0, 8
    /* 25660 80034E60 00FF1032 */  andi       $s0, $s0, 0xFF00
    /* 25664 80034E64 25987002 */  or         $s3, $s3, $s0
    /* 25668 80034E68 25A09102 */  or         $s4, $s4, $s1
    /* 2566C 80034E6C 25A8B202 */  or         $s5, $s5, $s2
    /* 25670 80034E70 02EC0400 */  srl        $sp, $a0, 16
    /* 25674 80034E74 FF00BD33 */  andi       $sp, $sp, 0xFF
    /* 25678 80034E78 8000BE2F */  sltiu      $fp, $sp, 0x80
    /* 2567C 80034E7C 0700C013 */  beqz       $fp, .L80034E9C
    /* 25680 80034E80 00000000 */   nop
    /* 25684 80034E84 00A8C048 */  ctc2       $zero, $21 /* handwritten instruction */
    /* 25688 80034E88 00B0C048 */  ctc2       $zero, $22 /* handwritten instruction */
    /* 2568C 80034E8C 00B8C048 */  ctc2       $zero, $23 /* handwritten instruction */
    /* 25690 80034E90 7F001E34 */  ori        $fp, $zero, 0x7F
    /* 25694 80034E94 06000104 */  bgez       $zero, .L80034EB0
    /* 25698 80034E98 23E8DD03 */   subu      $sp, $fp, $sp
  .L80034E9C:
    /* 2569C 80034E9C F00F1E34 */  ori        $fp, $zero, 0xFF0
    /* 256A0 80034EA0 00A8DE48 */  ctc2       $fp, $21 /* handwritten instruction */
    /* 256A4 80034EA4 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 256A8 80034EA8 00B8DE48 */  ctc2       $fp, $23 /* handwritten instruction */
    /* 256AC 80034EAC 80FFBD27 */  addiu      $sp, $sp, -0x80
  .L80034EB0:
    /* 256B0 80034EB0 40E91D00 */  sll        $sp, $sp, 5
    /* 256B4 80034EB4 00409D48 */  mtc2       $sp, $8 /* handwritten instruction */
    /* 256B8 80034EB8 00000000 */  nop
    /* 256BC 80034EBC 00000000 */  nop
    /* 256C0 80034EC0 1000784A */  dpcs
    /* 256C4 80034EC4 00000000 */  nop
    /* 256C8 80034EC8 00000000 */  nop
    /* 256CC 80034ECC 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 256D0 80034ED0 00000000 */  nop
    /* 256D4 80034ED4 00000000 */  nop
    /* 256D8 80034ED8 FF00B033 */  andi       $s0, $sp, 0xFF
    /* 256DC 80034EDC 00841000 */  sll        $s0, $s0, 16
    /* 256E0 80034EE0 00FFB133 */  andi       $s1, $sp, 0xFF00
    /* 256E4 80034EE4 008A1100 */  sll        $s1, $s1, 8
    /* 256E8 80034EE8 FF001E3C */  lui        $fp, (0xFF0000 >> 16)
    /* 256EC 80034EEC 2490BE03 */  and        $s2, $sp, $fp
    /* 256F0 80034EF0 25987002 */  or         $s3, $s3, $s0
    /* 256F4 80034EF4 25A09102 */  or         $s4, $s4, $s1
    /* 256F8 80034EF8 25A8B202 */  or         $s5, $s5, $s2
    /* 256FC 80034EFC 8000DD32 */  andi       $sp, $s6, 0x80
    /* 25700 80034F00 5900A013 */  beqz       $sp, .L80035068
    /* 25704 80034F04 00000000 */   nop
    /* 25708 80034F08 0800ECE8 */  swc2       $12, 0x8($a3)
    /* 2570C 80034F0C 1400EDE8 */  swc2       $13, 0x14($a3)
    /* 25710 80034F10 2000EEE8 */  swc2       $14, 0x20($a3)
    /* 25714 80034F14 801F1D3C */  lui        $sp, (0x1F8000EC >> 16)
    /* 25718 80034F18 EC00BD37 */  ori        $sp, $sp, (0x1F8000EC & 0xFFFF)
    /* 2571C 80034F1C 0000BE8F */  lw         $fp, 0x0($sp)
    /* 25720 80034F20 00000000 */  nop
    /* 25724 80034F24 0700C013 */  beqz       $fp, .L80034F44
    /* 25728 80034F28 0698D303 */   srlv      $s3, $s3, $fp
    /* 2572C 80034F2C 06A0D403 */  srlv       $s4, $s4, $fp
    /* 25730 80034F30 0400BD8F */  lw         $sp, 0x4($sp)
    /* 25734 80034F34 06A8D503 */  srlv       $s5, $s5, $fp
    /* 25738 80034F38 24987D02 */  and        $s3, $s3, $sp
    /* 2573C 80034F3C 24A09D02 */  and        $s4, $s4, $sp
    /* 25740 80034F40 24A8BD02 */  and        $s5, $s5, $sp
  .L80034F44:
    /* 25744 80034F44 00341E3C */  lui        $fp, (0x34000000 >> 16)
    /* 25748 80034F48 25987E02 */  or         $s3, $s3, $fp
    /* 2574C 80034F4C 24F0D802 */  and        $fp, $s6, $t8
    /* 25750 80034F50 0300D813 */  beq        $fp, $t8, .L80034F60
    /* 25754 80034F54 0800D08D */   lw        $s0, 0x8($t6)
    /* 25758 80034F58 00021D3C */  lui        $sp, (0x2000000 >> 16)
    /* 2575C 80034F5C 25987D02 */  or         $s3, $s3, $sp
  .L80034F60:
    /* 25760 80034F60 0400F3AC */  sw         $s3, 0x4($a3)
    /* 25764 80034F64 1000F4AC */  sw         $s4, 0x10($a3)
    /* 25768 80034F68 1C00F5AC */  sw         $s5, 0x1C($a3)
    /* 2576C 80034F6C 0400DD8D */  lw         $sp, 0x4($t6)
    /* 25770 80034F70 02951000 */  srl        $s2, $s0, 20
    /* 25774 80034F74 0000B18F */  lw         $s1, 0x0($sp)
    /* 25778 80034F78 82ED1000 */  srl        $sp, $s0, 22
    /* 2577C 80034F7C C0E81D00 */  sll        $sp, $sp, 3
    /* 25780 80034F80 2170FD02 */  addu       $t6, $s7, $sp
    /* 25784 80034F84 0000D38D */  lw         $s3, 0x0($t6)
    /* 25788 80034F88 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 2578C 80034F8C 03005232 */  andi       $s2, $s2, 0x3
    /* 25790 80034F90 C0E91200 */  sll        $sp, $s2, 7
    /* 25794 80034F94 1C003F32 */  andi       $ra, $s1, 0x1C
    /* 25798 80034F98 25E8BF03 */  or         $sp, $sp, $ra
    /* 2579C 80034F9C 82FC1000 */  srl        $ra, $s0, 18
    /* 257A0 80034FA0 0300FF33 */  andi       $ra, $ra, 0x3
    /* 257A4 80034FA4 25E8BF03 */  or         $sp, $sp, $ra
    /* 257A8 80034FA8 6000DF32 */  andi       $ra, $s6, 0x60
    /* 257AC 80034FAC 25E8BF03 */  or         $sp, $sp, $ra
    /* 257B0 80034FB0 00EC1D00 */  sll        $sp, $sp, 16
    /* 257B4 80034FB4 1F001E32 */  andi       $fp, $s0, 0x1F
    /* 257B8 80034FB8 80F01E00 */  sll        $fp, $fp, 2
    /* 257BC 80034FBC 80003F32 */  andi       $ra, $s1, 0x80
    /* 257C0 80034FC0 25F0DF03 */  or         $fp, $fp, $ra
    /* 257C4 80034FC4 00FA1E00 */  sll        $ra, $fp, 8
    /* 257C8 80034FC8 82F21000 */  srl        $fp, $s0, 10
    /* 257CC 80034FCC F800DE33 */  andi       $fp, $fp, 0xF8
    /* 257D0 80034FD0 06F05E02 */  srlv       $fp, $fp, $s2
    /* 257D4 80034FD4 2590DF03 */  or         $s2, $fp, $ra
    /* 257D8 80034FD8 02F41300 */  srl        $fp, $s3, 16
    /* 257DC 80034FDC 21F0D203 */  addu       $fp, $fp, $s2
    /* 257E0 80034FE0 25F8BE03 */  or         $ra, $sp, $fp
    /* 257E4 80034FE4 0F00DD32 */  andi       $sp, $s6, 0xF
    /* 257E8 80034FE8 C01F1E32 */  andi       $fp, $s0, 0x1FC0
    /* 257EC 80034FEC 25E8BE03 */  or         $sp, $sp, $fp
    /* 257F0 80034FF0 02F11100 */  srl        $fp, $s1, 4
    /* 257F4 80034FF4 F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 257F8 80034FF8 25E8BE03 */  or         $sp, $sp, $fp
    /* 257FC 80034FFC 00EC1D00 */  sll        $sp, $sp, 16
    /* 25800 80035000 FFFF7E32 */  andi       $fp, $s3, 0xFFFF
    /* 25804 80035004 21F0D203 */  addu       $fp, $fp, $s2
    /* 25808 80035008 25F0BE03 */  or         $fp, $sp, $fp
    /* 2580C 8003500C 2170D201 */  addu       $t6, $t6, $s2
    /* 25810 80035010 0C00FEAC */  sw         $fp, 0xC($a3)
    /* 25814 80035014 1800FFAC */  sw         $ra, 0x18($a3)
    /* 25818 80035018 2400EEA4 */  sh         $t6, 0x24($a3)
    /* 2581C 8003501C 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 25820 80035020 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 25824 80035024 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 25828 80035028 21E8BE03 */  addu       $sp, $sp, $fp
    /* 2582C 8003502C 21E8BF03 */  addu       $sp, $sp, $ra
    /* 25830 80035030 42E91D00 */  srl        $sp, $sp, 5
    /* 25834 80035034 80E81D00 */  sll        $sp, $sp, 2
    /* 25838 80035038 20E8AF03 */  add        $sp, $sp, $t7 /* handwritten instruction */
    /* 2583C 8003503C 22E83D01 */  sub        $sp, $t1, $sp /* handwritten instruction */
    /* 25840 80035040 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 25844 80035044 2170BD00 */  addu       $t6, $a1, $sp
    /* 25848 80035048 0000DD8D */  lw         $sp, 0x0($t6)
    /* 2584C 8003504C 24F0F900 */  and        $fp, $a3, $t9
    /* 25850 80035050 0000DEAD */  sw         $fp, 0x0($t6)
    /* 25854 80035054 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 25858 80035058 25E8BF03 */  or         $sp, $sp, $ra
    /* 2585C 8003505C 0000FDAC */  sw         $sp, 0x0($a3)
    /* 25860 80035060 27000104 */  bgez       $zero, .L80035100
    /* 25864 80035064 2800E724 */   addiu     $a3, $a3, 0x28
  .L80035068:
    /* 25868 80035068 0800ECE8 */  swc2       $12, 0x8($a3)
    /* 2586C 8003506C 1000EDE8 */  swc2       $13, 0x10($a3)
    /* 25870 80035070 1800EEE8 */  swc2       $14, 0x18($a3)
    /* 25874 80035074 801F1D3C */  lui        $sp, (0x1F8000EC >> 16)
    /* 25878 80035078 EC00BD37 */  ori        $sp, $sp, (0x1F8000EC & 0xFFFF)
    /* 2587C 8003507C 0000BE8F */  lw         $fp, 0x0($sp)
    /* 25880 80035080 00000000 */  nop
    /* 25884 80035084 0700C013 */  beqz       $fp, .L800350A4
    /* 25888 80035088 0698D303 */   srlv      $s3, $s3, $fp
    /* 2588C 8003508C 06A0D403 */  srlv       $s4, $s4, $fp
    /* 25890 80035090 0400BD8F */  lw         $sp, 0x4($sp)
    /* 25894 80035094 06A8D503 */  srlv       $s5, $s5, $fp
    /* 25898 80035098 24987D02 */  and        $s3, $s3, $sp
    /* 2589C 8003509C 24A09D02 */  and        $s4, $s4, $sp
    /* 258A0 800350A0 24A8BD02 */  and        $s5, $s5, $sp
  .L800350A4:
    /* 258A4 800350A4 00301F3C */  lui        $ra, (0x30000000 >> 16)
    /* 258A8 800350A8 25987F02 */  or         $s3, $s3, $ra
    /* 258AC 800350AC 0400F3AC */  sw         $s3, 0x4($a3)
    /* 258B0 800350B0 0C00F4AC */  sw         $s4, 0xC($a3)
    /* 258B4 800350B4 1400F5AC */  sw         $s5, 0x14($a3)
    /* 258B8 800350B8 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 258BC 800350BC 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 258C0 800350C0 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 258C4 800350C4 21E8BE03 */  addu       $sp, $sp, $fp
    /* 258C8 800350C8 21E8BF03 */  addu       $sp, $sp, $ra
    /* 258CC 800350CC C2E81D00 */  srl        $sp, $sp, 3
    /* 258D0 800350D0 20E8AF03 */  add        $sp, $sp, $t7 /* handwritten instruction */
    /* 258D4 800350D4 22E83D01 */  sub        $sp, $t1, $sp /* handwritten instruction */
    /* 258D8 800350D8 0200A107 */  bgez       $sp, .L800350E4
    /* 258DC 800350DC FC1FBD33 */   andi      $sp, $sp, 0x1FFC
    /* 258E0 800350E0 25E80000 */  or         $sp, $zero, $zero
  .L800350E4:
    /* 258E4 800350E4 2170BD00 */  addu       $t6, $a1, $sp
    /* 258E8 800350E8 0000DD8D */  lw         $sp, 0x0($t6)
    /* 258EC 800350EC 24F0F900 */  and        $fp, $a3, $t9
    /* 258F0 800350F0 0000DEAD */  sw         $fp, 0x0($t6)
    /* 258F4 800350F4 25E8BC03 */  or         $sp, $sp, $gp
    /* 258F8 800350F8 0000FDAC */  sw         $sp, 0x0($a3)
    /* 258FC 800350FC 1C00E724 */  addiu      $a3, $a3, 0x1C
  .L80035100:
    /* 25900 80035100 FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 25904 80035104 B5FEA015 */  bnez       $t5, .L80034BDC
    /* 25908 80035108 0800C624 */   addiu     $a2, $a2, 0x8
    /* 2590C 8003510C 801F013C */  lui        $at, (0x1F8000E0 >> 16)
    /* 25910 80035110 E0002134 */  ori        $at, $at, (0x1F8000E0 & 0xFFFF)
    /* 25914 80035114 00003D8C */  lw         $sp, 0x0($at)
    /* 25918 80035118 04003E8C */  lw         $fp, 0x4($at)
    /* 2591C 8003511C 08003F8C */  lw         $ra, 0x8($at)
    /* 25920 80035120 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 25924 80035124 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 25928 80035128 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 2592C 8003512C 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 25930 80035130 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 25934 80035134 00000000 */  nop
    /* 25938 80035138 1800A18F */  lw         $at, 0x18($sp)
    /* 2593C 8003513C 00000000 */  nop
    /* 25940 80035140 000027AC */  sw         $a3, 0x0($at)
    /* 25944 80035144 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 25948 80035148 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2594C 8003514C 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 25950 80035150 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 25954 80035154 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 25958 80035158 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2595C 8003515C 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 25960 80035160 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 25964 80035164 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 25968 80035168 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2596C 8003516C 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 25970 80035170 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 25974 80035174 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 25978 80035178 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2597C 8003517C 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 25980 80035180 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 25984 80035184 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 25988 80035188 0800E003 */  jr         $ra
    /* 2598C 8003518C 00000000 */   nop
  .L80035190:
    /* 25990 80035190 0600404B */  nclip
    /* 25994 80035194 00C01D48 */  mfc2       $sp, $24 /* handwritten instruction */
    /* 25998 80035198 00000000 */  nop
    /* 2599C 8003519C 0500A013 */  beqz       $sp, .L800351B4
    /* 259A0 800351A0 26E8A803 */   xor       $sp, $sp, $t0
    /* 259A4 800351A4 0300A007 */  bltz       $sp, .L800351B4
    /* 259A8 800351A8 00000000 */   nop
    /* 259AC 800351AC D6FE0104 */  bgez       $zero, .L80034D08
    /* 259B0 800351B0 00000000 */   nop
  .L800351B4:
    /* 259B4 800351B4 DFFF1D24 */  addiu      $sp, $zero, -0x21
    /* 259B8 800351B8 24B0DD02 */  and        $s6, $s6, $sp
    /* 259BC 800351BC D2FE0104 */  bgez       $zero, .L80034D08
    /* 259C0 800351C0 30000F34 */   ori       $t7, $zero, 0x30
endlabel Gte_RTransformCvtx
    /* 259C4 800351C4 00000000 */  nop
