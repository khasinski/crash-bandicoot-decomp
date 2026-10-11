#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern s32 BIOS_AToI(u8 *);
extern u8 D_80051728[];

s32 func_8001297C(u32 type, u8 *text) {
    s32 end_address;
    s32 character_code;
    s32 packed;
    s32 fallback;
    s32 index;
    s32 result;
    s32 alphabet_index;
    u8 *cursor;
    u8 first_character;
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
        first_character = *text;
        index = 0;
        character_code = first_character & 0xFF;
search_character:
        result = index;
        if (D_80051728[index] != character_code) {
            index += 1;
            if (index >= 0x40) {
                fallback = -0xE;
                if ((first_character & 0xFF) == 0x2D) {
                    fallback = 0x63;
                }
                return fallback;
            }
            goto search_character;
        }
        return result;
    default:
        result = BIOS_AToI(text);
        return result;
    }
}
