.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_80036340
    /* 26B40 80036340 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 26B44 80036344 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 26B48 80036348 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 26B4C 8003634C 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 26B50 80036350 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 26B54 80036354 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 26B58 80036358 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 26B5C 8003635C 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 26B60 80036360 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 26B64 80036364 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 26B68 80036368 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 26B6C 8003636C 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 26B70 80036370 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 26B74 80036374 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 26B78 80036378 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 26B7C 8003637C 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 26B80 80036380 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 26B84 80036384 1000AF8F */  lw         $t7, 0x10($sp)
    /* 26B88 80036388 1400B68F */  lw         $s6, 0x14($sp)
    /* 26B8C 8003638C 0000EB8D */  lw         $t3, 0x0($t7)
    /* 26B90 80036390 801F1D3C */  lui        $sp, (0x1F8000E0 >> 16)
    /* 26B94 80036394 E000BD37 */  ori        $sp, $sp, (0x1F8000E0 & 0xFFFF)
    /* 26B98 80036398 0000A7AF */  sw         $a3, 0x0($sp)
    /* 26B9C 8003639C FF001C3C */  lui        $gp, (0xFFFFFF >> 16)
    /* 26BA0 800363A0 FFFF9C37 */  ori        $gp, $gp, (0xFFFFFF & 0xFFFF)
    /* 26BA4 800363A4 60000F34 */  ori        $t7, $zero, 0x60
    /* 26BA8 800363A8 801F083C */  lui        $t0, (0x1F800100 >> 16)
    /* 26BAC 800363AC 00010835 */  ori        $t0, $t0, (0x1F800100 & 0xFFFF)
    /* 26BB0 800363B0 00008D8C */  lw         $t5, 0x0($a0)
    /* 26BB4 800363B4 02008A24 */  addiu      $t2, $a0, 0x2
    /* 26BB8 800363B8 21504D01 */  addu       $t2, $t2, $t5
    /* 26BBC 800363BC 21504D01 */  addu       $t2, $t2, $t5
    /* 26BC0 800363C0 FFFF0C34 */  ori        $t4, $zero, 0xFFFF
    /* 26BC4 800363C4 0002043C */  lui        $a0, (0x2000000 >> 16)
    /* 26BC8 800363C8 00004195 */  lhu        $at, 0x0($t2)
    /* 26BCC 800363CC 80300600 */  sll        $a2, $a2, 2
    /* 26BD0 800363D0 FC1F0334 */  ori        $v1, $zero, 0x1FFC
  .L800363D4:
    /* 26BD4 800363D4 FEFF4A25 */  addiu      $t2, $t2, -0x2
    /* 26BD8 800363D8 02F30100 */  srl        $fp, $at, 12
    /* 26BDC 800363DC 0E00CC13 */  beq        $fp, $t4, .L80036418
    /* 26BE0 800363E0 FF0F2130 */   andi      $at, $at, 0xFFF
    /* 26BE4 800363E4 2160C003 */  addu       $t4, $fp, $zero
    /* 26BE8 800363E8 80F90C00 */  sll        $ra, $t4, 6
    /* 26BEC 800363EC 2110E803 */  addu       $v0, $ra, $t0
    /* 26BF0 800363F0 04005D8C */  lw         $sp, 0x4($v0)
    /* 26BF4 800363F4 08005E8C */  lw         $fp, 0x8($v0)
    /* 26BF8 800363F8 0C005F8C */  lw         $ra, 0xC($v0)
    /* 26BFC 800363FC 0028DD48 */  ctc2       $sp, $5 /* handwritten instruction */
    /* 26C00 80036400 0030DE48 */  ctc2       $fp, $6 /* handwritten instruction */
    /* 26C04 80036404 0038DF48 */  ctc2       $ra, $7 /* handwritten instruction */
    /* 26C08 80036408 1400578C */  lw         $s7, 0x14($v0)
    /* 26C0C 8003640C 1800588C */  lw         $t8, 0x18($v0)
    /* 26C10 80036410 1C00598C */  lw         $t9, 0x1C($v0)
    /* 26C14 80036414 20004724 */  addiu      $a3, $v0, 0x20
  .L80036418:
    /* 26C18 80036418 C0080100 */  sll        $at, $at, 3
    /* 26C1C 8003641C 2148E102 */  addu       $t1, $s7, $at
    /* 26C20 80036420 0000218D */  lw         $at, 0x0($t1)
    /* 26C24 80036424 0400298D */  lw         $t1, 0x4($t1)
    /* 26C28 80036428 00130100 */  sll        $v0, $at, 12
    /* 26C2C 8003642C FF003D31 */  andi       $sp, $t1, 0xFF
    /* 26C30 80036430 25105D00 */  or         $v0, $v0, $sp
    /* 26C34 80036434 42840900 */  srl        $s0, $t1, 17
    /* 26C38 80036438 F87F1032 */  andi       $s0, $s0, 0x7FF8
    /* 26C3C 8003643C 21801802 */  addu       $s0, $s0, $t8
    /* 26C40 80036440 42890900 */  srl        $s1, $t1, 5
    /* 26C44 80036444 F87F3132 */  andi       $s1, $s1, 0x7FF8
    /* 26C48 80036448 21883802 */  addu       $s1, $s1, $t8
    /* 26C4C 8003644C 42940100 */  srl        $s2, $at, 17
    /* 26C50 80036450 F87F5232 */  andi       $s2, $s2, 0x7FF8
    /* 26C54 80036454 21905802 */  addu       $s2, $s2, $t8
    /* 26C58 80036458 0000138E */  lw         $s3, 0x0($s0)
    /* 26C5C 8003645C 0400108E */  lw         $s0, 0x4($s0)
    /* 26C60 80036460 0000348E */  lw         $s4, 0x0($s1)
    /* 26C64 80036464 0400318E */  lw         $s1, 0x4($s1)
    /* 26C68 80036468 0000558E */  lw         $s5, 0x0($s2)
    /* 26C6C 8003646C 0400528E */  lw         $s2, 0x4($s2)
    /* 26C70 80036470 801F093C */  lui        $t1, (0x1F800048 >> 16)
    /* 26C74 80036474 48002935 */  ori        $t1, $t1, (0x1F800048 & 0xFFFF)
    /* 26C78 80036478 0C003F8D */  lw         $ra, 0xC($t1)
    /* 26C7C 8003647C 01001D32 */  andi       $sp, $s0, 0x1
    /* 26C80 80036480 01003E32 */  andi       $fp, $s1, 0x1
    /* 26C84 80036484 40F01E00 */  sll        $fp, $fp, 1
    /* 26C88 80036488 25E8BE03 */  or         $sp, $sp, $fp
    /* 26C8C 8003648C 01005E32 */  andi       $fp, $s2, 0x1
    /* 26C90 80036490 80F01E00 */  sll        $fp, $fp, 2
    /* 26C94 80036494 2508BE03 */  or         $at, $sp, $fp
    /* 26C98 80036498 25F03F00 */  or         $fp, $at, $ra
    /* 26C9C 8003649C 0A01C013 */  beqz       $fp, .L800368C8
    /* 26CA0 800364A0 00409F48 */   mtc2      $ra, $8 /* handwritten instruction */
    /* 26CA4 800364A4 00003D8D */  lw         $sp, 0x0($t1)
    /* 26CA8 800364A8 04003E8D */  lw         $fp, 0x4($t1)
    /* 26CAC 800364AC 08003F8D */  lw         $ra, 0x8($t1)
    /* 26CB0 800364B0 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 26CB4 800364B4 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 26CB8 800364B8 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 26CBC 800364BC 03801F3C */  lui        $ra, %hi(D_800364D4)
    /* 26CC0 800364C0 D464FF27 */  addiu      $ra, $ra, %lo(D_800364D4)
    /* 26CC4 800364C4 C0E90100 */  sll        $sp, $at, 7
    /* 26CC8 800364C8 21F8FD03 */  addu       $ra, $ra, $sp
    /* 26CCC 800364CC 0800E003 */  jr         $ra
    /* 26CD0 800364D0 27F08003 */   not       $fp, $gp
  jlabel D_800364D4
    /* 26CD4 800364D4 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26CD8 800364D8 00000000 */  nop
    /* 26CDC 800364DC 00000000 */  nop
    /* 26CE0 800364E0 1000784A */  dpcs
    /* 26CE4 800364E4 24987E02 */  and        $s3, $s3, $fp
    /* 26CE8 800364E8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26CEC 800364EC 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26CF0 800364F0 24E8BC03 */  and        $sp, $sp, $gp
    /* 26CF4 800364F4 25987D02 */  or         $s3, $s3, $sp
    /* 26CF8 800364F8 1000784A */  dpcs
    /* 26CFC 800364FC 24A09E02 */  and        $s4, $s4, $fp
    /* 26D00 80036500 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26D04 80036504 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26D08 80036508 24E8BC03 */  and        $sp, $sp, $gp
    /* 26D0C 8003650C 25A09D02 */  or         $s4, $s4, $sp
    /* 26D10 80036510 1000784A */  dpcs
    /* 26D14 80036514 00000000 */  nop
    /* 26D18 80036518 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26D1C 8003651C 24A8BE02 */  and        $s5, $s5, $fp
    /* 26D20 80036520 24E8BC03 */  and        $sp, $sp, $gp
    /* 26D24 80036524 E8000104 */  bgez       $zero, .L800368C8
    /* 26D28 80036528 25A8BD02 */   or        $s5, $s5, $sp
    /* 26D2C 8003652C 00000000 */  nop
    /* 26D30 80036530 00000000 */  nop
    /* 26D34 80036534 00000000 */  nop
    /* 26D38 80036538 00000000 */  nop
    /* 26D3C 8003653C 00000000 */  nop
    /* 26D40 80036540 00000000 */  nop
    /* 26D44 80036544 00000000 */  nop
    /* 26D48 80036548 00000000 */  nop
    /* 26D4C 8003654C 00000000 */  nop
    /* 26D50 80036550 00000000 */  nop
    /* 26D54 80036554 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26D58 80036558 00000000 */  nop
    /* 26D5C 8003655C 24A09E02 */  and        $s4, $s4, $fp
    /* 26D60 80036560 1000784A */  dpcs
    /* 26D64 80036564 00000000 */  nop
    /* 26D68 80036568 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26D6C 8003656C 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26D70 80036570 24E8BC03 */  and        $sp, $sp, $gp
    /* 26D74 80036574 25A09D02 */  or         $s4, $s4, $sp
    /* 26D78 80036578 1000784A */  dpcs
    /* 26D7C 8003657C 00000000 */  nop
    /* 26D80 80036580 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26D84 80036584 24A8BE02 */  and        $s5, $s5, $fp
    /* 26D88 80036588 24E8BC03 */  and        $sp, $sp, $gp
    /* 26D8C 8003658C 25A8BD02 */  or         $s5, $s5, $sp
    /* 26D90 80036590 10003D8D */  lw         $sp, 0x10($t1)
    /* 26D94 80036594 14003E8D */  lw         $fp, 0x14($t1)
    /* 26D98 80036598 18003F8D */  lw         $ra, 0x18($t1)
    /* 26D9C 8003659C 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 26DA0 800365A0 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 26DA4 800365A4 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 26DA8 800365A8 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 26DAC 800365AC 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26DB0 800365B0 27F08003 */  not        $fp, $gp
    /* 26DB4 800365B4 24987E02 */  and        $s3, $s3, $fp
    /* 26DB8 800365B8 1000784A */  dpcs
    /* 26DBC 800365BC 00000000 */  nop
    /* 26DC0 800365C0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26DC4 800365C4 00000000 */  nop
    /* 26DC8 800365C8 24E8BC03 */  and        $sp, $sp, $gp
    /* 26DCC 800365CC BE000104 */  bgez       $zero, .L800368C8
    /* 26DD0 800365D0 25987D02 */   or        $s3, $s3, $sp
    /* 26DD4 800365D4 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26DD8 800365D8 00000000 */  nop
    /* 26DDC 800365DC 24987E02 */  and        $s3, $s3, $fp
    /* 26DE0 800365E0 1000784A */  dpcs
    /* 26DE4 800365E4 00000000 */  nop
    /* 26DE8 800365E8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26DEC 800365EC 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26DF0 800365F0 24E8BC03 */  and        $sp, $sp, $gp
    /* 26DF4 800365F4 25987D02 */  or         $s3, $s3, $sp
    /* 26DF8 800365F8 1000784A */  dpcs
    /* 26DFC 800365FC 00000000 */  nop
    /* 26E00 80036600 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26E04 80036604 24A8BE02 */  and        $s5, $s5, $fp
    /* 26E08 80036608 24E8BC03 */  and        $sp, $sp, $gp
    /* 26E0C 8003660C 25A8BD02 */  or         $s5, $s5, $sp
    /* 26E10 80036610 10003D8D */  lw         $sp, 0x10($t1)
    /* 26E14 80036614 14003E8D */  lw         $fp, 0x14($t1)
    /* 26E18 80036618 18003F8D */  lw         $ra, 0x18($t1)
    /* 26E1C 8003661C 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 26E20 80036620 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 26E24 80036624 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 26E28 80036628 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 26E2C 8003662C 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26E30 80036630 27F08003 */  not        $fp, $gp
    /* 26E34 80036634 24A09E02 */  and        $s4, $s4, $fp
    /* 26E38 80036638 1000784A */  dpcs
    /* 26E3C 8003663C 00000000 */  nop
    /* 26E40 80036640 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26E44 80036644 00000000 */  nop
    /* 26E48 80036648 24E8BC03 */  and        $sp, $sp, $gp
    /* 26E4C 8003664C 9E000104 */  bgez       $zero, .L800368C8
    /* 26E50 80036650 25A09D02 */   or        $s4, $s4, $sp
    /* 26E54 80036654 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26E58 80036658 00000000 */  nop
    /* 26E5C 8003665C 24A8BE02 */  and        $s5, $s5, $fp
    /* 26E60 80036660 1000784A */  dpcs
    /* 26E64 80036664 00000000 */  nop
    /* 26E68 80036668 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26E6C 8003666C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26E70 80036670 24E8BC03 */  and        $sp, $sp, $gp
    /* 26E74 80036674 25A8BD02 */  or         $s5, $s5, $sp
    /* 26E78 80036678 10003D8D */  lw         $sp, 0x10($t1)
    /* 26E7C 8003667C 14003E8D */  lw         $fp, 0x14($t1)
    /* 26E80 80036680 18003F8D */  lw         $ra, 0x18($t1)
    /* 26E84 80036684 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 26E88 80036688 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 26E8C 8003668C 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 26E90 80036690 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 26E94 80036694 27F08003 */  not        $fp, $gp
    /* 26E98 80036698 24987E02 */  and        $s3, $s3, $fp
    /* 26E9C 8003669C 1000784A */  dpcs
    /* 26EA0 800366A0 00000000 */  nop
    /* 26EA4 800366A4 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26EA8 800366A8 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26EAC 800366AC 24E8BC03 */  and        $sp, $sp, $gp
    /* 26EB0 800366B0 25987D02 */  or         $s3, $s3, $sp
    /* 26EB4 800366B4 24A09E02 */  and        $s4, $s4, $fp
    /* 26EB8 800366B8 1000784A */  dpcs
    /* 26EBC 800366BC 00000000 */  nop
    /* 26EC0 800366C0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26EC4 800366C4 00000000 */  nop
    /* 26EC8 800366C8 24E8BC03 */  and        $sp, $sp, $gp
    /* 26ECC 800366CC 7E000104 */  bgez       $zero, .L800368C8
    /* 26ED0 800366D0 25A09D02 */   or        $s4, $s4, $sp
    /* 26ED4 800366D4 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26ED8 800366D8 00000000 */  nop
    /* 26EDC 800366DC 24987E02 */  and        $s3, $s3, $fp
    /* 26EE0 800366E0 1000784A */  dpcs
    /* 26EE4 800366E4 00000000 */  nop
    /* 26EE8 800366E8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26EEC 800366EC 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26EF0 800366F0 24E8BC03 */  and        $sp, $sp, $gp
    /* 26EF4 800366F4 25987D02 */  or         $s3, $s3, $sp
    /* 26EF8 800366F8 1000784A */  dpcs
    /* 26EFC 800366FC 00000000 */  nop
    /* 26F00 80036700 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26F04 80036704 24A09E02 */  and        $s4, $s4, $fp
    /* 26F08 80036708 24E8BC03 */  and        $sp, $sp, $gp
    /* 26F0C 8003670C 25A09D02 */  or         $s4, $s4, $sp
    /* 26F10 80036710 10003D8D */  lw         $sp, 0x10($t1)
    /* 26F14 80036714 14003E8D */  lw         $fp, 0x14($t1)
    /* 26F18 80036718 18003F8D */  lw         $ra, 0x18($t1)
    /* 26F1C 8003671C 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 26F20 80036720 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 26F24 80036724 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 26F28 80036728 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 26F2C 8003672C 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26F30 80036730 27F08003 */  not        $fp, $gp
    /* 26F34 80036734 24A8BE02 */  and        $s5, $s5, $fp
    /* 26F38 80036738 1000784A */  dpcs
    /* 26F3C 8003673C 00000000 */  nop
    /* 26F40 80036740 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26F44 80036744 00000000 */  nop
    /* 26F48 80036748 24E8BC03 */  and        $sp, $sp, $gp
    /* 26F4C 8003674C 5E000104 */  bgez       $zero, .L800368C8
    /* 26F50 80036750 25A8BD02 */   or        $s5, $s5, $sp
    /* 26F54 80036754 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26F58 80036758 00000000 */  nop
    /* 26F5C 8003675C 24A09E02 */  and        $s4, $s4, $fp
    /* 26F60 80036760 1000784A */  dpcs
    /* 26F64 80036764 00000000 */  nop
    /* 26F68 80036768 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26F6C 8003676C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26F70 80036770 24E8BC03 */  and        $sp, $sp, $gp
    /* 26F74 80036774 25A09D02 */  or         $s4, $s4, $sp
    /* 26F78 80036778 10003D8D */  lw         $sp, 0x10($t1)
    /* 26F7C 8003677C 14003E8D */  lw         $fp, 0x14($t1)
    /* 26F80 80036780 18003F8D */  lw         $ra, 0x18($t1)
    /* 26F84 80036784 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 26F88 80036788 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 26F8C 8003678C 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 26F90 80036790 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 26F94 80036794 27F08003 */  not        $fp, $gp
    /* 26F98 80036798 24987E02 */  and        $s3, $s3, $fp
    /* 26F9C 8003679C 1000784A */  dpcs
    /* 26FA0 800367A0 00000000 */  nop
    /* 26FA4 800367A4 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26FA8 800367A8 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26FAC 800367AC 24E8BC03 */  and        $sp, $sp, $gp
    /* 26FB0 800367B0 25987D02 */  or         $s3, $s3, $sp
    /* 26FB4 800367B4 24A8BE02 */  and        $s5, $s5, $fp
    /* 26FB8 800367B8 1000784A */  dpcs
    /* 26FBC 800367BC 00000000 */  nop
    /* 26FC0 800367C0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26FC4 800367C4 00000000 */  nop
    /* 26FC8 800367C8 24E8BC03 */  and        $sp, $sp, $gp
    /* 26FCC 800367CC 3E000104 */  bgez       $zero, .L800368C8
    /* 26FD0 800367D0 25A8BD02 */   or        $s5, $s5, $sp
    /* 26FD4 800367D4 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26FD8 800367D8 00000000 */  nop
    /* 26FDC 800367DC 24987E02 */  and        $s3, $s3, $fp
    /* 26FE0 800367E0 1000784A */  dpcs
    /* 26FE4 800367E4 00000000 */  nop
    /* 26FE8 800367E8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 26FEC 800367EC 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 26FF0 800367F0 24E8BC03 */  and        $sp, $sp, $gp
    /* 26FF4 800367F4 25987D02 */  or         $s3, $s3, $sp
    /* 26FF8 800367F8 10003D8D */  lw         $sp, 0x10($t1)
    /* 26FFC 800367FC 14003E8D */  lw         $fp, 0x14($t1)
    /* 27000 80036800 18003F8D */  lw         $ra, 0x18($t1)
    /* 27004 80036804 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 27008 80036808 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 2700C 8003680C 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 27010 80036810 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 27014 80036814 27F08003 */  not        $fp, $gp
    /* 27018 80036818 24A09E02 */  and        $s4, $s4, $fp
    /* 2701C 8003681C 1000784A */  dpcs
    /* 27020 80036820 00000000 */  nop
    /* 27024 80036824 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27028 80036828 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 2702C 8003682C 24E8BC03 */  and        $sp, $sp, $gp
    /* 27030 80036830 25A09D02 */  or         $s4, $s4, $sp
    /* 27034 80036834 24A8BE02 */  and        $s5, $s5, $fp
    /* 27038 80036838 1000784A */  dpcs
    /* 2703C 8003683C 00000000 */  nop
    /* 27040 80036840 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27044 80036844 00000000 */  nop
    /* 27048 80036848 24E8BC03 */  and        $sp, $sp, $gp
    /* 2704C 8003684C 1E000104 */  bgez       $zero, .L800368C8
    /* 27050 80036850 25A8BD02 */   or        $s5, $s5, $sp
    /* 27054 80036854 10003D8D */  lw         $sp, 0x10($t1)
    /* 27058 80036858 14003E8D */  lw         $fp, 0x14($t1)
    /* 2705C 8003685C 18003F8D */  lw         $ra, 0x18($t1)
    /* 27060 80036860 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 27064 80036864 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 27068 80036868 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 2706C 8003686C 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 27070 80036870 27F08003 */  not        $fp, $gp
    /* 27074 80036874 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27078 80036878 00000000 */  nop
    /* 2707C 8003687C 00000000 */  nop
    /* 27080 80036880 1000784A */  dpcs
    /* 27084 80036884 24987E02 */  and        $s3, $s3, $fp
    /* 27088 80036888 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2708C 8003688C 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27090 80036890 24E8BC03 */  and        $sp, $sp, $gp
    /* 27094 80036894 25987D02 */  or         $s3, $s3, $sp
    /* 27098 80036898 1000784A */  dpcs
    /* 2709C 8003689C 24A09E02 */  and        $s4, $s4, $fp
    /* 270A0 800368A0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 270A4 800368A4 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 270A8 800368A8 24E8BC03 */  and        $sp, $sp, $gp
    /* 270AC 800368AC 25A09D02 */  or         $s4, $s4, $sp
    /* 270B0 800368B0 1000784A */  dpcs
    /* 270B4 800368B4 00000000 */  nop
    /* 270B8 800368B8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 270BC 800368BC 24A8BE02 */  and        $s5, $s5, $fp
    /* 270C0 800368C0 24E8BC03 */  and        $sp, $sp, $gp
    /* 270C4 800368C4 25A8BD02 */  or         $s5, $s5, $sp
  .L800368C8:
    /* 270C8 800368C8 F8FF013C */  lui        $at, (0xFFF8FFF8 >> 16)
    /* 270CC 800368CC F8FF2134 */  ori        $at, $at, (0xFFF8FFF8 & 0xFFFF)
    /* 270D0 800368D0 24E80102 */  and        $sp, $s0, $at
    /* 270D4 800368D4 24F02102 */  and        $fp, $s1, $at
    /* 270D8 800368D8 24F84102 */  and        $ra, $s2, $at
    /* 270DC 800368DC 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 270E0 800368E0 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 270E4 800368E4 00209F48 */  mtc2       $ra, $4 /* handwritten instruction */
    /* 270E8 800368E8 0700013C */  lui        $at, (0x70006 >> 16)
    /* 270EC 800368EC 06002134 */  ori        $at, $at, (0x70006 & 0xFFFF)
    /* 270F0 800368F0 02EE1300 */  srl        $sp, $s3, 24
    /* 270F4 800368F4 C0E81D00 */  sll        $sp, $sp, 3
    /* 270F8 800368F8 24800102 */  and        $s0, $s0, $at
    /* 270FC 800368FC 804A1000 */  sll        $t1, $s0, 10
    /* 27100 80036900 25E8A903 */  or         $sp, $sp, $t1
    /* 27104 80036904 C2481000 */  srl        $t1, $s0, 3
    /* 27108 80036908 25E8A903 */  or         $sp, $sp, $t1
    /* 2710C 8003690C 02F61400 */  srl        $fp, $s4, 24
    /* 27110 80036910 C0F01E00 */  sll        $fp, $fp, 3
    /* 27114 80036914 24882102 */  and        $s1, $s1, $at
    /* 27118 80036918 804A1100 */  sll        $t1, $s1, 10
    /* 2711C 8003691C 25F0C903 */  or         $fp, $fp, $t1
    /* 27120 80036920 C2481100 */  srl        $t1, $s1, 3
    /* 27124 80036924 25F0C903 */  or         $fp, $fp, $t1
    /* 27128 80036928 02FE1500 */  srl        $ra, $s5, 24
    /* 2712C 8003692C C0F81F00 */  sll        $ra, $ra, 3
    /* 27130 80036930 24904102 */  and        $s2, $s2, $at
    /* 27134 80036934 804A1200 */  sll        $t1, $s2, 10
    /* 27138 80036938 25F8E903 */  or         $ra, $ra, $t1
    /* 2713C 8003693C C2481200 */  srl        $t1, $s2, 3
    /* 27140 80036940 25F8E903 */  or         $ra, $ra, $t1
    /* 27144 80036944 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 27148 80036948 00189E48 */  mtc2       $fp, $3 /* handwritten instruction */
    /* 2714C 8003694C 00289F48 */  mtc2       $ra, $5 /* handwritten instruction */
    /* 27150 80036950 02F50200 */  srl        $fp, $v0, 20
    /* 27154 80036954 3000284A */  rtpt
    /* 27158 80036958 80F01E00 */  sll        $fp, $fp, 2
    /* 2715C 8003695C 21703E03 */  addu       $t6, $t9, $fp
    /* 27160 80036960 0000C98D */  lw         $t1, 0x0($t6)
    /* 27164 80036964 0034123C */  lui        $s2, (0x34000000 >> 16)
    /* 27168 80036968 024E0900 */  srl        $t1, $t1, 24
    /* 2716C 8003696C 80003D31 */  andi       $sp, $t1, 0x80
    /* 27170 80036970 6300A013 */  beqz       $sp, .L80036B00
    /* 27174 80036974 24987C02 */   and       $s3, $s3, $gp
    /* 27178 80036978 08006CE9 */  swc2       $12, 0x8($t3)
    /* 2717C 8003697C 14006DE9 */  swc2       $13, 0x14($t3)
    /* 27180 80036980 20006EE9 */  swc2       $14, 0x20($t3)
    /* 27184 80036984 24F02F01 */  and        $fp, $t1, $t7
    /* 27188 80036988 0200CF13 */  beq        $fp, $t7, .L80036994
    /* 2718C 8003698C 25987202 */   or        $s3, $s3, $s2
    /* 27190 80036990 25986402 */  or         $s3, $s3, $a0
  .L80036994:
    /* 27194 80036994 040073AD */  sw         $s3, 0x4($t3)
    /* 27198 80036998 100074AD */  sw         $s4, 0x10($t3)
    /* 2719C 8003699C 1C0075AD */  sw         $s5, 0x1C($t3)
    /* 271A0 800369A0 C2FB0200 */  srl        $ra, $v0, 15
    /* 271A4 800369A4 1C00FF33 */  andi       $ra, $ra, 0x1C
    /* 271A8 800369A8 2108E703 */  addu       $at, $ra, $a3
    /* 271AC 800369AC 1E005F30 */  andi       $ra, $v0, 0x1E
    /* 271B0 800369B0 0D00E013 */  beqz       $ra, .L800369E8
    /* 271B4 800369B4 42E90200 */   srl       $sp, $v0, 5
    /* 271B8 800369B8 801F1E3C */  lui        $fp, (0x1F8000E0 >> 16)
    /* 271BC 800369BC E000DE37 */  ori        $fp, $fp, (0x1F8000E0 & 0xFFFF)
    /* 271C0 800369C0 0000DE8F */  lw         $fp, 0x0($fp)
    /* 271C4 800369C4 0700BD33 */  andi       $sp, $sp, 0x7
    /* 271C8 800369C8 06F0BE03 */  srlv       $fp, $fp, $sp
    /* 271CC 800369CC 02EB0200 */  srl        $sp, $v0, 12
    /* 271D0 800369D0 1F00BD33 */  andi       $sp, $sp, 0x1F
    /* 271D4 800369D4 21E8DD03 */  addu       $sp, $fp, $sp
    /* 271D8 800369D8 0100FE37 */  ori        $fp, $ra, 0x1
    /* 271DC 800369DC 24E8BE03 */  and        $sp, $sp, $fp
    /* 271E0 800369E0 80E81D00 */  sll        $sp, $sp, 2
    /* 271E4 800369E4 2170AE03 */  addu       $t6, $sp, $t6
  .L800369E8:
    /* 271E8 800369E8 0400D38D */  lw         $s3, 0x4($t6)
    /* 271EC 800369EC 0000348C */  lw         $s4, 0x0($at)
    /* 271F0 800369F0 82ED1300 */  srl        $sp, $s3, 22
    /* 271F4 800369F4 C0E81D00 */  sll        $sp, $sp, 3
    /* 271F8 800369F8 2170DD02 */  addu       $t6, $s6, $sp
    /* 271FC 800369FC 0000D08D */  lw         $s0, 0x0($t6)
    /* 27200 80036A00 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 27204 80036A04 02AD1300 */  srl        $s5, $s3, 20
    /* 27208 80036A08 0300B532 */  andi       $s5, $s5, 0x3
    /* 2720C 80036A0C C0E91500 */  sll        $sp, $s5, 7
    /* 27210 80036A10 1C009E32 */  andi       $fp, $s4, 0x1C
    /* 27214 80036A14 25E8BE03 */  or         $sp, $sp, $fp
    /* 27218 80036A18 82F41300 */  srl        $fp, $s3, 18
    /* 2721C 80036A1C 0300DE33 */  andi       $fp, $fp, 0x3
    /* 27220 80036A20 25E8BE03 */  or         $sp, $sp, $fp
    /* 27224 80036A24 60003E31 */  andi       $fp, $t1, 0x60
    /* 27228 80036A28 25E8BE03 */  or         $sp, $sp, $fp
    /* 2722C 80036A2C 00EC1D00 */  sll        $sp, $sp, 16
    /* 27230 80036A30 1F007E32 */  andi       $fp, $s3, 0x1F
    /* 27234 80036A34 80F01E00 */  sll        $fp, $fp, 2
    /* 27238 80036A38 80009F32 */  andi       $ra, $s4, 0x80
    /* 2723C 80036A3C 25F0DF03 */  or         $fp, $fp, $ra
    /* 27240 80036A40 00FA1E00 */  sll        $ra, $fp, 8
    /* 27244 80036A44 82F21300 */  srl        $fp, $s3, 10
    /* 27248 80036A48 F800DE33 */  andi       $fp, $fp, 0xF8
    /* 2724C 80036A4C 06F0BE02 */  srlv       $fp, $fp, $s5
    /* 27250 80036A50 25A8DF03 */  or         $s5, $fp, $ra
    /* 27254 80036A54 02F41000 */  srl        $fp, $s0, 16
    /* 27258 80036A58 21F0D503 */  addu       $fp, $fp, $s5
    /* 2725C 80036A5C 25F8BE03 */  or         $ra, $sp, $fp
    /* 27260 80036A60 0F003D31 */  andi       $sp, $t1, 0xF
    /* 27264 80036A64 C01F7E32 */  andi       $fp, $s3, 0x1FC0
    /* 27268 80036A68 25E8BE03 */  or         $sp, $sp, $fp
    /* 2726C 80036A6C 02F11400 */  srl        $fp, $s4, 4
    /* 27270 80036A70 F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 27274 80036A74 25E8BE03 */  or         $sp, $sp, $fp
    /* 27278 80036A78 00EC1D00 */  sll        $sp, $sp, 16
    /* 2727C 80036A7C FFFF1E32 */  andi       $fp, $s0, 0xFFFF
    /* 27280 80036A80 21F0D503 */  addu       $fp, $fp, $s5
    /* 27284 80036A84 25F0BE03 */  or         $fp, $sp, $fp
    /* 27288 80036A88 2170D501 */  addu       $t6, $t6, $s5
    /* 2728C 80036A8C 0C007EAD */  sw         $fp, 0xC($t3)
    /* 27290 80036A90 18007FAD */  sw         $ra, 0x18($t3)
    /* 27294 80036A94 24006EA5 */  sh         $t6, 0x24($t3)
    /* 27298 80036A98 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 2729C 80036A9C 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 272A0 80036AA0 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 272A4 80036AA4 21E8BE03 */  addu       $sp, $sp, $fp
    /* 272A8 80036AA8 21E8BF03 */  addu       $sp, $sp, $ra
    /* 272AC 80036AAC 42E91D00 */  srl        $sp, $sp, 5
    /* 272B0 80036AB0 80E81D00 */  sll        $sp, $sp, 2
    /* 272B4 80036AB4 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 272B8 80036AB8 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 272BC 80036ABC 2AF0A303 */  slt        $fp, $sp, $v1
    /* 272C0 80036AC0 0600C013 */  beqz       $fp, .L80036ADC
    /* 272C4 80036AC4 2170A300 */   addu      $t6, $a1, $v1
    /* 272C8 80036AC8 2118A003 */  addu       $v1, $sp, $zero
    /* 272CC 80036ACC 03006104 */  bgez       $v1, .L80036ADC
    /* 272D0 80036AD0 2170A300 */   addu      $t6, $a1, $v1
    /* 272D4 80036AD4 21180000 */  addu       $v1, $zero, $zero
    /* 272D8 80036AD8 2170A300 */  addu       $t6, $a1, $v1
  .L80036ADC:
    /* 272DC 80036ADC 0000DD8D */  lw         $sp, 0x0($t6)
    /* 272E0 80036AE0 24F07C01 */  and        $fp, $t3, $gp
    /* 272E4 80036AE4 0000DEAD */  sw         $fp, 0x0($t6)
    /* 272E8 80036AE8 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 272EC 80036AEC 25E8BF03 */  or         $sp, $sp, $ra
    /* 272F0 80036AF0 00007DAD */  sw         $sp, 0x0($t3)
    /* 272F4 80036AF4 28006B25 */  addiu      $t3, $t3, 0x28
    /* 272F8 80036AF8 21000104 */  bgez       $zero, .L80036B80
    /* 272FC 80036AFC 00000000 */   nop
  .L80036B00:
    /* 27300 80036B00 08006CE9 */  swc2       $12, 0x8($t3)
    /* 27304 80036B04 10006DE9 */  swc2       $13, 0x10($t3)
    /* 27308 80036B08 18006EE9 */  swc2       $14, 0x18($t3)
    /* 2730C 80036B0C 0030123C */  lui        $s2, (0x30000000 >> 16)
    /* 27310 80036B10 25987202 */  or         $s3, $s3, $s2
    /* 27314 80036B14 040073AD */  sw         $s3, 0x4($t3)
    /* 27318 80036B18 0C0074AD */  sw         $s4, 0xC($t3)
    /* 2731C 80036B1C 140075AD */  sw         $s5, 0x14($t3)
    /* 27320 80036B20 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 27324 80036B24 00901E48 */  mfc2       $fp, $18 /* handwritten instruction */
    /* 27328 80036B28 00981F48 */  mfc2       $ra, $19 /* handwritten instruction */
    /* 2732C 80036B2C 21E8BE03 */  addu       $sp, $sp, $fp
    /* 27330 80036B30 21E8BF03 */  addu       $sp, $sp, $ra
    /* 27334 80036B34 42E91D00 */  srl        $sp, $sp, 5
    /* 27338 80036B38 80E81D00 */  sll        $sp, $sp, 2
    /* 2733C 80036B3C 22E8DD00 */  sub        $sp, $a2, $sp /* handwritten instruction */
    /* 27340 80036B40 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 27344 80036B44 2AF0A303 */  slt        $fp, $sp, $v1
    /* 27348 80036B48 0600C013 */  beqz       $fp, .L80036B64
    /* 2734C 80036B4C 2170A300 */   addu      $t6, $a1, $v1
    /* 27350 80036B50 2118A003 */  addu       $v1, $sp, $zero
    /* 27354 80036B54 03006104 */  bgez       $v1, .L80036B64
    /* 27358 80036B58 2170A300 */   addu      $t6, $a1, $v1
    /* 2735C 80036B5C 21180000 */  addu       $v1, $zero, $zero
    /* 27360 80036B60 2170A300 */  addu       $t6, $a1, $v1
  .L80036B64:
    /* 27364 80036B64 0000DD8D */  lw         $sp, 0x0($t6)
    /* 27368 80036B68 24F07C01 */  and        $fp, $t3, $gp
    /* 2736C 80036B6C 0000DEAD */  sw         $fp, 0x0($t6)
    /* 27370 80036B70 00061E3C */  lui        $fp, (0x6000000 >> 16)
    /* 27374 80036B74 25E8BE03 */  or         $sp, $sp, $fp
    /* 27378 80036B78 00007DAD */  sw         $sp, 0x0($t3)
    /* 2737C 80036B7C 1C006B25 */  addiu      $t3, $t3, 0x1C
  .L80036B80:
    /* 27380 80036B80 FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 27384 80036B84 13FEA015 */  bnez       $t5, .L800363D4
    /* 27388 80036B88 00004195 */   lhu       $at, 0x0($t2)
    /* 2738C 80036B8C 00000000 */  nop
    /* 27390 80036B90 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 27394 80036B94 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 27398 80036B98 00000000 */  nop
    /* 2739C 80036B9C 1000A18F */  lw         $at, 0x10($sp)
    /* 273A0 80036BA0 00000000 */  nop
    /* 273A4 80036BA4 00002BAC */  sw         $t3, 0x0($at)
    /* 273A8 80036BA8 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 273AC 80036BAC 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 273B0 80036BB0 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 273B4 80036BB4 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 273B8 80036BB8 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 273BC 80036BBC 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 273C0 80036BC0 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 273C4 80036BC4 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 273C8 80036BC8 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 273CC 80036BCC 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 273D0 80036BD0 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 273D4 80036BD4 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 273D8 80036BD8 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 273DC 80036BDC 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 273E0 80036BE0 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 273E4 80036BE4 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 273E8 80036BE8 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 273EC 80036BEC 0800E003 */  jr         $ra
    /* 273F0 80036BF0 00000000 */   nop
endlabel func_80036340
