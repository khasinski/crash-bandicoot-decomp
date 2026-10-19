.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel RMemcpy_2
    /* 24758 80033F58 FCFFD395 */  lhu        $s3, -0x4($t6)
    /* 2475C 80033F5C FAFF32A6 */  sh         $s2, -0x6($s1)
    /* 24760 80033F60 FEFFD295 */  lhu        $s2, -0x2($t6)
    /* 24764 80033F64 FCFF33A6 */  sh         $s3, -0x4($s1)
    /* 24768 80033F68 0800E003 */  jr         $ra
    /* 2476C 80033F6C FEFF32A6 */   sh        $s2, -0x2($s1)
endlabel RMemcpy_2
    /* 24770 80033F70 00000000 */  nop
    /* 24774 80033F74 00000000 */  nop
