/* GCC_VERSION: 2.6.3 */
#include "object_links.h"
Node *GOOL_CreateObject(Node *, s32, s32, s32, s32, s32);      /* extern */
void func_8002BE8C(s32, s32, s32);                           /* extern */
void func_8002EC68(s32);                                 /* extern */
extern s32 *D_8005C53C;

extern Node D_80060DD0;
extern Node *D_800618AC;
extern s32 D_800618D0;
extern s32 D_80061984;
extern s32 D_80061990;

extern s32 D_80061998;
extern s32 D_800619B4;
extern s32 D_800619BC;
extern s32 D_80061A30;
extern s32 D_80061A34;
extern s32 D_80061A38;

void func_800262DC(s32 arg0) {
    Node *root;
    s32 var_a1;
    s32 var_a2;
    s32 temp_v0;

    temp_v0 = D_8005C53C[1];
    switch (temp_v0) {
    case 23:
        if (arg0 != 0) {
            D_800618AC = GOOL_CreateObject(&D_80060DD0, 0x27, 4, 0, 0, 1);
        }
        break;
    case 20:
    case 22:
        var_a1 = 0x17;
        if (arg0 != 0) {
            root = &D_80060DD0;
            var_a2 = 6;
            goto create_object;
        }
        break;
    case 5:
        var_a1 = 9;
        if (arg0 != 0) {
            root = &D_80060DD0;
            var_a2 = 4;
            goto create_object;
        }
        break;
    case 34:
    case 46:
        var_a1 = 0x35;
        if (arg0 != 0) {
            root = &D_80060DD0;
            var_a2 = 0xD;
create_object:
            GOOL_CreateObject(root, var_a1, var_a2, 0, 0, 1);
        }
        break;
    case 14:
        break;
    case 40:
    case 42:
        func_8002EC68(1);
        break;
    default:
        D_800618AC = 0;
        break;
    }
    D_80061998 = 1;
    D_80061984 = 0;
    D_80061990 = 0;
    D_80061994 = 0;
    if (D_80061A30 != 2) {
        D_800619BC = 0;
    }
    D_800619B4 = 0;
    func_8002BE8C(0, 0, 0);
    D_80061A38 = 0x20;
    D_8005DFEC = 0;
    if (D_800618D0 != 0x600) {
        D_80061A34 = 0x120;
    }
}
