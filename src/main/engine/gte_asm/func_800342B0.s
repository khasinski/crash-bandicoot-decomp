.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_800342B0
    /* 24AB0 800342B0 0700C010 */  beqz       $a2, .L800342D0
    /* 24AB4 800342B4 FFFFC624 */   addiu     $a2, $a2, -0x1
  .L800342B8:
    /* 24AB8 800342B8 00008194 */  lhu        $at, 0x0($a0)
    /* 24ABC 800342BC 02008424 */  addiu      $a0, $a0, 0x2
    /* 24AC0 800342C0 0000A1A4 */  sh         $at, 0x0($a1)
    /* 24AC4 800342C4 0200A524 */  addiu      $a1, $a1, 0x2
    /* 24AC8 800342C8 FBFFC014 */  bnez       $a2, .L800342B8
    /* 24ACC 800342CC FFFFC624 */   addiu     $a2, $a2, -0x1
  .L800342D0:
    /* 24AD0 800342D0 0800E003 */  jr         $ra
    /* 24AD4 800342D4 00000000 */   nop
endlabel func_800342B0
