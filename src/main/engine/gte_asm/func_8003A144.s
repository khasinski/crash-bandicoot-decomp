.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_8003A144
    /* 2A944 8003A144 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 2A948 8003A148 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2A94C 8003A14C 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2A950 8003A150 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2A954 8003A154 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2A958 8003A158 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2A95C 8003A15C 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2A960 8003A160 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2A964 8003A164 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2A968 8003A168 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2A96C 8003A16C 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2A970 8003A170 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2A974 8003A174 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2A978 8003A178 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2A97C 8003A17C 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2A980 8003A180 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2A984 8003A184 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2A988 8003A188 1000BF8F */  lw         $ra, 0x10($sp)
    /* 2A98C 8003A18C 1400A28F */  lw         $v0, 0x14($sp)
    /* 2A990 8003A190 1800B98F */  lw         $t9, 0x18($sp)
    /* 2A994 8003A194 1C00BC8F */  lw         $gp, 0x1C($sp)
    /* 2A998 8003A198 0000E88F */  lw         $t0, 0x0($ra)
    /* 2A99C 8003A19C 0400E98F */  lw         $t1, 0x4($ra)
    /* 2A9A0 8003A1A0 0800EA8F */  lw         $t2, 0x8($ra)
    /* 2A9A4 8003A1A4 0C00EB8F */  lw         $t3, 0xC($ra)
    /* 2A9A8 8003A1A8 1000EC8F */  lw         $t4, 0x10($ra)
    /* 2A9AC 8003A1AC 0000C848 */  ctc2       $t0, $0 /* handwritten instruction */
    /* 2A9B0 8003A1B0 0008C948 */  ctc2       $t1, $1 /* handwritten instruction */
    /* 2A9B4 8003A1B4 0010CA48 */  ctc2       $t2, $2 /* handwritten instruction */
    /* 2A9B8 8003A1B8 0018CB48 */  ctc2       $t3, $3 /* handwritten instruction */
    /* 2A9BC 8003A1BC 0020CC48 */  ctc2       $t4, $4 /* handwritten instruction */
    /* 2A9C0 8003A1C0 0000908C */  lw         $s0, 0x0($a0)
    /* 2A9C4 8003A1C4 0800C010 */  beqz       $a2, .L8003A1E8
    /* 2A9C8 8003A1C8 0400918C */   lw        $s1, 0x4($a0)
    /* 2A9CC 8003A1CC 03821000 */  sra        $s0, $s0, 8
    /* 2A9D0 8003A1D0 23881100 */  negu       $s1, $s1
    /* 2A9D4 8003A1D4 038A1100 */  sra        $s1, $s1, 8
    /* 2A9D8 8003A1D8 0028D048 */  ctc2       $s0, $5 /* handwritten instruction */
    /* 2A9DC 8003A1DC 0030D148 */  ctc2       $s1, $6 /* handwritten instruction */
    /* 2A9E0 8003A1E0 20000104 */  bgez       $zero, .L8003A264
    /* 2A9E4 8003A1E4 0038C248 */   ctc2      $v0, $7 /* handwritten instruction */
  .L8003A1E8:
    /* 2A9E8 8003A1E8 0800928C */  lw         $s2, 0x8($a0)
    /* 2A9EC 8003A1EC 0000B38C */  lw         $s3, 0x0($a1)
    /* 2A9F0 8003A1F0 0400B48C */  lw         $s4, 0x4($a1)
    /* 2A9F4 8003A1F4 0800B58C */  lw         $s5, 0x8($a1)
    /* 2A9F8 8003A1F8 23801302 */  subu       $s0, $s0, $s3
    /* 2A9FC 8003A1FC 23883402 */  subu       $s1, $s1, $s4
    /* 2AA00 8003A200 23905502 */  subu       $s2, $s2, $s5
    /* 2AA04 8003A204 03821000 */  sra        $s0, $s0, 8
    /* 2AA08 8003A208 038A1100 */  sra        $s1, $s1, 8
    /* 2AA0C 8003A20C 03921200 */  sra        $s2, $s2, 8
    /* 2AA10 8003A210 00489048 */  mtc2       $s0, $9 /* handwritten instruction */
    /* 2AA14 8003A214 00509148 */  mtc2       $s1, $10 /* handwritten instruction */
    /* 2AA18 8003A218 00589248 */  mtc2       $s2, $11 /* handwritten instruction */
    /* 2AA1C 8003A21C 00000000 */  nop
    /* 2AA20 8003A220 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2AA24 8003A224 00000000 */  nop
    /* 2AA28 8003A228 00481048 */  mfc2       $s0, $9 /* handwritten instruction */
    /* 2AA2C 8003A22C 00501148 */  mfc2       $s1, $10 /* handwritten instruction */
    /* 2AA30 8003A230 00581248 */  mfc2       $s2, $11 /* handwritten instruction */
    /* 2AA34 8003A234 0028D048 */  ctc2       $s0, $5 /* handwritten instruction */
    /* 2AA38 8003A238 0030D148 */  ctc2       $s1, $6 /* handwritten instruction */
    /* 2AA3C 8003A23C 0038D248 */  ctc2       $s2, $7 /* handwritten instruction */
    /* 2AA40 8003A240 2A085200 */  slt        $at, $v0, $s2
    /* 2AA44 8003A244 35012010 */  beqz       $at, .L8003A71C
    /* 2AA48 8003A248 E02E0134 */   ori       $at, $zero, 0x2EE0
    /* 2AA4C 8003A24C 2A083200 */  slt        $at, $at, $s2
    /* 2AA50 8003A250 32012014 */  bnez       $at, .L8003A71C
    /* 2AA54 8003A254 2A083203 */   slt       $at, $t9, $s2
    /* 2AA58 8003A258 02002013 */  beqz       $t9, .L8003A264
    /* 2AA5C 8003A25C 00000000 */   nop
    /* 2AA60 8003A260 2E012014 */  bnez       $at, .L8003A71C
  .L8003A264:
    /* 2AA64 8003A264 10009E8C */   lw        $fp, 0x10($a0)
    /* 2AA68 8003A268 0C009D8C */  lw         $sp, 0xC($a0)
    /* 2AA6C 8003A26C 1D00C014 */  bnez       $a2, .L8003A2E4
    /* 2AA70 8003A270 14009C8C */   lw        $gp, 0x14($a0)
    /* 2AA74 8003A274 0C00B08C */  lw         $s0, 0xC($a1)
    /* 2AA78 8003A278 1000B18C */  lw         $s1, 0x10($a1)
    /* 2AA7C 8003A27C 1400B28C */  lw         $s2, 0x14($a1)
    /* 2AA80 8003A280 40851000 */  sll        $s0, $s0, 21
    /* 2AA84 8003A284 43851000 */  sra        $s0, $s0, 21
    /* 2AA88 8003A288 408D1100 */  sll        $s1, $s1, 21
    /* 2AA8C 8003A28C 438D1100 */  sra        $s1, $s1, 21
    /* 2AA90 8003A290 00951200 */  sll        $s2, $s2, 20
    /* 2AA94 8003A294 03951200 */  sra        $s2, $s2, 20
    /* 2AA98 8003A298 23981000 */  negu       $s3, $s0
    /* 2AA9C 8003A29C 56FF012A */  slti       $at, $s0, -0xAA
    /* 2AAA0 8003A2A0 05002014 */  bnez       $at, .L8003A2B8
    /* 2AAA4 8003A2A4 AA000134 */   ori       $at, $zero, 0xAA
    /* 2AAA8 8003A2A8 56FF612A */  slti       $at, $s3, -0xAA
    /* 2AAAC 8003A2AC 02002014 */  bnez       $at, .L8003A2B8
    /* 2AAB0 8003A2B0 56FF0120 */   addi      $at, $zero, -0xAA /* handwritten instruction */
    /* 2AAB4 8003A2B4 21086002 */  addu       $at, $s3, $zero
  .L8003A2B8:
    /* 2AAB8 8003A2B8 21E83D00 */  addu       $sp, $at, $sp
    /* 2AABC 8003A2BC 23981100 */  negu       $s3, $s1
    /* 2AAC0 8003A2C0 56FF212A */  slti       $at, $s1, -0xAA
    /* 2AAC4 8003A2C4 05002014 */  bnez       $at, .L8003A2DC
    /* 2AAC8 8003A2C8 AA000134 */   ori       $at, $zero, 0xAA
    /* 2AACC 8003A2CC 56FF612A */  slti       $at, $s3, -0xAA
    /* 2AAD0 8003A2D0 02002014 */  bnez       $at, .L8003A2DC
    /* 2AAD4 8003A2D4 56FF0120 */   addi      $at, $zero, -0xAA /* handwritten instruction */
    /* 2AAD8 8003A2D8 21086002 */  addu       $at, $s3, $zero
  .L8003A2DC:
    /* 2AADC 8003A2DC 21F03E00 */  addu       $fp, $at, $fp
    /* 2AAE0 8003A2E0 23E09203 */  subu       $gp, $gp, $s2
  .L8003A2E4:
    /* 2AAE4 8003A2E4 FF0FDE33 */  andi       $fp, $fp, 0xFFF
    /* 2AAE8 8003A2E8 FF0FBD33 */  andi       $sp, $sp, 0xFFF
    /* 2AAEC 8003A2EC FF0F9C33 */  andi       $gp, $gp, 0xFFF
    /* 2AAF0 8003A2F0 0580033C */  lui        $v1, %hi(D_8005306C)
    /* 2AAF4 8003A2F4 6C306324 */  addiu      $v1, $v1, %lo(D_8005306C)
    /* 2AAF8 8003A2F8 00088E2B */  slti       $t6, $gp, 0x800
    /* 2AAFC 8003A2FC 0B00C011 */  beqz       $t6, .L8003A32C
    /* 2AB00 8003A300 00048E2B */   slti      $t6, $gp, 0x400
    /* 2AB04 8003A304 0500C011 */  beqz       $t6, .L8003A31C
    /* 2AB08 8003A308 40701C00 */   sll       $t6, $gp, 1
    /* 2AB0C 8003A30C 21706E00 */  addu       $t6, $v1, $t6
    /* 2AB10 8003A310 11000104 */  bgez       $zero, .L8003A358
    /* 2AB14 8003A314 0000CE85 */   lh        $t6, 0x0($t6)
    /* 2AB18 8003A318 00000000 */  nop
  .L8003A31C:
    /* 2AB1C 8003A31C 23706E00 */  subu       $t6, $v1, $t6
    /* 2AB20 8003A320 0D000104 */  bgez       $zero, .L8003A358
    /* 2AB24 8003A324 0010CE85 */   lh        $t6, 0x1000($t6)
    /* 2AB28 8003A328 00000000 */  nop
  .L8003A32C:
    /* 2AB2C 8003A32C 000C8E2B */  slti       $t6, $gp, 0xC00
    /* 2AB30 8003A330 0500C011 */  beqz       $t6, .L8003A348
    /* 2AB34 8003A334 40701C00 */   sll       $t6, $gp, 1
    /* 2AB38 8003A338 21706E00 */  addu       $t6, $v1, $t6
    /* 2AB3C 8003A33C 00F0CE85 */  lh         $t6, -0x1000($t6)
    /* 2AB40 8003A340 05000104 */  bgez       $zero, .L8003A358
    /* 2AB44 8003A344 23700E00 */   negu      $t6, $t6
  .L8003A348:
    /* 2AB48 8003A348 23706E00 */  subu       $t6, $v1, $t6
    /* 2AB4C 8003A34C 0020CE85 */  lh         $t6, 0x2000($t6)
    /* 2AB50 8003A350 01000104 */  bgez       $zero, .L8003A358
    /* 2AB54 8003A354 23700E00 */   negu      $t6, $t6
  .L8003A358:
    /* 2AB58 8003A358 0008AD2B */  slti       $t5, $sp, 0x800
    /* 2AB5C 8003A35C 0B00A011 */  beqz       $t5, .L8003A38C
    /* 2AB60 8003A360 0004AD2B */   slti      $t5, $sp, 0x400
    /* 2AB64 8003A364 0500A011 */  beqz       $t5, .L8003A37C
    /* 2AB68 8003A368 40681D00 */   sll       $t5, $sp, 1
    /* 2AB6C 8003A36C 21686D00 */  addu       $t5, $v1, $t5
    /* 2AB70 8003A370 11000104 */  bgez       $zero, .L8003A3B8
    /* 2AB74 8003A374 0000AD85 */   lh        $t5, 0x0($t5)
    /* 2AB78 8003A378 00000000 */  nop
  .L8003A37C:
    /* 2AB7C 8003A37C 23686D00 */  subu       $t5, $v1, $t5
    /* 2AB80 8003A380 0D000104 */  bgez       $zero, .L8003A3B8
    /* 2AB84 8003A384 0010AD85 */   lh        $t5, 0x1000($t5)
    /* 2AB88 8003A388 00000000 */  nop
  .L8003A38C:
    /* 2AB8C 8003A38C 000CAD2B */  slti       $t5, $sp, 0xC00
    /* 2AB90 8003A390 0500A011 */  beqz       $t5, .L8003A3A8
    /* 2AB94 8003A394 40681D00 */   sll       $t5, $sp, 1
    /* 2AB98 8003A398 21686D00 */  addu       $t5, $v1, $t5
    /* 2AB9C 8003A39C 00F0AD85 */  lh         $t5, -0x1000($t5)
    /* 2ABA0 8003A3A0 05000104 */  bgez       $zero, .L8003A3B8
    /* 2ABA4 8003A3A4 23680D00 */   negu      $t5, $t5
  .L8003A3A8:
    /* 2ABA8 8003A3A8 23686D00 */  subu       $t5, $v1, $t5
    /* 2ABAC 8003A3AC 0020AD85 */  lh         $t5, 0x2000($t5)
    /* 2ABB0 8003A3B0 01000104 */  bgez       $zero, .L8003A3B8
    /* 2ABB4 8003A3B4 23680D00 */   negu      $t5, $t5
  .L8003A3B8:
    /* 2ABB8 8003A3B8 0008CF2B */  slti       $t7, $fp, 0x800
    /* 2ABBC 8003A3BC 0B00E011 */  beqz       $t7, .L8003A3EC
    /* 2ABC0 8003A3C0 0004CF2B */   slti      $t7, $fp, 0x400
    /* 2ABC4 8003A3C4 0500E011 */  beqz       $t7, .L8003A3DC
    /* 2ABC8 8003A3C8 40781E00 */   sll       $t7, $fp, 1
    /* 2ABCC 8003A3CC 21786F00 */  addu       $t7, $v1, $t7
    /* 2ABD0 8003A3D0 11000104 */  bgez       $zero, .L8003A418
    /* 2ABD4 8003A3D4 0000EF85 */   lh        $t7, 0x0($t7)
    /* 2ABD8 8003A3D8 00000000 */  nop
  .L8003A3DC:
    /* 2ABDC 8003A3DC 23786F00 */  subu       $t7, $v1, $t7
    /* 2ABE0 8003A3E0 0D000104 */  bgez       $zero, .L8003A418
    /* 2ABE4 8003A3E4 0010EF85 */   lh        $t7, 0x1000($t7)
    /* 2ABE8 8003A3E8 00000000 */  nop
  .L8003A3EC:
    /* 2ABEC 8003A3EC 000CCF2B */  slti       $t7, $fp, 0xC00
    /* 2ABF0 8003A3F0 0500E011 */  beqz       $t7, .L8003A408
    /* 2ABF4 8003A3F4 40781E00 */   sll       $t7, $fp, 1
    /* 2ABF8 8003A3F8 21786F00 */  addu       $t7, $v1, $t7
    /* 2ABFC 8003A3FC 00F0EF85 */  lh         $t7, -0x1000($t7)
    /* 2AC00 8003A400 05000104 */  bgez       $zero, .L8003A418
    /* 2AC04 8003A404 23780F00 */   negu      $t7, $t7
  .L8003A408:
    /* 2AC08 8003A408 23786F00 */  subu       $t7, $v1, $t7
    /* 2AC0C 8003A40C 0020EF85 */  lh         $t7, 0x2000($t7)
    /* 2AC10 8003A410 01000104 */  bgez       $zero, .L8003A418
    /* 2AC14 8003A414 23780F00 */   negu      $t7, $t7
  .L8003A418:
    /* 2AC18 8003A418 0008882B */  slti       $t0, $gp, 0x800
    /* 2AC1C 8003A41C 0B000011 */  beqz       $t0, .L8003A44C
    /* 2AC20 8003A420 0004882B */   slti      $t0, $gp, 0x400
    /* 2AC24 8003A424 05000011 */  beqz       $t0, .L8003A43C
    /* 2AC28 8003A428 40401C00 */   sll       $t0, $gp, 1
    /* 2AC2C 8003A42C 23406800 */  subu       $t0, $v1, $t0
    /* 2AC30 8003A430 0F000104 */  bgez       $zero, .L8003A470
    /* 2AC34 8003A434 00080885 */   lh        $t0, 0x800($t0)
    /* 2AC38 8003A438 00000000 */  nop
  .L8003A43C:
    /* 2AC3C 8003A43C 21406800 */  addu       $t0, $v1, $t0
    /* 2AC40 8003A440 00F80885 */  lh         $t0, -0x800($t0)
    /* 2AC44 8003A444 0A000104 */  bgez       $zero, .L8003A470
    /* 2AC48 8003A448 23400800 */   negu      $t0, $t0
  .L8003A44C:
    /* 2AC4C 8003A44C 000C882B */  slti       $t0, $gp, 0xC00
    /* 2AC50 8003A450 05000011 */  beqz       $t0, .L8003A468
    /* 2AC54 8003A454 40401C00 */   sll       $t0, $gp, 1
    /* 2AC58 8003A458 23406800 */  subu       $t0, $v1, $t0
    /* 2AC5C 8003A45C 00180885 */  lh         $t0, 0x1800($t0)
    /* 2AC60 8003A460 03000104 */  bgez       $zero, .L8003A470
    /* 2AC64 8003A464 23400800 */   negu      $t0, $t0
  .L8003A468:
    /* 2AC68 8003A468 21406800 */  addu       $t0, $v1, $t0
    /* 2AC6C 8003A46C 00E80885 */  lh         $t0, -0x1800($t0)
  .L8003A470:
    /* 2AC70 8003A470 0008A92B */  slti       $t1, $sp, 0x800
    /* 2AC74 8003A474 0B002011 */  beqz       $t1, .L8003A4A4
    /* 2AC78 8003A478 0004A92B */   slti      $t1, $sp, 0x400
    /* 2AC7C 8003A47C 05002011 */  beqz       $t1, .L8003A494
    /* 2AC80 8003A480 40481D00 */   sll       $t1, $sp, 1
    /* 2AC84 8003A484 23486900 */  subu       $t1, $v1, $t1
    /* 2AC88 8003A488 0F000104 */  bgez       $zero, .L8003A4C8
    /* 2AC8C 8003A48C 00082985 */   lh        $t1, 0x800($t1)
    /* 2AC90 8003A490 00000000 */  nop
  .L8003A494:
    /* 2AC94 8003A494 21486900 */  addu       $t1, $v1, $t1
    /* 2AC98 8003A498 00F82985 */  lh         $t1, -0x800($t1)
    /* 2AC9C 8003A49C 0A000104 */  bgez       $zero, .L8003A4C8
    /* 2ACA0 8003A4A0 23480900 */   negu      $t1, $t1
  .L8003A4A4:
    /* 2ACA4 8003A4A4 000CA92B */  slti       $t1, $sp, 0xC00
    /* 2ACA8 8003A4A8 05002011 */  beqz       $t1, .L8003A4C0
    /* 2ACAC 8003A4AC 40481D00 */   sll       $t1, $sp, 1
    /* 2ACB0 8003A4B0 23486900 */  subu       $t1, $v1, $t1
    /* 2ACB4 8003A4B4 00182985 */  lh         $t1, 0x1800($t1)
    /* 2ACB8 8003A4B8 03000104 */  bgez       $zero, .L8003A4C8
    /* 2ACBC 8003A4BC 23480900 */   negu      $t1, $t1
  .L8003A4C0:
    /* 2ACC0 8003A4C0 21486900 */  addu       $t1, $v1, $t1
    /* 2ACC4 8003A4C4 00E82985 */  lh         $t1, -0x1800($t1)
  .L8003A4C8:
    /* 2ACC8 8003A4C8 0008CB2B */  slti       $t3, $fp, 0x800
    /* 2ACCC 8003A4CC 0B006011 */  beqz       $t3, .L8003A4FC
    /* 2ACD0 8003A4D0 0004CB2B */   slti      $t3, $fp, 0x400
    /* 2ACD4 8003A4D4 05006011 */  beqz       $t3, .L8003A4EC
    /* 2ACD8 8003A4D8 40581E00 */   sll       $t3, $fp, 1
    /* 2ACDC 8003A4DC 23586B00 */  subu       $t3, $v1, $t3
    /* 2ACE0 8003A4E0 0F000104 */  bgez       $zero, .L8003A520
    /* 2ACE4 8003A4E4 00086B85 */   lh        $t3, 0x800($t3)
    /* 2ACE8 8003A4E8 00000000 */  nop
  .L8003A4EC:
    /* 2ACEC 8003A4EC 21586B00 */  addu       $t3, $v1, $t3
    /* 2ACF0 8003A4F0 00F86B85 */  lh         $t3, -0x800($t3)
    /* 2ACF4 8003A4F4 0A000104 */  bgez       $zero, .L8003A520
    /* 2ACF8 8003A4F8 23580B00 */   negu      $t3, $t3
  .L8003A4FC:
    /* 2ACFC 8003A4FC 000CCB2B */  slti       $t3, $fp, 0xC00
    /* 2AD00 8003A500 05006011 */  beqz       $t3, .L8003A518
    /* 2AD04 8003A504 40581E00 */   sll       $t3, $fp, 1
    /* 2AD08 8003A508 23586B00 */  subu       $t3, $v1, $t3
    /* 2AD0C 8003A50C 00186B85 */  lh         $t3, 0x1800($t3)
    /* 2AD10 8003A510 03000104 */  bgez       $zero, .L8003A520
    /* 2AD14 8003A514 23580B00 */   negu      $t3, $t3
  .L8003A518:
    /* 2AD18 8003A518 21586B00 */  addu       $t3, $v1, $t3
    /* 2AD1C 8003A51C 00E86B85 */  lh         $t3, -0x1800($t3)
  .L8003A520:
    /* 2AD20 8003A520 1800AF01 */  mult       $t5, $t7
    /* 2AD24 8003A524 FFFFCC31 */  andi       $t4, $t6, 0xFFFF
    /* 2AD28 8003A528 FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 2AD2C 8003A52C FFFFEF31 */  andi       $t7, $t7, 0xFFFF
    /* 2AD30 8003A530 FFFF0831 */  andi       $t0, $t0, 0xFFFF
    /* 2AD34 8003A534 FFFF2A31 */  andi       $t2, $t1, 0xFFFF
    /* 2AD38 8003A538 FFFF6B31 */  andi       $t3, $t3, 0xFFFF
    /* 2AD3C 8003A53C 0008C048 */  ctc2       $zero, $1 /* handwritten instruction */
    /* 2AD40 8003A540 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 2AD44 8003A544 00088848 */  mtc2       $t0, $1 /* handwritten instruction */
    /* 2AD48 8003A548 000C0B00 */  sll        $at, $t3, 16
    /* 2AD4C 8003A54C 25082F00 */  or         $at, $at, $t7
    /* 2AD50 8003A550 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 2AD54 8003A554 12E00000 */  mflo       $gp
    /* 2AD58 8003A558 0000C048 */  ctc2       $zero, $0 /* handwritten instruction */
    /* 2AD5C 8003A55C 0010CD48 */  ctc2       $t5, $2 /* handwritten instruction */
    /* 2AD60 8003A560 0020CA48 */  ctc2       $t2, $4 /* handwritten instruction */
    /* 2AD64 8003A564 1800C901 */  mult       $t6, $t1
    /* 2AD68 8003A568 03E31C00 */  sra        $gp, $gp, 12
    /* 2AD6C 8003A56C 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 2AD70 8003A570 0000C848 */  ctc2       $t0, $0 /* handwritten instruction */
    /* 2AD74 8003A574 0010C848 */  ctc2       $t0, $2 /* handwritten instruction */
    /* 2AD78 8003A578 FFFF8133 */  andi       $at, $gp, 0xFFFF
    /* 2AD7C 8003A57C 0020C148 */  ctc2       $at, $4 /* handwritten instruction */
    /* 2AD80 8003A580 12B80000 */  mflo       $s7
    /* 2AD84 8003A584 00501D48 */  mfc2       $sp, $10 /* handwritten instruction */
    /* 2AD88 8003A588 00581048 */  mfc2       $s0, $11 /* handwritten instruction */
    /* 2AD8C 8003A58C 1800DC01 */  mult       $t6, $gp
    /* 2AD90 8003A590 03BB1700 */  sra        $s7, $s7, 12
    /* 2AD94 8003A594 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 2AD98 8003A598 0000CC48 */  ctc2       $t4, $0 /* handwritten instruction */
    /* 2AD9C 8003A59C 0010CC48 */  ctc2       $t4, $2 /* handwritten instruction */
    /* 2ADA0 8003A5A0 FFFFA133 */  andi       $at, $sp, 0xFFFF
    /* 2ADA4 8003A5A4 0020C148 */  ctc2       $at, $4 /* handwritten instruction */
    /* 2ADA8 8003A5A8 12C00000 */  mflo       $t8
    /* 2ADAC 8003A5AC 00481148 */  mfc2       $s1, $9 /* handwritten instruction */
    /* 2ADB0 8003A5B0 00501248 */  mfc2       $s2, $10 /* handwritten instruction */
    /* 2ADB4 8003A5B4 00581348 */  mfc2       $s3, $11 /* handwritten instruction */
    /* 2ADB8 8003A5B8 18009D01 */  mult       $t4, $sp
    /* 2ADBC 8003A5BC 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 2ADC0 8003A5C0 03C31800 */  sra        $t8, $t8, 12
    /* 2ADC4 8003A5C4 00481448 */  mfc2       $s4, $9 /* handwritten instruction */
    /* 2ADC8 8003A5C8 00501548 */  mfc2       $s5, $10 /* handwritten instruction */
    /* 2ADCC 8003A5CC 00581648 */  mfc2       $s6, $11 /* handwritten instruction */
    /* 2ADD0 8003A5D0 12080000 */  mflo       $at
    /* 2ADD4 8003A5D4 030B0100 */  sra        $at, $at, 12
    /* 2ADD8 8003A5D8 23905802 */  subu       $s2, $s2, $t8
    /* 2ADDC 8003A5DC 23B81700 */  negu       $s7, $s7
    /* 2ADE0 8003A5E0 21882102 */  addu       $s1, $s1, $at
    /* 2ADE4 8003A5E4 2198B302 */  addu       $s3, $s5, $s3
    /* 2ADE8 8003A5E8 23A09602 */  subu       $s4, $s4, $s6
    /* 2ADEC 8003A5EC 18008A8C */  lw         $t2, 0x18($a0)
    /* 2ADF0 8003A5F0 1C008B8C */  lw         $t3, 0x1C($a0)
    /* 2ADF4 8003A5F4 20008C8C */  lw         $t4, 0x20($a0)
    /* 2ADF8 8003A5F8 0750EA00 */  srav       $t2, $t2, $a3
    /* 2ADFC 8003A5FC 0758EB00 */  srav       $t3, $t3, $a3
    /* 2AE00 8003A600 0760EC00 */  srav       $t4, $t4, $a3
    /* 2AE04 8003A604 0000CA48 */  ctc2       $t2, $0 /* handwritten instruction */
    /* 2AE08 8003A608 0008C048 */  ctc2       $zero, $1 /* handwritten instruction */
    /* 2AE0C 8003A60C 0010CB48 */  ctc2       $t3, $2 /* handwritten instruction */
    /* 2AE10 8003A610 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 2AE14 8003A614 0020CC48 */  ctc2       $t4, $4 /* handwritten instruction */
    /* 2AE18 8003A618 00489348 */  mtc2       $s3, $9 /* handwritten instruction */
    /* 2AE1C 8003A61C 00509048 */  mtc2       $s0, $10 /* handwritten instruction */
    /* 2AE20 8003A620 00589448 */  mtc2       $s4, $11 /* handwritten instruction */
    /* 2AE24 8003A624 00000000 */  nop
    /* 2AE28 8003A628 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2AE2C 8003A62C 00000000 */  nop
    /* 2AE30 8003A630 00481348 */  mfc2       $s3, $9 /* handwritten instruction */
    /* 2AE34 8003A634 00501048 */  mfc2       $s0, $10 /* handwritten instruction */
    /* 2AE38 8003A638 00581448 */  mfc2       $s4, $11 /* handwritten instruction */
    /* 2AE3C 8003A63C 00489248 */  mtc2       $s2, $9 /* handwritten instruction */
    /* 2AE40 8003A640 00509748 */  mtc2       $s7, $10 /* handwritten instruction */
    /* 2AE44 8003A644 00589148 */  mtc2       $s1, $11 /* handwritten instruction */
    /* 2AE48 8003A648 21406002 */  addu       $t0, $s3, $zero
    /* 2AE4C 8003A64C 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 2AE50 8003A650 21480002 */  addu       $t1, $s0, $zero
    /* 2AE54 8003A654 00481248 */  mfc2       $s2, $9 /* handwritten instruction */
    /* 2AE58 8003A658 00501748 */  mfc2       $s7, $10 /* handwritten instruction */
    /* 2AE5C 8003A65C 00581148 */  mfc2       $s1, $11 /* handwritten instruction */
    /* 2AE60 8003A660 21508002 */  addu       $t2, $s4, $zero
    /* 2AE64 8003A664 80981300 */  sll        $s3, $s3, 2
    /* 2AE68 8003A668 21986802 */  addu       $s3, $s3, $t0
    /* 2AE6C 8003A66C C3981300 */  sra        $s3, $s3, 3
    /* 2AE70 8003A670 23981300 */  negu       $s3, $s3
    /* 2AE74 8003A674 80801000 */  sll        $s0, $s0, 2
    /* 2AE78 8003A678 21800902 */  addu       $s0, $s0, $t1
    /* 2AE7C 8003A67C C3801000 */  sra        $s0, $s0, 3
    /* 2AE80 8003A680 23801000 */  negu       $s0, $s0
    /* 2AE84 8003A684 80A01400 */  sll        $s4, $s4, 2
    /* 2AE88 8003A688 21A08A02 */  addu       $s4, $s4, $t2
    /* 2AE8C 8003A68C C3A01400 */  sra        $s4, $s4, 3
    /* 2AE90 8003A690 23A01400 */  negu       $s4, $s4
    /* 2AE94 8003A694 FFFF4132 */  andi       $at, $s2, 0xFFFF
    /* 2AE98 8003A698 00441700 */  sll        $t0, $s7, 16
    /* 2AE9C 8003A69C 25400101 */  or         $t0, $t0, $at
    /* 2AEA0 8003A6A0 FFFF2132 */  andi       $at, $s1, 0xFFFF
    /* 2AEA4 8003A6A4 004C1300 */  sll        $t1, $s3, 16
    /* 2AEA8 8003A6A8 25482101 */  or         $t1, $t1, $at
    /* 2AEAC 8003A6AC FFFF0132 */  andi       $at, $s0, 0xFFFF
    /* 2AEB0 8003A6B0 00541400 */  sll        $t2, $s4, 16
    /* 2AEB4 8003A6B4 25504101 */  or         $t2, $t2, $at
    /* 2AEB8 8003A6B8 0000C848 */  ctc2       $t0, $0 /* handwritten instruction */
    /* 2AEBC 8003A6BC 0008C948 */  ctc2       $t1, $1 /* handwritten instruction */
    /* 2AEC0 8003A6C0 0010CA48 */  ctc2       $t2, $2 /* handwritten instruction */
    /* 2AEC4 8003A6C4 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 2AEC8 8003A6C8 0020C048 */  ctc2       $zero, $4 /* handwritten instruction */
    /* 2AECC 8003A6CC 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 2AED0 8003A6D0 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2AED4 8003A6D4 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2AED8 8003A6D8 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2AEDC 8003A6DC 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2AEE0 8003A6E0 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2AEE4 8003A6E4 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2AEE8 8003A6E8 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2AEEC 8003A6EC 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2AEF0 8003A6F0 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2AEF4 8003A6F4 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2AEF8 8003A6F8 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2AEFC 8003A6FC 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2AF00 8003A700 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2AF04 8003A704 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2AF08 8003A708 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2AF0C 8003A70C 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2AF10 8003A710 01000224 */  addiu      $v0, $zero, 0x1
    /* 2AF14 8003A714 0800E003 */  jr         $ra
    /* 2AF18 8003A718 00000000 */   nop
  .L8003A71C:
    /* 2AF1C 8003A71C 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 2AF20 8003A720 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2AF24 8003A724 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2AF28 8003A728 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2AF2C 8003A72C 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2AF30 8003A730 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2AF34 8003A734 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2AF38 8003A738 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2AF3C 8003A73C 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2AF40 8003A740 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2AF44 8003A744 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2AF48 8003A748 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2AF4C 8003A74C 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2AF50 8003A750 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2AF54 8003A754 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2AF58 8003A758 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2AF5C 8003A75C 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2AF60 8003A760 21100000 */  addu       $v0, $zero, $zero
    /* 2AF64 8003A764 0800E003 */  jr         $ra
    /* 2AF68 8003A768 00000000 */   nop
endlabel func_8003A144
