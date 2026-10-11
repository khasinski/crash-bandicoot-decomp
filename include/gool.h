#ifndef CRASH_GOOL_H
#define CRASH_GOOL_H

#include "common.h"

/* Partial view for routines accessing the resource pointer at offset 0x10.
 * This is not yet a reconstruction of the full object/resource layout.
 */
typedef struct ObjectView {
    u8 pad00[0x10];
    u8 *resource;
} ObjectView;

#endif
