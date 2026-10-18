.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Writable engine/frame counter word placed in .text immediately after func_80034504. */
dlabel func_80034520
    /* 24D20 80034520 00000000 */  .word      0x00000000
enddlabel func_80034520
