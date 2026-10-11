/* GCC_VERSION: 2.6.3 */
#include "common.h"
void func_8003D730(const char *);
s32 func_80043384(s32);
typedef void (*Callback)(void);
Callback func_800434D8(Callback);
Callback func_800434F0(Callback);
Callback func_80043508(Callback);
void func_800432DC(void),func_80043304(void),func_8004332C(void);
extern const char D_8001139C[];
s32 func_8004324C(void)
{
    s32 retries = 4;
    while (func_80043384(1) != 1) {
        if (--retries == -1) {
            func_8003D730(D_8001139C);
            return 0;
        }
    }
    func_800434D8(func_800432DC);
    func_800434F0(func_80043304);
    func_80043508(func_8004332C);
    return 1;
}
