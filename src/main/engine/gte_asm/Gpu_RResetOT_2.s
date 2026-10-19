.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel Gpu_RResetOT_2
    /* 24A70 80034270 02008294 */  lhu        $v0, 0x2($a0)
    /* 24A74 80034274 0000A1A4 */  sh         $at, 0x0($a1)
    /* 24A78 80034278 04008194 */  lhu        $at, 0x4($a0)
    /* 24A7C 8003427C 0200A2A4 */  sh         $v0, 0x2($a1)
    /* 24A80 80034280 0800E003 */  jr         $ra
    /* 24A84 80034284 0400A1A4 */   sh        $at, 0x4($a1)
endlabel Gpu_RResetOT_2
    /* 24A88 80034288 00000000 */  nop
    /* 24A8C 8003428C 00000000 */  nop
