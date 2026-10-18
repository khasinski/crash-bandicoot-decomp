.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_800351C8
    /* 259C8 800351C8 801F013C */  lui        $at, (0x1F800000 >> 16)
    /* 259CC 800351CC 00003FAC */  sw         $ra, (0x1F800000 & 0xFFFF)($at)
    /* 259D0 800351D0 0000CA8C */  lw         $t2, 0x0($a2)
    /* 259D4 800351D4 0400CB8C */  lw         $t3, 0x4($a2)
    /* 259D8 800351D8 0800CC8C */  lw         $t4, 0x8($a2)
    /* 259DC 800351DC 0000AD8C */  lw         $t5, 0x0($a1)
    /* 259E0 800351E0 0400AE8C */  lw         $t6, 0x4($a1)
    /* 259E4 800351E4 0800AF8C */  lw         $t7, 0x8($a1)
    /* 259E8 800351E8 0000818C */  lw         $at, 0x0($a0)
    /* 259EC 800351EC 0400828C */  lw         $v0, 0x4($a0)
    /* 259F0 800351F0 0800838C */  lw         $v1, 0x8($a0)
    /* 259F4 800351F4 0C00868C */  lw         $a2, 0xC($a0)
    /* 259F8 800351F8 1000858C */  lw         $a1, 0x10($a0)
    /* 259FC 800351FC 1400848C */  lw         $a0, 0x14($a0)
    /* 25A00 80035200 0000E98C */  lw         $t1, 0x0($a3)
    /* 25A04 80035204 0400E88C */  lw         $t0, 0x4($a3)
    /* 25A08 80035208 0800E78C */  lw         $a3, 0x8($a3)
    /* 25A0C 8003520C 21082A00 */  addu       $at, $at, $t2
    /* 25A10 80035210 21104B00 */  addu       $v0, $v0, $t3
    /* 25A14 80035214 21186C00 */  addu       $v1, $v1, $t4
    /* 25A18 80035218 2130CA00 */  addu       $a2, $a2, $t2
    /* 25A1C 8003521C 2128AB00 */  addu       $a1, $a1, $t3
    /* 25A20 80035220 21208C00 */  addu       $a0, $a0, $t4
    /* 25A24 80035224 2368A901 */  subu       $t5, $t5, $t1
    /* 25A28 80035228 2370C801 */  subu       $t6, $t6, $t0
    /* 25A2C 8003522C 2378E701 */  subu       $t7, $t7, $a3
    /* 25A30 80035230 21502D00 */  addu       $t2, $at, $t5
    /* 25A34 80035234 21584E00 */  addu       $t3, $v0, $t6
    /* 25A38 80035238 21606F00 */  addu       $t4, $v1, $t7
    /* 25A3C 8003523C 2168CD00 */  addu       $t5, $a2, $t5
    /* 25A40 80035240 2170AE00 */  addu       $t6, $a1, $t6
    /* 25A44 80035244 21788F00 */  addu       $t7, $a0, $t7
    /* 25A48 80035248 03520A00 */  sra        $t2, $t2, 8
    /* 25A4C 8003524C 035A0B00 */  sra        $t3, $t3, 8
    /* 25A50 80035250 03620C00 */  sra        $t4, $t4, 8
    /* 25A54 80035254 036A0D00 */  sra        $t5, $t5, 8
    /* 25A58 80035258 03720E00 */  sra        $t6, $t6, 8
    /* 25A5C 8003525C 037A0F00 */  sra        $t7, $t7, 8
    /* 25A60 80035260 FFFF4A31 */  andi       $t2, $t2, 0xFFFF
    /* 25A64 80035264 FFFFAD31 */  andi       $t5, $t5, 0xFFFF
    /* 25A68 80035268 005C0B00 */  sll        $t3, $t3, 16
    /* 25A6C 8003526C 00740E00 */  sll        $t6, $t6, 16
    /* 25A70 80035270 FFFF8C31 */  andi       $t4, $t4, 0xFFFF
    /* 25A74 80035274 FFFFEF31 */  andi       $t7, $t7, 0xFFFF
    /* 25A78 80035278 25084B01 */  or         $at, $t2, $t3
    /* 25A7C 8003527C 25104E01 */  or         $v0, $t2, $t6
    /* 25A80 80035280 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 25A84 80035284 00108148 */  mtc2       $at, $2 /* handwritten instruction */
    /* 25A88 80035288 00208248 */  mtc2       $v0, $4 /* handwritten instruction */
    /* 25A8C 8003528C 00088C48 */  mtc2       $t4, $1 /* handwritten instruction */
    /* 25A90 80035290 00188F48 */  mtc2       $t7, $3 /* handwritten instruction */
    /* 25A94 80035294 00288C48 */  mtc2       $t4, $5 /* handwritten instruction */
    /* 25A98 80035298 00000000 */  nop
    /* 25A9C 8003529C 00000000 */  nop
    /* 25AA0 800352A0 3000284A */  rtpt
    /* 25AA4 800352A4 00000000 */  nop
    /* 25AA8 800352A8 00600148 */  mfc2       $at, $12 /* handwritten instruction */
    /* 25AAC 800352AC 00680248 */  mfc2       $v0, $13 /* handwritten instruction */
    /* 25AB0 800352B0 00700348 */  mfc2       $v1, $14 /* handwritten instruction */
    /* 25AB4 800352B4 0080053C */  lui        $a1, (0x80000000 >> 16)
    /* 25AB8 800352B8 0080073C */  lui        $a3, (0x80000000 >> 16)
    /* 25ABC 800352BC 2720A000 */  not        $a0, $a1
    /* 25AC0 800352C0 2730E000 */  not        $a2, $a3
    /* 25AC4 800352C4 DCD4000C */  jal        func_80035370
    /* 25AC8 800352C8 00000000 */   nop
    /* 25ACC 800352CC 25084E01 */  or         $at, $t2, $t6
    /* 25AD0 800352D0 2510AB01 */  or         $v0, $t5, $t3
    /* 25AD4 800352D4 00008148 */  mtc2       $at, $0 /* handwritten instruction */
    /* 25AD8 800352D8 00108248 */  mtc2       $v0, $2 /* handwritten instruction */
    /* 25ADC 800352DC 00208248 */  mtc2       $v0, $4 /* handwritten instruction */
    /* 25AE0 800352E0 00088F48 */  mtc2       $t7, $1 /* handwritten instruction */
    /* 25AE4 800352E4 00188C48 */  mtc2       $t4, $3 /* handwritten instruction */
    /* 25AE8 800352E8 00288F48 */  mtc2       $t7, $5 /* handwritten instruction */
    /* 25AEC 800352EC 00000000 */  nop
    /* 25AF0 800352F0 00000000 */  nop
    /* 25AF4 800352F4 3000284A */  rtpt
    /* 25AF8 800352F8 00000000 */  nop
    /* 25AFC 800352FC 00600148 */  mfc2       $at, $12 /* handwritten instruction */
    /* 25B00 80035300 00680248 */  mfc2       $v0, $13 /* handwritten instruction */
    /* 25B04 80035304 00700348 */  mfc2       $v1, $14 /* handwritten instruction */
    /* 25B08 80035308 DCD4000C */  jal        func_80035370
    /* 25B0C 8003530C 00000000 */   nop
    /* 25B10 80035310 2508AE01 */  or         $at, $t5, $t6
    /* 25B14 80035314 00108148 */  mtc2       $at, $2 /* handwritten instruction */
    /* 25B18 80035318 00208148 */  mtc2       $at, $4 /* handwritten instruction */
    /* 25B1C 8003531C 00188C48 */  mtc2       $t4, $3 /* handwritten instruction */
    /* 25B20 80035320 00288F48 */  mtc2       $t7, $5 /* handwritten instruction */
    /* 25B24 80035324 00000000 */  nop
    /* 25B28 80035328 00000000 */  nop
    /* 25B2C 8003532C 3000284A */  rtpt
    /* 25B30 80035330 00000000 */  nop
    /* 25B34 80035334 00680248 */  mfc2       $v0, $13 /* handwritten instruction */
    /* 25B38 80035338 00700348 */  mfc2       $v1, $14 /* handwritten instruction */
    /* 25B3C 8003533C ECD4000C */  jal        func_800353B0
    /* 25B40 80035340 00000000 */   nop
    /* 25B44 80035344 801F013C */  lui        $at, (0x1F800048 >> 16)
    /* 25B48 80035348 48002134 */  ori        $at, $at, (0x1F800048 & 0xFFFF)
    /* 25B4C 8003534C 000024AC */  sw         $a0, 0x0($at)
    /* 25B50 80035350 040026AC */  sw         $a2, 0x4($at)
    /* 25B54 80035354 080025AC */  sw         $a1, 0x8($at)
    /* 25B58 80035358 0C0027AC */  sw         $a3, 0xC($at)
    /* 25B5C 8003535C 801F013C */  lui        $at, (0x1F800000 >> 16)
    /* 25B60 80035360 00003F8C */  lw         $ra, (0x1F800000 & 0xFFFF)($at)
    /* 25B64 80035364 25100000 */  or         $v0, $zero, $zero
    /* 25B68 80035368 0800E003 */  jr         $ra
    /* 25B6C 8003536C 00000000 */   nop
endlabel func_800351C8
