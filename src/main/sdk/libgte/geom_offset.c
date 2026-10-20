/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gte.h"

/* LIBGTE.A fgo_04.o, fgo_05.o. Each library object's code is padded to 16 bytes (the pad
 * segments that follow it in configs/USA/main.yaml). */

void SetBackColor(s32 r, s32 g, s32 b)
{
    r <<= 4;
    g <<= 4;
    b <<= 4;
    gte_ctc2(r, 21);
    gte_ctc2(g, 22);
    gte_ctc2(b, 23);
}

void SetGeomOffset(s32 ofx, s32 ofy)
{
    ofx <<= 16;
    ofy <<= 16;
    gte_ctc2(ofx, 24);
    gte_ctc2(ofy, 25);
}
