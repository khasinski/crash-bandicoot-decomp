.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_80033F78
    /* 24778 80033F78 FAFFD395 */  lhu        $s3, -0x6($t6)
    /* 2477C 80033F7C F8FF32A6 */  sh         $s2, -0x8($s1)
    /* 24780 80033F80 FCFFD295 */  lhu        $s2, -0x4($t6)
    /* 24784 80033F84 FAFF33A6 */  sh         $s3, -0x6($s1)
    /* 24788 80033F88 FEFFD395 */  lhu        $s3, -0x2($t6)
    /* 2478C 80033F8C FCFF32A6 */  sh         $s2, -0x4($s1)
    /* 24790 80033F90 0800E003 */  jr         $ra
    /* 24794 80033F94 FEFF33A6 */   sh        $s3, -0x2($s1)
endlabel func_80033F78
