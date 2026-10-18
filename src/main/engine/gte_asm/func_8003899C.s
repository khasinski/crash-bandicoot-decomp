.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8003899C
    /* 2919C 8003899C 25188000 */  or         $v1, $a0, $zero
    /* 291A0 800389A0 01000104 */  bgez       $zero, func_800389A8
    /* 291A4 800389A4 2538A000 */   or        $a3, $a1, $zero
endlabel func_8003899C
