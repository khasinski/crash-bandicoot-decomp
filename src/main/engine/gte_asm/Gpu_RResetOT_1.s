.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel Gpu_RResetOT_1
    /* 24A50 80034250 02008294 */  lhu        $v0, 0x2($a0)
    /* 24A54 80034254 0000A1A4 */  sh         $at, 0x0($a1)
    /* 24A58 80034258 0800E003 */  jr         $ra
    /* 24A5C 8003425C 0200A2A4 */   sh        $v0, 0x2($a1)
endlabel Gpu_RResetOT_1
    /* 24A60 80034260 00000000 */  nop
    /* 24A64 80034264 00000000 */  nop
    /* 24A68 80034268 00000000 */  nop
    /* 24A6C 8003426C 00000000 */  nop
