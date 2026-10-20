#include "common.h"

/* The engine tick counter: the word at 0x80034520 (engine_counter) sits in
 * .text right after this function, between the hand-written routines of
 * engine/gte_render and engine/gte_transform. */
void RIncTickCount(void)
{
    engine_counter[0]++;
}
