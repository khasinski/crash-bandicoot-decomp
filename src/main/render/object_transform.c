#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Pass the object and its field at 0x80 to the transform routine. */

void Zone_QueryOctrees(void *, void *, s32);

void Zone_QueryOctrees2(u8 *object, s32 arg)
{
    Zone_QueryOctrees(object + 0x80, object, arg);
}
