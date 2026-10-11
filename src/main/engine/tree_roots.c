#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

extern u8 D_80060DB8[];
void func_8001BA18(Traversal traversal, Visitor visitor, void *context)
{
    s32 i = 0;
    u8 *root = D_80060DB8;
    do {
        traversal((Node *)root, visitor, context);
        i++;
        root += 8;
    } while(i < 8);
}
