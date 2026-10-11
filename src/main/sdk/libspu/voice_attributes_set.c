/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: r3000 */
#include "common.h"
#include "sdk/libspu/voice_attributes.h"
extern volatile u16 *D_800558E4;
extern u16 D_80055970[];
u32 func_80046E00(s32,u32);
s32 func_80048EC4(s32,s32,s32,s32);
static inline u16 encode_attack(s32 mode) {
    switch (mode) {
    case 1: return 0;
    case 5: return 128;
    default: return 0;
    }
}
static inline u16 encode_sustain(s32 mode) {
    switch (mode) {
    case 1: return 0;
    case 3: return 256;
    case 5: return 512;
    case 7: return 768;
    default: return 256;
    }
}
static inline u16 encode_release(s32 mode) {
    switch (mode) {
    case 3: return 0;
    case 7: return 32;
    default: return 0;
    }
}
static inline u16 clamp_rate4(const u16 *rate) {
    u16 value = *rate;
    if (value < 16) return *rate;
    return 15;
}
s32 func_80047F84(VoiceAttributes *attr, s32 first, s32 last, s32 skip_wait) {
    volatile s32 delay_count;
    volatile s32 delay_product;
    /* ADSR words and the MMIO base occupy this scratch value in separate phases. */
    union { u32 word; volatile u16 *base; } operand;
    u32 voice_address;
    s16 left_input;
    s16 right_input;
    s16 right_mode;
    s16 left_mode;
    s32 field_mask;
    s32 all_fields;
    s32 word_index;
    s32 invalid_range;
    s32 first_voice;
    u16 adsr_mode;
    u32 volume_mode;
    s32 voice;
    s32 end_voice;
    s32 skip_delay;
    s32 encoded_volume;
    u16 base_note;
    u16 note;
    u16 rate;
    u16 right_volume;
    u16 left_volume;
    volatile u8 *attack_regs;
    volatile u8 *decay_regs;
    volatile u8 *level_regs;
    volatile u8 *sustain_regs;
    volatile u8 *release_regs;

    first_voice = first;
    end_voice = last;
    skip_delay = skip_wait;
    left_volume = 0;
    field_mask = attr->field_4;
    right_volume = 0;
    all_fields = field_mask == 0;
    if (first_voice < 0) {
        first_voice = 0;
    }
    if (first_voice >= 24) goto invalid;
    if (end_voice >= 24) end_voice = 23;
    if (end_voice < 0) goto invalid;
    invalid_range = end_voice < first_voice;
    end_voice++;
    if (!invalid_range) goto valid;
invalid:
return -3;
valid:
    voice = first_voice;
    if (voice < end_voice) {
        do {
            if ((1 << voice) & attr->field_0) {
                word_index = voice * 8;
                if ((all_fields != 0) || (field_mask & 0x10)) {
                    *(volatile u16 *)(((voice * 0x10) + ((volatile u8 *)D_800558E4)) + 4) = (u16) attr->field_14;
                }
                if ((all_fields != 0) || (field_mask & 0x40)) {
                    D_80055970[voice] = attr->field_18;
                }
                if ((all_fields != 0) || ((field_mask & 0x20) != 0)) {
                    base_note = D_80055970[voice];
                    note = attr->field_16;
                    *(volatile u16 *)(((word_index * 2) + ((volatile u8 *)D_800558E4)) + 4) = func_80048EC4(base_note >> 8, base_note & 0xFF, note >> 8, note & 0xFF);
                }
                if ((all_fields != 0) || (field_mask & 0x80)) {
                    func_80046E00(word_index | 3, attr->field_1C);
                }
                if (all_fields == 0) {
                    if (field_mask & 0x800) {
                        adsr_mode = 0;
                        if (field_mask & 0x100) {
                            goto load_attack_mode;
                        }
                        goto set_attack_rate;
                    }
                } else {
load_attack_mode:
                    adsr_mode = encode_attack(attr->field_24);
set_attack_rate:
                    rate = 0x7F;
                    if ((u16) attr->field_30 < 0x80U) {
                        rate = attr->field_30;
                    }
                    attack_regs = (word_index * 2) + ((volatile u8 *)D_800558E4);
                    operand.word = *(volatile u16 *)(attack_regs + 8) & 0xFF;
                    *(volatile u16 *)(attack_regs + 8) = (u16) (operand.word | ((rate | adsr_mode) << 8));
                }
                if ((all_fields != 0) || (field_mask & 0x1000)) {
                    rate = clamp_rate4(&attr->field_32);
                    decay_regs = (word_index * 2) + ((volatile u8 *)D_800558E4);
                    operand.word = *(volatile u16 *)(decay_regs + 8) & 0xFF0F;
                    *(volatile u16 *)(decay_regs + 8) = (u16) (operand.word | (rate * 0x10));
                }
                if ((all_fields != 0) || (field_mask & 0x8000)) {
                    rate = clamp_rate4(&attr->field_38);
                    level_regs = (word_index * 2) + ((volatile u8 *)D_800558E4);
                    *(volatile u16 *)(level_regs + 8) = (u16) (rate | (*(volatile u16 *)(level_regs + 8) & 0xFFF0));
                }
                if (all_fields == 0) {
                    if (field_mask & 0x2000) {
                        adsr_mode = 0;
                        if (field_mask & 0x200) {
                            goto load_sustain_mode;
                        }
                        goto set_sustain_rate;
                    }
                } else {
load_sustain_mode:
                    adsr_mode = encode_sustain(attr->field_28);
set_sustain_rate:
                    rate = 0x7F;
                    if ((u16) attr->field_34 < 0x80U) {
                        rate = attr->field_34;
                    }
                    sustain_regs = (word_index * 2) + ((volatile u8 *)D_800558E4);
                    operand.word = *(volatile u16 *)(sustain_regs + 10) & 0x3F;
                    *(volatile u16 *)(sustain_regs + 10) = (u16) (operand.word | ((rate | adsr_mode) << 6));
                }
                if (all_fields == 0) {
                    if (field_mask & 0x4000) {
                        adsr_mode = 0;
                        if (field_mask & 0x400) {
                            goto load_release_mode;
                        }
                        goto set_release_rate;
                    }
                } else {
load_release_mode:
                    adsr_mode = encode_release(attr->field_2C);
set_release_rate:
                    rate = 0x1F;
                    if ((u16) attr->field_36 < 0x20U) {
                        rate = attr->field_36;
                    }
                    release_regs = (word_index * 2) + ((volatile u8 *)D_800558E4);
                    operand.word = *(volatile u16 *)(release_regs + 10) & 0xFFC0;
                    *(volatile u16 *)(release_regs + 10) = (u16) (operand.word | (rate | adsr_mode));
                }
                if ((all_fields != 0) || ((field_mask & 0x20000) != 0)) {
                    operand.word = attr->field_3A;
                    *(volatile u16 *)((word_index * 2 + ((volatile u8 *)D_800558E4)) + 8) = (u16) operand.word;
                }
                if ((all_fields != 0) || ((field_mask & 0x40000) != 0)) {
                    operand.word = attr->field_3C;
                    *(volatile u16 *)((word_index * 2 + ((volatile u8 *)D_800558E4)) + 10) = (u16) operand.word;
                }
                if ((all_fields != 0) || (field_mask & 0x10000)) {
                    func_80046E00(word_index | 7, attr->field_20);
                }
                if ((all_fields != 0) || (field_mask & 1)) {
                    if ((all_fields != 0) || (field_mask & 4)) {
                        left_mode = attr->field_C;
                        switch (left_mode) {
                        case 1:
                            volume_mode = 0x8000;
                            break;
                        case 2:
                            volume_mode = 0x9000;
                            break;
                        case 3:
                            volume_mode = 0xA000;
                            break;
                        case 4:
                            volume_mode = 0xB000;
                            break;
                        case 5:
                            volume_mode = 0xC000;
                            break;
                        case 6:
                            volume_mode = 0xD000;
                            break;
                        case 7:
                            volume_mode = 0xE000;
                            break;
                        case 0:
                        default:
                            left_volume = attr->field_8;
                            volume_mode = 0;
                            break;
                        }
                    } else {
                        left_volume = attr->field_8;
                        volume_mode = 0;
                    }
                    if (volume_mode != 0) {
                        left_input = (s16) attr->field_8;
                        if (left_input >= 0x80) {
                            left_volume = 0x7F;
                        } else {
                            left_volume = (u16) left_input;
                            if (left_input < 0) {
                                left_volume = 0;
                            }
                        }
                    }
                    encoded_volume = left_volume & 0x7FFF;
                    voice_address = word_index * 2;
                    operand.base = D_800558E4;
                    voice_address += (u32)operand.base;
                    *(volatile u16 *)(voice_address + 0) = encoded_volume | volume_mode;
                }
                if ((all_fields != 0) || (field_mask & 2)) {
                    if ((all_fields != 0) || (field_mask & 8)) {
                        right_mode = attr->field_E;
                        switch (right_mode) {
                        case 1:
                            volume_mode = 0x8000;
                            break;
                        case 2:
                            volume_mode = 0x9000;
                            break;
                        case 3:
                            volume_mode = 0xA000;
                            break;
                        case 4:
                            volume_mode = 0xB000;
                            break;
                        case 5:
                            volume_mode = 0xC000;
                            break;
                        case 6:
                            volume_mode = 0xD000;
                            break;
                        case 7:
                            volume_mode = 0xE000;
                            break;
                        case 0:
                        default:
                            right_volume = attr->field_A;
                            volume_mode = 0;
                            break;
                        }
                    } else {
                        right_volume = attr->field_A;
                        volume_mode = 0;
                    }
                    if (volume_mode != 0) {
                        right_input = (s16) attr->field_A;
                        if (right_input >= 0x80) {
                            right_volume = 0x7F;
                        } else {
                            right_volume = (u16) right_input;
                            if (right_input < 0) {
                                right_volume = 0;
                            }
                        }
                    }
                    encoded_volume = right_volume & 0x7FFF;
                    voice_address = word_index * 2;
                    operand.base = D_800558E4;
                    voice_address += (u32)operand.base;
                    *(volatile u16 *)(voice_address + 2) = encoded_volume | volume_mode;
                }
            }
            voice += 1;
        } while (voice < end_voice);
    }
    /* Normalize the cached flag before the optional SDK wait. */
    skip_delay = skip_delay != 0;
    if (skip_delay == 0) {
        delay_product = 1;
        delay_count = 0;
        while (delay_count < 2) {
            delay_product *= 13;
            delay_count++;
        }
    }
    return 0;
}
