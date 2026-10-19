.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

/* Handwritten function */

glabel Gpu_RResetOT
    /* 24AD8 800342D8 FF00083C */  lui        $t0, (0xFFFFFF >> 16)
    /* 24ADC 800342DC FFFF0835 */  ori        $t0, $t0, (0xFFFFFF & 0xFFFF)
    /* 24AE0 800342E0 24088800 */  and        $at, $a0, $t0
    /* 24AE4 800342E4 82290500 */  srl        $a1, $a1, 6
    /* 24AE8 800342E8 FFFFA524 */  addiu      $a1, $a1, -0x1
  .L800342EC:
    /* 24AEC 800342EC 04002124 */  addiu      $at, $at, 0x4
    /* 24AF0 800342F0 000081AC */  sw         $at, 0x0($a0)
    /* 24AF4 800342F4 04002124 */  addiu      $at, $at, 0x4
    /* 24AF8 800342F8 040081AC */  sw         $at, 0x4($a0)
    /* 24AFC 800342FC 04002124 */  addiu      $at, $at, 0x4
    /* 24B00 80034300 080081AC */  sw         $at, 0x8($a0)
    /* 24B04 80034304 04002124 */  addiu      $at, $at, 0x4
    /* 24B08 80034308 0C0081AC */  sw         $at, 0xC($a0)
    /* 24B0C 8003430C 04002124 */  addiu      $at, $at, 0x4
    /* 24B10 80034310 100081AC */  sw         $at, 0x10($a0)
    /* 24B14 80034314 04002124 */  addiu      $at, $at, 0x4
    /* 24B18 80034318 140081AC */  sw         $at, 0x14($a0)
    /* 24B1C 8003431C 04002124 */  addiu      $at, $at, 0x4
    /* 24B20 80034320 180081AC */  sw         $at, 0x18($a0)
    /* 24B24 80034324 04002124 */  addiu      $at, $at, 0x4
    /* 24B28 80034328 1C0081AC */  sw         $at, 0x1C($a0)
    /* 24B2C 8003432C 04002124 */  addiu      $at, $at, 0x4
    /* 24B30 80034330 200081AC */  sw         $at, 0x20($a0)
    /* 24B34 80034334 04002124 */  addiu      $at, $at, 0x4
    /* 24B38 80034338 240081AC */  sw         $at, 0x24($a0)
    /* 24B3C 8003433C 04002124 */  addiu      $at, $at, 0x4
    /* 24B40 80034340 280081AC */  sw         $at, 0x28($a0)
    /* 24B44 80034344 04002124 */  addiu      $at, $at, 0x4
    /* 24B48 80034348 2C0081AC */  sw         $at, 0x2C($a0)
    /* 24B4C 8003434C 04002124 */  addiu      $at, $at, 0x4
    /* 24B50 80034350 300081AC */  sw         $at, 0x30($a0)
    /* 24B54 80034354 04002124 */  addiu      $at, $at, 0x4
    /* 24B58 80034358 340081AC */  sw         $at, 0x34($a0)
    /* 24B5C 8003435C 04002124 */  addiu      $at, $at, 0x4
    /* 24B60 80034360 380081AC */  sw         $at, 0x38($a0)
    /* 24B64 80034364 04002124 */  addiu      $at, $at, 0x4
    /* 24B68 80034368 3C0081AC */  sw         $at, 0x3C($a0)
    /* 24B6C 8003436C 04002124 */  addiu      $at, $at, 0x4
    /* 24B70 80034370 400081AC */  sw         $at, 0x40($a0)
    /* 24B74 80034374 04002124 */  addiu      $at, $at, 0x4
    /* 24B78 80034378 440081AC */  sw         $at, 0x44($a0)
    /* 24B7C 8003437C 04002124 */  addiu      $at, $at, 0x4
    /* 24B80 80034380 480081AC */  sw         $at, 0x48($a0)
    /* 24B84 80034384 04002124 */  addiu      $at, $at, 0x4
    /* 24B88 80034388 4C0081AC */  sw         $at, 0x4C($a0)
    /* 24B8C 8003438C 04002124 */  addiu      $at, $at, 0x4
    /* 24B90 80034390 500081AC */  sw         $at, 0x50($a0)
    /* 24B94 80034394 04002124 */  addiu      $at, $at, 0x4
    /* 24B98 80034398 540081AC */  sw         $at, 0x54($a0)
    /* 24B9C 8003439C 04002124 */  addiu      $at, $at, 0x4
    /* 24BA0 800343A0 580081AC */  sw         $at, 0x58($a0)
    /* 24BA4 800343A4 04002124 */  addiu      $at, $at, 0x4
    /* 24BA8 800343A8 5C0081AC */  sw         $at, 0x5C($a0)
    /* 24BAC 800343AC 04002124 */  addiu      $at, $at, 0x4
    /* 24BB0 800343B0 600081AC */  sw         $at, 0x60($a0)
    /* 24BB4 800343B4 04002124 */  addiu      $at, $at, 0x4
    /* 24BB8 800343B8 640081AC */  sw         $at, 0x64($a0)
    /* 24BBC 800343BC 04002124 */  addiu      $at, $at, 0x4
    /* 24BC0 800343C0 680081AC */  sw         $at, 0x68($a0)
    /* 24BC4 800343C4 04002124 */  addiu      $at, $at, 0x4
    /* 24BC8 800343C8 6C0081AC */  sw         $at, 0x6C($a0)
    /* 24BCC 800343CC 04002124 */  addiu      $at, $at, 0x4
    /* 24BD0 800343D0 700081AC */  sw         $at, 0x70($a0)
    /* 24BD4 800343D4 04002124 */  addiu      $at, $at, 0x4
    /* 24BD8 800343D8 740081AC */  sw         $at, 0x74($a0)
    /* 24BDC 800343DC 04002124 */  addiu      $at, $at, 0x4
    /* 24BE0 800343E0 780081AC */  sw         $at, 0x78($a0)
    /* 24BE4 800343E4 04002124 */  addiu      $at, $at, 0x4
    /* 24BE8 800343E8 7C0081AC */  sw         $at, 0x7C($a0)
    /* 24BEC 800343EC 04002124 */  addiu      $at, $at, 0x4
    /* 24BF0 800343F0 800081AC */  sw         $at, 0x80($a0)
    /* 24BF4 800343F4 04002124 */  addiu      $at, $at, 0x4
    /* 24BF8 800343F8 840081AC */  sw         $at, 0x84($a0)
    /* 24BFC 800343FC 04002124 */  addiu      $at, $at, 0x4
    /* 24C00 80034400 880081AC */  sw         $at, 0x88($a0)
    /* 24C04 80034404 04002124 */  addiu      $at, $at, 0x4
    /* 24C08 80034408 8C0081AC */  sw         $at, 0x8C($a0)
    /* 24C0C 8003440C 04002124 */  addiu      $at, $at, 0x4
    /* 24C10 80034410 900081AC */  sw         $at, 0x90($a0)
    /* 24C14 80034414 04002124 */  addiu      $at, $at, 0x4
    /* 24C18 80034418 940081AC */  sw         $at, 0x94($a0)
    /* 24C1C 8003441C 04002124 */  addiu      $at, $at, 0x4
    /* 24C20 80034420 980081AC */  sw         $at, 0x98($a0)
    /* 24C24 80034424 04002124 */  addiu      $at, $at, 0x4
    /* 24C28 80034428 9C0081AC */  sw         $at, 0x9C($a0)
    /* 24C2C 8003442C 04002124 */  addiu      $at, $at, 0x4
    /* 24C30 80034430 A00081AC */  sw         $at, 0xA0($a0)
    /* 24C34 80034434 04002124 */  addiu      $at, $at, 0x4
    /* 24C38 80034438 A40081AC */  sw         $at, 0xA4($a0)
    /* 24C3C 8003443C 04002124 */  addiu      $at, $at, 0x4
    /* 24C40 80034440 A80081AC */  sw         $at, 0xA8($a0)
    /* 24C44 80034444 04002124 */  addiu      $at, $at, 0x4
    /* 24C48 80034448 AC0081AC */  sw         $at, 0xAC($a0)
    /* 24C4C 8003444C 04002124 */  addiu      $at, $at, 0x4
    /* 24C50 80034450 B00081AC */  sw         $at, 0xB0($a0)
    /* 24C54 80034454 04002124 */  addiu      $at, $at, 0x4
    /* 24C58 80034458 B40081AC */  sw         $at, 0xB4($a0)
    /* 24C5C 8003445C 04002124 */  addiu      $at, $at, 0x4
    /* 24C60 80034460 B80081AC */  sw         $at, 0xB8($a0)
    /* 24C64 80034464 04002124 */  addiu      $at, $at, 0x4
    /* 24C68 80034468 BC0081AC */  sw         $at, 0xBC($a0)
    /* 24C6C 8003446C 04002124 */  addiu      $at, $at, 0x4
    /* 24C70 80034470 C00081AC */  sw         $at, 0xC0($a0)
    /* 24C74 80034474 04002124 */  addiu      $at, $at, 0x4
    /* 24C78 80034478 C40081AC */  sw         $at, 0xC4($a0)
    /* 24C7C 8003447C 04002124 */  addiu      $at, $at, 0x4
    /* 24C80 80034480 C80081AC */  sw         $at, 0xC8($a0)
    /* 24C84 80034484 04002124 */  addiu      $at, $at, 0x4
    /* 24C88 80034488 CC0081AC */  sw         $at, 0xCC($a0)
    /* 24C8C 8003448C 04002124 */  addiu      $at, $at, 0x4
    /* 24C90 80034490 D00081AC */  sw         $at, 0xD0($a0)
    /* 24C94 80034494 04002124 */  addiu      $at, $at, 0x4
    /* 24C98 80034498 D40081AC */  sw         $at, 0xD4($a0)
    /* 24C9C 8003449C 04002124 */  addiu      $at, $at, 0x4
    /* 24CA0 800344A0 D80081AC */  sw         $at, 0xD8($a0)
    /* 24CA4 800344A4 04002124 */  addiu      $at, $at, 0x4
    /* 24CA8 800344A8 DC0081AC */  sw         $at, 0xDC($a0)
    /* 24CAC 800344AC 04002124 */  addiu      $at, $at, 0x4
    /* 24CB0 800344B0 E00081AC */  sw         $at, 0xE0($a0)
    /* 24CB4 800344B4 04002124 */  addiu      $at, $at, 0x4
    /* 24CB8 800344B8 E40081AC */  sw         $at, 0xE4($a0)
    /* 24CBC 800344BC 04002124 */  addiu      $at, $at, 0x4
    /* 24CC0 800344C0 E80081AC */  sw         $at, 0xE8($a0)
    /* 24CC4 800344C4 04002124 */  addiu      $at, $at, 0x4
    /* 24CC8 800344C8 EC0081AC */  sw         $at, 0xEC($a0)
    /* 24CCC 800344CC 04002124 */  addiu      $at, $at, 0x4
    /* 24CD0 800344D0 F00081AC */  sw         $at, 0xF0($a0)
    /* 24CD4 800344D4 04002124 */  addiu      $at, $at, 0x4
    /* 24CD8 800344D8 F40081AC */  sw         $at, 0xF4($a0)
    /* 24CDC 800344DC 04002124 */  addiu      $at, $at, 0x4
    /* 24CE0 800344E0 F80081AC */  sw         $at, 0xF8($a0)
    /* 24CE4 800344E4 04002124 */  addiu      $at, $at, 0x4
    /* 24CE8 800344E8 FC0081AC */  sw         $at, 0xFC($a0)
    /* 24CEC 800344EC 0300A010 */  beqz       $a1, .L800344FC
    /* 24CF0 800344F0 00018424 */   addiu     $a0, $a0, 0x100
    /* 24CF4 800344F4 7DFF0104 */  bgez       $zero, .L800342EC
    /* 24CF8 800344F8 FFFFA520 */   addi      $a1, $a1, -0x1 /* handwritten instruction */
  .L800344FC:
    /* 24CFC 800344FC 0800E003 */  jr         $ra
    /* 24D00 80034500 FCFF88AC */   sw        $t0, -0x4($a0)
endlabel Gpu_RResetOT
