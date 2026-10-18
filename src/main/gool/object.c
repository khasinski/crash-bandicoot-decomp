#include "object_links.h"
#include "zone.h"

/* GCC_VERSION: 2.6.3 */

/* Call the object cleanup routine with its recursive/event flag enabled. */

s32 func_8001CDD0(Node *, s32);

s32 func_8001D1E0(Node *obj, void *context)
{
    return func_8001CDD0(obj, 1);
}

/* Apply the callback to each of eight object roots. */

typedef struct ObjectRoot {
    s32 kind;
    Node *word04;
} ObjectRoot;

extern ObjectRoot D_80060DB8[];
s32 func_8001D11C(Node *, void *);
void *func_80015A98(u32 *);

void func_8001D200(void *object)
{
    s32 index = 0;
    u8 *root = (u8 *)D_80060DB8;

    do {
        func_8001B92C((Node *)root, func_8001D11C, object);
        index++;
        root += 8;
    } while (index < 8);
}

void func_8001D264(void)
{
    ZoneHeader *zone;
    s32 i;
    void *entry;
    s32 index;

    if (*(ResourceEntry *volatile *)&D_80057914 != NULL) {
        zone = (ZoneHeader *)(*(ResourceEntry *volatile *)&D_80057914)->data;
        for (i = 0; i < zone->neighbor_count; i++) {
            entry = func_80015A98(&zone->neighbors[i]);
            index = 0;
            do {
                func_8001B92C((Node *)&D_80060DB8[index], func_8001D11C, entry);
                index++;
            } while (index < 8);
        }
    }
}

