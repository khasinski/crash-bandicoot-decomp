/* GCC_VERSION: 2.6.3 */
#include "common.h"

/* Export the real small-common state object. */
asm(".globl D_80056654");
s16 D_80056654;
void func_800319DC(s16,s32);
void func_80049648(void);
void func_80031938(void) {
    func_800319DC(D_80056654,1);
    func_80049648();
}
