.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RCalcObjectRotMatrix
    /* 2993C 8003913C 801F013C */  lui        $at, (0x1F80003C >> 16)
    /* 29940 80039140 000030AC */  sw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 29944 80039144 040031AC */  sw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 29948 80039148 080032AC */  sw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2994C 8003914C 0C0033AC */  sw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 29950 80039150 100034AC */  sw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 29954 80039154 140035AC */  sw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 29958 80039158 180036AC */  sw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2995C 8003915C 1C0037AC */  sw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 29960 80039160 200038AC */  sw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 29964 80039164 240039AC */  sw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 29968 80039168 28003AAC */  sw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2996C 8003916C 2C003BAC */  sw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 29970 80039170 30003CAC */  sw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 29974 80039174 34003DAC */  sw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 29978 80039178 38003EAC */  sw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2997C 8003917C 3C003FAC */  sw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 29980 80039180 0580033C */  lui        $v1, %hi(D_8005306C)
    /* 29984 80039184 6C306324 */  addiu      $v1, $v1, %lo(D_8005306C)
    /* 29988 80039188 1400DC8C */  lw         $gp, 0x14($a2)
    /* 2998C 8003918C 1000DE8C */  lw         $fp, 0x10($a2)
    /* 29990 80039190 0C00DD8C */  lw         $sp, 0xC($a2)
    /* 29994 80039194 23F09E03 */  subu       $fp, $gp, $fp
    /* 29998 80039198 23F01E00 */  negu       $fp, $fp
    /* 2999C 8003919C FF0F9C33 */  andi       $gp, $gp, 0xFFF
    /* 299A0 800391A0 FF0FBD33 */  andi       $sp, $sp, 0xFFF
    /* 299A4 800391A4 FF0FDE33 */  andi       $fp, $fp, 0xFFF
    /* 299A8 800391A8 00088D2B */  slti       $t5, $gp, 0x800
    /* 299AC 800391AC 0B00A011 */  beqz       $t5, .L800391DC
    /* 299B0 800391B0 00048D2B */   slti      $t5, $gp, 0x400
    /* 299B4 800391B4 0500A011 */  beqz       $t5, .L800391CC
    /* 299B8 800391B8 40681C00 */   sll       $t5, $gp, 1
    /* 299BC 800391BC 21686D00 */  addu       $t5, $v1, $t5
    /* 299C0 800391C0 11000104 */  bgez       $zero, .L80039208
    /* 299C4 800391C4 0000AD85 */   lh        $t5, 0x0($t5)
    /* 299C8 800391C8 00000000 */  nop
  .L800391CC:
    /* 299CC 800391CC 23686D00 */  subu       $t5, $v1, $t5
    /* 299D0 800391D0 0D000104 */  bgez       $zero, .L80039208
    /* 299D4 800391D4 0010AD85 */   lh        $t5, 0x1000($t5)
    /* 299D8 800391D8 00000000 */  nop
  .L800391DC:
    /* 299DC 800391DC 000C8D2B */  slti       $t5, $gp, 0xC00
    /* 299E0 800391E0 0500A011 */  beqz       $t5, .L800391F8
    /* 299E4 800391E4 40681C00 */   sll       $t5, $gp, 1
    /* 299E8 800391E8 21686D00 */  addu       $t5, $v1, $t5
    /* 299EC 800391EC 00F0AD85 */  lh         $t5, -0x1000($t5)
    /* 299F0 800391F0 05000104 */  bgez       $zero, .L80039208
    /* 299F4 800391F4 23680D00 */   negu      $t5, $t5
  .L800391F8:
    /* 299F8 800391F8 23686D00 */  subu       $t5, $v1, $t5
    /* 299FC 800391FC 0020AD85 */  lh         $t5, 0x2000($t5)
    /* 29A00 80039200 01000104 */  bgez       $zero, .L80039208
    /* 29A04 80039204 23680D00 */   negu      $t5, $t5
  .L80039208:
    /* 29A08 80039208 0008AE2B */  slti       $t6, $sp, 0x800
    /* 29A0C 8003920C 0B00C011 */  beqz       $t6, .L8003923C
    /* 29A10 80039210 0004AE2B */   slti      $t6, $sp, 0x400
    /* 29A14 80039214 0500C011 */  beqz       $t6, .L8003922C
    /* 29A18 80039218 40701D00 */   sll       $t6, $sp, 1
    /* 29A1C 8003921C 21706E00 */  addu       $t6, $v1, $t6
    /* 29A20 80039220 11000104 */  bgez       $zero, .L80039268
    /* 29A24 80039224 0000CE85 */   lh        $t6, 0x0($t6)
    /* 29A28 80039228 00000000 */  nop
  .L8003922C:
    /* 29A2C 8003922C 23706E00 */  subu       $t6, $v1, $t6
    /* 29A30 80039230 0D000104 */  bgez       $zero, .L80039268
    /* 29A34 80039234 0010CE85 */   lh        $t6, 0x1000($t6)
    /* 29A38 80039238 00000000 */  nop
  .L8003923C:
    /* 29A3C 8003923C 000CAE2B */  slti       $t6, $sp, 0xC00
    /* 29A40 80039240 0500C011 */  beqz       $t6, .L80039258
    /* 29A44 80039244 40701D00 */   sll       $t6, $sp, 1
    /* 29A48 80039248 21706E00 */  addu       $t6, $v1, $t6
    /* 29A4C 8003924C 00F0CE85 */  lh         $t6, -0x1000($t6)
    /* 29A50 80039250 05000104 */  bgez       $zero, .L80039268
    /* 29A54 80039254 23700E00 */   negu      $t6, $t6
  .L80039258:
    /* 29A58 80039258 23706E00 */  subu       $t6, $v1, $t6
    /* 29A5C 8003925C 0020CE85 */  lh         $t6, 0x2000($t6)
    /* 29A60 80039260 01000104 */  bgez       $zero, .L80039268
    /* 29A64 80039264 23700E00 */   negu      $t6, $t6
  .L80039268:
    /* 29A68 80039268 0008CF2B */  slti       $t7, $fp, 0x800
    /* 29A6C 8003926C 0B00E011 */  beqz       $t7, .L8003929C
    /* 29A70 80039270 0004CF2B */   slti      $t7, $fp, 0x400
    /* 29A74 80039274 0500E011 */  beqz       $t7, .L8003928C
    /* 29A78 80039278 40781E00 */   sll       $t7, $fp, 1
    /* 29A7C 8003927C 21786F00 */  addu       $t7, $v1, $t7
    /* 29A80 80039280 11000104 */  bgez       $zero, .L800392C8
    /* 29A84 80039284 0000EF85 */   lh        $t7, 0x0($t7)
    /* 29A88 80039288 00000000 */  nop
  .L8003928C:
    /* 29A8C 8003928C 23786F00 */  subu       $t7, $v1, $t7
    /* 29A90 80039290 0D000104 */  bgez       $zero, .L800392C8
    /* 29A94 80039294 0010EF85 */   lh        $t7, 0x1000($t7)
    /* 29A98 80039298 00000000 */  nop
  .L8003929C:
    /* 29A9C 8003929C 000CCF2B */  slti       $t7, $fp, 0xC00
    /* 29AA0 800392A0 0500E011 */  beqz       $t7, .L800392B8
    /* 29AA4 800392A4 40781E00 */   sll       $t7, $fp, 1
    /* 29AA8 800392A8 21786F00 */  addu       $t7, $v1, $t7
    /* 29AAC 800392AC 00F0EF85 */  lh         $t7, -0x1000($t7)
    /* 29AB0 800392B0 05000104 */  bgez       $zero, .L800392C8
    /* 29AB4 800392B4 23780F00 */   negu      $t7, $t7
  .L800392B8:
    /* 29AB8 800392B8 23786F00 */  subu       $t7, $v1, $t7
    /* 29ABC 800392BC 0020EF85 */  lh         $t7, 0x2000($t7)
    /* 29AC0 800392C0 01000104 */  bgez       $zero, .L800392C8
    /* 29AC4 800392C4 23780F00 */   negu      $t7, $t7
  .L800392C8:
    /* 29AC8 800392C8 0008892B */  slti       $t1, $gp, 0x800
    /* 29ACC 800392CC 0B002011 */  beqz       $t1, .L800392FC
    /* 29AD0 800392D0 0004892B */   slti      $t1, $gp, 0x400
    /* 29AD4 800392D4 05002011 */  beqz       $t1, .L800392EC
    /* 29AD8 800392D8 40481C00 */   sll       $t1, $gp, 1
    /* 29ADC 800392DC 23486900 */  subu       $t1, $v1, $t1
    /* 29AE0 800392E0 0F000104 */  bgez       $zero, .L80039320
    /* 29AE4 800392E4 00082985 */   lh        $t1, 0x800($t1)
    /* 29AE8 800392E8 00000000 */  nop
  .L800392EC:
    /* 29AEC 800392EC 21486900 */  addu       $t1, $v1, $t1
    /* 29AF0 800392F0 00F82985 */  lh         $t1, -0x800($t1)
    /* 29AF4 800392F4 0A000104 */  bgez       $zero, .L80039320
    /* 29AF8 800392F8 23480900 */   negu      $t1, $t1
  .L800392FC:
    /* 29AFC 800392FC 000C892B */  slti       $t1, $gp, 0xC00
    /* 29B00 80039300 05002011 */  beqz       $t1, .L80039318
    /* 29B04 80039304 40481C00 */   sll       $t1, $gp, 1
    /* 29B08 80039308 23486900 */  subu       $t1, $v1, $t1
    /* 29B0C 8003930C 00182985 */  lh         $t1, 0x1800($t1)
    /* 29B10 80039310 03000104 */  bgez       $zero, .L80039320
    /* 29B14 80039314 23480900 */   negu      $t1, $t1
  .L80039318:
    /* 29B18 80039318 21486900 */  addu       $t1, $v1, $t1
    /* 29B1C 8003931C 00E82985 */  lh         $t1, -0x1800($t1)
  .L80039320:
    /* 29B20 80039320 0008AA2B */  slti       $t2, $sp, 0x800
    /* 29B24 80039324 0B004011 */  beqz       $t2, .L80039354
    /* 29B28 80039328 0004AA2B */   slti      $t2, $sp, 0x400
    /* 29B2C 8003932C 05004011 */  beqz       $t2, .L80039344
    /* 29B30 80039330 40501D00 */   sll       $t2, $sp, 1
    /* 29B34 80039334 23506A00 */  subu       $t2, $v1, $t2
    /* 29B38 80039338 0F000104 */  bgez       $zero, .L80039378
    /* 29B3C 8003933C 00084A85 */   lh        $t2, 0x800($t2)
    /* 29B40 80039340 00000000 */  nop
  .L80039344:
    /* 29B44 80039344 21506A00 */  addu       $t2, $v1, $t2
    /* 29B48 80039348 00F84A85 */  lh         $t2, -0x800($t2)
    /* 29B4C 8003934C 0A000104 */  bgez       $zero, .L80039378
    /* 29B50 80039350 23500A00 */   negu      $t2, $t2
  .L80039354:
    /* 29B54 80039354 000CAA2B */  slti       $t2, $sp, 0xC00
    /* 29B58 80039358 05004011 */  beqz       $t2, .L80039370
    /* 29B5C 8003935C 40501D00 */   sll       $t2, $sp, 1
    /* 29B60 80039360 23506A00 */  subu       $t2, $v1, $t2
    /* 29B64 80039364 00184A85 */  lh         $t2, 0x1800($t2)
    /* 29B68 80039368 03000104 */  bgez       $zero, .L80039378
    /* 29B6C 8003936C 23500A00 */   negu      $t2, $t2
  .L80039370:
    /* 29B70 80039370 21506A00 */  addu       $t2, $v1, $t2
    /* 29B74 80039374 00E84A85 */  lh         $t2, -0x1800($t2)
  .L80039378:
    /* 29B78 80039378 0008CC2B */  slti       $t4, $fp, 0x800
    /* 29B7C 8003937C 0B008011 */  beqz       $t4, .L800393AC
    /* 29B80 80039380 0004CC2B */   slti      $t4, $fp, 0x400
    /* 29B84 80039384 05008011 */  beqz       $t4, .L8003939C
    /* 29B88 80039388 40601E00 */   sll       $t4, $fp, 1
    /* 29B8C 8003938C 23606C00 */  subu       $t4, $v1, $t4
    /* 29B90 80039390 0F000104 */  bgez       $zero, .L800393D0
    /* 29B94 80039394 00088C85 */   lh        $t4, 0x800($t4)
    /* 29B98 80039398 00000000 */  nop
  .L8003939C:
    /* 29B9C 8003939C 21606C00 */  addu       $t4, $v1, $t4
    /* 29BA0 800393A0 00F88C85 */  lh         $t4, -0x800($t4)
    /* 29BA4 800393A4 0A000104 */  bgez       $zero, .L800393D0
    /* 29BA8 800393A8 23600C00 */   negu      $t4, $t4
  .L800393AC:
    /* 29BAC 800393AC 000CCC2B */  slti       $t4, $fp, 0xC00
    /* 29BB0 800393B0 05008011 */  beqz       $t4, .L800393C8
    /* 29BB4 800393B4 40601E00 */   sll       $t4, $fp, 1
    /* 29BB8 800393B8 23606C00 */  subu       $t4, $v1, $t4
    /* 29BBC 800393BC 00188C85 */  lh         $t4, 0x1800($t4)
    /* 29BC0 800393C0 03000104 */  bgez       $zero, .L800393D0
    /* 29BC4 800393C4 23600C00 */   negu      $t4, $t4
  .L800393C8:
    /* 29BC8 800393C8 21606C00 */  addu       $t4, $v1, $t4
    /* 29BCC 800393CC 00E88C85 */  lh         $t4, -0x1800($t4)
  .L800393D0:
    /* 29BD0 800393D0 18002F01 */  mult       $t1, $t7
    /* 29BD4 800393D4 FFFFF031 */  andi       $s0, $t7, 0xFFFF
    /* 29BD8 800393D8 FFFF2931 */  andi       $t1, $t1, 0xFFFF
    /* 29BDC 800393DC FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 29BE0 800393E0 FFFFCE31 */  andi       $t6, $t6, 0xFFFF
    /* 29BE4 800393E4 FFFF4B31 */  andi       $t3, $t2, 0xFFFF
    /* 29BE8 800393E8 FFFF8C31 */  andi       $t4, $t4, 0xFFFF
    /* 29BEC 800393EC 0008C048 */  ctc2       $zero, $1 /* handwritten instruction */
    /* 29BF0 800393F0 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 29BF4 800393F4 00088E48 */  mtc2       $t6, $1 /* handwritten instruction */
    /* 29BF8 800393F8 000C0C00 */  sll        $at, $t4, 16
    /* 29BFC 800393FC 25082D00 */  or         $at, $at, $t5
    /* 29C00 80039400 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 29C04 80039404 12F00000 */  mflo       $fp
    /* 29C08 80039408 0000CB48 */  ctc2       $t3, $0 /* handwritten instruction */
    /* 29C0C 8003940C 0010C948 */  ctc2       $t1, $2 /* handwritten instruction */
    /* 29C10 80039410 0020CD48 */  ctc2       $t5, $4 /* handwritten instruction */
    /* 29C14 80039414 03F31E00 */  sra        $fp, $fp, 12
    /* 29C18 80039418 1800CA03 */  mult       $fp, $t2
    /* 29C1C 8003941C 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 29C20 80039420 0000CC48 */  ctc2       $t4, $0 /* handwritten instruction */
    /* 29C24 80039424 0010CE48 */  ctc2       $t6, $2 /* handwritten instruction */
    /* 29C28 80039428 0020D048 */  ctc2       $s0, $4 /* handwritten instruction */
    /* 29C2C 8003942C 00481D48 */  mfc2       $sp, $9 /* handwritten instruction */
    /* 29C30 80039430 12C00000 */  mflo       $t8
    /* 29C34 80039434 03C31800 */  sra        $t8, $t8, 12
    /* 29C38 80039438 00501C48 */  mfc2       $gp, $10 /* handwritten instruction */
    /* 29C3C 8003943C 00581148 */  mfc2       $s1, $11 /* handwritten instruction */
    /* 29C40 80039440 1800AF03 */  mult       $sp, $t7
    /* 29C44 80039444 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 29C48 80039448 0000D048 */  ctc2       $s0, $0 /* handwritten instruction */
    /* 29C4C 8003944C FFFFA133 */  andi       $at, $sp, 0xFFFF
    /* 29C50 80039450 0010C148 */  ctc2       $at, $2 /* handwritten instruction */
    /* 29C54 80039454 0020C948 */  ctc2       $t1, $4 /* handwritten instruction */
    /* 29C58 80039458 00480148 */  mfc2       $at, $9 /* handwritten instruction */
    /* 29C5C 8003945C 12B80000 */  mflo       $s7
    /* 29C60 80039460 00501248 */  mfc2       $s2, $10 /* handwritten instruction */
    /* 29C64 80039464 00581348 */  mfc2       $s3, $11 /* handwritten instruction */
    /* 29C68 80039468 18008A03 */  mult       $gp, $t2
    /* 29C6C 8003946C 1260484A */  mvmva      1, 0, 0, 3, 0
    /* 29C70 80039470 03BB1700 */  sra        $s7, $s7, 12
    /* 29C74 80039474 00481448 */  mfc2       $s4, $9 /* handwritten instruction */
    /* 29C78 80039478 00501548 */  mfc2       $s5, $10 /* handwritten instruction */
    /* 29C7C 8003947C 00581648 */  mfc2       $s6, $11 /* handwritten instruction */
    /* 29C80 80039480 12C80000 */  mflo       $t9
    /* 29C84 80039484 03CB1900 */  sra        $t9, $t9, 12
    /* 29C88 80039488 23901200 */  negu       $s2, $s2
    /* 29C8C 8003948C 23B89703 */  subu       $s7, $gp, $s7
    /* 29C90 80039490 21A8D503 */  addu       $s5, $fp, $s5
    /* 29C94 80039494 21C03800 */  addu       $t8, $at, $t8
    /* 29C98 80039498 23C01800 */  negu       $t8, $t8
    /* 29C9C 8003949C 23C83403 */  subu       $t9, $t9, $s4
    /* 29CA0 800394A0 0000898C */  lw         $t1, 0x0($a0)
    /* 29CA4 800394A4 04008B8C */  lw         $t3, 0x4($a0)
    /* 29CA8 800394A8 08008C8C */  lw         $t4, 0x8($a0)
    /* 29CAC 800394AC 0C008D8C */  lw         $t5, 0xC($a0)
    /* 29CB0 800394B0 10008E8C */  lw         $t6, 0x10($a0)
    /* 29CB4 800394B4 0000C948 */  ctc2       $t1, $0 /* handwritten instruction */
    /* 29CB8 800394B8 0008CB48 */  ctc2       $t3, $1 /* handwritten instruction */
    /* 29CBC 800394BC 0010CC48 */  ctc2       $t4, $2 /* handwritten instruction */
    /* 29CC0 800394C0 0018CD48 */  ctc2       $t5, $3 /* handwritten instruction */
    /* 29CC4 800394C4 0020CE48 */  ctc2       $t6, $4 /* handwritten instruction */
    /* 29CC8 800394C8 1800C98C */  lw         $t1, 0x18($a2)
    /* 29CCC 800394CC 0400AB8C */  lw         $t3, 0x4($a1)
    /* 29CD0 800394D0 00489748 */  mtc2       $s7, $9 /* handwritten instruction */
    /* 29CD4 800394D4 00509348 */  mtc2       $s3, $10 /* handwritten instruction */
    /* 29CD8 800394D8 00589848 */  mtc2       $t8, $11 /* handwritten instruction */
    /* 29CDC 800394DC 18002B01 */  mult       $t1, $t3
    /* 29CE0 800394E0 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 29CE4 800394E4 1C00C98C */  lw         $t1, 0x1C($a2)
    /* 29CE8 800394E8 0800AB8C */  lw         $t3, 0x8($a1)
    /* 29CEC 800394EC 00481748 */  mfc2       $s7, $9 /* handwritten instruction */
    /* 29CF0 800394F0 00501348 */  mfc2       $s3, $10 /* handwritten instruction */
    /* 29CF4 800394F4 00581848 */  mfc2       $t8, $11 /* handwritten instruction */
    /* 29CF8 800394F8 12600000 */  mflo       $t4
    /* 29CFC 800394FC 00489148 */  mtc2       $s1, $9 /* handwritten instruction */
    /* 29D00 80039500 00508A48 */  mtc2       $t2, $10 /* handwritten instruction */
    /* 29D04 80039504 00589648 */  mtc2       $s6, $11 /* handwritten instruction */
    /* 29D08 80039508 18002B01 */  mult       $t1, $t3
    /* 29D0C 8003950C 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 29D10 80039510 2000C98C */  lw         $t1, 0x20($a2)
    /* 29D14 80039514 0C00AB8C */  lw         $t3, 0xC($a1)
    /* 29D18 80039518 00481148 */  mfc2       $s1, $9 /* handwritten instruction */
    /* 29D1C 8003951C 00500A48 */  mfc2       $t2, $10 /* handwritten instruction */
    /* 29D20 80039520 00581648 */  mfc2       $s6, $11 /* handwritten instruction */
    /* 29D24 80039524 03630C00 */  sra        $t4, $t4, 12
    /* 29D28 80039528 12680000 */  mflo       $t5
    /* 29D2C 8003952C 00489548 */  mtc2       $s5, $9 /* handwritten instruction */
    /* 29D30 80039530 00509248 */  mtc2       $s2, $10 /* handwritten instruction */
    /* 29D34 80039534 00589948 */  mtc2       $t9, $11 /* handwritten instruction */
    /* 29D38 80039538 18002B01 */  mult       $t1, $t3
    /* 29D3C 8003953C 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 29D40 80039540 036B0D00 */  sra        $t5, $t5, 12
    /* 29D44 80039544 00481548 */  mfc2       $s5, $9 /* handwritten instruction */
    /* 29D48 80039548 00501248 */  mfc2       $s2, $10 /* handwritten instruction */
    /* 29D4C 8003954C 00581948 */  mfc2       $t9, $11 /* handwritten instruction */
    /* 29D50 80039550 FFFF8C31 */  andi       $t4, $t4, 0xFFFF
    /* 29D54 80039554 FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 29D58 80039558 12700000 */  mflo       $t6
    /* 29D5C 8003955C 03730E00 */  sra        $t6, $t6, 12
    /* 29D60 80039560 FFFFCE31 */  andi       $t6, $t6, 0xFFFF
    /* 29D64 80039564 0000CC48 */  ctc2       $t4, $0 /* handwritten instruction */
    /* 29D68 80039568 0008C048 */  ctc2       $zero, $1 /* handwritten instruction */
    /* 29D6C 8003956C 0010CD48 */  ctc2       $t5, $2 /* handwritten instruction */
    /* 29D70 80039570 0018C048 */  ctc2       $zero, $3 /* handwritten instruction */
    /* 29D74 80039574 0020CE48 */  ctc2       $t6, $4 /* handwritten instruction */
    /* 29D78 80039578 00489348 */  mtc2       $s3, $9 /* handwritten instruction */
    /* 29D7C 8003957C 00508A48 */  mtc2       $t2, $10 /* handwritten instruction */
    /* 29D80 80039580 00589248 */  mtc2       $s2, $11 /* handwritten instruction */
    /* 29D84 80039584 00000000 */  nop
    /* 29D88 80039588 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 29D8C 8003958C 00000000 */  nop
    /* 29D90 80039590 00481348 */  mfc2       $s3, $9 /* handwritten instruction */
    /* 29D94 80039594 00500A48 */  mfc2       $t2, $10 /* handwritten instruction */
    /* 29D98 80039598 00581248 */  mfc2       $s2, $11 /* handwritten instruction */
    /* 29D9C 8003959C 00489848 */  mtc2       $t8, $9 /* handwritten instruction */
    /* 29DA0 800395A0 00509648 */  mtc2       $s6, $10 /* handwritten instruction */
    /* 29DA4 800395A4 00589948 */  mtc2       $t9, $11 /* handwritten instruction */
    /* 29DA8 800395A8 21486002 */  addu       $t1, $s3, $zero
    /* 29DAC 800395AC 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 29DB0 800395B0 21584001 */  addu       $t3, $t2, $zero
    /* 29DB4 800395B4 00481848 */  mfc2       $t8, $9 /* handwritten instruction */
    /* 29DB8 800395B8 00501648 */  mfc2       $s6, $10 /* handwritten instruction */
    /* 29DBC 800395BC 00581948 */  mfc2       $t9, $11 /* handwritten instruction */
    /* 29DC0 800395C0 00489748 */  mtc2       $s7, $9 /* handwritten instruction */
    /* 29DC4 800395C4 00509148 */  mtc2       $s1, $10 /* handwritten instruction */
    /* 29DC8 800395C8 00589548 */  mtc2       $s5, $11 /* handwritten instruction */
    /* 29DCC 800395CC 21604002 */  addu       $t4, $s2, $zero
    /* 29DD0 800395D0 12E0494A */  mvmva      1, 0, 3, 3, 0
    /* 29DD4 800395D4 80981300 */  sll        $s3, $s3, 2
    /* 29DD8 800395D8 00481748 */  mfc2       $s7, $9 /* handwritten instruction */
    /* 29DDC 800395DC 00501148 */  mfc2       $s1, $10 /* handwritten instruction */
    /* 29DE0 800395E0 00581548 */  mfc2       $s5, $11 /* handwritten instruction */
    /* 29DE4 800395E4 21986902 */  addu       $s3, $s3, $t1
    /* 29DE8 800395E8 C3981300 */  sra        $s3, $s3, 3
    /* 29DEC 800395EC 23981300 */  negu       $s3, $s3
    /* 29DF0 800395F0 80500A00 */  sll        $t2, $t2, 2
    /* 29DF4 800395F4 21504B01 */  addu       $t2, $t2, $t3
    /* 29DF8 800395F8 C3500A00 */  sra        $t2, $t2, 3
    /* 29DFC 800395FC 23500A00 */  negu       $t2, $t2
    /* 29E00 80039600 80901200 */  sll        $s2, $s2, 2
    /* 29E04 80039604 21904C02 */  addu       $s2, $s2, $t4
    /* 29E08 80039608 C3901200 */  sra        $s2, $s2, 3
    /* 29E0C 8003960C 23901200 */  negu       $s2, $s2
    /* 29E10 80039610 23C01800 */  negu       $t8, $t8
    /* 29E14 80039614 23B01600 */  negu       $s6, $s6
    /* 29E18 80039618 23C81900 */  negu       $t9, $t9
    /* 29E1C 8003961C FFFFE132 */  andi       $at, $s7, 0xFFFF
    /* 29E20 80039620 004C1100 */  sll        $t1, $s1, 16
    /* 29E24 80039624 25482101 */  or         $t1, $t1, $at
    /* 29E28 80039628 FFFFA132 */  andi       $at, $s5, 0xFFFF
    /* 29E2C 8003962C 005C1300 */  sll        $t3, $s3, 16
    /* 29E30 80039630 25586101 */  or         $t3, $t3, $at
    /* 29E34 80039634 FFFF4131 */  andi       $at, $t2, 0xFFFF
    /* 29E38 80039638 00641200 */  sll        $t4, $s2, 16
    /* 29E3C 8003963C 25608101 */  or         $t4, $t4, $at
    /* 29E40 80039640 FFFF0133 */  andi       $at, $t8, 0xFFFF
    /* 29E44 80039644 006C1600 */  sll        $t5, $s6, 16
    /* 29E48 80039648 2568A101 */  or         $t5, $t5, $at
    /* 29E4C 8003964C 0000C948 */  ctc2       $t1, $0 /* handwritten instruction */
    /* 29E50 80039650 0008CB48 */  ctc2       $t3, $1 /* handwritten instruction */
    /* 29E54 80039654 0010CC48 */  ctc2       $t4, $2 /* handwritten instruction */
    /* 29E58 80039658 0018CD48 */  ctc2       $t5, $3 /* handwritten instruction */
    /* 29E5C 8003965C 0020D948 */  ctc2       $t9, $4 /* handwritten instruction */
    /* 29E60 80039660 1800C18C */  lw         $at, 0x18($a2)
    /* 29E64 80039664 1400DE8C */  lw         $fp, 0x14($a2)
    /* 29E68 80039668 1000DC8C */  lw         $gp, 0x10($a2)
    /* 29E6C 8003966C 2A202000 */  slt        $a0, $at, $zero
    /* 29E70 80039670 03008014 */  bnez       $a0, .L80039680
    /* 29E74 80039674 0C00DD8C */   lw        $sp, 0xC($a2)
    /* 29E78 80039678 02000104 */  bgez       $zero, .L80039684
    /* 29E7C 8003967C 23E0DC03 */   subu      $gp, $fp, $gp
  .L80039680:
    /* 29E80 80039680 21E0DC03 */  addu       $gp, $fp, $gp
  .L80039684:
    /* 29E84 80039684 23F01E00 */  negu       $fp, $fp
    /* 29E88 80039688 23E81D00 */  negu       $sp, $sp
    /* 29E8C 8003968C FF0F9C33 */  andi       $gp, $gp, 0xFFF
    /* 29E90 80039690 FF0FBD33 */  andi       $sp, $sp, 0xFFF
    /* 29E94 80039694 FF0FDE33 */  andi       $fp, $fp, 0xFFF
    /* 29E98 80039698 00088D2B */  slti       $t5, $gp, 0x800
    /* 29E9C 8003969C 0B00A011 */  beqz       $t5, .L800396CC
    /* 29EA0 800396A0 00048D2B */   slti      $t5, $gp, 0x400
    /* 29EA4 800396A4 0500A011 */  beqz       $t5, .L800396BC
    /* 29EA8 800396A8 40681C00 */   sll       $t5, $gp, 1
    /* 29EAC 800396AC 21686D00 */  addu       $t5, $v1, $t5
    /* 29EB0 800396B0 11000104 */  bgez       $zero, .L800396F8
    /* 29EB4 800396B4 0000AD85 */   lh        $t5, 0x0($t5)
    /* 29EB8 800396B8 00000000 */  nop
  .L800396BC:
    /* 29EBC 800396BC 23686D00 */  subu       $t5, $v1, $t5
    /* 29EC0 800396C0 0D000104 */  bgez       $zero, .L800396F8
    /* 29EC4 800396C4 0010AD85 */   lh        $t5, 0x1000($t5)
    /* 29EC8 800396C8 00000000 */  nop
  .L800396CC:
    /* 29ECC 800396CC 000C8D2B */  slti       $t5, $gp, 0xC00
    /* 29ED0 800396D0 0500A011 */  beqz       $t5, .L800396E8
    /* 29ED4 800396D4 40681C00 */   sll       $t5, $gp, 1
    /* 29ED8 800396D8 21686D00 */  addu       $t5, $v1, $t5
    /* 29EDC 800396DC 00F0AD85 */  lh         $t5, -0x1000($t5)
    /* 29EE0 800396E0 05000104 */  bgez       $zero, .L800396F8
    /* 29EE4 800396E4 23680D00 */   negu      $t5, $t5
  .L800396E8:
    /* 29EE8 800396E8 23686D00 */  subu       $t5, $v1, $t5
    /* 29EEC 800396EC 0020AD85 */  lh         $t5, 0x2000($t5)
    /* 29EF0 800396F0 01000104 */  bgez       $zero, .L800396F8
    /* 29EF4 800396F4 23680D00 */   negu      $t5, $t5
  .L800396F8:
    /* 29EF8 800396F8 0008AE2B */  slti       $t6, $sp, 0x800
    /* 29EFC 800396FC 0B00C011 */  beqz       $t6, .L8003972C
    /* 29F00 80039700 0004AE2B */   slti      $t6, $sp, 0x400
    /* 29F04 80039704 0500C011 */  beqz       $t6, .L8003971C
    /* 29F08 80039708 40701D00 */   sll       $t6, $sp, 1
    /* 29F0C 8003970C 21706E00 */  addu       $t6, $v1, $t6
    /* 29F10 80039710 11000104 */  bgez       $zero, .L80039758
    /* 29F14 80039714 0000CE85 */   lh        $t6, 0x0($t6)
    /* 29F18 80039718 00000000 */  nop
  .L8003971C:
    /* 29F1C 8003971C 23706E00 */  subu       $t6, $v1, $t6
    /* 29F20 80039720 0D000104 */  bgez       $zero, .L80039758
    /* 29F24 80039724 0010CE85 */   lh        $t6, 0x1000($t6)
    /* 29F28 80039728 00000000 */  nop
  .L8003972C:
    /* 29F2C 8003972C 000CAE2B */  slti       $t6, $sp, 0xC00
    /* 29F30 80039730 0500C011 */  beqz       $t6, .L80039748
    /* 29F34 80039734 40701D00 */   sll       $t6, $sp, 1
    /* 29F38 80039738 21706E00 */  addu       $t6, $v1, $t6
    /* 29F3C 8003973C 00F0CE85 */  lh         $t6, -0x1000($t6)
    /* 29F40 80039740 05000104 */  bgez       $zero, .L80039758
    /* 29F44 80039744 23700E00 */   negu      $t6, $t6
  .L80039748:
    /* 29F48 80039748 23706E00 */  subu       $t6, $v1, $t6
    /* 29F4C 8003974C 0020CE85 */  lh         $t6, 0x2000($t6)
    /* 29F50 80039750 01000104 */  bgez       $zero, .L80039758
    /* 29F54 80039754 23700E00 */   negu      $t6, $t6
  .L80039758:
    /* 29F58 80039758 0008CF2B */  slti       $t7, $fp, 0x800
    /* 29F5C 8003975C 0B00E011 */  beqz       $t7, .L8003978C
    /* 29F60 80039760 0004CF2B */   slti      $t7, $fp, 0x400
    /* 29F64 80039764 0500E011 */  beqz       $t7, .L8003977C
    /* 29F68 80039768 40781E00 */   sll       $t7, $fp, 1
    /* 29F6C 8003976C 21786F00 */  addu       $t7, $v1, $t7
    /* 29F70 80039770 11000104 */  bgez       $zero, .L800397B8
    /* 29F74 80039774 0000EF85 */   lh        $t7, 0x0($t7)
    /* 29F78 80039778 00000000 */  nop
  .L8003977C:
    /* 29F7C 8003977C 23786F00 */  subu       $t7, $v1, $t7
    /* 29F80 80039780 0D000104 */  bgez       $zero, .L800397B8
    /* 29F84 80039784 0010EF85 */   lh        $t7, 0x1000($t7)
    /* 29F88 80039788 00000000 */  nop
  .L8003978C:
    /* 29F8C 8003978C 000CCF2B */  slti       $t7, $fp, 0xC00
    /* 29F90 80039790 0500E011 */  beqz       $t7, .L800397A8
    /* 29F94 80039794 40781E00 */   sll       $t7, $fp, 1
    /* 29F98 80039798 21786F00 */  addu       $t7, $v1, $t7
    /* 29F9C 8003979C 00F0EF85 */  lh         $t7, -0x1000($t7)
    /* 29FA0 800397A0 05000104 */  bgez       $zero, .L800397B8
    /* 29FA4 800397A4 23780F00 */   negu      $t7, $t7
  .L800397A8:
    /* 29FA8 800397A8 23786F00 */  subu       $t7, $v1, $t7
    /* 29FAC 800397AC 0020EF85 */  lh         $t7, 0x2000($t7)
    /* 29FB0 800397B0 01000104 */  bgez       $zero, .L800397B8
    /* 29FB4 800397B4 23780F00 */   negu      $t7, $t7
  .L800397B8:
    /* 29FB8 800397B8 0008892B */  slti       $t1, $gp, 0x800
    /* 29FBC 800397BC 0B002011 */  beqz       $t1, .L800397EC
    /* 29FC0 800397C0 0004892B */   slti      $t1, $gp, 0x400
    /* 29FC4 800397C4 05002011 */  beqz       $t1, .L800397DC
    /* 29FC8 800397C8 40481C00 */   sll       $t1, $gp, 1
    /* 29FCC 800397CC 23486900 */  subu       $t1, $v1, $t1
    /* 29FD0 800397D0 0F000104 */  bgez       $zero, .L80039810
    /* 29FD4 800397D4 00082985 */   lh        $t1, 0x800($t1)
    /* 29FD8 800397D8 00000000 */  nop
  .L800397DC:
    /* 29FDC 800397DC 21486900 */  addu       $t1, $v1, $t1
    /* 29FE0 800397E0 00F82985 */  lh         $t1, -0x800($t1)
    /* 29FE4 800397E4 0A000104 */  bgez       $zero, .L80039810
    /* 29FE8 800397E8 23480900 */   negu      $t1, $t1
  .L800397EC:
    /* 29FEC 800397EC 000C892B */  slti       $t1, $gp, 0xC00
    /* 29FF0 800397F0 05002011 */  beqz       $t1, .L80039808
    /* 29FF4 800397F4 40481C00 */   sll       $t1, $gp, 1
    /* 29FF8 800397F8 23486900 */  subu       $t1, $v1, $t1
    /* 29FFC 800397FC 00182985 */  lh         $t1, 0x1800($t1)
    /* 2A000 80039800 03000104 */  bgez       $zero, .L80039810
    /* 2A004 80039804 23480900 */   negu      $t1, $t1
  .L80039808:
    /* 2A008 80039808 21486900 */  addu       $t1, $v1, $t1
    /* 2A00C 8003980C 00E82985 */  lh         $t1, -0x1800($t1)
  .L80039810:
    /* 2A010 80039810 0008AA2B */  slti       $t2, $sp, 0x800
    /* 2A014 80039814 0B004011 */  beqz       $t2, .L80039844
    /* 2A018 80039818 0004AA2B */   slti      $t2, $sp, 0x400
    /* 2A01C 8003981C 05004011 */  beqz       $t2, .L80039834
    /* 2A020 80039820 40501D00 */   sll       $t2, $sp, 1
    /* 2A024 80039824 23506A00 */  subu       $t2, $v1, $t2
    /* 2A028 80039828 0F000104 */  bgez       $zero, .L80039868
    /* 2A02C 8003982C 00084A85 */   lh        $t2, 0x800($t2)
    /* 2A030 80039830 00000000 */  nop
  .L80039834:
    /* 2A034 80039834 21506A00 */  addu       $t2, $v1, $t2
    /* 2A038 80039838 00F84A85 */  lh         $t2, -0x800($t2)
    /* 2A03C 8003983C 0A000104 */  bgez       $zero, .L80039868
    /* 2A040 80039840 23500A00 */   negu      $t2, $t2
  .L80039844:
    /* 2A044 80039844 000CAA2B */  slti       $t2, $sp, 0xC00
    /* 2A048 80039848 05004011 */  beqz       $t2, .L80039860
    /* 2A04C 8003984C 40501D00 */   sll       $t2, $sp, 1
    /* 2A050 80039850 23506A00 */  subu       $t2, $v1, $t2
    /* 2A054 80039854 00184A85 */  lh         $t2, 0x1800($t2)
    /* 2A058 80039858 03000104 */  bgez       $zero, .L80039868
    /* 2A05C 8003985C 23500A00 */   negu      $t2, $t2
  .L80039860:
    /* 2A060 80039860 21506A00 */  addu       $t2, $v1, $t2
    /* 2A064 80039864 00E84A85 */  lh         $t2, -0x1800($t2)
  .L80039868:
    /* 2A068 80039868 0008CC2B */  slti       $t4, $fp, 0x800
    /* 2A06C 8003986C 0B008011 */  beqz       $t4, .L8003989C
    /* 2A070 80039870 0004CC2B */   slti      $t4, $fp, 0x400
    /* 2A074 80039874 05008011 */  beqz       $t4, .L8003988C
    /* 2A078 80039878 40601E00 */   sll       $t4, $fp, 1
    /* 2A07C 8003987C 23606C00 */  subu       $t4, $v1, $t4
    /* 2A080 80039880 0F000104 */  bgez       $zero, .L800398C0
    /* 2A084 80039884 00088C85 */   lh        $t4, 0x800($t4)
    /* 2A088 80039888 00000000 */  nop
  .L8003988C:
    /* 2A08C 8003988C 21606C00 */  addu       $t4, $v1, $t4
    /* 2A090 80039890 00F88C85 */  lh         $t4, -0x800($t4)
    /* 2A094 80039894 0A000104 */  bgez       $zero, .L800398C0
    /* 2A098 80039898 23600C00 */   negu      $t4, $t4
  .L8003989C:
    /* 2A09C 8003989C 000CCC2B */  slti       $t4, $fp, 0xC00
    /* 2A0A0 800398A0 05008011 */  beqz       $t4, .L800398B8
    /* 2A0A4 800398A4 40601E00 */   sll       $t4, $fp, 1
    /* 2A0A8 800398A8 23606C00 */  subu       $t4, $v1, $t4
    /* 2A0AC 800398AC 00188C85 */  lh         $t4, 0x1800($t4)
    /* 2A0B0 800398B0 03000104 */  bgez       $zero, .L800398C0
    /* 2A0B4 800398B4 23600C00 */   negu      $t4, $t4
  .L800398B8:
    /* 2A0B8 800398B8 21606C00 */  addu       $t4, $v1, $t4
    /* 2A0BC 800398BC 00E88C85 */  lh         $t4, -0x1800($t4)
  .L800398C0:
    /* 2A0C0 800398C0 18002F01 */  mult       $t1, $t7
    /* 2A0C4 800398C4 FFFFF031 */  andi       $s0, $t7, 0xFFFF
    /* 2A0C8 800398C8 FFFF2931 */  andi       $t1, $t1, 0xFFFF
    /* 2A0CC 800398CC FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 2A0D0 800398D0 FFFFCE31 */  andi       $t6, $t6, 0xFFFF
    /* 2A0D4 800398D4 FFFF4B31 */  andi       $t3, $t2, 0xFFFF
    /* 2A0D8 800398D8 FFFF8C31 */  andi       $t4, $t4, 0xFFFF
    /* 2A0DC 800398DC 0048C048 */  ctc2       $zero, $9 /* handwritten instruction */
    /* 2A0E0 800398E0 0058C048 */  ctc2       $zero, $11 /* handwritten instruction */
    /* 2A0E4 800398E4 00088E48 */  mtc2       $t6, $1 /* handwritten instruction */
    /* 2A0E8 800398E8 000C0C00 */  sll        $at, $t4, 16
    /* 2A0EC 800398EC 25082D00 */  or         $at, $at, $t5
    /* 2A0F0 800398F0 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 2A0F4 800398F4 12F00000 */  mflo       $fp
    /* 2A0F8 800398F8 0040CB48 */  ctc2       $t3, $8 /* handwritten instruction */
    /* 2A0FC 800398FC 0050C948 */  ctc2       $t1, $10 /* handwritten instruction */
    /* 2A100 80039900 0060CD48 */  ctc2       $t5, $12 /* handwritten instruction */
    /* 2A104 80039904 03F31E00 */  sra        $fp, $fp, 12
    /* 2A108 80039908 1800CA03 */  mult       $fp, $t2
    /* 2A10C 8003990C 12604A4A */  mvmva      1, 1, 0, 3, 0
    /* 2A110 80039910 0040CC48 */  ctc2       $t4, $8 /* handwritten instruction */
    /* 2A114 80039914 0050CE48 */  ctc2       $t6, $10 /* handwritten instruction */
    /* 2A118 80039918 0060D048 */  ctc2       $s0, $12 /* handwritten instruction */
    /* 2A11C 8003991C 00481D48 */  mfc2       $sp, $9 /* handwritten instruction */
    /* 2A120 80039920 12C00000 */  mflo       $t8
    /* 2A124 80039924 03C31800 */  sra        $t8, $t8, 12
    /* 2A128 80039928 00501C48 */  mfc2       $gp, $10 /* handwritten instruction */
    /* 2A12C 8003992C 00581148 */  mfc2       $s1, $11 /* handwritten instruction */
    /* 2A130 80039930 1800AF03 */  mult       $sp, $t7
    /* 2A134 80039934 12604A4A */  mvmva      1, 1, 0, 3, 0
    /* 2A138 80039938 0040D048 */  ctc2       $s0, $8 /* handwritten instruction */
    /* 2A13C 8003993C FFFFA133 */  andi       $at, $sp, 0xFFFF
    /* 2A140 80039940 0050C148 */  ctc2       $at, $10 /* handwritten instruction */
    /* 2A144 80039944 0060C948 */  ctc2       $t1, $12 /* handwritten instruction */
    /* 2A148 80039948 00480148 */  mfc2       $at, $9 /* handwritten instruction */
    /* 2A14C 8003994C 12B80000 */  mflo       $s7
    /* 2A150 80039950 00501248 */  mfc2       $s2, $10 /* handwritten instruction */
    /* 2A154 80039954 00581348 */  mfc2       $s3, $11 /* handwritten instruction */
    /* 2A158 80039958 18008A03 */  mult       $gp, $t2
    /* 2A15C 8003995C 12604A4A */  mvmva      1, 1, 0, 3, 0
    /* 2A160 80039960 03BB1700 */  sra        $s7, $s7, 12
    /* 2A164 80039964 00481448 */  mfc2       $s4, $9 /* handwritten instruction */
    /* 2A168 80039968 00501548 */  mfc2       $s5, $10 /* handwritten instruction */
    /* 2A16C 8003996C 00581648 */  mfc2       $s6, $11 /* handwritten instruction */
    /* 2A170 80039970 12C80000 */  mflo       $t9
    /* 2A174 80039974 03CB1900 */  sra        $t9, $t9, 12
    /* 2A178 80039978 23901200 */  negu       $s2, $s2
    /* 2A17C 8003997C 23B89703 */  subu       $s7, $gp, $s7
    /* 2A180 80039980 21A8D503 */  addu       $s5, $fp, $s5
    /* 2A184 80039984 21C03800 */  addu       $t8, $at, $t8
    /* 2A188 80039988 23C01800 */  negu       $t8, $t8
    /* 2A18C 8003998C 23C83403 */  subu       $t9, $t9, $s4
    /* 2A190 80039990 FFFFE132 */  andi       $at, $s7, 0xFFFF
    /* 2A194 80039994 004C1100 */  sll        $t1, $s1, 16
    /* 2A198 80039998 25482101 */  or         $t1, $t1, $at
    /* 2A19C 8003999C FFFFA132 */  andi       $at, $s5, 0xFFFF
    /* 2A1A0 800399A0 005C1300 */  sll        $t3, $s3, 16
    /* 2A1A4 800399A4 25586101 */  or         $t3, $t3, $at
    /* 2A1A8 800399A8 FFFF4131 */  andi       $at, $t2, 0xFFFF
    /* 2A1AC 800399AC 00641200 */  sll        $t4, $s2, 16
    /* 2A1B0 800399B0 25608101 */  or         $t4, $t4, $at
    /* 2A1B4 800399B4 FFFF0133 */  andi       $at, $t8, 0xFFFF
    /* 2A1B8 800399B8 006C1600 */  sll        $t5, $s6, 16
    /* 2A1BC 800399BC 2568A101 */  or         $t5, $t5, $at
    /* 2A1C0 800399C0 0040C948 */  ctc2       $t1, $8 /* handwritten instruction */
    /* 2A1C4 800399C4 0048CB48 */  ctc2       $t3, $9 /* handwritten instruction */
    /* 2A1C8 800399C8 0050CC48 */  ctc2       $t4, $10 /* handwritten instruction */
    /* 2A1CC 800399CC 0058CD48 */  ctc2       $t5, $11 /* handwritten instruction */
    /* 2A1D0 800399D0 0060D948 */  ctc2       $t9, $12 /* handwritten instruction */
    /* 2A1D4 800399D4 0000E98C */  lw         $t1, 0x0($a3)
    /* 2A1D8 800399D8 0400EB8C */  lw         $t3, 0x4($a3)
    /* 2A1DC 800399DC 0800EC8C */  lw         $t4, 0x8($a3)
    /* 2A1E0 800399E0 0C00ED8C */  lw         $t5, 0xC($a3)
    /* 2A1E4 800399E4 1000EE8C */  lw         $t6, 0x10($a3)
    /* 2A1E8 800399E8 1400EF8C */  lw         $t7, 0x14($a3)
    /* 2A1EC 800399EC 1800F08C */  lw         $s0, 0x18($a3)
    /* 2A1F0 800399F0 1C00F48C */  lw         $s4, 0x1C($a3)
    /* 2A1F4 800399F4 2000FC8C */  lw         $gp, 0x20($a3)
    /* 2A1F8 800399F8 2400FD8C */  lw         $sp, 0x24($a3)
    /* 2A1FC 800399FC 2800FE8C */  lw         $fp, 0x28($a3)
    /* 2A200 80039A00 2C00E38C */  lw         $v1, 0x2C($a3)
    /* 2A204 80039A04 00BC0900 */  sll        $s7, $t1, 16
    /* 2A208 80039A08 02008010 */  beqz       $a0, .L80039A14
    /* 2A20C 80039A0C 03BC1700 */   sra       $s7, $s7, 16
    /* 2A210 80039A10 23B81700 */  negu       $s7, $s7
  .L80039A14:
    /* 2A214 80039A14 038C0900 */  sra        $s1, $t1, 16
    /* 2A218 80039A18 00AC0B00 */  sll        $s5, $t3, 16
    /* 2A21C 80039A1C 03AC1500 */  sra        $s5, $s5, 16
    /* 2A220 80039A20 00489748 */  mtc2       $s7, $9 /* handwritten instruction */
    /* 2A224 80039A24 00509148 */  mtc2       $s1, $10 /* handwritten instruction */
    /* 2A228 80039A28 00589548 */  mtc2       $s5, $11 /* handwritten instruction */
    /* 2A22C 80039A2C 03141E00 */  sra        $v0, $fp, 16
    /* 2A230 80039A30 03440E00 */  sra        $t0, $t6, 16
    /* 2A234 80039A34 18004800 */  mult       $v0, $t0
    /* 2A238 80039A38 12E04B4A */  mvmva      1, 1, 3, 3, 0
    /* 2A23C 80039A3C 00140300 */  sll        $v0, $v1, 16
    /* 2A240 80039A40 03140200 */  sra        $v0, $v0, 16
    /* 2A244 80039A44 00440F00 */  sll        $t0, $t7, 16
    /* 2A248 80039A48 03440800 */  sra        $t0, $t0, 16
    /* 2A24C 80039A4C 00481748 */  mfc2       $s7, $9 /* handwritten instruction */
    /* 2A250 80039A50 00501148 */  mfc2       $s1, $10 /* handwritten instruction */
    /* 2A254 80039A54 00581548 */  mfc2       $s5, $11 /* handwritten instruction */
    /* 2A258 80039A58 12F80000 */  mflo       $ra
    /* 2A25C 80039A5C 03FA1F00 */  sra        $ra, $ra, 8
    /* 2A260 80039A60 0068DF48 */  ctc2       $ra, $13 /* handwritten instruction */
    /* 2A264 80039A64 02008010 */  beqz       $a0, .L80039A70
    /* 2A268 80039A68 039C0B00 */   sra       $s3, $t3, 16
    /* 2A26C 80039A6C 23981300 */  negu       $s3, $s3
  .L80039A70:
    /* 2A270 80039A70 00540C00 */  sll        $t2, $t4, 16
    /* 2A274 80039A74 03540A00 */  sra        $t2, $t2, 16
    /* 2A278 80039A78 03940C00 */  sra        $s2, $t4, 16
    /* 2A27C 80039A7C 00489348 */  mtc2       $s3, $9 /* handwritten instruction */
    /* 2A280 80039A80 00508A48 */  mtc2       $t2, $10 /* handwritten instruction */
    /* 2A284 80039A84 00589248 */  mtc2       $s2, $11 /* handwritten instruction */
    /* 2A288 80039A88 18004800 */  mult       $v0, $t0
    /* 2A28C 80039A8C 12E04B4A */  mvmva      1, 1, 3, 3, 0
    /* 2A290 80039A90 03140300 */  sra        $v0, $v1, 16
    /* 2A294 80039A94 03440F00 */  sra        $t0, $t7, 16
    /* 2A298 80039A98 00481348 */  mfc2       $s3, $9 /* handwritten instruction */
    /* 2A29C 80039A9C 00500A48 */  mfc2       $t2, $10 /* handwritten instruction */
    /* 2A2A0 80039AA0 00581248 */  mfc2       $s2, $11 /* handwritten instruction */
    /* 2A2A4 80039AA4 12F80000 */  mflo       $ra
    /* 2A2A8 80039AA8 03FA1F00 */  sra        $ra, $ra, 8
    /* 2A2AC 80039AAC 0070DF48 */  ctc2       $ra, $14 /* handwritten instruction */
    /* 2A2B0 80039AB0 00C40D00 */  sll        $t8, $t5, 16
    /* 2A2B4 80039AB4 02008010 */  beqz       $a0, .L80039AC0
    /* 2A2B8 80039AB8 03C41800 */   sra       $t8, $t8, 16
    /* 2A2BC 80039ABC 23C01800 */  negu       $t8, $t8
  .L80039AC0:
    /* 2A2C0 80039AC0 03B40D00 */  sra        $s6, $t5, 16
    /* 2A2C4 80039AC4 00CC0E00 */  sll        $t9, $t6, 16
    /* 2A2C8 80039AC8 03CC1900 */  sra        $t9, $t9, 16
    /* 2A2CC 80039ACC 00489848 */  mtc2       $t8, $9 /* handwritten instruction */
    /* 2A2D0 80039AD0 00509648 */  mtc2       $s6, $10 /* handwritten instruction */
    /* 2A2D4 80039AD4 00589948 */  mtc2       $t9, $11 /* handwritten instruction */
    /* 2A2D8 80039AD8 18004800 */  mult       $v0, $t0
    /* 2A2DC 80039ADC 12E04B4A */  mvmva      1, 1, 3, 3, 0
    /* 2A2E0 80039AE0 00000000 */  nop
    /* 2A2E4 80039AE4 00481848 */  mfc2       $t8, $9 /* handwritten instruction */
    /* 2A2E8 80039AE8 00501648 */  mfc2       $s6, $10 /* handwritten instruction */
    /* 2A2EC 80039AEC 00581948 */  mfc2       $t9, $11 /* handwritten instruction */
    /* 2A2F0 80039AF0 12F80000 */  mflo       $ra
    /* 2A2F4 80039AF4 03FA1F00 */  sra        $ra, $ra, 8
    /* 2A2F8 80039AF8 0078DF48 */  ctc2       $ra, $15 /* handwritten instruction */
    /* 2A2FC 80039AFC FFFFE132 */  andi       $at, $s7, 0xFFFF
    /* 2A300 80039B00 004C1100 */  sll        $t1, $s1, 16
    /* 2A304 80039B04 25482101 */  or         $t1, $t1, $at
    /* 2A308 80039B08 0040C948 */  ctc2       $t1, $8 /* handwritten instruction */
    /* 2A30C 80039B0C FFFFA132 */  andi       $at, $s5, 0xFFFF
    /* 2A310 80039B10 004C1300 */  sll        $t1, $s3, 16
    /* 2A314 80039B14 25482101 */  or         $t1, $t1, $at
    /* 2A318 80039B18 0048C948 */  ctc2       $t1, $9 /* handwritten instruction */
    /* 2A31C 80039B1C FFFF4131 */  andi       $at, $t2, 0xFFFF
    /* 2A320 80039B20 004C1200 */  sll        $t1, $s2, 16
    /* 2A324 80039B24 25482101 */  or         $t1, $t1, $at
    /* 2A328 80039B28 0050C948 */  ctc2       $t1, $10 /* handwritten instruction */
    /* 2A32C 80039B2C FFFF0133 */  andi       $at, $t8, 0xFFFF
    /* 2A330 80039B30 004C1600 */  sll        $t1, $s6, 16
    /* 2A334 80039B34 25482101 */  or         $t1, $t1, $at
    /* 2A338 80039B38 0058C948 */  ctc2       $t1, $11 /* handwritten instruction */
    /* 2A33C 80039B3C 0060D948 */  ctc2       $t9, $12 /* handwritten instruction */
    /* 2A340 80039B40 FFFF013C */  lui        $at, (0xFFFF0000 >> 16)
    /* 2A344 80039B44 24488102 */  and        $t1, $s4, $at
    /* 2A348 80039B48 FFFF0B32 */  andi       $t3, $s0, 0xFFFF
    /* 2A34C 80039B4C 25482B01 */  or         $t1, $t1, $t3
    /* 2A350 80039B50 0080C948 */  ctc2       $t1, $16 /* handwritten instruction */
    /* 2A354 80039B54 24480102 */  and        $t1, $s0, $at
    /* 2A358 80039B58 FFFFAB33 */  andi       $t3, $sp, 0xFFFF
    /* 2A35C 80039B5C 25482B01 */  or         $t1, $t1, $t3
    /* 2A360 80039B60 0088C948 */  ctc2       $t1, $17 /* handwritten instruction */
    /* 2A364 80039B64 2448A103 */  and        $t1, $sp, $at
    /* 2A368 80039B68 FFFF8B33 */  andi       $t3, $gp, 0xFFFF
    /* 2A36C 80039B6C 25482B01 */  or         $t1, $t1, $t3
    /* 2A370 80039B70 0090C948 */  ctc2       $t1, $18 /* handwritten instruction */
    /* 2A374 80039B74 24488103 */  and        $t1, $gp, $at
    /* 2A378 80039B78 FFFF8B32 */  andi       $t3, $s4, 0xFFFF
    /* 2A37C 80039B7C 25482B01 */  or         $t1, $t1, $t3
    /* 2A380 80039B80 0098C948 */  ctc2       $t1, $19 /* handwritten instruction */
    /* 2A384 80039B84 00A0DE48 */  ctc2       $fp, $20 /* handwritten instruction */
    /* 2A388 80039B88 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 2A38C 80039B8C 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 2A390 80039B90 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 2A394 80039B94 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 2A398 80039B98 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 2A39C 80039B9C 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 2A3A0 80039BA0 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 2A3A4 80039BA4 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 2A3A8 80039BA8 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 2A3AC 80039BAC 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 2A3B0 80039BB0 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 2A3B4 80039BB4 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 2A3B8 80039BB8 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 2A3BC 80039BBC 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 2A3C0 80039BC0 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 2A3C4 80039BC4 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 2A3C8 80039BC8 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 2A3CC 80039BCC 0800E003 */  jr         $ra
    /* 2A3D0 80039BD0 00000000 */   nop
endlabel Gte_RCalcObjectRotMatrix
