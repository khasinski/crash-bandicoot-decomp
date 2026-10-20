/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gte.h"

/* LIBGTE.A mtx_10.o..mtx_13.o, fgo_03.o. Each library object's code is padded to 16 bytes (the pad
 * segments that follow it in configs/USA/main.yaml). */

void SetRotMatrix(void *m)
{
    gte_ldrotmatrix(m);
}

void SetLightMatrix(void *m)
{
    gte_ldlightmatrix(m);
}

void SetColorMatrix(void *m)
{
    gte_ldcolormatrix(m);
}

void SetTransMatrix(void *m)
{
    gte_ldtransmatrix(m);
}

void ReadSZfifo3(s32 *sz0, s32 *sz1, s32 *sz2)
{
    gte_stsz3(sz0, sz1, sz2);
}
