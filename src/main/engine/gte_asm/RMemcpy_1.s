.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel RMemcpy_1
    /* 24738 80033F38 FEFFD395 */  lhu        $s3, -0x2($t6)
    /* 2473C 80033F3C FCFF32A6 */  sh         $s2, -0x4($s1)
    /* 24740 80033F40 0800E003 */  jr         $ra
    /* 24744 80033F44 FEFF33A6 */   sh        $s3, -0x2($s1)
endlabel RMemcpy_1
    /* 24748 80033F48 00000000 */  nop
    /* 2474C 80033F4C 00000000 */  nop
    /* 24750 80033F50 00000000 */  nop
    /* 24754 80033F54 00000000 */  nop
