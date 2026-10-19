#ifndef CRASH_ENGINE_TICKS_H
#define CRASH_ENGINE_TICKS_H

#include "common.h"

/* Retail stores this counter in the text word at 0x80034520. The update
 * routine modifies it, and polling/profile code samples it repeatedly. */
extern volatile u32 g_rcnt_ticks;

#ifdef M2CTX
/* Some split assembly names the same text-resident data word as a function.
 * Tell m2c that loads through this alias are counter samples as well. */
extern volatile u32 g_rcnt_ticks;
#endif

#endif
