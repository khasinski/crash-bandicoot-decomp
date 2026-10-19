.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel Gte_RExtendBound3
    /* 25B70 80035370 004C0100 */  sll        $t1, $at, 16
    /* 25B74 80035374 034C0900 */  sra        $t1, $t1, 16
    /* 25B78 80035378 2A402401 */  slt        $t0, $t1, $a0
    /* 25B7C 8003537C 02000011 */  beqz       $t0, .L80035388
    /* 25B80 80035380 2A40A900 */   slt       $t0, $a1, $t1
    /* 25B84 80035384 25200900 */  or         $a0, $zero, $t1
  .L80035388:
    /* 25B88 80035388 02000011 */  beqz       $t0, .L80035394
    /* 25B8C 8003538C 03440100 */   sra       $t0, $at, 16
    /* 25B90 80035390 25280900 */  or         $a1, $zero, $t1
  .L80035394:
    /* 25B94 80035394 2A480601 */  slt        $t1, $t0, $a2
    /* 25B98 80035398 02002011 */  beqz       $t1, .L800353A4
    /* 25B9C 8003539C 2A48E800 */   slt       $t1, $a3, $t0
    /* 25BA0 800353A0 25300800 */  or         $a2, $zero, $t0
  .L800353A4:
    /* 25BA4 800353A4 02002011 */  beqz       $t1, Gte_RExtendBound2
    /* 25BA8 800353A8 00000000 */   nop
    /* 25BAC 800353AC 25380800 */  or         $a3, $zero, $t0
endlabel Gte_RExtendBound3
