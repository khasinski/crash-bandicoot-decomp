#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Pass the matrix at g_m_rot to the two GTE setup routines. */

extern u8 g_m_rot[];
void SetRotMatrix(void *);
void SetTransMatrix(void *);

void Gfx_SetGteMatrices(void)
{
    SetRotMatrix(g_m_rot);
    SetTransMatrix(g_m_rot);
}
