#ifndef CRASH_INCLUDE_ASM_H
#define CRASH_INCLUDE_ASM_H

#if !defined(M2CTX) && !defined(PERMUTER)

/*
 * INCLUDE_ASM(FOLDER, NAME) pulls the not-yet-decompiled function NAME from
 * asm/USA/main/nonmatchings/FOLDER/NAME.s into a C translation unit, so a unit
 * can be decompiled one function at a time while the build stays byte-exact.
 *
 * Crash is compiled with a non-zero -G. gcc 2.6.3 then emits every function
 * after the data definitions, which would move a plain file-scope __asm__
 * block. Wrapping it in a __maspsx_include_asm_hack_ function with
 * "maspsx-keep" lines is the documented maspsx workaround.
 */
#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME) \
    void __maspsx_include_asm_hack_##NAME(void) { \
        __asm__( \
            ".text # maspsx-keep\n" \
            "\t.align\t2 # maspsx-keep\n" \
            "\t.set\tnoreorder # maspsx-keep\n" \
            "\t.set\tnoat # maspsx-keep\n" \
            "\t.include \"" FOLDER "/" #NAME ".s\" # maspsx-keep\n" \
            "\t.set\treorder # maspsx-keep\n" \
            "\t.set\tat # maspsx-keep\n" \
        ); \
    }
#endif

#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME) \
    void __maspsx_include_asm_hack_rodata_##NAME(void) { \
        __asm__( \
            ".section .rodata # maspsx-keep\n" \
            "\t.include \"" FOLDER "/" #NAME ".s\" # maspsx-keep\n" \
            ".section .text # maspsx-keep\n" \
        ); \
    }
#endif

__asm__(".include \"include/macro.inc\"\n");

#else

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif

#endif

#endif
