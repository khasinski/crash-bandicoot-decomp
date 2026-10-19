.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gte_RTransformWorldsDarkLoop
    /* 2759C 80036D9C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 275A0 80036DA0 00000000 */  nop
    /* 275A4 80036DA4 00000000 */  nop
    /* 275A8 80036DA8 1000784A */  dpcs
    /* 275AC 80036DAC 24987E02 */  and        $s3, $s3, $fp
    /* 275B0 80036DB0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 275B4 80036DB4 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 275B8 80036DB8 24E8BC03 */  and        $sp, $sp, $gp
    /* 275BC 80036DBC 25987D02 */  or         $s3, $s3, $sp
    /* 275C0 80036DC0 1000784A */  dpcs
    /* 275C4 80036DC4 24A09E02 */  and        $s4, $s4, $fp
    /* 275C8 80036DC8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 275CC 80036DCC 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 275D0 80036DD0 24E8BC03 */  and        $sp, $sp, $gp
    /* 275D4 80036DD4 25A09D02 */  or         $s4, $s4, $sp
    /* 275D8 80036DD8 1000784A */  dpcs
    /* 275DC 80036DDC 00000000 */  nop
    /* 275E0 80036DE0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 275E4 80036DE4 24A8BE02 */  and        $s5, $s5, $fp
    /* 275E8 80036DE8 24E8BC03 */  and        $sp, $sp, $gp
    /* 275EC 80036DEC E8000104 */  bgez       $zero, .L80037190
    /* 275F0 80036DF0 25A8BD02 */   or        $s5, $s5, $sp
    /* 275F4 80036DF4 00000000 */  nop
    /* 275F8 80036DF8 00000000 */  nop
    /* 275FC 80036DFC 00000000 */  nop
    /* 27600 80036E00 00000000 */  nop
    /* 27604 80036E04 00000000 */  nop
    /* 27608 80036E08 00000000 */  nop
    /* 2760C 80036E0C 00000000 */  nop
    /* 27610 80036E10 00000000 */  nop
    /* 27614 80036E14 00000000 */  nop
    /* 27618 80036E18 00000000 */  nop
    /* 2761C 80036E1C 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27620 80036E20 00000000 */  nop
    /* 27624 80036E24 24A09E02 */  and        $s4, $s4, $fp
    /* 27628 80036E28 1000784A */  dpcs
    /* 2762C 80036E2C 00000000 */  nop
    /* 27630 80036E30 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27634 80036E34 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 27638 80036E38 24E8BC03 */  and        $sp, $sp, $gp
    /* 2763C 80036E3C 25A09D02 */  or         $s4, $s4, $sp
    /* 27640 80036E40 1000784A */  dpcs
    /* 27644 80036E44 00000000 */  nop
    /* 27648 80036E48 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2764C 80036E4C 24A8BE02 */  and        $s5, $s5, $fp
    /* 27650 80036E50 24E8BC03 */  and        $sp, $sp, $gp
    /* 27654 80036E54 25A8BD02 */  or         $s5, $s5, $sp
    /* 27658 80036E58 10003D8D */  lw         $sp, 0x10($t1)
    /* 2765C 80036E5C 14003E8D */  lw         $fp, 0x14($t1)
    /* 27660 80036E60 18003F8D */  lw         $ra, 0x18($t1)
    /* 27664 80036E64 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 27668 80036E68 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 2766C 80036E6C 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 27670 80036E70 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 27674 80036E74 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27678 80036E78 27F08003 */  not        $fp, $gp
    /* 2767C 80036E7C 24987E02 */  and        $s3, $s3, $fp
    /* 27680 80036E80 1000784A */  dpcs
    /* 27684 80036E84 00000000 */  nop
    /* 27688 80036E88 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2768C 80036E8C 00000000 */  nop
    /* 27690 80036E90 24E8BC03 */  and        $sp, $sp, $gp
    /* 27694 80036E94 BE000104 */  bgez       $zero, .L80037190
    /* 27698 80036E98 25987D02 */   or        $s3, $s3, $sp
    /* 2769C 80036E9C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 276A0 80036EA0 00000000 */  nop
    /* 276A4 80036EA4 24987E02 */  and        $s3, $s3, $fp
    /* 276A8 80036EA8 1000784A */  dpcs
    /* 276AC 80036EAC 00000000 */  nop
    /* 276B0 80036EB0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 276B4 80036EB4 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 276B8 80036EB8 24E8BC03 */  and        $sp, $sp, $gp
    /* 276BC 80036EBC 25987D02 */  or         $s3, $s3, $sp
    /* 276C0 80036EC0 1000784A */  dpcs
    /* 276C4 80036EC4 00000000 */  nop
    /* 276C8 80036EC8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 276CC 80036ECC 24A8BE02 */  and        $s5, $s5, $fp
    /* 276D0 80036ED0 24E8BC03 */  and        $sp, $sp, $gp
    /* 276D4 80036ED4 25A8BD02 */  or         $s5, $s5, $sp
    /* 276D8 80036ED8 10003D8D */  lw         $sp, 0x10($t1)
    /* 276DC 80036EDC 14003E8D */  lw         $fp, 0x14($t1)
    /* 276E0 80036EE0 18003F8D */  lw         $ra, 0x18($t1)
    /* 276E4 80036EE4 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 276E8 80036EE8 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 276EC 80036EEC 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 276F0 80036EF0 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 276F4 80036EF4 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 276F8 80036EF8 27F08003 */  not        $fp, $gp
    /* 276FC 80036EFC 24A09E02 */  and        $s4, $s4, $fp
    /* 27700 80036F00 1000784A */  dpcs
    /* 27704 80036F04 00000000 */  nop
    /* 27708 80036F08 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2770C 80036F0C 00000000 */  nop
    /* 27710 80036F10 24E8BC03 */  and        $sp, $sp, $gp
    /* 27714 80036F14 9E000104 */  bgez       $zero, .L80037190
    /* 27718 80036F18 25A09D02 */   or        $s4, $s4, $sp
    /* 2771C 80036F1C 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 27720 80036F20 00000000 */  nop
    /* 27724 80036F24 24A8BE02 */  and        $s5, $s5, $fp
    /* 27728 80036F28 1000784A */  dpcs
    /* 2772C 80036F2C 00000000 */  nop
    /* 27730 80036F30 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27734 80036F34 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27738 80036F38 24E8BC03 */  and        $sp, $sp, $gp
    /* 2773C 80036F3C 25A8BD02 */  or         $s5, $s5, $sp
    /* 27740 80036F40 10003D8D */  lw         $sp, 0x10($t1)
    /* 27744 80036F44 14003E8D */  lw         $fp, 0x14($t1)
    /* 27748 80036F48 18003F8D */  lw         $ra, 0x18($t1)
    /* 2774C 80036F4C 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 27750 80036F50 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 27754 80036F54 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 27758 80036F58 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 2775C 80036F5C 27F08003 */  not        $fp, $gp
    /* 27760 80036F60 24987E02 */  and        $s3, $s3, $fp
    /* 27764 80036F64 1000784A */  dpcs
    /* 27768 80036F68 00000000 */  nop
    /* 2776C 80036F6C 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27770 80036F70 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27774 80036F74 24E8BC03 */  and        $sp, $sp, $gp
    /* 27778 80036F78 25987D02 */  or         $s3, $s3, $sp
    /* 2777C 80036F7C 24A09E02 */  and        $s4, $s4, $fp
    /* 27780 80036F80 1000784A */  dpcs
    /* 27784 80036F84 00000000 */  nop
    /* 27788 80036F88 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2778C 80036F8C 00000000 */  nop
    /* 27790 80036F90 24E8BC03 */  and        $sp, $sp, $gp
    /* 27794 80036F94 7E000104 */  bgez       $zero, .L80037190
    /* 27798 80036F98 25A09D02 */   or        $s4, $s4, $sp
    /* 2779C 80036F9C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 277A0 80036FA0 00000000 */  nop
    /* 277A4 80036FA4 24987E02 */  and        $s3, $s3, $fp
    /* 277A8 80036FA8 1000784A */  dpcs
    /* 277AC 80036FAC 00000000 */  nop
    /* 277B0 80036FB0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 277B4 80036FB4 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 277B8 80036FB8 24E8BC03 */  and        $sp, $sp, $gp
    /* 277BC 80036FBC 25987D02 */  or         $s3, $s3, $sp
    /* 277C0 80036FC0 1000784A */  dpcs
    /* 277C4 80036FC4 00000000 */  nop
    /* 277C8 80036FC8 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 277CC 80036FCC 24A09E02 */  and        $s4, $s4, $fp
    /* 277D0 80036FD0 24E8BC03 */  and        $sp, $sp, $gp
    /* 277D4 80036FD4 25A09D02 */  or         $s4, $s4, $sp
    /* 277D8 80036FD8 10003D8D */  lw         $sp, 0x10($t1)
    /* 277DC 80036FDC 14003E8D */  lw         $fp, 0x14($t1)
    /* 277E0 80036FE0 18003F8D */  lw         $ra, 0x18($t1)
    /* 277E4 80036FE4 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 277E8 80036FE8 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 277EC 80036FEC 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 277F0 80036FF0 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 277F4 80036FF4 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 277F8 80036FF8 27F08003 */  not        $fp, $gp
    /* 277FC 80036FFC 24A8BE02 */  and        $s5, $s5, $fp
    /* 27800 80037000 1000784A */  dpcs
    /* 27804 80037004 00000000 */  nop
    /* 27808 80037008 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2780C 8003700C 00000000 */  nop
    /* 27810 80037010 24E8BC03 */  and        $sp, $sp, $gp
    /* 27814 80037014 5E000104 */  bgez       $zero, .L80037190
    /* 27818 80037018 25A8BD02 */   or        $s5, $s5, $sp
    /* 2781C 8003701C 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27820 80037020 00000000 */  nop
    /* 27824 80037024 24A09E02 */  and        $s4, $s4, $fp
    /* 27828 80037028 1000784A */  dpcs
    /* 2782C 8003702C 00000000 */  nop
    /* 27830 80037030 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27834 80037034 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27838 80037038 24E8BC03 */  and        $sp, $sp, $gp
    /* 2783C 8003703C 25A09D02 */  or         $s4, $s4, $sp
    /* 27840 80037040 10003D8D */  lw         $sp, 0x10($t1)
    /* 27844 80037044 14003E8D */  lw         $fp, 0x14($t1)
    /* 27848 80037048 18003F8D */  lw         $ra, 0x18($t1)
    /* 2784C 8003704C 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 27850 80037050 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 27854 80037054 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 27858 80037058 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 2785C 8003705C 27F08003 */  not        $fp, $gp
    /* 27860 80037060 24987E02 */  and        $s3, $s3, $fp
    /* 27864 80037064 1000784A */  dpcs
    /* 27868 80037068 00000000 */  nop
    /* 2786C 8003706C 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27870 80037070 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 27874 80037074 24E8BC03 */  and        $sp, $sp, $gp
    /* 27878 80037078 25987D02 */  or         $s3, $s3, $sp
    /* 2787C 8003707C 24A8BE02 */  and        $s5, $s5, $fp
    /* 27880 80037080 1000784A */  dpcs
    /* 27884 80037084 00000000 */  nop
    /* 27888 80037088 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2788C 8003708C 00000000 */  nop
    /* 27890 80037090 24E8BC03 */  and        $sp, $sp, $gp
    /* 27894 80037094 3E000104 */  bgez       $zero, .L80037190
    /* 27898 80037098 25A8BD02 */   or        $s5, $s5, $sp
    /* 2789C 8003709C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 278A0 800370A0 00000000 */  nop
    /* 278A4 800370A4 24987E02 */  and        $s3, $s3, $fp
    /* 278A8 800370A8 1000784A */  dpcs
    /* 278AC 800370AC 00000000 */  nop
    /* 278B0 800370B0 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 278B4 800370B4 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 278B8 800370B8 24E8BC03 */  and        $sp, $sp, $gp
    /* 278BC 800370BC 25987D02 */  or         $s3, $s3, $sp
    /* 278C0 800370C0 10003D8D */  lw         $sp, 0x10($t1)
    /* 278C4 800370C4 14003E8D */  lw         $fp, 0x14($t1)
    /* 278C8 800370C8 18003F8D */  lw         $ra, 0x18($t1)
    /* 278CC 800370CC 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 278D0 800370D0 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 278D4 800370D4 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 278D8 800370D8 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 278DC 800370DC 27F08003 */  not        $fp, $gp
    /* 278E0 800370E0 24A09E02 */  and        $s4, $s4, $fp
    /* 278E4 800370E4 1000784A */  dpcs
    /* 278E8 800370E8 00000000 */  nop
    /* 278EC 800370EC 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 278F0 800370F0 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 278F4 800370F4 24E8BC03 */  and        $sp, $sp, $gp
    /* 278F8 800370F8 25A09D02 */  or         $s4, $s4, $sp
    /* 278FC 800370FC 24A8BE02 */  and        $s5, $s5, $fp
    /* 27900 80037100 1000784A */  dpcs
    /* 27904 80037104 00000000 */  nop
    /* 27908 80037108 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2790C 8003710C 00000000 */  nop
    /* 27910 80037110 24E8BC03 */  and        $sp, $sp, $gp
    /* 27914 80037114 1E000104 */  bgez       $zero, .L80037190
    /* 27918 80037118 25A8BD02 */   or        $s5, $s5, $sp
    /* 2791C 8003711C 10003D8D */  lw         $sp, 0x10($t1)
    /* 27920 80037120 14003E8D */  lw         $fp, 0x14($t1)
    /* 27924 80037124 18003F8D */  lw         $ra, 0x18($t1)
    /* 27928 80037128 1C0028C9 */  lwc2       $8, 0x1C($t1)
    /* 2792C 8003712C 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 27930 80037130 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 27934 80037134 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 27938 80037138 27F08003 */  not        $fp, $gp
    /* 2793C 8003713C 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27940 80037140 00000000 */  nop
    /* 27944 80037144 00000000 */  nop
    /* 27948 80037148 1000784A */  dpcs
    /* 2794C 8003714C 24987E02 */  and        $s3, $s3, $fp
    /* 27950 80037150 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27954 80037154 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27958 80037158 24E8BC03 */  and        $sp, $sp, $gp
    /* 2795C 8003715C 25987D02 */  or         $s3, $s3, $sp
    /* 27960 80037160 1000784A */  dpcs
    /* 27964 80037164 24A09E02 */  and        $s4, $s4, $fp
    /* 27968 80037168 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 2796C 8003716C 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 27970 80037170 24E8BC03 */  and        $sp, $sp, $gp
    /* 27974 80037174 25A09D02 */  or         $s4, $s4, $sp
    /* 27978 80037178 1000784A */  dpcs
    /* 2797C 8003717C 00000000 */  nop
    /* 27980 80037180 00B01D48 */  mfc2       $sp, $22 /* handwritten instruction */
    /* 27984 80037184 24A8BE02 */  and        $s5, $s5, $fp
    /* 27988 80037188 24E8BC03 */  and        $sp, $sp, $gp
    /* 2798C 8003718C 25A8BD02 */  or         $s5, $s5, $sp
  .L80037190:
    /* 27990 80037190 9C003D8D */  lw         $sp, 0x9C($t1)
    /* 27994 80037194 A0003E8D */  lw         $fp, 0xA0($t1)
    /* 27998 80037198 A4003F8D */  lw         $ra, 0xA4($t1)
    /* 2799C 8003719C 00A8DD48 */  ctc2       $sp, $21 /* handwritten instruction */
    /* 279A0 800371A0 00B0DE48 */  ctc2       $fp, $22 /* handwritten instruction */
    /* 279A4 800371A4 00B8DF48 */  ctc2       $ra, $23 /* handwritten instruction */
    /* 279A8 800371A8 F8FF013C */  lui        $at, (0xFFF8FFF8 >> 16)
    /* 279AC 800371AC F8FF2134 */  ori        $at, $at, (0xFFF8FFF8 & 0xFFFF)
    /* 279B0 800371B0 24E80102 */  and        $sp, $s0, $at
    /* 279B4 800371B4 24F02102 */  and        $fp, $s1, $at
    /* 279B8 800371B8 24F84102 */  and        $ra, $s2, $at
    /* 279BC 800371BC 00009D48 */  mtc2       $sp, $0 /* handwritten instruction */
    /* 279C0 800371C0 00109E48 */  mtc2       $fp, $2 /* handwritten instruction */
    /* 279C4 800371C4 00209F48 */  mtc2       $ra, $4 /* handwritten instruction */
    /* 279C8 800371C8 0700013C */  lui        $at, (0x70006 >> 16)
    /* 279CC 800371CC 06002134 */  ori        $at, $at, (0x70006 & 0xFFFF)
    /* 279D0 800371D0 02EE1300 */  srl        $sp, $s3, 24
    /* 279D4 800371D4 C0E81D00 */  sll        $sp, $sp, 3
    /* 279D8 800371D8 24800102 */  and        $s0, $s0, $at
    /* 279DC 800371DC 804A1000 */  sll        $t1, $s0, 10
    /* 279E0 800371E0 25E8A903 */  or         $sp, $sp, $t1
    /* 279E4 800371E4 C2481000 */  srl        $t1, $s0, 3
    /* 279E8 800371E8 25E8A903 */  or         $sp, $sp, $t1
    /* 279EC 800371EC 02F61400 */  srl        $fp, $s4, 24
    /* 279F0 800371F0 C0F01E00 */  sll        $fp, $fp, 3
    /* 279F4 800371F4 24882102 */  and        $s1, $s1, $at
    /* 279F8 800371F8 804A1100 */  sll        $t1, $s1, 10
    /* 279FC 800371FC 25F0C903 */  or         $fp, $fp, $t1
    /* 27A00 80037200 C2481100 */  srl        $t1, $s1, 3
    /* 27A04 80037204 25F0C903 */  or         $fp, $fp, $t1
    /* 27A08 80037208 02FE1500 */  srl        $ra, $s5, 24
    /* 27A0C 8003720C C0F81F00 */  sll        $ra, $ra, 3
    /* 27A10 80037210 24904102 */  and        $s2, $s2, $at
    /* 27A14 80037214 804A1200 */  sll        $t1, $s2, 10
    /* 27A18 80037218 25F8E903 */  or         $ra, $ra, $t1
    /* 27A1C 8003721C C2481200 */  srl        $t1, $s2, 3
    /* 27A20 80037220 25F8E903 */  or         $ra, $ra, $t1
    /* 27A24 80037224 00089D48 */  mtc2       $sp, $1 /* handwritten instruction */
    /* 27A28 80037228 00189E48 */  mtc2       $fp, $3 /* handwritten instruction */
    /* 27A2C 8003722C 00289F48 */  mtc2       $ra, $5 /* handwritten instruction */
    /* 27A30 80037230 02F50200 */  srl        $fp, $v0, 20
    /* 27A34 80037234 3000284A */  rtpt
    /* 27A38 80037238 80F01E00 */  sll        $fp, $fp, 2
    /* 27A3C 8003723C 21703E03 */  addu       $t6, $t9, $fp
    /* 27A40 80037240 0000C98D */  lw         $t1, 0x0($t6)
    /* 27A44 80037244 0034123C */  lui        $s2, (0x34000000 >> 16)
    /* 27A48 80037248 024E0900 */  srl        $t1, $t1, 24
    /* 27A4C 8003724C 80003D31 */  andi       $sp, $t1, 0x80
    /* 27A50 80037250 8800A013 */  beqz       $sp, .L80037474
    /* 27A54 80037254 00000000 */   nop
    /* 27A58 80037258 08006CE9 */  swc2       $12, 0x8($t3)
    /* 27A5C 8003725C 14006DE9 */  swc2       $13, 0x14($t3)
    /* 27A60 80037260 20006EE9 */  swc2       $14, 0x20($t3)
    /* 27A64 80037264 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 27A68 80037268 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27A6C 8003726C 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 27A70 80037270 0700C013 */  beqz       $fp, .L80037290
    /* 27A74 80037274 23F0A703 */   subu      $fp, $sp, $a3
    /* 27A78 80037278 04F09E00 */  sllv       $fp, $fp, $a0
    /* 27A7C 8003727C 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 27A80 80037280 00000000 */  nop
    /* 27A84 80037284 1000784A */  dpcs
    /* 27A88 80037288 00000000 */  nop
    /* 27A8C 8003728C 00B01348 */  mfc2       $s3, $22 /* handwritten instruction */
  .L80037290:
    /* 27A90 80037290 00901F48 */  mfc2       $ra, $18 /* handwritten instruction */
    /* 27A94 80037294 00000000 */  nop
    /* 27A98 80037298 2188BF03 */  addu       $s1, $sp, $ra
    /* 27A9C 8003729C 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27AA0 800372A0 2AF0FF00 */  slt        $fp, $a3, $ra
    /* 27AA4 800372A4 0700C013 */  beqz       $fp, .L800372C4
    /* 27AA8 800372A8 23F0E703 */   subu      $fp, $ra, $a3
    /* 27AAC 800372AC 04F09E00 */  sllv       $fp, $fp, $a0
    /* 27AB0 800372B0 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 27AB4 800372B4 00000000 */  nop
    /* 27AB8 800372B8 1000784A */  dpcs
    /* 27ABC 800372BC 00000000 */  nop
    /* 27AC0 800372C0 00B01448 */  mfc2       $s4, $22 /* handwritten instruction */
  .L800372C4:
    /* 27AC4 800372C4 00981D48 */  mfc2       $sp, $19 /* handwritten instruction */
    /* 27AC8 800372C8 00000000 */  nop
    /* 27ACC 800372CC 21883D02 */  addu       $s1, $s1, $sp
    /* 27AD0 800372D0 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 27AD4 800372D4 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 27AD8 800372D8 0700C013 */  beqz       $fp, .L800372F8
    /* 27ADC 800372DC 23F0A703 */   subu      $fp, $sp, $a3
    /* 27AE0 800372E0 04F09E00 */  sllv       $fp, $fp, $a0
    /* 27AE4 800372E4 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 27AE8 800372E8 00000000 */  nop
    /* 27AEC 800372EC 1000784A */  dpcs
    /* 27AF0 800372F0 00000000 */  nop
    /* 27AF4 800372F4 00B01548 */  mfc2       $s5, $22 /* handwritten instruction */
  .L800372F8:
    /* 27AF8 800372F8 42891100 */  srl        $s1, $s1, 5
    /* 27AFC 800372FC 80881100 */  sll        $s1, $s1, 2
    /* 27B00 80037300 24987C02 */  and        $s3, $s3, $gp
    /* 27B04 80037304 24F02F01 */  and        $fp, $t1, $t7
    /* 27B08 80037308 0300CF13 */  beq        $fp, $t7, .L80037318
    /* 27B0C 8003730C 25987202 */   or        $s3, $s3, $s2
    /* 27B10 80037310 00021E3C */  lui        $fp, (0x2000000 >> 16)
    /* 27B14 80037314 25987E02 */  or         $s3, $s3, $fp
  .L80037318:
    /* 27B18 80037318 040073AD */  sw         $s3, 0x4($t3)
    /* 27B1C 8003731C 100074AD */  sw         $s4, 0x10($t3)
    /* 27B20 80037320 1C0075AD */  sw         $s5, 0x1C($t3)
    /* 27B24 80037324 C2FB0200 */  srl        $ra, $v0, 15
    /* 27B28 80037328 1C00FF33 */  andi       $ra, $ra, 0x1C
    /* 27B2C 8003732C 80E90C00 */  sll        $sp, $t4, 6
    /* 27B30 80037330 21E8A803 */  addu       $sp, $sp, $t0
    /* 27B34 80037334 2000BD27 */  addiu      $sp, $sp, 0x20
    /* 27B38 80037338 2108FD03 */  addu       $at, $ra, $sp
    /* 27B3C 8003733C 1E005F30 */  andi       $ra, $v0, 0x1E
    /* 27B40 80037340 0D00E013 */  beqz       $ra, .L80037378
    /* 27B44 80037344 42E90200 */   srl       $sp, $v0, 5
    /* 27B48 80037348 801F1E3C */  lui        $fp, (0x1F8000E0 >> 16)
    /* 27B4C 8003734C E000DE37 */  ori        $fp, $fp, (0x1F8000E0 & 0xFFFF)
    /* 27B50 80037350 0000DE8F */  lw         $fp, 0x0($fp)
    /* 27B54 80037354 0700BD33 */  andi       $sp, $sp, 0x7
    /* 27B58 80037358 06F0BE03 */  srlv       $fp, $fp, $sp
    /* 27B5C 8003735C 02EB0200 */  srl        $sp, $v0, 12
    /* 27B60 80037360 1F00BD33 */  andi       $sp, $sp, 0x1F
    /* 27B64 80037364 21E8DD03 */  addu       $sp, $fp, $sp
    /* 27B68 80037368 0100FE37 */  ori        $fp, $ra, 0x1
    /* 27B6C 8003736C 24E8BE03 */  and        $sp, $sp, $fp
    /* 27B70 80037370 80E81D00 */  sll        $sp, $sp, 2
    /* 27B74 80037374 2170AE03 */  addu       $t6, $sp, $t6
  .L80037378:
    /* 27B78 80037378 0400D38D */  lw         $s3, 0x4($t6)
    /* 27B7C 8003737C 0000348C */  lw         $s4, 0x0($at)
    /* 27B80 80037380 82ED1300 */  srl        $sp, $s3, 22
    /* 27B84 80037384 C0E81D00 */  sll        $sp, $sp, 3
    /* 27B88 80037388 2170DD02 */  addu       $t6, $s6, $sp
    /* 27B8C 8003738C 0000D08D */  lw         $s0, 0x0($t6)
    /* 27B90 80037390 0400CE95 */  lhu        $t6, 0x4($t6)
    /* 27B94 80037394 02AD1300 */  srl        $s5, $s3, 20
    /* 27B98 80037398 0300B532 */  andi       $s5, $s5, 0x3
    /* 27B9C 8003739C C0E91500 */  sll        $sp, $s5, 7
    /* 27BA0 800373A0 1C009E32 */  andi       $fp, $s4, 0x1C
    /* 27BA4 800373A4 25E8BE03 */  or         $sp, $sp, $fp
    /* 27BA8 800373A8 82F41300 */  srl        $fp, $s3, 18
    /* 27BAC 800373AC 0300DE33 */  andi       $fp, $fp, 0x3
    /* 27BB0 800373B0 25E8BE03 */  or         $sp, $sp, $fp
    /* 27BB4 800373B4 60003E31 */  andi       $fp, $t1, 0x60
    /* 27BB8 800373B8 25E8BE03 */  or         $sp, $sp, $fp
    /* 27BBC 800373BC 00EC1D00 */  sll        $sp, $sp, 16
    /* 27BC0 800373C0 1F007E32 */  andi       $fp, $s3, 0x1F
    /* 27BC4 800373C4 80F01E00 */  sll        $fp, $fp, 2
    /* 27BC8 800373C8 80009F32 */  andi       $ra, $s4, 0x80
    /* 27BCC 800373CC 25F0DF03 */  or         $fp, $fp, $ra
    /* 27BD0 800373D0 00FA1E00 */  sll        $ra, $fp, 8
    /* 27BD4 800373D4 82F21300 */  srl        $fp, $s3, 10
    /* 27BD8 800373D8 F800DE33 */  andi       $fp, $fp, 0xF8
    /* 27BDC 800373DC 06F0BE02 */  srlv       $fp, $fp, $s5
    /* 27BE0 800373E0 25A8DF03 */  or         $s5, $fp, $ra
    /* 27BE4 800373E4 02F41000 */  srl        $fp, $s0, 16
    /* 27BE8 800373E8 21F0D503 */  addu       $fp, $fp, $s5
    /* 27BEC 800373EC 25F8BE03 */  or         $ra, $sp, $fp
    /* 27BF0 800373F0 0F003D31 */  andi       $sp, $t1, 0xF
    /* 27BF4 800373F4 C01F7E32 */  andi       $fp, $s3, 0x1FC0
    /* 27BF8 800373F8 25E8BE03 */  or         $sp, $sp, $fp
    /* 27BFC 800373FC 02F11400 */  srl        $fp, $s4, 4
    /* 27C00 80037400 F0FFDE33 */  andi       $fp, $fp, 0xFFF0
    /* 27C04 80037404 25E8BE03 */  or         $sp, $sp, $fp
    /* 27C08 80037408 00EC1D00 */  sll        $sp, $sp, 16
    /* 27C0C 8003740C FFFF1E32 */  andi       $fp, $s0, 0xFFFF
    /* 27C10 80037410 21F0D503 */  addu       $fp, $fp, $s5
    /* 27C14 80037414 25F0BE03 */  or         $fp, $sp, $fp
    /* 27C18 80037418 2170D501 */  addu       $t6, $t6, $s5
    /* 27C1C 8003741C 0C007EAD */  sw         $fp, 0xC($t3)
    /* 27C20 80037420 18007FAD */  sw         $ra, 0x18($t3)
    /* 27C24 80037424 24006EA5 */  sh         $t6, 0x24($t3)
    /* 27C28 80037428 22E8D100 */  sub        $sp, $a2, $s1 /* handwritten instruction */
    /* 27C2C 8003742C FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 27C30 80037430 2AF0A303 */  slt        $fp, $sp, $v1
    /* 27C34 80037434 0600C013 */  beqz       $fp, .L80037450
    /* 27C38 80037438 2170A300 */   addu      $t6, $a1, $v1
    /* 27C3C 8003743C 2118A003 */  addu       $v1, $sp, $zero
    /* 27C40 80037440 03006104 */  bgez       $v1, .L80037450
    /* 27C44 80037444 2170A300 */   addu      $t6, $a1, $v1
    /* 27C48 80037448 21180000 */  addu       $v1, $zero, $zero
    /* 27C4C 8003744C 2170A300 */  addu       $t6, $a1, $v1
  .L80037450:
    /* 27C50 80037450 0000DD8D */  lw         $sp, 0x0($t6)
    /* 27C54 80037454 24F07C01 */  and        $fp, $t3, $gp
    /* 27C58 80037458 0000DEAD */  sw         $fp, 0x0($t6)
    /* 27C5C 8003745C 00091F3C */  lui        $ra, (0x9000000 >> 16)
    /* 27C60 80037460 25E8BF03 */  or         $sp, $sp, $ra
    /* 27C64 80037464 00007DAD */  sw         $sp, 0x0($t3)
    /* 27C68 80037468 28006B25 */  addiu      $t3, $t3, 0x28
    /* 27C6C 8003746C 42000104 */  bgez       $zero, .L80037578
    /* 27C70 80037470 00000000 */   nop
  .L80037474:
    /* 27C74 80037474 08006CE9 */  swc2       $12, 0x8($t3)
    /* 27C78 80037478 10006DE9 */  swc2       $13, 0x10($t3)
    /* 27C7C 8003747C 18006EE9 */  swc2       $14, 0x18($t3)
    /* 27C80 80037480 00881D48 */  mfc2       $sp, $17 /* handwritten instruction */
    /* 27C84 80037484 00309348 */  mtc2       $s3, $6 /* handwritten instruction */
    /* 27C88 80037488 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 27C8C 8003748C 0700C013 */  beqz       $fp, .L800374AC
    /* 27C90 80037490 23F0A703 */   subu      $fp, $sp, $a3
    /* 27C94 80037494 04F09E00 */  sllv       $fp, $fp, $a0
    /* 27C98 80037498 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 27C9C 8003749C 00000000 */  nop
    /* 27CA0 800374A0 1000784A */  dpcs
    /* 27CA4 800374A4 00000000 */  nop
    /* 27CA8 800374A8 00B01348 */  mfc2       $s3, $22 /* handwritten instruction */
  .L800374AC:
    /* 27CAC 800374AC 00901F48 */  mfc2       $ra, $18 /* handwritten instruction */
    /* 27CB0 800374B0 00000000 */  nop
    /* 27CB4 800374B4 2188BF03 */  addu       $s1, $sp, $ra
    /* 27CB8 800374B8 00309448 */  mtc2       $s4, $6 /* handwritten instruction */
    /* 27CBC 800374BC 2AF0FF00 */  slt        $fp, $a3, $ra
    /* 27CC0 800374C0 0700C013 */  beqz       $fp, .L800374E0
    /* 27CC4 800374C4 23F0E703 */   subu      $fp, $ra, $a3
    /* 27CC8 800374C8 04F09E00 */  sllv       $fp, $fp, $a0
    /* 27CCC 800374CC 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 27CD0 800374D0 00000000 */  nop
    /* 27CD4 800374D4 1000784A */  dpcs
    /* 27CD8 800374D8 00000000 */  nop
    /* 27CDC 800374DC 00B01448 */  mfc2       $s4, $22 /* handwritten instruction */
  .L800374E0:
    /* 27CE0 800374E0 00981D48 */  mfc2       $sp, $19 /* handwritten instruction */
    /* 27CE4 800374E4 00000000 */  nop
    /* 27CE8 800374E8 21883D02 */  addu       $s1, $s1, $sp
    /* 27CEC 800374EC 00309548 */  mtc2       $s5, $6 /* handwritten instruction */
    /* 27CF0 800374F0 2AF0FD00 */  slt        $fp, $a3, $sp
    /* 27CF4 800374F4 0700C013 */  beqz       $fp, .L80037514
    /* 27CF8 800374F8 23F0A703 */   subu      $fp, $sp, $a3
    /* 27CFC 800374FC 04F09E00 */  sllv       $fp, $fp, $a0
    /* 27D00 80037500 00409E48 */  mtc2       $fp, $8 /* handwritten instruction */
    /* 27D04 80037504 00000000 */  nop
    /* 27D08 80037508 1000784A */  dpcs
    /* 27D0C 8003750C 00000000 */  nop
    /* 27D10 80037510 00B01548 */  mfc2       $s5, $22 /* handwritten instruction */
  .L80037514:
    /* 27D14 80037514 42891100 */  srl        $s1, $s1, 5
    /* 27D18 80037518 80881100 */  sll        $s1, $s1, 2
    /* 27D1C 8003751C 24987C02 */  and        $s3, $s3, $gp
    /* 27D20 80037520 0030123C */  lui        $s2, (0x30000000 >> 16)
    /* 27D24 80037524 25987202 */  or         $s3, $s3, $s2
    /* 27D28 80037528 040073AD */  sw         $s3, 0x4($t3)
    /* 27D2C 8003752C 0C0074AD */  sw         $s4, 0xC($t3)
    /* 27D30 80037530 140075AD */  sw         $s5, 0x14($t3)
    /* 27D34 80037534 22E8D100 */  sub        $sp, $a2, $s1 /* handwritten instruction */
    /* 27D38 80037538 FC1FBD33 */  andi       $sp, $sp, 0x1FFC
    /* 27D3C 8003753C 2AF0A303 */  slt        $fp, $sp, $v1
    /* 27D40 80037540 0600C013 */  beqz       $fp, .L8003755C
    /* 27D44 80037544 2170A300 */   addu      $t6, $a1, $v1
    /* 27D48 80037548 2118A003 */  addu       $v1, $sp, $zero
    /* 27D4C 8003754C 03006104 */  bgez       $v1, .L8003755C
    /* 27D50 80037550 2170A300 */   addu      $t6, $a1, $v1
    /* 27D54 80037554 21180000 */  addu       $v1, $zero, $zero
    /* 27D58 80037558 2170A300 */  addu       $t6, $a1, $v1
  .L8003755C:
    /* 27D5C 8003755C 0000DD8D */  lw         $sp, 0x0($t6)
    /* 27D60 80037560 24F07C01 */  and        $fp, $t3, $gp
    /* 27D64 80037564 0000DEAD */  sw         $fp, 0x0($t6)
    /* 27D68 80037568 00061E3C */  lui        $fp, (0x6000000 >> 16)
    /* 27D6C 8003756C 25E8BE03 */  or         $sp, $sp, $fp
    /* 27D70 80037570 00007DAD */  sw         $sp, 0x0($t3)
    /* 27D74 80037574 1C006B25 */  addiu      $t3, $t3, 0x1C
  .L80037578:
    /* 27D78 80037578 FFFFAD25 */  addiu      $t5, $t5, -0x1
    /* 27D7C 8003757C CBFDA015 */  bnez       $t5, .L80036CAC
    /* 27D80 80037580 00004195 */   lhu       $at, 0x0($t2)
    /* 27D84 80037584 00000000 */  nop
    /* 27D88 80037588 801F013C */  lui        $at, (0x1F800034 >> 16)
    /* 27D8C 8003758C 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 27D90 80037590 00000000 */  nop
    /* 27D94 80037594 1000A18F */  lw         $at, 0x10($sp)
    /* 27D98 80037598 00000000 */  nop
    /* 27D9C 8003759C 00002BAC */  sw         $t3, 0x0($at)
    /* 27DA0 800375A0 801F013C */  lui        $at, (0x1F800038 >> 16)
    /* 27DA4 800375A4 0000308C */  lw         $s0, (0x1F800000 & 0xFFFF)($at)
    /* 27DA8 800375A8 0400318C */  lw         $s1, (0x1F800004 & 0xFFFF)($at)
    /* 27DAC 800375AC 0800328C */  lw         $s2, (0x1F800008 & 0xFFFF)($at)
    /* 27DB0 800375B0 0C00338C */  lw         $s3, (0x1F80000C & 0xFFFF)($at)
    /* 27DB4 800375B4 1000348C */  lw         $s4, (0x1F800010 & 0xFFFF)($at)
    /* 27DB8 800375B8 1400358C */  lw         $s5, (0x1F800014 & 0xFFFF)($at)
    /* 27DBC 800375BC 1800368C */  lw         $s6, (0x1F800018 & 0xFFFF)($at)
    /* 27DC0 800375C0 1C00378C */  lw         $s7, (0x1F80001C & 0xFFFF)($at)
    /* 27DC4 800375C4 2000388C */  lw         $t8, (0x1F800020 & 0xFFFF)($at)
    /* 27DC8 800375C8 2400398C */  lw         $t9, (0x1F800024 & 0xFFFF)($at)
    /* 27DCC 800375CC 28003A8C */  lw         $k0, (0x1F800028 & 0xFFFF)($at) /* handwritten instruction */
    /* 27DD0 800375D0 2C003B8C */  lw         $k1, (0x1F80002C & 0xFFFF)($at) /* handwritten instruction */
    /* 27DD4 800375D4 30003C8C */  lw         $gp, (0x1F800030 & 0xFFFF)($at)
    /* 27DD8 800375D8 34003D8C */  lw         $sp, (0x1F800034 & 0xFFFF)($at)
    /* 27DDC 800375DC 3C003F8C */  lw         $ra, (0x1F80003C & 0xFFFF)($at)
    /* 27DE0 800375E0 38003E8C */  lw         $fp, (0x1F800038 & 0xFFFF)($at)
    /* 27DE4 800375E4 0800E003 */  jr         $ra
    /* 27DE8 800375E8 00000000 */   nop
endlabel Gte_RTransformWorldsDarkLoop
