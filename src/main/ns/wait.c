#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Set the wait flag and service pending resource operations until the counter reaches zero. */

void Ns_Update(s32);

void Ns_Update2(void)
{
    D_8005CFC0 = 1;
    while (D_8005CFA8 != 0)
        Ns_Update(-1);
}
