#ifndef CRASH_PSYQ_BIOS_H
#define CRASH_PSYQ_BIOS_H

/*
 * Sony PSY-Q BIOS A0/B0/C0 vector veneers.
 *
 * Each veneer is a 16-byte (4-word) assembled object in libc.lib / libapi.lib /
 * libcard.lib that loads the vector address (0xA0, 0xB0, or 0xC0) into $t2 and
 * jumps to it with the service selector in $t1 in the branch delay slot,
 * followed by a 4-byte padding nop.
 */
#define PSYQ_BIOS_TRAMPOLINE(name, table, selector) \
    asm( \
        ".include \"macro.inc\"\n" \
        ".set noat\n" \
        ".set noreorder\n" \
        ".section .text, \"ax\"\n" \
        "glabel " #name "\n" \
        "    addiu $t2, $zero, " #table "\n" \
        "    jr $t2\n" \
        "    addiu $t1, $zero, " #selector "\n" \
        "endlabel " #name "\n" \
        "    nop\n")

#endif
