/* GCC_VERSION: 2.6.3 */
#include "common.h"
/* GNU_AS_G: 8 */
s32 func_8003CD3C(void);
void func_8003E1B8(s32);
void func_8003E1E8(s32);
void func_8003E1F8(void);
void func_8003E208(void);
void func_8003E3A4(s32);
void func_8003E490(void);
void func_8003E7E8(void);
s32 func_8003FDC0(s32);
s32 func_80043520(u8, u8 *, u8 *);
/* External word view: this unit uses an absolute reference to the flag. */
extern s32 D_80056410[];
extern s32 D_80056708;

s32 func_8001668C(void)
{
    if (D_80056410[0] != 0) {
        func_80043520(8, NULL, NULL);
        func_8003E7E8();
    }
    func_8003CD3C();
    func_8003E490();
    func_8003FDC0(3);
    func_8003E1F8();
    func_8003E3A4(0xF2000002);
    func_8003E1E8(D_80056708);
    func_8003E1B8(D_80056708);
    func_8003E208();
    return -0xFF;
}
