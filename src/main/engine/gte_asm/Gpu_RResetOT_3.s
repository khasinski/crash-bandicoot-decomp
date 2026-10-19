.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel Gpu_RResetOT_3
    /* 24A90 80034290 02008294 */  lhu        $v0, 0x2($a0)
    /* 24A94 80034294 0000A1A4 */  sh         $at, 0x0($a1)
    /* 24A98 80034298 04008194 */  lhu        $at, 0x4($a0)
    /* 24A9C 8003429C 0200A2A4 */  sh         $v0, 0x2($a1)
    /* 24AA0 800342A0 06008294 */  lhu        $v0, 0x6($a0)
    /* 24AA4 800342A4 0400A1A4 */  sh         $at, 0x4($a1)
    /* 24AA8 800342A8 0800E003 */  jr         $ra
    /* 24AAC 800342AC 0600A2A4 */   sh        $v0, 0x6($a1)
endlabel Gpu_RResetOT_3
