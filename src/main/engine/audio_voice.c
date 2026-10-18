/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 4 */
/* GCC_CPU: 3000 */
#include "common.h"
extern s32 D_80061910;
extern s32 D_80061918;
extern s32 D_80061914;

/* =========================================================================
 * Section 2: Audio / SPU Voice Management (asm/USA/main/text_20878.s)
 * ========================================================================= */

typedef struct {
    s16 left;
    s16 right;
} AudioVolume;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    u8 pad00[0x80];
    Vec3 trans;
    u8 pad8C[0x40];
    u32 status_b;
} GoolObjectAudio;

typedef struct {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    s32 unk04;
    GoolObjectAudio *obj;
    u8 unk0C;
    u8 priority;
    s16 volume;
    s16 delay;
    u16 pitch;
    Vec3 trans_pos;
    Vec3 world_pos;
    s16 target_vol;
    u16 target_pitch;
    s32 vol_ticks;
    s32 vol_step;
    s32 pitch_ticks;
    s32 pitch_step;
} VoiceParams;

typedef struct {
    s32 id;
    VoiceParams params;
} VoiceEntry;

typedef struct {
    u32 voice;
    u32 mask;
    AudioVolume volume;
    AudioVolume volmode;
    AudioVolume volumex;
    u16 pitch;
    u16 note;
    u16 sample_note;
    s16 envx;
    u32 addr;
    u32 loop_addr;
    s32 a_mode;
    s32 s_mode;
    s32 r_mode;
    u16 ar;
    u16 dr;
    u16 sr;
    u16 rr;
    u16 sl;
    u16 ads_stat;
    u16 r_stat;
    u16 pad;
} SpuVoiceAttrLocal;

typedef struct {
    s32 unk00;
    s32 id;
} LevelHeaderInfo;

extern LevelHeaderInfo *D_8005C53C;
s32 D_800564F4 = 0x1E;
asm(".globl D_8005663C, D_80056640, D_80056642, D_80056644");
s32 D_8005663C;
s16 D_80056640;
s16 D_80056642;
s16 D_80056644;

extern struct { s32 v, pad; } D_8005640C;
extern VoiceEntry D_80056804[24];

extern VoiceParams D_80056E7C;
extern u8 D_80056ED0[];
typedef struct {
    u8 pad00[0x10];
    s32 unk10;
} ZonePtr57914;
extern ZonePtr57914 *D_80057914;

s32 func_80034580(s32, s32, s32);
s32 func_80034524();
s32 func_8004301C(s32, s32);
s32 func_800390D0(s32);
void func_800485E0(SpuVoiceAttrLocal *);
s32 func_8002F778(s32);
s32 func_80015A98(u32);
void func_800248A0(Vec3 *, Vec3 *, s32);
void func_80047F5C(SpuVoiceAttrLocal *);
void func_80047C60(s32, u32);
void func_80047EE4(s32, u32);
void func_800311B0(s32);
void func_800317F8(s32);
void func_8004B7D8(s32, s32);
void func_80031A40(u8 *, s32, s32);
void func_800491E0(u8 *);

s32 func_80030840(s32 id, u32 op, void *arg2, GoolObjectAudio *obj);

AudioVolume *func_80030078(Vec3 *pos, s32 vol) {
    s32 x, z, y, dist, pan, base_vol, left, right;

    x = pos->x / 32;
    z = (pos->z - 0x4B000) / 32;
    if (D_8005C53C->id == 0x22 || D_8005C53C->id == 0x2E) {
        y = pos->y / 32;
        dist = func_80034580(x, z, y);
        func_80034524(x, z, y);
    } else {
        dist = func_80034524(x, z);
    }
    if (dist <= 0x7FFF) {
        D_80056640 = vol;
        D_80056642 = vol;
    } else {
        pan = func_800390D0(func_8004301C(z, x)) + 0x1000;
        base_vol = (vol << 15) / dist;
        if (D_80061910 == 0) {
            left = (base_vol + base_vol * (0x2000 - pan)) >> 11;
            right = (base_vol + base_vol * pan) >> 11;
        } else {
            left = right = base_vol;
        }
        D_80056640 = left >= vol ? vol : (left < 0 ? 0 : left);
        D_80056642 = right >= vol ? vol : (right < 0 ? 0 : right);
    }
    return (AudioVolume *)&D_80056640;
}

void func_80030260(GoolObjectAudio *obj) {
    s32 i;
    s32 zero;
    VoiceEntry *entry;

    if (obj != NULL) {
        i = D_80056668;
        entry = &D_80056804[i];
        for (; i < 24; i++, entry++) {
            if ((entry->params.b3) && entry->params.obj == obj) {
                zero = 0;
                D_800564F4 = 9;
                func_80030840(entry->id, 0x40000000, &zero, entry->params.obj);
                entry->params.obj = NULL;
                entry->params.priority = 0;
            }
        }
    }
}

s32 func_80030328(void) {
    SpuVoiceAttrLocal attr;
    s32 min_vol = 0x3FFF;
    s32 min_prio = 0xFF;
    s32 best_idx;
    VoiceEntry *entry;
    s32 i;
    s32 left, right, vol;

    best_idx = D_80056668;
    entry = &D_80056804[best_idx];
    for (; best_idx < 24; best_idx++, entry++) {
        if (entry->params.priority < min_prio) {
            min_prio = entry->params.priority;
        }
        if (!entry->params.b3) {
            return best_idx;
        }
    }
    if (D_80056E7C.priority < min_prio) {
        return -1;
    }
    i = D_80056668;
    entry = &D_80056804[i];
    best_idx = -1;
    for (; i < 24; i++, entry++) {
        if (entry->params.priority == min_prio) {
            attr.voice = 1 << i;
            func_800485E0(&attr);
            left = attr.volume.left;
            right = attr.volume.right;
            vol = left < 0 ? -left : left;
            right = right < 0 ? -right : right;
            if (vol < right) {
                vol = right;
            }
            if (vol < min_vol) {
                best_idx = i;
                min_vol = vol;
            }
        }
    }
    if (min_prio == D_80056E7C.priority && min_vol >= 0x800 && func_8002F778(100) >= 50) {
        return -1;
    }
    return best_idx;
}

s32 func_800304C8(GoolObjectAudio *obj, u32 arg1, s32 vol) {
    SpuVoiceAttrLocal attr;
    Vec3 pos;
    VoiceEntry *entry;
    s32 voice_idx;
    s32 res;
    u32 addr;

    if (D_80061914 == 0) {
        return;
    }
    voice_idx = func_80030328();
    if (voice_idx > 0) {
        entry = &D_80056804[voice_idx];
        if (arg1 & 1) {
            addr = arg1 & ~1;
        } else {
            res = func_80015A98(arg1);
            if (res >= -0xFE) {
                return -1;
            }
            addr = ((u32)res << 1) >> 3;
        }
        entry->params = D_80056E7C;
        entry->params.volume = (vol * D_80056644) >> 14;
        if (entry->params.b6) {
            entry->params.vol_step = (entry->params.target_vol - entry->params.volume) / entry->params.vol_ticks;
        }
        entry->params.obj = obj;
        if (obj != NULL) {
            entry->params.world_pos = obj->trans;
            func_800248A0(&obj->trans, &pos, 1);
            entry->params.trans_pos = pos;
        }
        D_80056E7C.unk0C = 1;
        D_80056E7C.priority = 0x80;
        D_80056E7C.volume = 0x3FFF;
        D_80056E7C.pitch = 0x1000;
        D_80056E7C.obj = NULL;
        D_80056E7C.delay = 0;
        D_80056E7C.trans_pos.x = 0;
        D_80056E7C.trans_pos.y = 0;
        D_80056E7C.trans_pos.z = 0;
        D_80056E7C.b1 = 0;
        D_80056E7C.b0 = 0;
        D_80056E7C.b2 = 0;
        D_80056E7C.b3 = 0;
        D_80056E7C.b4 = 0;
        D_80056E7C.b5 = 0;
        D_80056E7C.b6 = 0;
        D_80056E7C.b7 = 0;
        D_80056E7C.b8 = 0;
        D_80056E7C.b9 = 1;
        D_80056E7C.b10 = 1;
        D_80056E7C.b11 = 0;
        attr.mask = 0xFF93;
        attr.voice = 1 << voice_idx;
        if (entry->params.obj->status_b & 0x200) {
            attr.volume.left = attr.volume.right = entry->params.volume;
            entry->params.b9 = 0;
        } else {
            attr.volume = *func_80030078(&entry->params.trans_pos, entry->params.volume);
        }
        attr.pitch = entry->params.pitch;
        attr.addr = addr;
        attr.a_mode = 1;
        attr.s_mode = 1;
        attr.r_mode = 3;
        attr.ar = 0;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 0;
        attr.sl = 0xF;
        func_80047F5C(&attr);
        func_80047C60(entry->params.b10, attr.voice);
        if (!entry->params.b4) {
            func_80047EE4(1, attr.voice);
        }
        entry->id = ++D_8005663C;
        entry->params.b3 = 1;
        return entry->id;
    }
    return -1;
}

s32 func_80030840(s32 id, u32 op, void *arg2, GoolObjectAudio *obj) {
    SpuVoiceAttrLocal s_attr;
    u8 c_attr[0x28];
    Vec3 v1;
    Vec3 v2;
    s32 i;
    VoiceEntry *entry;
    VoiceParams *params;

    i = D_80056668;
    entry = &D_80056804[i];
    for (; i < 24; i++, entry++) {
        if ((id == 0 || (id == -1 || entry->id == id)) && (id != -1 || entry->params.obj == obj)) {
            params = &D_80056E7C;
            if (id != 0) {
                params = &entry->params;
            }
            if (op & 0x80000000) {
                params->b0 = 1;
            }
            if (op & 0x40000000) {
                params->b1 = 1;
            }
            if (op & 0x20000000) {
                params->b2 = 1;
            }
            s_attr.mask = 0;
            switch (op & 0xFFFFFFF) {
            case 0:
                if (params->b2) {
                    params->target_vol = *(s16 *)arg2;
                    params->vol_ticks = D_800564F4;
                    if (id != 0) {
                        params->vol_step = (params->target_vol - params->volume) / params->vol_ticks;
                    }
                    params->b6 = 1;
                } else {
                    params->volume = *(s16 *)arg2;
                    if (id != 0) {
                        s_attr.mask |= 3;
                        s_attr.volume = *func_80030078(&params->trans_pos, params->volume);
                    }
                }
                break;
            case 1:
                if (params->b2) {
                    params->target_pitch = *(u16 *)arg2;
                    params->pitch_step = (params->target_pitch - params->pitch) / D_800564F4;
                    params->pitch_ticks = D_800564F4;
                    params->b7 = 1;
                } else {
                    params->pitch = *(u16 *)arg2;
                    if (id != 0) {
                        s_attr.mask = 0x10;
                        s_attr.pitch = params->pitch;
                    }
                }
                break;
            case 2:
                v1 = *(Vec3 *)arg2;
                func_800248A0(&v1, (Vec3 *)arg2, 1);
            case 3:
                v2 = *(Vec3 *)arg2;
                if (!params->b2) {
                    params->trans_pos = *(Vec3 *)arg2;
                    if (id != 0) {
                        entry->params.trans_pos = *(Vec3 *)arg2;
                        s_attr.mask = 3;
                        s_attr.volume = *func_80030078(&params->trans_pos, params->volume);
                    }
                }
                break;
            case 4:
                params->unk0C = *(u8 *)arg2;
                break;
            case 5:
                params->obj = *(GoolObjectAudio **)arg2;
                break;
            case 6:
                D_800564F4 = *(s32 *)arg2;
                if (D_800564F4 == 0) {
                    D_800564F4 = 1;
                }
                break;
            case 7:
                params->delay = *(s16 *)arg2;
                params->b4 = 1;
                break;
            case 8:
                params->b9 = 1;
                break;
            case 9:
                params->b9 = 0;
                break;
            case 10:
                params->b11 = *(s32 *)arg2 >> 8;
                break;
            case 11:
                params->b10 = *(s32 *)arg2 >> 8;
                break;
            case 12:
                params->priority = *(u8 *)arg2;
                break;
            }
            if (s_attr.mask != 0) {
                s_attr.voice = 1 << i;
                func_80047F5C(&s_attr);
            }
            if (id != -1) {
                return 0;
            }
        }
    }
    return id == -1 ? 0 : -1;
}

void func_80030CC0(void) {
    SpuVoiceAttrLocal attr;
    Vec3 pos;
    s32 flag = 0;
    s32 i;
    VoiceEntry *entry;
    s32 v;
    u32 tmp;
    GoolObjectAudio *obj;

    tmp = D_8005C53C->id;
    if (tmp == 0x19) {
        v = D_80061914;
        tmp = v << 14;
        tmp -= v;
        tmp >>= 8;
        D_80056644 = tmp;
        v = D_80061918;
        func_800311B0((s16)((v * 0x3FFF) >> 8));
    }
    if (D_80057914 != NULL) {
        func_800317F8(D_80057914->unk10 + 0x304);
    }
    if (D_80056664 != 0) {
        if (D_80056664 < 0 && D_80056660 < -D_80056664) {
            D_80056660 = 0;
            D_80056664 = 0;
        }
        if (D_80056664 > 0 && 0x3FFF - D_80056660 < D_80056664) {
            D_80056660 = 0x3FFF;
            D_80056664 = 0;
        }
        D_80056660 += D_80056664;
        func_8004B7D8(D_80056660 >> 7, D_80056660 >> 7);
    }
    if (D_8005640C.v == 1) {
        D_80056664 = -0x222;
        if (D_8005666C != 0 && D_8005665C >= 2 && D_800566C0 == 3) {
            func_80031A40(D_80056ED0, 2, 0);
        }
    }
    if (D_8005640C.v == -1) {
        D_80056664 = 0x667;
        if (D_8005666C != 0 && D_8005665C >= 2 && D_800566C0 == 3) {
            func_80031A40(D_80056ED0, 3, 0);
        }
    }
    func_800491E0(D_80056E64);
    i = D_80056668;
    entry = &D_80056804[i];
    for (; i < 24; i++, entry++) {
        if (entry->params.b3) {
            if (entry->params.b4) {
                if (--entry->params.delay != 0) {
                    continue;
                }
                entry->params.b4 = 0;
                func_80047EE4(1, 1 << i);
            }
            if (D_80056E64[i] == 3) {
                if (--entry->params.unk0C == 0) {
                    func_80047EE4(0, 1 << i);
                    entry->params.b3 = 0;
                    goto check_end;
                } else {
                    func_80047EE4(1, 1 << i);
                }
            }
            attr.mask = 0;
            if (entry->params.b6) {
                entry->params.volume += entry->params.vol_step;
                if (--entry->params.vol_ticks > 0) {
                    flag = 1;
                } else {
                    entry->params.b6 = 0;
                }
                attr.mask |= 3;
                if (entry->params.obj->status_b & 0x200) {
                    attr.volume.left = attr.volume.right = entry->params.volume;
                } else {
                    attr.volume = *func_80030078(&entry->params.trans_pos, entry->params.volume);
                }
            }
            if (entry->params.b7) {
                entry->params.pitch += entry->params.pitch_step;
                if (--entry->params.pitch_ticks > 0) {
                    flag = 1;
                } else {
                    entry->params.b7 = 0;
                }
                attr.mask |= 0x10;
                attr.pitch = entry->params.pitch;
            }
            if (entry->params.b9 && (obj = entry->params.obj) != NULL) {
                entry->params.world_pos = obj->trans;
                func_800248A0(&obj->trans, &pos, 1);
                entry->params.trans_pos = pos;
                attr.mask |= 3;
                attr.volume = *func_80030078(&entry->params.trans_pos, entry->params.volume);
            }
            if (attr.mask != 0) {
                attr.voice = 1 << i;
                func_80047F5C(&attr);
            }
        check_end:
            if (entry->params.b0 || (!flag && entry->params.b1)) {
                func_80047EE4(0, 1 << i);
                entry->params.b3 = 0;
            }
        }
    }
}
