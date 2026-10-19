.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformWorldsFog
    /* 26098 80035898 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 2609C 8003589C 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 260A0 800358A0 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 260A4 800358A4 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 260A8 800358A8 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 260AC 800358AC 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 260B0 800358B0 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 260B4 800358B4 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 260B8 800358B8 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 260BC 800358BC 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 260C0 800358C0 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 260C4 800358C4 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 260C8 800358C8 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 260CC 800358CC 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 260D0 800358D0 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 260D4 800358D4 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 260D8 800358D8 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 260DC 800358DC 1000AF8F */  lw         $t7, 0x10($sp)
    /* 260E0 800358E0 1400B68F */  lw         $s6, 0x14($sp)
    /* 260E4 800358E4 0000EB8D */  lw         $t3, 0x0($t7)
    /* 260E8 800358E8 801F1D3C */  lui        $sp, (0x1F8000E0 >> 16)
    /* 260EC 800358EC E000BD37 */  ori        $sp, $sp, (0x1F8000E0 & 0xFFFF)
    /* 260F0 800358F0 0000A7AF */  sw         $a3, 0x0($sp)
    /* 260F4 800358F4 FF001C3C */  lui        $gp, (0xFFFFFF >> 16)
    /* 260F8 800358F8 FFFF9C37 */  ori        $gp, $gp, (0xFFFFFF & 0xFFFF)
    /* 260FC 800358FC 60000F34 */  ori        $t7, $zero, 0x60
    /* 26100 80035900 801F083C */  lui        $t0, (0x1F800100 >> 16)
    /* 26104 80035904 00010835 */  ori        $t0, $t0, (0x1F800100 & 0xFFFF)
    /* 26108 80035908 00008D8C */  lw         $t5, 0x0($a0)
    /* 2610C 8003590C 02008A24 */  addiu      $t2, $a0, 0x2
    /* 26110 80035910 21504D01 */  addu       $t2, $t2, $t5
    /* 26114 80035914 21504D01 */  addu       $t2, $t2, $t5
    /* 26118 80035918 FFFF0C34 */  ori        $t4, $zero, 0xFFFF
    /* 2611C 8003591C 00004195 */  lhu        $at, 0x0($t2)
    /* 26120 80035920 80300600 */  sll        $a2, $a2, 2
    /* 26124 80035924 FC1F0334 */  ori        $v1, $zero, 0x1FFC
  .L80035928:
    /* 26128 80035928 FEFF4A25 */  addiu      $t2, $t2, -0x2
    /* 2612C 8003592C 02F30100 */  srl        $fp, $at, 12
    /* 26130 80035930 1000CC13 */  beq        $fp, $t4, .L80035974
    /* 26134 80035934 FF0F2130 */   andi      $at, $at, 0xFFF
    /* 26138 80035938 2160C003 */  addu       $t4, $fp, $zero
    /* 2613C 8003593C 80F90C00 */  sll        $ra, $t4, 6
    /* 26140 80035940 2110E803 */  addu       $v0, $ra, $t0
    /* 26144 80035944 04005D8C */  lw         $sp, 0x4($v0)
    /* 26148 80035948 08005E8C */  lw         $fp, 0x8($v0)
    /* 2614C 8003594C 0C005F8C */  lw         $ra, 0xC($v0)
    /* 26150 80035950 0028DD48 */  ctc2       $sp, $5 /* handwritten instruction */
    /* 26154 80035954 0030DE48 */  ctc2       $fp, $6 /* handwritten instruction */
    /* 26158 80035958 0038DF48 */  ctc2       $ra, $7 /* handwritten instruction */
    /* 2615C 8003595C 0000478C */  lw         $a3, 0x0($v0)
    /* 26160 80035960 1400578C */  lw         $s7, 0x14($v0)
    /* 26164 80035964 1800588C */  lw         $t8, 0x18($v0)
    /* 26168 80035968 1C00598C */  lw         $t9, 0x1C($v0)
    /* 2616C 8003596C 02240700 */  srl        $a0, $a3, 16
    /* 26170 80035970 FFFFE730 */  andi       $a3, $a3, 0xFFFF
  .L80035974:
    /* 26174 80035974 C0080100 */  sll        $at, $at, 3
    /* 26178 80035978 2148E102 */  addu       $t1, $s7, $at
    /* 2617C 8003597C 0000218D */  lw         $at, 0x0($t1)
    /* 26180 80035980 0400298D */  lw         $t1, 0x4($t1)
    /* 26184 80035984 00130100 */  sll        $v0, $at, 12
    /* 26188 80035988 FF003D31 */  andi       $sp, $t1, 0xFF
    /* 2618C 8003598C 25105D00 */  or         $v0, $v0, $sp
    /* 26190 80035990 42840900 */  srl        $s0, $t1, 17
    /* 26194 80035994 F87F1032 */  andi       $s0, $s0, 0x7FF8
    /* 26198 80035998 21801802 */  addu       $s0, $s0, $t8
    /* 2619C 8003599C 42890900 */  srl        $s1, $t1, 5
    /* 261A0 800359A0 F87F3132 */  andi       $s1, $s1, 0x7FF8
    /* 261A4 800359A4 21883802 */  addu       $s1, $s1, $t8
    /* 261A8 800359A8 42940100 */  srl        $s2, $at, 17
    /* 261AC 800359AC F87F5232 */  andi       $s2, $s2, 0x7FF8
    /* 261B0 800359B0 21905802 */  addu       $s2, $s2, $t8
    /* 261B4 800359B4 0000138E */  lw         $s3, 0x0($s0)
    /* 261B8 800359B8 0400108E */  lw         $s0, 0x4($s0)
    /* 261BC 800359BC 0000348E */  lw         $s4, 0x0($s1)
    /* 261C0 800359C0 0400318E */  lw         $s1, 0x4($s1)
    /* 261C4 800359C4 0000558E */  lw         $s5, 0x0($s2)
    /* 261C8 800359C8 0400528E */  lw         $s2, 0x4($s2)
    /* 261CC 800359CC F8FF013C */  lui        $at, (0xFFF8FFF8 >> 16)
    /* 261D0 800359D0 F8FF2134 */  ori        $at, $at, (0xFFF8FFF8 & 0xFFFF)
    /* 261D4 800359D4 24E80102 */  and        $sp, $s0, $at
    /* 261D8 800359D8 24F02102 */  and        $fp, $s1, $at
    /* 261DC 800359DC 24F84102 */  and        $ra, $s2, $at
    /* 261E0 800359E0 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 261E4 800359E4 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 261E8 800359E8 00209F48 */  mtc2       $ra, $4 /* handwritten instruction */
    /* 261EC 800359EC 0700013C */  lui        $at, (0x70006 >> 16)
    /* 261F0 800359F0 06002134 */  ori        $at, $at, (0x70006 & 0xFFFF)
    /* 261F4 800359F4 02EE1300 */  srl        $sp, $s3, 24
    /* 261F8 800359F8 C0E81D00 */  sll        $sp, $sp, 3
    /* 261FC 800359FC 24800102 */  and        $s0, $s0, $at
    /* 26200 80035A00 804A1000 */  sll        $t1, $s0, 10
    /* 26204 80035A04 25E8A903 */  or         $sp, $sp, $t1
    /* 26208 80035A08 C2481000 */  srl        $t1, $s0, 3
    /* 2620C 80035A0C 25E8A903 */  or         $sp, $sp, $t1
    /* 26210 80035A10 02F61400 */  srl        $fp, $s4, 24
    /* 26214 80035A14 C0F01E00 */  sll        $fp, $fp, 3
    /* 26218 80035A18 24882102 */  and        $s1, $s1, $at
    /* 2621C 80035A1C 804A1100 */  sll        $t1, $s1, 10
    /* 26220 80035A20 25F0C903 */  or         $fp, $fp, $t1
    /* 26224 80035A24 C2481100 */  srl        $t1, $s1, 3
    /* 26228 80035A28 25F0C903 */  or         $fp, $fp, $t1
    /* 2622C 80035A2C 02FE1500 */  srl        $ra, $s5, 24
    /* 26230 80035A30 C0F81F00 */  sll        $ra, $ra, 3
    /* 26234 80035A34 24904102 */  and        $s2, $s2, $at
    /* 26238 80035A38 804A1200 */  sll        $t1, $s2, 10
    /* 2623C 80035A3C 25F8E903 */  or         $ra, $ra, $t1
    /* 26240 80035A40 C2481200 */  srl        $t1, $s2, 3
    /* 26244 80035A44 25F8E903 */  or         $ra, $ra, $t1
    /* 26248 80035A48 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 2624C 80035A4C 00189E48 */  mtc2       $fp, $3 /* handwritten instruction */
    /* 26250 80035A50 00289F48 */  mtc2       $ra, $5 /* handwritten instruction */
    /* 26254 80035A54 02F50200 */  srl        $fp, $v0, 20
    /* 26258 80035A58 3000284A */  rtpt
    /* 2625C 80035A5C 80F01E00 */  sll        $fp, $fp, 2
    /* 26260 80035A60 21703E03 */  addu       $t6, $t9, $fp
    /* 26264 80035A64 0000C98D */  lw         $t1, 0x0($t6)
    /* 26268 80035A68 0034123C */  lui        $s2, (0x34000000 >> 16)
    /* 2626C 80035A6C 024E0900 */  srl        $t1, $t1, 24
    /* 26270 80035A70 80003D31 */  andi       $sp, $t1, 0x80
    /* 26274 80035A74 8800A013 */  beqz       $sp, .L80035C98
    /* 26278 80035A78 00000000 */   nop
    /* 2627C 80035A7C 08006CE9 */  swc2       $12, 0x8($t3)
    /* 26280 80035A80 14006DE9 */  swc2       $13, 0x14($t3)
    /* 26284 80035A84 20006EE9 */  swc2       $14, 0x20($t3)
    /* 26288 80035A88 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 2628C 80035A8C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 26290 80035A90 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 26294 80035A94 0700C013 */  beqz       $fp, .L80035AB4
    /* 26298 80035A98 23F0A703 */   subu      $fp, $sp, $a3
    /* 2629C 80035A9C 04F09E00 */  sllv       $fp, $fp, $a0
    /* 262A0 80035AA0 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 262A4 80035AA4 00000000 */  nop
    /* 262A8 80035AA8 1000784A */  dpcs
    /* 262AC 80035AAC 00000000 */  nop
    /* 262B0 80035AB0 00B01348 */  mfc2       $s3, $22 /* handwritten instruction */
  .L80035AB4:
    /* 262B4 80035AB4 00901F48 */  mfc2       $ra, $18 /* handwritten instruction */
    /* 262B8 80035AB8 00000000 */  nop
    /* 262BC 80035ABC 2188BF03 */  addu       $s1, $sp, $ra
    /* 262C0 80035AC0 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 262C4 80035AC4 2AF0FF00 */  slt        $fp, $a3, $ra
    /* 262C8 80035AC8 0700C013 */  beqz       $fp, .L80035AE8
    /* 262CC 80035ACC 23F0E703 */   subu      $fp, $ra, $a3
    /* 262D0 80035AD0 04F09E00 */  sllv       $fp, $fp, $a0
    /* 262D4 80035AD4 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 262D8 80035AD8 00000000 */  nop
    /* 262DC 80035ADC 1000784A */  dpcs
    /* 262E0 80035AE0 00000000 */  nop
    /* 262E4 80035AE4 00B01448 */  mfc2       $s4, $22 /* handwritten instruction */
  .L80035AE8:
    /* 262E8 80035AE8 00981D48 */  mfc2       $sp, $19 /* handwritten instruction */
    /* 262EC 80035AEC 00000000 */  nop
    /* 262F0 80035AF0 21883D02 */  addu       $s1, $s1, $sp
    /* 262F4 80035AF4 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 262F8 80035AF8 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 262FC 80035AFC 0700C013 */  beqz       $fp, .L80035B1C
    /* 26300 80035B00 23F0A703 */   subu      $fp, $sp, $a3
    /* 26304 80035B04 04F09E00 */  sllv       $fp, $fp, $a0
    /* 26308 80035B08 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 2630C 80035B0C 00000000 */  nop
    /* 26310 80035B10 1000784A */  dpcs
    /* 26314 80035B14 00000000 */  nop
    /* 26318 80035B18 00B01548 */  mfc2       $s5, $22 /* handwritten instruction */
  .L80035B1C:
    /* 2631C 80035B1C 42891100 */  srl        $s1, $s1, 5
    /* 26320 80035B20 80881100 */  sll        $s1, $s1, 2
    /* 26324 80035B24 24987C02 */  and        $s3, $s3, $gp
    /* 26328 80035B28 24F02F01 */  and        $fp, $t1, $t7
    /* 2632C 80035B2C 0300CF13 */  beq        $fp, $t7, .L80035B3C
    /* 26330 80035B30 25987202 */   or        $s3, $s3, $s2
    /* 26334 80035B34 00021E3C */  lui        $fp, (0x2000000 >> 16)
    /* 26338 80035B38 25987E02 */  or         $s3, $s3, $fp
  .L80035B3C:
    /* 2633C 80035B3C 040073AD */  sw         $s3, 0x4($t3)
    /* 26340 80035B40 100074AD */  sw         $s4, 0x10($t3)
    /* 26344 80035B44 1C0075AD */  sw         $s5, 0x1C($t3)
    /* 26348 80035B48 C2FB0200 */  srl        $ra, $v0, 15
    /* 2634C 80035B4C 1C00FF33 */  andi       $ra, $ra, 0x1C
    /* 26350 80035B50 80E90C00 */  sll        $sp, $t4, 6
    /* 26354 80035B54 21E8A803 */  addu       $sp, $sp, $t0
    /* 26358 80035B58 2000BD27 */  addiu      $sp, $sp, 0x20
    /* 2635C 80035B5C 2108FD03 */  addu       $at, $ra, $sp
    /* 26360 80035B60 1E005F30 */  andi       $ra, $v0, 0x1E
    /* 26364 80035B64 0D00E013 */  beqz       $ra, .L80035B9C
    /* 26368 80035B68 42E90200 */   srl       $sp, $v0, 5
    /* 2636C 80035B6C 801F1E3C */  lui        $fp, (0x1F8000E0 >> 16)
    /* 26370 80035B70 E000DE37 */  ori        $fp, $fp, (0x1F8000E0 & 0xFFFF)
    /* 26374 80035B74 0000DE8F */  lw         $fp, 0x0($fp)
    /* 26378 80035B78 0700BD33 */  andi       $sp, $sp, 0x7
    /* 2637C 80035B7C 06F0BE03 */  srlv       $fp, $fp, $sp
    /* 26380 80035B80 02EB0200 */  srl        $sp, $v0, 12
    /* 26384 80035B84 1F00BD33 */  andi       $sp, $sp, 0x1F
    /* 26388 80035B88 21E8DD03 */  addu       $sp, $fp, $sp
    /* 2638C 80035B8C 0100FE37 */  ori        $fp, $ra, 0x1
    /* 26390 80035B90 24E8BE03 */  and        $sp, $sp, $fp
    /* 26394 80035B94 80E81D00 */  sll        $sp, $sp, 2
    /* 26398 80035B98 2170AE03 */  addu       $t6, $sp, $t6
  .L80035B9C:
    /* 2639C 80035B9C 0400D38D */  lw         $s3, 0x4($t6)
    /* 263A0 80035BA0 0000348C */  lw         $s4, 0x0($at)
    /* 263A4 80035BA4 82ED1300 */  srl        $sp, $s3, 22
    /* 263A8 80035BA8 C0E81D00 */  sll        $sp, $sp, 3
    /* 263AC 80035BAC 2170DD02 */  addu       $t6, $s6, $sp
    /* 263B0 80035BB0 0000D08D */  lw         $s0, 0x0($t6)
    /* 263B4 80035BB4 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 263B8 80035BB8 02AD1300 */  srl        $s5, $s3, 20
    /* 263BC 80035BBC 0300B532 */  andi       $s5, $s5, 0x3
    /* 263C0 80035BC0 C0E91500 */  sll        $sp, $s5, 7
    /* 263C4 80035BC4 1C009E32 */  andi       $fp, $s4, 0x1C
    /* 263C8 80035BC8 25E8BE03 */  or         $sp, $sp, $fp
    /* 263CC 80035BCC 82F41300 */  srl        $fp, $s3, 18
    /* 263D0 80035BD0 0300DE33 */  andi       $fp, $fp, 0x3
    /* 263D4 80035BD4 25E8BE03 */  or         $sp, $sp, $fp
    /* 263D8 80035BD8 60003E31 */  andi       $fp, $t1, 0x60
    /* 263DC 80035BDC 25E8BE03 */  or         $sp, $sp, $fp
    /* 263E0 80035BE0 00EC1D00 */  sll        $sp, $sp, 16
    /* 263E4 80035BE4 1F007E32 */  andi       $fp, $s3, 0x1F
    /* 263E8 80035BE8 80F01E00 */  sll        $fp, $fp, 2
    /* 263EC 80035BEC 80009F32 */  andi       $ra, $s4, 0x80
    /* 263F0 80035BF0 25F0DF03 */  or         $fp, $fp, $ra
    /* 263F4 80035BF4 00FA1E00 */  sll        $ra, $fp, 8
    /* 263F8 80035BF8 82F21300 */  srl        $fp, $s3, 10
    /* 263FC 80035BFC F800DE33 */  andi       $fp, $fp, 0xF8
    /* 26400 80035C00 06F0BE02 */  srlv       $fp, $fp, $s5
    /* 26404 80035C04 25A8DF03 */  or         $s5, $fp, $ra
    /* 26408 80035C08 02F41000 */  srl        $fp, $s0, 16
    /* 2640C 80035C0C 21F0D503 */  addu       $fp, $fp, $s5
    /* 26410 80035C10 25F8BE03 */  or         $ra, $sp, $fp
    /* 26414 80035C14 0F003D31 */  andi       $sp, $t1, 0xF
    /* 26418 80035C18 C01F7E32 */  andi       $fp, $s3, 0x1FC0
    /* 2641C 80035C1C 25E8BE03 */  or         $sp, $sp, $fp
    /* 26420 80035C20 02F11400 */  srl        $fp, $s4, 4
    /* 26424 80035C24 F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 26428 80035C28 25E8BE03 */  or         $sp, $sp, $fp
    /* 2642C 80035C2C 00EC1D00 */  sll        $sp, $sp, 16
    /* 26430 80035C30 FFFF1E32 */  andi       $fp, $s0, 0xFFFF
    /* 26434 80035C34 21F0D503 */  addu       $fp, $fp, $s5
    /* 26438 80035C38 25F0BE03 */  or         $fp, $sp, $fp
    /* 2643C 80035C3C 2170D501 */  addu       $t6, $t6, $s5
    /* 26440 80035C40 0C007EAD */  sw         $fp, 0xC($t3)
    /* 26444 80035C44 18007FAD */  sw         $ra, 0x18($t3)
    /* 26448 80035C48 24006EA5 */  sh         $t6, 0x24($t3)
    /* 2644C 80035C4C 22E8D100 */  sub        $sp, $a2, $s1 /* handwritten instruction */
    /* 26450 80035C50 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 26454 80035C54 2AF0A303 */  slt        $fp, $sp, $v1
    /* 26458 80035C58 0600C013 */  beqz       $fp, .L80035C74
    /* 2645C 80035C5C 2170A300 */   addu      $t6, $a1, $v1
    /* 26460 80035C60 2118A003 */  addu       $v1, $sp, $zero
    /* 26464 80035C64 03006104 */  bgez       $v1, .L80035C74
    /* 26468 80035C68 2170A300 */   addu      $t6, $a1, $v1
    /* 2646C 80035C6C 21180000 */  addu       $v1, $zero, $zero
    /* 26470 80035C70 2170A300 */  addu       $t6, $a1, $v1
  .L80035C74:
    /* 26474 80035C74 0000DD8D */  lw         $sp, 0x0($t6)
    /* 26478 80035C78 24F07C01 */  and        $fp, $t3, $gp
    /* 2647C 80035C7C 0000DEAD */  sw         $fp, 0x0($t6)
    /* 26480 80035C80 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 26484 80035C84 25E8BF03 */  or         $sp, $sp, $ra
    /* 26488 80035C88 00007DAD */  sw         $sp, 0x0($t3)
    /* 2648C 80035C8C 28006B25 */  addiu      $t3, $t3, 0x28
    /* 26490 80035C90 42000104 */  bgez       $zero, .L80035D9C
    /* 26494 80035C94 00000000 */   nop
  .L80035C98:
    /* 26498 80035C98 08006CE9 */  swc2       $12, 0x8($t3)
    /* 2649C 80035C9C 10006DE9 */  swc2       $13, 0x10($t3)
    /* 264A0 80035CA0 18006EE9 */  swc2       $14, 0x18($t3)
    /* 264A4 80035CA4 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 264A8 80035CA8 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 264AC 80035CAC 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 264B0 80035CB0 0700C013 */  beqz       $fp, .L80035CD0
    /* 264B4 80035CB4 23F0A703 */   subu      $fp, $sp, $a3
    /* 264B8 80035CB8 04F09E00 */  sllv       $fp, $fp, $a0
    /* 264BC 80035CBC 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 264C0 80035CC0 00000000 */  nop
    /* 264C4 80035CC4 1000784A */  dpcs
    /* 264C8 80035CC8 00000000 */  nop
    /* 264CC 80035CCC 00B01348 */  mfc2       $s3, $22 /* handwritten instruction */
  .L80035CD0:
    /* 264D0 80035CD0 00901F48 */  mfc2       $ra, $18 /* handwritten instruction */
    /* 264D4 80035CD4 00000000 */  nop
    /* 264D8 80035CD8 2188BF03 */  addu       $s1, $sp, $ra
    /* 264DC 80035CDC 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 264E0 80035CE0 2AF0FF00 */  slt        $fp, $a3, $ra
    /* 264E4 80035CE4 0700C013 */  beqz       $fp, .L80035D04
    /* 264E8 80035CE8 23F0E703 */   subu      $fp, $ra, $a3
    /* 264EC 80035CEC 04F09E00 */  sllv       $fp, $fp, $a0
    /* 264F0 80035CF0 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 264F4 80035CF4 00000000 */  nop
    /* 264F8 80035CF8 1000784A */  dpcs
    /* 264FC 80035CFC 00000000 */  nop
    /* 26500 80035D00 00B01448 */  mfc2       $s4, $22 /* handwritten instruction */
  .L80035D04:
    /* 26504 80035D04 00981D48 */  mfc2       $sp, $19 /* handwritten instruction */
    /* 26508 80035D08 00000000 */  nop
    /* 2650C 80035D0C 21883D02 */  addu       $s1, $s1, $sp
    /* 26510 80035D10 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 26514 80035D14 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 26518 80035D18 0700C013 */  beqz       $fp, .L80035D38
    /* 2651C 80035D1C 23F0A703 */   subu      $fp, $sp, $a3
    /* 26520 80035D20 04F09E00 */  sllv       $fp, $fp, $a0
    /* 26524 80035D24 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 26528 80035D28 00000000 */  nop
    /* 2652C 80035D2C 1000784A */  dpcs
    /* 26530 80035D30 00000000 */  nop
    /* 26534 80035D34 00B01548 */  mfc2       $s5, $22 /* handwritten instruction */
  .L80035D38:
    /* 26538 80035D38 42891100 */  srl        $s1, $s1, 5
    /* 2653C 80035D3C 80881100 */  sll        $s1, $s1, 2
    /* 26540 80035D40 24987C02 */  and        $s3, $s3, $gp
    /* 26544 80035D44 0030123C */  lui        $s2, (0x30000000 >> 16)
    /* 26548 80035D48 25987202 */  or         $s3, $s3, $s2
    /* 2654C 80035D4C 040073AD */  sw         $s3, 0x4($t3)
    /* 26550 80035D50 0C0074AD */  sw         $s4, 0xC($t3)
    /* 26554 80035D54 140075AD */  sw         $s5, 0x14($t3)
    /* 26558 80035D58 22E8D100 */  sub        $sp, $a2, $s1 /* handwritten instruction */
    /* 2655C 80035D5C FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 26560 80035D60 2AF0A303 */  slt        $fp, $sp, $v1
    /* 26564 80035D64 0600C013 */  beqz       $fp, .L80035D80
    /* 26568 80035D68 2170A300 */   addu      $t6, $a1, $v1
    /* 2656C 80035D6C 2118A003 */  addu       $v1, $sp, $zero
    /* 26570 80035D70 03006104 */  bgez       $v1, .L80035D80
    /* 26574 80035D74 2170A300 */   addu      $t6, $a1, $v1
    /* 26578 80035D78 21180000 */  addu       $v1, $zero, $zero
    /* 2657C 80035D7C 2170A300 */  addu       $t6, $a1, $v1
  .L80035D80:
    /* 26580 80035D80 0000DD8D */  lw         $sp, 0x0($t6)
    /* 26584 80035D84 24F07C01 */  and        $fp, $t3, $gp
    /* 26588 80035D88 0000DEAD */  sw         $fp, 0x0($t6)
    /* 2658C 80035D8C 00061E3C */  lui        $fp, (0x6000000 >> 16)
    /* 26590 80035D90 25E8BE03 */  or         $sp, $sp, $fp
    /* 26594 80035D94 00007DAD */  sw         $sp, 0x0($t3)
    /* 26598 80035D98 1C006B25 */  addiu      $t3, $t3, 0x1C
  .L80035D9C:
    /* 2659C 80035D9C FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 265A0 80035DA0 E1FEA015 */  bnez       $t5, .L80035928
    /* 265A4 80035DA4 00004195 */   lhu       $at, 0x0($t2)
    /* 265A8 80035DA8 00000000 */  nop
    /* 265AC 80035DAC 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 265B0 80035DB0 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 265B4 80035DB4 00000000 */  nop
    /* 265B8 80035DB8 1000A18F */  lw         $at, 0x10($sp)
    /* 265BC 80035DBC 00000000 */  nop
    /* 265C0 80035DC0 00002BAC */  sw         $t3, 0x0($at)
    /* 265C4 80035DC4 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 265C8 80035DC8 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 265CC 80035DCC 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 265D0 80035DD0 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 265D4 80035DD4 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 265D8 80035DD8 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 265DC 80035DDC 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 265E0 80035DE0 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 265E4 80035DE4 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 265E8 80035DE8 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 265EC 80035DEC 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 265F0 80035DF0 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 265F4 80035DF4 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 265F8 80035DF8 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 265FC 80035DFC 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 26600 80035E00 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 26604 80035E04 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 26608 80035E08 0800E003 */  jr         $ra
    /* 2660C 80035E0C 00000000 */   nop
endlabel Gte_RTransformWorldsFog
