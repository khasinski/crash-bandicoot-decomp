#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Compute XYZ or XZ distance through the integer root helper, using 8-bit scaled deltas. */

#include "vector.h"

s32 func_80042B9C(s32);

s32 func_80029D30(Vec3 *a, Vec3 *b)
{
    Vec3 delta;

    delta.x = (a->x - b->x) >> 8;
    delta.y = (a->y - b->y) >> 8;
    delta.z = (a->z - b->z) >> 8;
    return func_80042B9C(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) << 8;
}

s32 func_80029DB0(Vec3 *a, Vec3 *b)
{
    Vec3 delta;

    delta.x = (a->x - b->x) >> 8;
    delta.z = (a->z - b->z) >> 8;
    return func_80042B9C(delta.x * delta.x + delta.z * delta.z) << 8;
}
