/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

typedef void (*Callback)(void);
void func_8003E1F8(void);
void func_8003E208(void);
Callback func_8003E724(s32, Callback);
s32 func_8003E784(s32);
extern s32 D_8005625C;
extern Callback D_80056264;
extern u8 D_80056268;
extern s8 D_80056269;
extern u8 D_8005626A;

void func_80049648(void)
{
    if (D_8005625C == 0) {
        D_80056269 = 0;
        if (D_8005626A != 0x7F) {
            func_8003E1F8();
            if (D_80056268 != 0) {
                func_8003E784(0);
                D_80056268 = 0;
            } else if (D_8005626A == 0) {
                func_8003E724(0, D_80056264);
                D_80056264 = NULL;
            } else {
                func_8003E724(6, NULL);
            }
            func_8003E208();
            D_8005626A = 0x7F;
        }
    }
}
