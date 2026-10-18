#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Pass the matrix at D_800577C4 to the two GTE setup routines. */

extern u8 D_800577C4[];
void func_80042E9C(void *);
void func_80042F2C(void *);

void func_8001892C(void)
{
    func_80042E9C(D_800577C4);
    func_80042F2C(D_800577C4);
}
