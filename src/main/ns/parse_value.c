#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern s32 BIOS_AToI(u8 *);
extern s32 func_800128A4(s32, s32, s32, s32);
extern u8 D_80051728[];

static __inline__ s32 func_80012834(u8 ch)
{
    s32 index;
    for (index = 0; index < 0x40; index++) {
        if (D_80051728[index] == ch)
            return index;
    }
    if (ch == 0x2D)
        return 0x63;
    return -0xE;
}

__inline__ s32 func_8001297C(u32 type, u8 *text) {
    s32 end_address;
    s32 packed;
    s32 alphabet_index;
    u8 *cursor;
    u32 character;

    switch (type) {
    case 3:
        packed = 0;
        cursor = text;
        end_address = (s32)(cursor + 5);
        do {
            packed <<= 6;
            alphabet_index = 0;
            character = *cursor;
search_packed_character:
            if (D_80051728[alphabet_index] == character) {
                packed |= alphabet_index;
            } else {
                alphabet_index += 1;
                if (alphabet_index < 0x40) {
                    goto search_packed_character;
                }
            }
            cursor += 1;
        } while ((s32)cursor < end_address);
        packed *= 2;
        return packed | 1;
    case 2:
        return (BIOS_AToI(text) * 2) | 1;
    case 0:
    case 1:
    case 13:
    case 14:
        return func_80012834(*text);
    default:
        return BIOS_AToI(text);
    }
}

s32 func_80012A84(u32 type, u8 *text) {
    return func_800128A4(type, func_8001297C(type, text), 0, 0);
}
