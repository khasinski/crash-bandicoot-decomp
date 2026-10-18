#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Reset the buffer cursor and initialise its ordering table; expose the cursor word. */

#include "render.h"

void func_800342D8(void *, s32);

void func_80016DCC(RenderBuffer *buffer)
{
    buffer->word78 = buffer->word74;
    func_800342D8(buffer->ordering_table, 0x800);
}

void func_80016DF8(s32 amount)
{
    amount += D_8005840C->word78;
    D_8005840C->word78 = amount;
}

s32 *func_80016E18(void)
{
    return &D_8005840C->word78;
}
