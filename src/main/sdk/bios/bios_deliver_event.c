/* GCC_VERSION: 2.6.3 */
#include "common.h"

asm(
    ".include \"macro.inc\"\n"
    ".set noat\n"
    ".set noreorder\n"
    ".section .text, \"ax\"\n"
    "glabel func_80043354\n"
    "    addiu      $t2, $zero, 0xB0\n"
    "    jr         $t2\n"
    "     addiu     $t1, $zero, 0x7\n"
    "endlabel func_80043354\n"
    "    nop\n"
);
