.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel func_80033F98
    /* 24798 80033F98 FFFF2120 */  addi       $at, $at, -0x1 /* handwritten instruction */
  .L80033F9C:
    /* 2479C 80033F9C 0000C795 */  lhu        $a3, 0x0($t6)
    /* 247A0 80033FA0 0200CE25 */  addiu      $t6, $t6, 0x2
    /* 247A4 80033FA4 000027A6 */  sh         $a3, 0x0($s1)
    /* 247A8 80033FA8 02003126 */  addiu      $s1, $s1, 0x2
    /* 247AC 80033FAC FBFF2014 */  bnez       $at, .L80033F9C
    /* 247B0 80033FB0 FFFF2120 */   addi      $at, $at, -0x1 /* handwritten instruction */
    /* 247B4 80033FB4 0800E003 */  jr         $ra
    /* 247B8 80033FB8 00000000 */   nop
endlabel func_80033F98
