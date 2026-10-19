.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel RMemcpy_0
    /* 24718 80033F18 0800E003 */  jr         $ra
    /* 2471C 80033F1C FEFF32A6 */   sh        $s2, -0x2($s1)
endlabel RMemcpy_0
    /* 24720 80033F20 00000000 */  nop
    /* 24724 80033F24 00000000 */  nop
    /* 24728 80033F28 00000000 */  nop
    /* 2472C 80033F2C 00000000 */  nop
    /* 24730 80033F30 00000000 */  nop
    /* 24734 80033F34 00000000 */  nop
