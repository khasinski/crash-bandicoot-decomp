.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel Gpu_RResetOT_0
    /* 24A30 80034230 0800E003 */  jr         $ra
    /* 24A34 80034234 0000A1A4 */   sh        $at, 0x0($a1)
endlabel Gpu_RResetOT_0
    /* 24A38 80034238 00000000 */  nop
    /* 24A3C 8003423C 00000000 */  nop
    /* 24A40 80034240 00000000 */  nop
    /* 24A44 80034244 00000000 */  nop
    /* 24A48 80034248 00000000 */  nop
    /* 24A4C 8003424C 00000000 */  nop
