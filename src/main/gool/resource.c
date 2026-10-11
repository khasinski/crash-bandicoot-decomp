#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise resource state on first use; visit object roots and clear flags on release. */

#include "gool.h"

extern void func_8001D200(void *);
extern s32 D_80061A5C;
extern s32 D_80061A60;
extern s32 D_80061A64;

void func_800257B4(ObjectView *object)
{
    u8 *resource = object->resource;
    if (!(*(u32 *)(resource + 0x2DC) & 1)) {
        D_80061A5C = 0;
        D_80061A64 = 0;
        D_80061A60 = 0x19000;
        *(u32 *)(resource + 0x2DC) |= 3;
    }
}

void func_80025804(ObjectView *object)
{
    u8 *resource = object->resource;
    if (*(u32 *)(resource + 0x2DC) & 1) {
        func_8001D200(object);
        *(u32 *)(resource + 0x2DC) &= ~3;
    }
}
