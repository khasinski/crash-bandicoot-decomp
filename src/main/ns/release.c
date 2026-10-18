#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Mark a resource slot free and place the -0x12 sentinel in its ID-indexed table entry. */

#include "resource.h"

void func_80014930(ResourceSlot *slot)
{
    slot->state = 1;
    D_8005CFBC[slot->id >> 1] = -0x12;
}
