#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise the runtime, run the game loop for initial level 0x19, then shut down. */

extern void func_8003E0C0(void);
extern void func_8001652C(void);
extern void CORE_Loop(s32);
extern void func_8001668C(void);
extern s32 D_80056410;

s32 CORE_Main(void)
{
    func_8003E0C0();
    D_80056410 = 1;
    func_8001652C();
    CORE_Loop(0x19);
    func_8001668C();
    return 0;
}
