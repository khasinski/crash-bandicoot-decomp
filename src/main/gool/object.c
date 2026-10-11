#include "object_links.h"

/* GCC_VERSION: 2.6.3 */

/* Call the object cleanup routine with its recursive/event flag enabled. */

extern s32 func_8001CDD0(Node *, s32);

s32 func_8001D1E0(Node *obj, void *context)
{
    return func_8001CDD0(obj, 1);
}

/* Apply the callback to each of eight object roots. */

extern u8 D_80060DB8[];
extern s32 func_8001D11C(Node *, void *);

void func_8001D200(void *object)
{
    s32 index = 0;
    u8 *root = D_80060DB8;

    do {
        func_8001B92C((Node *)root, func_8001D11C, object);
        index++;
        root += 8;
    } while (index < 8);
}
