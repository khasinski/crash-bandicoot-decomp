/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"

/* =========================================================================
 * Section 1: CD Directory Reader (asm/USA/main/text_200C4.s)
 * ========================================================================= */

typedef struct {
    u32 directory_sector : 23;
    u32 pad0 : 9;
    u32 directory_size : 17;
    u32 pad1 : 15;
    u32 page_sector : 24;
    u32 pad2 : 8;
} NsFileMapBits;

extern NsFileMapBits D_8005E03C[];

extern struct { s16 a; s8 b; } D_800564EC;

void *LIBC_Malloc(s32);
void LIBC_Free(void *);
u8 *func_80043A24(s32, u8 *);
s32 func_80043520(u8, u8 *, u8 *);
s32 func_800439A4(s32, void *, s32);
s32 func_80043984(s32, void *);
s32 BIOS_StrNCmp(const char *, const char *, s32);
void *BIOS_MemCpy(void *, const void *, s32);
s32 BIOS_StrLen(const char *);
s32 func_8003D730(const char *, ...);

static __inline__ s32 cd_read_sectors(s32 sector_count, s32 first_sector, void *destination, u8 *position) {
    func_80043A24(first_sector, position);
    func_80043520(2, position, NULL);
    func_800439A4(sector_count, destination, 0x80);
    return func_80043984(0, NULL) == 0;
}

static __inline__ void *cd_memcpy(void *dst, const void *src, s32 len) {
    dst = BIOS_MemCpy(dst, src, len);
    return dst;
}

s32 func_8002F8C4(void) {
    u8 name[32];
    s32 subdirs[4];
    u8 position[8];
    s32 sector;
    s32 pt_sector;
    s32 size;
    u8 *buf;
    u8 *p;
    s32 i;
    s32 j;
    s32 level;

    buf = LIBC_Malloc(0x800);
    if (cd_read_sectors(1, 0x10, buf, position) != 1) {
        goto fail;
    }
    if (BIOS_StrNCmp((char *)(buf + 1), D_800564E0, 5) != 0) {
        goto fail;
    }
    func_8003D730(D_80010BC0);
    __builtin_memcpy(&sector, buf + 0x8C, 4);
    if (cd_read_sectors(1, sector, buf, position) != 1) {
        goto fail;
    }
    p = buf;
    for (j = 0; j < 4; j++) {
        subdirs[j] = -1;
    }
    i = 0;
    while (p < buf + 0x800) {
        s32 len;
        s32 step;
        if (*p == 0) {
            break;
        }
        cd_memcpy(name, p + 8, *p);
        name[*p] = 0;
        __builtin_memcpy(&pt_sector, p + 2, 4);
        if (BIOS_StrLen((char *)name) == 2 && (name[0] == 'S' || name[0] == 's')) {
            subdirs[name[1] - '0'] = pt_sector;
        }
        len = *p;
        i++;
        step = (len & 1) + 8;
        p += len + step;
        if (i >= 0x80) {
            break;
        }
    }
    for (j = 0; j < 4; j++) {
        if (subdirs[j] != -1) {
            if (cd_read_sectors(1, subdirs[j], buf, position) != 1) {
                goto fail;
            }
        }
        p = buf;
        i = 0;
        while (p < buf + 0x800) {
            if (*p == 0) {
                break;
            }
            __builtin_memcpy(&sector, p + 2, 4);
            __builtin_memcpy(&size, p + 10, 4);
            switch (i) {
            case 0:
                __builtin_memcpy(name, &D_800564E8, 2);
                break;
            case 1:
                __builtin_memcpy(name, &D_800564EC, 3);
                break;
            default:
                cd_memcpy(name, p + 0x21, p[0x20]);
                name[p[0x20]] = 0;
                break;
            }
            if (name[0] == 'S' || name[0] == 's') {
                if (name[7] >= 'A') {
                    level = (name[6] - '0') * 16 + (name[7] - 'A' + 10);
                } else {
                    level = (name[6] - '0') * 16 + (name[7] - '0');
                }
                if (name[11] == 'D' || name[11] == 'd') {
                    D_8005E03C[level].directory_sector = sector;
                    D_8005E03C[level].directory_size = size;
                } else {
                    D_8005E03C[level].page_sector = sector;
                }
            }
            i++;
            p += *p;
            if (i >= 0x40) {
                break;
            }
        }
    }
    LIBC_Free(buf);
    return 1;
fail:
    LIBC_Free(buf);
    return 0;
}

