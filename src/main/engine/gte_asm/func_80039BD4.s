.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_80039BD4
    /* 2A3D4 80039BD4 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 2A3D8 80039BD8 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2A3DC 80039BDC 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2A3E0 80039BE0 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2A3E4 80039BE4 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2A3E8 80039BE8 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2A3EC 80039BEC 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2A3F0 80039BF0 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2A3F4 80039BF4 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2A3F8 80039BF8 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2A3FC 80039BFC 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2A400 80039C00 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2A404 80039C04 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2A408 80039C08 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2A40C 80039C0C 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2A410 80039C10 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2A414 80039C14 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2A418 80039C18 0580033C */  lui        $v1, %hi(D_8005306C)
    /* 2A41C 80039C1C 6C306324 */  addiu      $v1, $v1, %lo(D_8005306C)
    /* 2A420 80039C20 1400DC8C */  lw         $gp, 0x14($a2)
    /* 2A424 80039C24 1000DE8C */  lw         $fp, 0x10($a2)
    /* 2A428 80039C28 0C00DD8C */  lw         $sp, 0xC($a2)
    /* 2A42C 80039C2C 23F09E03 */  subu       $fp, $gp, $fp
    /* 2A430 80039C30 23F01E00 */  negu       $fp, $fp
    /* 2A434 80039C34 FF0F9C33 */  andi       $gp, $gp, 0xFFF
    /* 2A438 80039C38 FF0FBD33 */  andi       $sp, $sp, 0xFFF
    /* 2A43C 80039C3C FF0FDE33 */  andi       $fp, $fp, 0xFFF
    /* 2A440 80039C40 00088D2B */  slti       $t5, $gp, 0x800
    /* 2A444 80039C44 0B00A011 */  beqz       $t5, .L80039C74
    /* 2A448 80039C48 00048D2B */   slti      $t5, $gp, 0x400
    /* 2A44C 80039C4C 0500A011 */  beqz       $t5, .L80039C64
    /* 2A450 80039C50 40681C00 */   sll       $t5, $gp, 1
    /* 2A454 80039C54 21686D00 */  addu       $t5, $v1, $t5
    /* 2A458 80039C58 11000104 */  bgez       $zero, .L80039CA0
    /* 2A45C 80039C5C 0000AD85 */   lh        $t5, 0x0($t5)
    /* 2A460 80039C60 00000000 */  nop
  .L80039C64:
    /* 2A464 80039C64 23686D00 */  subu       $t5, $v1, $t5
    /* 2A468 80039C68 0D000104 */  bgez       $zero, .L80039CA0
    /* 2A46C 80039C6C 0010AD85 */   lh        $t5, 0x1000($t5)
    /* 2A470 80039C70 00000000 */  nop
  .L80039C74:
    /* 2A474 80039C74 000C8D2B */  slti       $t5, $gp, 0xC00
    /* 2A478 80039C78 0500A011 */  beqz       $t5, .L80039C90
    /* 2A47C 80039C7C 40681C00 */   sll       $t5, $gp, 1
    /* 2A480 80039C80 21686D00 */  addu       $t5, $v1, $t5
    /* 2A484 80039C84 00F0AD85 */  lh         $t5, -0x1000($t5)
    /* 2A488 80039C88 05000104 */  bgez       $zero, .L80039CA0
    /* 2A48C 80039C8C 23680D00 */   negu      $t5, $t5
  .L80039C90:
    /* 2A490 80039C90 23686D00 */  subu       $t5, $v1, $t5
    /* 2A494 80039C94 0020AD85 */  lh         $t5, 0x2000($t5)
    /* 2A498 80039C98 01000104 */  bgez       $zero, .L80039CA0
    /* 2A49C 80039C9C 23680D00 */   negu      $t5, $t5
  .L80039CA0:
    /* 2A4A0 80039CA0 0008AE2B */  slti       $t6, $sp, 0x800
    /* 2A4A4 80039CA4 0B00C011 */  beqz       $t6, .L80039CD4
    /* 2A4A8 80039CA8 0004AE2B */   slti      $t6, $sp, 0x400
    /* 2A4AC 80039CAC 0500C011 */  beqz       $t6, .L80039CC4
    /* 2A4B0 80039CB0 40701D00 */   sll       $t6, $sp, 1
    /* 2A4B4 80039CB4 21706E00 */  addu       $t6, $v1, $t6
    /* 2A4B8 80039CB8 11000104 */  bgez       $zero, .L80039D00
    /* 2A4BC 80039CBC 0000CE85 */   lh        $t6, 0x0($t6)
    /* 2A4C0 80039CC0 00000000 */  nop
  .L80039CC4:
    /* 2A4C4 80039CC4 23706E00 */  subu       $t6, $v1, $t6
    /* 2A4C8 80039CC8 0D000104 */  bgez       $zero, .L80039D00
    /* 2A4CC 80039CCC 0010CE85 */   lh        $t6, 0x1000($t6)
    /* 2A4D0 80039CD0 00000000 */  nop
  .L80039CD4:
    /* 2A4D4 80039CD4 000CAE2B */  slti       $t6, $sp, 0xC00
    /* 2A4D8 80039CD8 0500C011 */  beqz       $t6, .L80039CF0
    /* 2A4DC 80039CDC 40701D00 */   sll       $t6, $sp, 1
    /* 2A4E0 80039CE0 21706E00 */  addu       $t6, $v1, $t6
    /* 2A4E4 80039CE4 00F0CE85 */  lh         $t6, -0x1000($t6)
    /* 2A4E8 80039CE8 05000104 */  bgez       $zero, .L80039D00
    /* 2A4EC 80039CEC 23700E00 */   negu      $t6, $t6
  .L80039CF0:
    /* 2A4F0 80039CF0 23706E00 */  subu       $t6, $v1, $t6
    /* 2A4F4 80039CF4 0020CE85 */  lh         $t6, 0x2000($t6)
    /* 2A4F8 80039CF8 01000104 */  bgez       $zero, .L80039D00
    /* 2A4FC 80039CFC 23700E00 */   negu      $t6, $t6
  .L80039D00:
    /* 2A500 80039D00 0008CF2B */  slti       $t7, $fp, 0x800
    /* 2A504 80039D04 0B00E011 */  beqz       $t7, .L80039D34
    /* 2A508 80039D08 0004CF2B */   slti      $t7, $fp, 0x400
    /* 2A50C 80039D0C 0500E011 */  beqz       $t7, .L80039D24
    /* 2A510 80039D10 40781E00 */   sll       $t7, $fp, 1
    /* 2A514 80039D14 21786F00 */  addu       $t7, $v1, $t7
    /* 2A518 80039D18 11000104 */  bgez       $zero, .L80039D60
    /* 2A51C 80039D1C 0000EF85 */   lh        $t7, 0x0($t7)
    /* 2A520 80039D20 00000000 */  nop
  .L80039D24:
    /* 2A524 80039D24 23786F00 */  subu       $t7, $v1, $t7
    /* 2A528 80039D28 0D000104 */  bgez       $zero, .L80039D60
    /* 2A52C 80039D2C 0010EF85 */   lh        $t7, 0x1000($t7)
    /* 2A530 80039D30 00000000 */  nop
  .L80039D34:
    /* 2A534 80039D34 000CCF2B */  slti       $t7, $fp, 0xC00
    /* 2A538 80039D38 0500E011 */  beqz       $t7, .L80039D50
    /* 2A53C 80039D3C 40781E00 */   sll       $t7, $fp, 1
    /* 2A540 80039D40 21786F00 */  addu       $t7, $v1, $t7
    /* 2A544 80039D44 00F0EF85 */  lh         $t7, -0x1000($t7)
    /* 2A548 80039D48 05000104 */  bgez       $zero, .L80039D60
    /* 2A54C 80039D4C 23780F00 */   negu      $t7, $t7
  .L80039D50:
    /* 2A550 80039D50 23786F00 */  subu       $t7, $v1, $t7
    /* 2A554 80039D54 0020EF85 */  lh         $t7, 0x2000($t7)
    /* 2A558 80039D58 01000104 */  bgez       $zero, .L80039D60
    /* 2A55C 80039D5C 23780F00 */   negu      $t7, $t7
  .L80039D60:
    /* 2A560 80039D60 0008892B */  slti       $t1, $gp, 0x800
    /* 2A564 80039D64 0B002011 */  beqz       $t1, .L80039D94
    /* 2A568 80039D68 0004892B */   slti      $t1, $gp, 0x400
    /* 2A56C 80039D6C 05002011 */  beqz       $t1, .L80039D84
    /* 2A570 80039D70 40481C00 */   sll       $t1, $gp, 1
    /* 2A574 80039D74 23486900 */  subu       $t1, $v1, $t1
    /* 2A578 80039D78 0F000104 */  bgez       $zero, .L80039DB8
    /* 2A57C 80039D7C 00082985 */   lh        $t1, 0x800($t1)
    /* 2A580 80039D80 00000000 */  nop
  .L80039D84:
    /* 2A584 80039D84 21486900 */  addu       $t1, $v1, $t1
    /* 2A588 80039D88 00F82985 */  lh         $t1, -0x800($t1)
    /* 2A58C 80039D8C 0A000104 */  bgez       $zero, .L80039DB8
    /* 2A590 80039D90 23480900 */   negu      $t1, $t1
  .L80039D94:
    /* 2A594 80039D94 000C892B */  slti       $t1, $gp, 0xC00
    /* 2A598 80039D98 05002011 */  beqz       $t1, .L80039DB0
    /* 2A59C 80039D9C 40481C00 */   sll       $t1, $gp, 1
    /* 2A5A0 80039DA0 23486900 */  subu       $t1, $v1, $t1
    /* 2A5A4 80039DA4 00182985 */  lh         $t1, 0x1800($t1)
    /* 2A5A8 80039DA8 03000104 */  bgez       $zero, .L80039DB8
    /* 2A5AC 80039DAC 23480900 */   negu      $t1, $t1
  .L80039DB0:
    /* 2A5B0 80039DB0 21486900 */  addu       $t1, $v1, $t1
    /* 2A5B4 80039DB4 00E82985 */  lh         $t1, -0x1800($t1)
  .L80039DB8:
    /* 2A5B8 80039DB8 0008AA2B */  slti       $t2, $sp, 0x800
    /* 2A5BC 80039DBC 0B004011 */  beqz       $t2, .L80039DEC
    /* 2A5C0 80039DC0 0004AA2B */   slti      $t2, $sp, 0x400
    /* 2A5C4 80039DC4 05004011 */  beqz       $t2, .L80039DDC
    /* 2A5C8 80039DC8 40501D00 */   sll       $t2, $sp, 1
    /* 2A5CC 80039DCC 23506A00 */  subu       $t2, $v1, $t2
    /* 2A5D0 80039DD0 0F000104 */  bgez       $zero, .L80039E10
    /* 2A5D4 80039DD4 00084A85 */   lh        $t2, 0x800($t2)
    /* 2A5D8 80039DD8 00000000 */  nop
  .L80039DDC:
    /* 2A5DC 80039DDC 21506A00 */  addu       $t2, $v1, $t2
    /* 2A5E0 80039DE0 00F84A85 */  lh         $t2, -0x800($t2)
    /* 2A5E4 80039DE4 0A000104 */  bgez       $zero, .L80039E10
    /* 2A5E8 80039DE8 23500A00 */   negu      $t2, $t2
  .L80039DEC:
    /* 2A5EC 80039DEC 000CAA2B */  slti       $t2, $sp, 0xC00
    /* 2A5F0 80039DF0 05004011 */  beqz       $t2, .L80039E08
    /* 2A5F4 80039DF4 40501D00 */   sll       $t2, $sp, 1
    /* 2A5F8 80039DF8 23506A00 */  subu       $t2, $v1, $t2
    /* 2A5FC 80039DFC 00184A85 */  lh         $t2, 0x1800($t2)
    /* 2A600 80039E00 03000104 */  bgez       $zero, .L80039E10
    /* 2A604 80039E04 23500A00 */   negu      $t2, $t2
  .L80039E08:
    /* 2A608 80039E08 21506A00 */  addu       $t2, $v1, $t2
    /* 2A60C 80039E0C 00E84A85 */  lh         $t2, -0x1800($t2)
  .L80039E10:
    /* 2A610 80039E10 0008CC2B */  slti       $t4, $fp, 0x800
    /* 2A614 80039E14 0B008011 */  beqz       $t4, .L80039E44
    /* 2A618 80039E18 0004CC2B */   slti      $t4, $fp, 0x400
    /* 2A61C 80039E1C 05008011 */  beqz       $t4, .L80039E34
    /* 2A620 80039E20 40601E00 */   sll       $t4, $fp, 1
    /* 2A624 80039E24 23606C00 */  subu       $t4, $v1, $t4
    /* 2A628 80039E28 0F000104 */  bgez       $zero, .L80039E68
    /* 2A62C 80039E2C 00088C85 */   lh        $t4, 0x800($t4)
    /* 2A630 80039E30 00000000 */  nop
  .L80039E34:
    /* 2A634 80039E34 21606C00 */  addu       $t4, $v1, $t4
    /* 2A638 80039E38 00F88C85 */  lh         $t4, -0x800($t4)
    /* 2A63C 80039E3C 0A000104 */  bgez       $zero, .L80039E68
    /* 2A640 80039E40 23600C00 */   negu      $t4, $t4
  .L80039E44:
    /* 2A644 80039E44 000CCC2B */  slti       $t4, $fp, 0xC00
    /* 2A648 80039E48 05008011 */  beqz       $t4, .L80039E60
    /* 2A64C 80039E4C 40601E00 */   sll       $t4, $fp, 1
    /* 2A650 80039E50 23606C00 */  subu       $t4, $v1, $t4
    /* 2A654 80039E54 00188C85 */  lh         $t4, 0x1800($t4)
    /* 2A658 80039E58 03000104 */  bgez       $zero, .L80039E68
    /* 2A65C 80039E5C 23600C00 */   negu      $t4, $t4
  .L80039E60:
    /* 2A660 80039E60 21606C00 */  addu       $t4, $v1, $t4
    /* 2A664 80039E64 00E88C85 */  lh         $t4, -0x1800($t4)
  .L80039E68:
    /* 2A668 80039E68 18002F01 */  mult       $t1, $t7
    /* 2A66C 80039E6C FFFFF031 */  andi       $s0, $t7, 0xFFFF
    /* 2A670 80039E70 FFFF2931 */  andi       $t1, $t1, 0xFFFF
    /* 2A674 80039E74 FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 2A678 80039E78 FFFFCE31 */  andi       $t6, $t6, 0xFFFF
    /* 2A67C 80039E7C FFFF4B31 */  andi       $t3, $t2, 0xFFFF
    /* 2A680 80039E80 FFFF8C31 */  andi       $t4, $t4, 0xFFFF
    /* 2A684 80039E84 0008C048 */  ctc2       $zero, $1 /* handwritten instruction */
    /* 2A688 80039E88 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 2A68C 80039E8C 00088E48 */  mtc2       $t6, $1 /* handwritten instruction */
    /* 2A690 80039E90 000C0C00 */  sll        $at, $t4, 16
    /* 2A694 80039E94 25082D00 */  or         $at, $at, $t5
    /* 2A698 80039E98 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 2A69C 80039E9C 12F00000 */  mflo       $fp
    /* 2A6A0 80039EA0 0000CB48 */  ctc2       $t3, $0 /* handwritten instruction */
    /* 2A6A4 80039EA4 0010C948 */  ctc2       $t1, $2 /* handwritten instruction */
    /* 2A6A8 80039EA8 0020CD48 */  ctc2       $t5, $4 /* handwritten instruction */
    /* 2A6AC 80039EAC 03F31E00 */  sra        $fp, $fp, 12
    /* 2A6B0 80039EB0 1800CA03 */  mult       $fp, $t2
    /* 2A6B4 80039EB4 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 2A6B8 80039EB8 0000CC48 */  ctc2       $t4, $0 /* handwritten instruction */
    /* 2A6BC 80039EBC 0010CE48 */  ctc2       $t6, $2 /* handwritten instruction */
    /* 2A6C0 80039EC0 0020D048 */  ctc2       $s0, $4 /* handwritten instruction */
    /* 2A6C4 80039EC4 00481D48 */  mfc2       $sp, $9 /* handwritten instruction */
    /* 2A6C8 80039EC8 12C00000 */  mflo       $t8
    /* 2A6CC 80039ECC 03C31800 */  sra        $t8, $t8, 12
    /* 2A6D0 80039ED0 00501C48 */  mfc2       $gp, $10 /* handwritten instruction */
    /* 2A6D4 80039ED4 00581148 */  mfc2       $s1, $11 /* handwritten instruction */
    /* 2A6D8 80039ED8 1800AF03 */  mult       $sp, $t7
    /* 2A6DC 80039EDC 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 2A6E0 80039EE0 0000D048 */  ctc2       $s0, $0 /* handwritten instruction */
    /* 2A6E4 80039EE4 FFFFA133 */  andi       $at, $sp, 0xFFFF
    /* 2A6E8 80039EE8 0010C148 */  ctc2       $at, $2 /* handwritten instruction */
    /* 2A6EC 80039EEC 0020C948 */  ctc2       $t1, $4 /* handwritten instruction */
    /* 2A6F0 80039EF0 00480148 */  mfc2       $at, $9 /* handwritten instruction */
    /* 2A6F4 80039EF4 12B80000 */  mflo       $s7
    /* 2A6F8 80039EF8 00501248 */  mfc2       $s2, $10 /* handwritten instruction */
    /* 2A6FC 80039EFC 00581348 */  mfc2       $s3, $11 /* handwritten instruction */
    /* 2A700 80039F00 18008A03 */  mult       $gp, $t2
    /* 2A704 80039F04 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 2A708 80039F08 03BB1700 */  sra        $s7, $s7, 12
    /* 2A70C 80039F0C 00481448 */  mfc2       $s4, $9 /* handwritten instruction */
    /* 2A710 80039F10 00501548 */  mfc2       $s5, $10 /* handwritten instruction */
    /* 2A714 80039F14 00581648 */  mfc2       $s6, $11 /* handwritten instruction */
    /* 2A718 80039F18 12C80000 */  mflo       $t9
    /* 2A71C 80039F1C 03CB1900 */  sra        $t9, $t9, 12
    /* 2A720 80039F20 23901200 */  negu       $s2, $s2
    /* 2A724 80039F24 23B89703 */  subu       $s7, $gp, $s7
    /* 2A728 80039F28 21A8D503 */  addu       $s5, $fp, $s5
    /* 2A72C 80039F2C 21C03800 */  addu       $t8, $at, $t8
    /* 2A730 80039F30 23C01800 */  negu       $t8, $t8
    /* 2A734 80039F34 23C83403 */  subu       $t9, $t9, $s4
    /* 2A738 80039F38 0000898C */  lw         $t1, 0x0($a0)
    /* 2A73C 80039F3C 04008B8C */  lw         $t3, 0x4($a0)
    /* 2A740 80039F40 08008C8C */  lw         $t4, 0x8($a0)
    /* 2A744 80039F44 0C008D8C */  lw         $t5, 0xC($a0)
    /* 2A748 80039F48 10008E8C */  lw         $t6, 0x10($a0)
    /* 2A74C 80039F4C 0000C948 */  ctc2       $t1, $0 /* handwritten instruction */
    /* 2A750 80039F50 0008CB48 */  ctc2       $t3, $1 /* handwritten instruction */
    /* 2A754 80039F54 0010CC48 */  ctc2       $t4, $2 /* handwritten instruction */
    /* 2A758 80039F58 0018CD48 */  ctc2       $t5, $3 /* handwritten instruction */
    /* 2A75C 80039F5C 0020CE48 */  ctc2       $t6, $4 /* handwritten instruction */
    /* 2A760 80039F60 1800C98C */  lw         $t1, 0x18($a2)
    /* 2A764 80039F64 0400AB8C */  lw         $t3, 0x4($a1)
    /* 2A768 80039F68 00489748 */  mtc2       $s7, $9 /* handwritten instruction */
    /* 2A76C 80039F6C 00509348 */  mtc2       $s3, $10 /* handwritten instruction */
    /* 2A770 80039F70 00589848 */  mtc2       $t8, $11 /* handwritten instruction */
    /* 2A774 80039F74 18002B01 */  mult       $t1, $t3
    /* 2A778 80039F78 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2A77C 80039F7C 1C00C98C */  lw         $t1, 0x1C($a2)
    /* 2A780 80039F80 0800AB8C */  lw         $t3, 0x8($a1)
    /* 2A784 80039F84 00481748 */  mfc2       $s7, $9 /* handwritten instruction */
    /* 2A788 80039F88 00501348 */  mfc2       $s3, $10 /* handwritten instruction */
    /* 2A78C 80039F8C 00581848 */  mfc2       $t8, $11 /* handwritten instruction */
    /* 2A790 80039F90 12600000 */  mflo       $t4
    /* 2A794 80039F94 00489148 */  mtc2       $s1, $9 /* handwritten instruction */
    /* 2A798 80039F98 00508A48 */  mtc2       $t2, $10 /* handwritten instruction */
    /* 2A79C 80039F9C 00589648 */  mtc2       $s6, $11 /* handwritten instruction */
    /* 2A7A0 80039FA0 18002B01 */  mult       $t1, $t3
    /* 2A7A4 80039FA4 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2A7A8 80039FA8 2000C98C */  lw         $t1, 0x20($a2)
    /* 2A7AC 80039FAC 0C00AB8C */  lw         $t3, 0xC($a1)
    /* 2A7B0 80039FB0 00481148 */  mfc2       $s1, $9 /* handwritten instruction */
    /* 2A7B4 80039FB4 00500A48 */  mfc2       $t2, $10 /* handwritten instruction */
    /* 2A7B8 80039FB8 00581648 */  mfc2       $s6, $11 /* handwritten instruction */
    /* 2A7BC 80039FBC 03630C00 */  sra        $t4, $t4, 12
    /* 2A7C0 80039FC0 12680000 */  mflo       $t5
    /* 2A7C4 80039FC4 00489548 */  mtc2       $s5, $9 /* handwritten instruction */
    /* 2A7C8 80039FC8 00509248 */  mtc2       $s2, $10 /* handwritten instruction */
    /* 2A7CC 80039FCC 00589948 */  mtc2       $t9, $11 /* handwritten instruction */
    /* 2A7D0 80039FD0 18002B01 */  mult       $t1, $t3
    /* 2A7D4 80039FD4 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2A7D8 80039FD8 036B0D00 */  sra        $t5, $t5, 12
    /* 2A7DC 80039FDC 00481548 */  mfc2       $s5, $9 /* handwritten instruction */
    /* 2A7E0 80039FE0 00501248 */  mfc2       $s2, $10 /* handwritten instruction */
    /* 2A7E4 80039FE4 00581948 */  mfc2       $t9, $11 /* handwritten instruction */
    /* 2A7E8 80039FE8 FFFF8C31 */  andi       $t4, $t4, 0xFFFF
    /* 2A7EC 80039FEC FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 2A7F0 80039FF0 12700000 */  mflo       $t6
    /* 2A7F4 80039FF4 03730E00 */  sra        $t6, $t6, 12
    /* 2A7F8 80039FF8 FFFFCE31 */  andi       $t6, $t6, 0xFFFF
    /* 2A7FC 80039FFC 0000CC48 */  ctc2       $t4, $0 /* handwritten instruction */
    /* 2A800 8003A000 0008C048 */  ctc2       $zero, $1 /* handwritten instruction */
    /* 2A804 8003A004 0010CD48 */  ctc2       $t5, $2 /* handwritten instruction */
    /* 2A808 8003A008 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 2A80C 8003A00C 0020CE48 */  ctc2       $t6, $4 /* handwritten instruction */
    /* 2A810 8003A010 00489348 */  mtc2       $s3, $9 /* handwritten instruction */
    /* 2A814 8003A014 00508A48 */  mtc2       $t2, $10 /* handwritten instruction */
    /* 2A818 8003A018 00589248 */  mtc2       $s2, $11 /* handwritten instruction */
    /* 2A81C 8003A01C 00000000 */  nop
    /* 2A820 8003A020 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2A824 8003A024 00000000 */  nop
    /* 2A828 8003A028 00481348 */  mfc2       $s3, $9 /* handwritten instruction */
    /* 2A82C 8003A02C 00500A48 */  mfc2       $t2, $10 /* handwritten instruction */
    /* 2A830 8003A030 00581248 */  mfc2       $s2, $11 /* handwritten instruction */
    /* 2A834 8003A034 00489848 */  mtc2       $t8, $9 /* handwritten instruction */
    /* 2A838 8003A038 00509648 */  mtc2       $s6, $10 /* handwritten instruction */
    /* 2A83C 8003A03C 00589948 */  mtc2       $t9, $11 /* handwritten instruction */
    /* 2A840 8003A040 21486002 */  addu       $t1, $s3, $zero
    /* 2A844 8003A044 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2A848 8003A048 21584001 */  addu       $t3, $t2, $zero
    /* 2A84C 8003A04C 00481848 */  mfc2       $t8, $9 /* handwritten instruction */
    /* 2A850 8003A050 00501648 */  mfc2       $s6, $10 /* handwritten instruction */
    /* 2A854 8003A054 00581948 */  mfc2       $t9, $11 /* handwritten instruction */
    /* 2A858 8003A058 00489748 */  mtc2       $s7, $9 /* handwritten instruction */
    /* 2A85C 8003A05C 00509148 */  mtc2       $s1, $10 /* handwritten instruction */
    /* 2A860 8003A060 00589548 */  mtc2       $s5, $11 /* handwritten instruction */
    /* 2A864 8003A064 21604002 */  addu       $t4, $s2, $zero
    /* 2A868 8003A068 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2A86C 8003A06C 80981300 */  sll        $s3, $s3, 2
    /* 2A870 8003A070 00481748 */  mfc2       $s7, $9 /* handwritten instruction */
    /* 2A874 8003A074 00501148 */  mfc2       $s1, $10 /* handwritten instruction */
    /* 2A878 8003A078 00581548 */  mfc2       $s5, $11 /* handwritten instruction */
    /* 2A87C 8003A07C 21986902 */  addu       $s3, $s3, $t1
    /* 2A880 8003A080 C3981300 */  sra        $s3, $s3, 3
    /* 2A884 8003A084 23981300 */  negu       $s3, $s3
    /* 2A888 8003A088 80500A00 */  sll        $t2, $t2, 2
    /* 2A88C 8003A08C 21504B01 */  addu       $t2, $t2, $t3
    /* 2A890 8003A090 C3500A00 */  sra        $t2, $t2, 3
    /* 2A894 8003A094 23500A00 */  negu       $t2, $t2
    /* 2A898 8003A098 80901200 */  sll        $s2, $s2, 2
    /* 2A89C 8003A09C 21904C02 */  addu       $s2, $s2, $t4
    /* 2A8A0 8003A0A0 C3901200 */  sra        $s2, $s2, 3
    /* 2A8A4 8003A0A4 23901200 */  negu       $s2, $s2
    /* 2A8A8 8003A0A8 23C01800 */  negu       $t8, $t8
    /* 2A8AC 8003A0AC 23B01600 */  negu       $s6, $s6
    /* 2A8B0 8003A0B0 23C81900 */  negu       $t9, $t9
    /* 2A8B4 8003A0B4 FFFFE132 */  andi       $at, $s7, 0xFFFF
    /* 2A8B8 8003A0B8 004C1100 */  sll        $t1, $s1, 16
    /* 2A8BC 8003A0BC 25482101 */  or         $t1, $t1, $at
    /* 2A8C0 8003A0C0 FFFFA132 */  andi       $at, $s5, 0xFFFF
    /* 2A8C4 8003A0C4 005C1300 */  sll        $t3, $s3, 16
    /* 2A8C8 8003A0C8 25586101 */  or         $t3, $t3, $at
    /* 2A8CC 8003A0CC FFFF4131 */  andi       $at, $t2, 0xFFFF
    /* 2A8D0 8003A0D0 00641200 */  sll        $t4, $s2, 16
    /* 2A8D4 8003A0D4 25608101 */  or         $t4, $t4, $at
    /* 2A8D8 8003A0D8 FFFF0133 */  andi       $at, $t8, 0xFFFF
    /* 2A8DC 8003A0DC 006C1600 */  sll        $t5, $s6, 16
    /* 2A8E0 8003A0E0 2568A101 */  or         $t5, $t5, $at
    /* 2A8E4 8003A0E4 0000C948 */  ctc2       $t1, $0 /* handwritten instruction */
    /* 2A8E8 8003A0E8 0008CB48 */  ctc2       $t3, $1 /* handwritten instruction */
    /* 2A8EC 8003A0EC 0010CC48 */  ctc2       $t4, $2 /* handwritten instruction */
    /* 2A8F0 8003A0F0 0018CD48 */  ctc2       $t5, $3 /* handwritten instruction */
    /* 2A8F4 8003A0F4 0020D948 */  ctc2       $t9, $4 /* handwritten instruction */
    /* 2A8F8 8003A0F8 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 2A8FC 8003A0FC 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2A900 8003A100 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2A904 8003A104 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2A908 8003A108 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2A90C 8003A10C 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2A910 8003A110 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2A914 8003A114 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2A918 8003A118 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2A91C 8003A11C 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2A920 8003A120 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2A924 8003A124 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2A928 8003A128 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2A92C 8003A12C 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2A930 8003A130 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2A934 8003A134 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2A938 8003A138 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2A93C 8003A13C 0800E003 */  jr         $ra
    /* 2A940 8003A140 00000000 */   nop
endlabel func_80039BD4
