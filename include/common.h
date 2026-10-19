#ifndef CRASH_COMMON_H
#define CRASH_COMMON_H

#include "include_asm.h"

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

/* Historical GCC has no __builtin_offsetof. Evaluated for the target's
 * 32-bit pointer ABI; also usable in compile-time layout checks. */
#define CRASH_OFFSETOF(type, member) ((u32)&(((type *)0)->member))

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Preserves a pointer/register value across GCC 2.6.3 CSE without folding
 * its SYMBOL_REF into subsequent offset calculations. */
#define KEEP_REGISTER_VALUE(dst, val) asm("" : "=r"(dst) : "0"(val))

#include "globals.h"

#endif
