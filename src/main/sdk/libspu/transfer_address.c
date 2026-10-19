#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Cache the encoded SPU transfer address and return the supplied address. */

s32 _spu_FsetRXXa(s32,s32);

s32 SpuSetTransferStartAddr(s32 arg0) {
    D_800558E0 = _spu_FsetRXXa(-1, arg0);
    return arg0;
}
