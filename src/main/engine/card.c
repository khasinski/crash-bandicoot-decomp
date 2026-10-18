/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "engine_ticks.h"
#define CRASH_ENGINE_STATE_STORAGE
#include "engine_state.h"
#include "resource.h"
#include "gool.h"
#include "object_links.h"

extern EngineState *D_80056564;
extern s32 D_80056568;
extern s32 D_8005656C;
extern u32 D_80056570;
extern s32 D_80061978;
extern s32 engine_flag_shadow[] __asm__("D_80061978");
extern u32 D_8005668C, D_80056690;
extern s32 D_800566C4, D_800566C8, D_800566CC, D_800566D0;
extern s32 D_800566EC, D_800566F0;
extern s32 D_800566F8, D_800566FC;
asm(".sdata\n"
    ".size D_80056564,4\n.size D_80056568,4\n.size D_8005656C,4\n.size D_80056570,4\n"
    ".size D_8005668C,4\n.size D_80056690,4\n"
    ".size D_800566C4,4\n.size D_800566C8,4\n.size D_800566CC,4\n.size D_800566D0,4\n"
    ".size D_800566EC,4\n.size D_800566F0,4\n.size D_800566F8,4\n.size D_800566FC,4\n"
    ".text");
typedef EngineFileRequest FileRequest;
s32 func_8003CEF0(s32);
s32 func_8003CAD8(s32);
s32 func_8003CAF8(s32);
s32 func_8003C9B8(void);
s32 func_8003C3FC(void);
s32 func_8003CA04(s32);
s32 func_8003CAB0(s32);
void func_8003C900(s32 *);
s32 VSync(s32);
s32 func_8003E288(char *);
s32 func_8003E1C8(s32);
s32 func_8002F778(s32);
/* Both cached words are compared before dispatching the current card mode. */
s32 func_8003CB88(void), func_8003CB74(void), func_8003AC2C(void), func_8003ABA4(void);
void func_8003C3D4(void), func_8003C3DC(void), func_8003AA7C(void), func_8003AF24(void);
void func_8003B8B8(s32), func_8003C358(void);
s32 func_8003C038(void);
extern s32 D_80061980;

void func_8003A94C(void)
{
    u32 mode;

    if (D_8005656C != func_8003CB88()) {
        D_8005656C = func_8003CB88();
        func_8003C3D4();
    }
    if (D_80056570 != func_8003CB74()) {
        D_80056570 = func_8003CB74();
        func_8003C3DC();
    }
    mode = func_8003CB74();
    switch (mode) {
    case 0: func_8003AA7C(); break;
    case 1: func_8003AC2C(); break;
    case 5: func_8003AF24(); break;
    case 6: case 7: case 8: func_8003B8B8(func_8003CB74()); break;
    case 2: func_8003C038(); break;
    case 3: func_8003C358(); break;
    case 4: func_8003ABA4(); break;
    }
    engine_flag_shadow[0] = func_8003CB88();
    D_80061980 = D_80056564->word08;
}

s32 func_8003C420(void), func_8003C608(void), func_8003C3E4(s32);
void func_8003C69C(void), func_80051424(s32), func_80051494(s32);

void func_8003AA7C(void)
{
    s32 result;

    if (D_80056564->word18) {
        D_80056564->word18 = 0;
        func_80051424(0);
    }
    result = func_8003C420();
    switch (result) {
    case 1:
        func_8003CAF8(0);
        func_8003CAB0(2);
        return;
    case 0:
        if (!(func_8003CB88() & 4)) {
            func_8003CAF8(0);
            return;
        }
    case 3:
        func_8003C69C();
        func_80051494(0);
        if (!func_8003C608()) {
            func_8003CAD8(6);
            func_8003CAB0(0x38);
            func_8003CAF8(4);
            func_8003C3E4(150);
            goto reset_list;
        }
    case 2:
        func_8003CAF8(0);
        func_8003CAB0(4);
        func_8003CAD8(8);
reset_list:
        func_8003CA04(0);
        return;
    }
}

s32 func_8003ABA4(void) {
    s32 result;
    D_80056564->word18 = 0;
    if (func_8003CEF0(0) == 1) {
        func_8003CAD8(10);
        func_8003CAF8(0);
        func_8003C9B8();
        result = 1;
    } else {
        if (func_8003C3FC()) {
            func_8003CA04(0);
            func_8003CAD8(6);
            func_8003CAB0(8);
            func_8003CAF8(0);
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

extern char D_80056574[];
void func_8003C538(void), func_80051434(s32), func_8003CA50(void);
void func_8003C7A8(EngineDirectoryRecord *, s32);

s32 func_8003AC2C(void)
{
    s32 result, count;

    if (D_80056564->word18) {
        D_80056564->word18 = 0;
        func_8003C538();
        func_80051434(0);
    }
    result = func_8003C420();
    switch (result) {
    case 0:
        count = func_8003C714(D_80056574, ((EngineDirectoryState *)D_80056564)->records);
        func_8003C7A8(((EngineDirectoryState *)D_80056564)->records, count);
        if (count > 0 || ++((EngineDirectoryState *)D_80056564)->empty_scan_count >= 11) {
            func_8003CAD8(2);
            func_8003CA50();
            func_8003CAF8(5);
            func_8003C3E4(32);
            D_80056564->word08 = 0;
            ((EngineDirectoryState *)D_80056564)->record_count = count;
            ((EngineDirectoryState *)D_80056564)->record_cursor = 0;
            return 1;
        }
        goto retry;
    case 1:
        goto check_card;
    case 2:
check_card:
        if (!func_8003C3FC()) {
retry:
            func_8003CAF8(1);
            return 0;
        }
    case 3:
        func_8003CA04(4);
        func_8003CAB0(2);
        func_8003CAF8(0);
        return 1;
    default:
        return 0;
    }
}

s32 func_8003AD84(s32 count,s32 limit,void (*callback)(void *),void *arg) {
    s32 result;
    if (count < limit) result = 0;
    else {callback(arg);result = 1;}
    return result;
}

void func_8003ADB8(s32 **resource) {
    if (func_8003C3FC()) {
        D_80056564->word08 = 0;
        func_8003CAB0(6);
        func_8003CAF8(0);
    }
    func_8003C900(*resource);
}

void func_8003AE08(FileRequest *request) {
    if (func_8003C3FC()) {
        func_8003CAB0(2);
        func_8003CAF8(0);
    }
    func_8003C900(request->resource);
    if (*request->pending) {
        s32 retries;
        s32 status;
        VSync(60);
        retries = 0;
        do {
            status = func_8003E288(request->path);
            VSync(20);
            if (status == 1) break;
            retries++;
        } while (retries < 9);
        if (retries < 3) *request->pending = 0;
    }
}

void func_8003AED8(FileRequest *request) {
    if (func_8003C3FC()) {
        func_8003CAB0(2);
        func_8003CAF8(0);
    }
    func_8003C900(request->resource);
}

typedef struct {
    s32 word00;
    s32 word04;
    s32 record_index;
    char pad0C[64];
} EngineDirectorySlotView;

typedef struct {
    EngineState prefix;
    s32 empty_scan_count, record_count, record_cursor;
    EngineDirectorySlotView slots[15];
    EngineDirectoryRecord records[15];
} EngineDirectoryStateView;

extern char D_8005657C[];
extern s32 D_800619CC_arr[] __asm__("D_800619CC");
extern u32 D_800619D0_arr[] __asm__("D_800619D0");
extern s32 D_800619D4[15];
extern u32 D_80010E58[];
extern char D_80010E68[];
s32 func_8003D740(char *, char *, ...);
s32 func_8003E218(char *, s32);
s32 func_8003E228(s32, void *, s32);
s32 func_8003C6E4(const char *);
void func_8003B5E0(u8 *);
char *BIOS_StrCpy(char *, const char *);
void func_8003C970(u8 *);
void func_8001A754(s32, s32, void *, s32, s32);
void func_8001A850(s32, u32, s32, u16 *, u8 *);

#define ENGINE_CARD_SCAN_RETRY(io, request) ({ \
    s32 retries = 0, failed; \
    do { \
        if (io) break; \
        retries++; \
    } while (retries < 3); \
    if (retries >= 3) { \
        func_8003ADB8((s32 **)(request)); \
        failed = 1; \
    } else { \
        failed = 0; \
    } \
    failed; \
})

void func_8003AF24(void)
{
    char path[64];
    u8 images[3][0x80];
    EngineCardBlock block;
    EngineFileRequest request;
    s32 descriptor;
    s32 invalid = 0;
    s32 slot_idx;
    s32 cur_rec;
    s32 blocks;
    s32 i, j;

    slot_idx = D_80056564->word08;
    request.resource = &descriptor;
    descriptor = -1;
    if (((EngineDirectoryStateView *)D_80056564)->record_cursor >= ((EngineDirectoryStateView *)D_80056564)->record_count) {
        func_8003CAD8(2);
        func_8003CAF8(0);
        return;
    }
    cur_rec = ((EngineDirectoryStateView *)D_80056564)->record_cursor;
    func_8003D740(path, D_8005657C, D_80056574,
        ((EngineDirectoryStateView *)D_80056564)->records[cur_rec].bytes);
    if (ENGINE_CARD_SCAN_RETRY((descriptor = func_8003E218(path, 1)) >= 0, &request))
        return;
    if (ENGINE_CARD_SCAN_RETRY(func_8003E228(descriptor, &block, 128) == 128, &request))
        return;
    if (func_8003C6E4((char *)((EngineDirectoryStateView *)D_80056564)->records[cur_rec].bytes)) {
        ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word00 = 1;
    } else {
        ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word00 = 0;
    }
    ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04 = block.header.icons - 0x10;
    if (((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04 < 1
        || ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04 > 3) {
        ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04 = 1;
        invalid = 1;
    }
    if (!invalid) {
        ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].pad0C[0] = 0;
        if ((u8)block.header.title[0] >= 0x80) {
            func_8003B5E0((u8 *)&block);
        }
        block.header.title[31] = 0;
        BIOS_StrCpy((char *)((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].pad0C,
            block.header.title);
    } else {
        __builtin_memcpy(((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].pad0C,
            D_80010E58, 13);
    }
    func_8003C970((u8 *)((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].pad0C);
    if (invalid) {
        blocks = 1;
    } else {
        blocks = block.header.blocks;
    }
    ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].record_index = cur_rec;
    if (!invalid) {
        for (i = 0; i < ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04; i++) {
            if (ENGINE_CARD_SCAN_RETRY(func_8003E228(descriptor, images[i], 128) == 128, &request))
                return;
        }
    }
    for (i = 0; i < blocks; i++) {
        char part_str[80];
        func_8003D740(part_str, D_80010E68, i + 1, blocks);
        func_8001A754(D_800619CC_arr[0], (slot_idx + i) << 8,
            i == 0 ? (char *)((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].pad0C : part_str,
            0x28, 1);
    }
    if (!invalid) {
        for (i = 0; i < blocks; i++) {
            for (j = 0; j < 3; j++) {
                s32 img_idx = j < ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04 ? j : 0;
                func_8001A850(1, D_800619D0_arr[0], ((slot_idx + i) * 3 + j) << 8,
                    j == 0 ? block.header.palette : NULL,
                    images[img_idx]);
            }
        }
    }
    D_800619D4[slot_idx] = 0;
    D_800619D4[slot_idx] = ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word04 << 1;
    if (((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word00 != 0) {
        if (!invalid) {
            j = 0;
            do {
                if (func_8003E228(descriptor, &block, 128) == 128)
                    break;
                j++;
            } while (j < 30);
            if (j == 30) {
                ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx].word00 = 0;
                D_800619D4[slot_idx] |= 0x10;
            } else {
                D_800619D4[slot_idx] |= 8;
                D_800619D4[slot_idx] |= *(s32 *)&block << 5;
            }
        }
    }
    if (invalid) {
        D_800619D4[slot_idx] |= 0x20000;
    }
    D_800619D4[slot_idx] |= 1;
    func_8003C900(&descriptor);
    if (!invalid) {
        for (j = 1; j < blocks; j++) {
            ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx + j] =
                ((EngineDirectoryStateView *)D_80056564)->slots[slot_idx];
            D_800619D4[slot_idx + j] = D_800619D4[slot_idx];
        }
    }
    ((EngineDirectoryStateView *)D_80056564)->record_cursor++;
    D_80056564->word08 += blocks;
}

extern u8 D_80053890[][2];
char *BIOS_StrCpy(char *, const char *);

/* Convert a Shift-JIS memory-card block title in place to printable ASCII. */
void func_8003B5E0(u8 *header)
{
    u8 *dst;
    s32 i, j;
    u8 c1, c2, out;
    s32 len = 64;

    header += 4;
    dst = header;
    for (i = 0; i < len; i += 2, header += 2) {
        c1 = header[0];
        c2 = header[1];
        if (c1 < 0x81) {
            out = c1;
            header--;
        } else if (c1 == 0xA0) {
            out = ' ';
            header--;
        } else if (c1 == 0x81) {
            out = '.';
            for (j = 0; D_80053890[j][0] != 0xFF; j++) {
                if (D_80053890[j][1] == c2) {
                    out = D_80053890[j][0];
                    break;
                }
            }
        } else if (c1 == 0x82) {
            out = '?';
            if ((c2 >= 0x60 && c2 <= 0x79) || (c2 >= 0x4F && c2 <= 0x58)) {
                out = c2 - 0x1F;
            }
            if (c2 >= 0x81 && c2 <= 0x9A) {
                out = c2 - 0x20;
            }
        } else if (c1 >= 0xA1 && c1 <= 0xDF) {
            out = '?';
            header--;
        } else {
            out = '?';
        }
        if (out != 0 && (out < 0x20 || out > 0x7E)) {
            out = ' ';
        }
        *dst++ = out;
        if (out == 0) {
            break;
        }
    }
}

/* Convert an ASCII title string in place to big-endian Shift-JIS characters. */
void func_8003B74C(char *title, s32 len)
{
    char buf[64];
    s32 i, j;
    s32 ended = 0;
    u16 *dst;
    char *p;
    u8 c;

    BIOS_StrCpy(buf, title);
    dst = (u16 *)title;
    p = buf;
    for (i = 0; i < len; p++, i++, dst++) {
        c = *p;
        if (ended) {
            *dst = 0x8140;
        } else if (c >= 'a' && c <= 'z') {
            *dst = c + 0x8220;
        } else if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            *dst = c + 0x821F;
        } else {
            *dst = 0x8140;
            for (j = 0; D_80053890[j][0] != 0xFF; j++) {
                if (D_80053890[j][0] == c) {
                    *dst = D_80053890[j][1] | 0x8100;
                    break;
                }
            }
            if (c == 0) {
                ended = 1;
                *dst = 0;
            }
        }
    }
    p = title;
    for (i = 0; i < len; i++, p += 2) {
        c = p[0];
        p[0] = p[1];
        p[1] = c;
    }
}

extern char D_80056574[], D_8005657C[];
extern char D_80010E78[], D_80010E88[], D_80010E98[], D_80010EB0[];
extern EngineByteRecord D_8005703C;
extern s32 D_80061974;
extern u32 D_800619D0;
s32 func_8003D740(char *, char *, ...);
void func_8003D730(char *, s32);
s32 func_8003E218(char *, s32), func_8003E238(s32, void *, s32);
s32 func_8003C6E4(const char *), func_8003CAF8(s32), func_8003CAD8(s32);
void func_8001A850(s32, u32, s32, u16 *, u8 *);

static inline EngineDirectorySlot *engine_selected_file(void)
{
    s32 count = D_80056564->word08;
    s32 index = D_80056564->word0C;

    if (count > 0 && index < count)
        return &((EngineDirectoryState *)D_80056564)->slots[index];
    return NULL;
}

/* This writer reuses its operation counter across filename selection,
 * buffer clearing and I/O attempts; each failed operation runs full cleanup. */
#define ENGINE_CARD_WRITE_RETRY(io, request, attempts) ({ \
    s32 failed; \
    attempts = 0; \
    do { \
        if (io) break; \
        attempts++; \
    } while (attempts < 3); \
    if (attempts >= 3) { \
        func_8003AE08(request); \
        failed = 1; \
    } else { \
        failed = 0; \
    } \
    failed; \
})

void func_8003B8B8(s32 mode)
{
    char path[64];
    u8 images[3][0x80];
    EngineCardBlock block;
    EngineFileRequest request;
    s32 descriptor = -1;
    EngineDirectorySlot *slot;
    s32 index, counter;

    slot = engine_selected_file();
    if (mode == 6) {
        D_8005668C = func_8002F778(999999);
        D_80056690 = 0;
    }
    request.resource = &descriptor;
    request.pending = (s32 *)&D_80056690;
    request.path = path;
    if (slot != NULL && slot->word00 == 0) {
        func_8003D740(path, D_8005657C, D_80056574,
            ((EngineDirectoryState *)D_80056564)->records[slot->record_index].bytes);
        if (mode == 6) {
            VSync(20);
            if (!ENGINE_CARD_WRITE_RETRY(({
                    s32 status = func_8003E288(path);
                    VSync(20);
                    index = status;
                    index;
                }) == 1, &request, counter)) func_8003CAF8(7);
            return;
        }
    } else if (mode == 6) {
        func_8003CAF8(7);
        mode = 7;
    }
    if (slot != NULL && slot->word00 != 0) {
        func_8003D740(path, D_8005657C, D_80056574,
            ((EngineDirectoryState *)D_80056564)->records[slot->record_index].bytes);
    } else {
        counter = ((EngineDirectoryState *)D_80056564)->record_count - 1;
        index = 0;
        if (counter >= 0) {
            counter = counter * sizeof(EngineDirectoryRecord)
                + CRASH_OFFSETOF(EngineDirectoryState, records);
            if (func_8003C6E4((char *)((u8 *)D_80056564 + counter))) {
                EngineDirectoryRecord *record =
                    (EngineDirectoryRecord *)((u8 *)D_80056564 + counter);
                index = (record->bytes[12] - '0') * 10 + record->bytes[13] - '/';
            }
        }
        if (index >= 100) index = 99;
        func_8003D740(path, D_80010E78, D_80056574, D_80010E88, index, D_8005668C);
    }
    if (slot == NULL || slot->word00 == 0) {
        if (mode == 7) {
            VSync(20);
            if (!ENGINE_CARD_WRITE_RETRY(
                    (descriptor = func_8003E218(path, 0x10200)) >= 0,
                    &request, counter)) {
                func_8003D730(D_80010E98, descriptor);
                func_8003C900(&descriptor);
                D_80056690 = 1;
                func_8003CAF8(8);
            }
            return;
        }
    } else if (mode == 7) {
        func_8003CAF8(8);
    }
    if (ENGINE_CARD_WRITE_RETRY(
            (descriptor = func_8003E218(path, 2)) >= 0, &request, counter)) return;
    for (counter = 127; counter >= 0; counter--) block.bytes[counter] = 0;
    block.header.magic[0] = 'S';
    block.header.magic[1] = 'C';
    block.header.icons = 0x13;
    block.header.blocks = 1;
    func_8003D740(block.header.title, D_80010EB0, D_80061974);
    func_8003B74C(block.header.title, 32);
    func_8001A850(2, D_800619D0, 0x2D00, block.header.palette, images[0]);
    func_8001A850(2, D_800619D0, 0x2D00, NULL, images[1]);
    func_8001A850(2, D_800619D0, 0x2E00, NULL, images[2]);
    if (ENGINE_CARD_WRITE_RETRY(
            func_8003E238(descriptor, &block, 128) == 128, &request, counter)) return;
    for (index = 0; index < 3; index++) {
        if (ENGINE_CARD_WRITE_RETRY(
                func_8003E238(descriptor, images[index], 128) == 128,
                &request, counter)) return;
    }
    func_8003BE40(&block.record);
    for (index = 0; index < 5; index++) {
        if (ENGINE_CARD_WRITE_RETRY(
                func_8003E238(descriptor, &block, 128) == 128,
                &request, counter)) return;
    }
    func_8003C900(&descriptor);
    func_8003CAD8(2);
    func_8003CAF8(0);
    func_8003C9B8();
    BIOS_StrCpy((char *)&D_8005703C, path + 5);
    func_8003CAD8(16);
}

#undef ENGINE_CARD_WRITE_RETRY

/* Word views of the runtime values serialised in the save record. */
extern u32 D_80061944[], D_80061908[], D_8006190C[], D_80061910[];
extern u32 D_80061914[], D_80061918[], D_80061988[], D_800619AC[];
extern u32 D_80061948[], D_800618DC[], D_80061A10[], D_80061A14[];
u32 func_8003BFFC(u8 *, u32);
void func_80026200(s32);

void func_8003BE40(EngineSaveRecord *record)
{
    s32 index;
    u32 settings;

    for (index = sizeof(*record) - 1; index >= 0; index--)
        ((u8 *)record)[index] = 0;
    record->word00 = D_80061944[0] | (D_80061A10[0] << 5)
        | (D_80061A14[0] << 10);
    record->word04 = D_80061944[0];
    record->word08 = D_80061908[0];
    record->word0C = D_8006190C[0];
    record->word10 = D_80061910[0];
    record->word14 = D_80061914[0];
    record->word18 = D_80061918[0];
    record->word1C = D_80061988[0];
    settings = D_800619AC[0];
    record->word24 = 0;
    record->word20 = settings;
    record->checksum = func_8003BFFC((u8 *)record, sizeof(*record));
}

inline s32 func_8003BF34(EngineSaveRecord *record)
{
    u32 level, settings;
    u32 checksum = record->checksum;

    record->checksum = 0;
    if (checksum != func_8003BFFC((u8 *)record, sizeof(*record))) {
        return 0;
    } else {
        func_80026200(1);
        level = record->word04;
        D_80061944[0] = level;
        D_80061908[0] = record->word08;
        D_8006190C[0] = record->word0C;
        D_80061910[0] = record->word10;
        D_80061914[0] = record->word14;
        D_80061918[0] = record->word18;
        D_80061988[0] = record->word1C;
        settings = record->word20;
        D_800619AC[0] = settings;
        D_80061948[0] = level;
        D_800618DC[0] = level;
        return 1;
    }
}

#include "engine/checksum.c"

extern char D_80056574[], D_8005657C[];
s32 func_8003D740(char *, char *, ...);
s32 func_8003E218(char *, s32);
s32 func_8003E228(s32, void *, s32);
s32 func_8003CAF8(s32);

/* Retry the I/O expression up to three times and release the event request
 * on failure. The expression is evaluated anew for each attempt. */
#define ENGINE_CARD_RETRY(io, request) ({ \
    s32 retries = 0, failed; \
    do { \
        if (io) break; \
        retries++; \
    } while (retries < 3); \
    if (retries >= 3) { \
        func_8003AED8(request); \
        failed = 1; \
    } else { \
        failed = 0; \
    } \
    failed; \
})

s32 func_8003C038(void)
{
    char path[64];
    u8 blocks[3][0x80];
    EngineSaveRecord record;
    EngineFileRequest request;
    s32 descriptor = -1;
    EngineDirectorySlot *slot;
    s32 index;

    slot = engine_selected_file();
    request.resource = &descriptor;
    if (slot == NULL || slot->word00 == 0) {
        func_8003CAB0(2);
        func_8003CAF8(0);
        return 0;
    }
    func_8003D740(path, D_8005657C, D_80056574,
        ((EngineDirectoryState *)D_80056564)->records[slot->record_index].bytes);
    if (ENGINE_CARD_RETRY(
            (descriptor = func_8003E218(path, 1)) >= 0, &request)) return 0;
    if (ENGINE_CARD_RETRY(
            func_8003E228(descriptor, &record, sizeof(record)) == sizeof(record),
            &request)) return 0;
    for (index = 0; index < 3; index++) {
        if (ENGINE_CARD_RETRY(
                func_8003E228(descriptor, blocks[index], sizeof(blocks[index]))
                    == sizeof(blocks[index]), &request)) return 0;
    }
    index = 0;
    do {
        if (ENGINE_CARD_RETRY(
                func_8003E228(descriptor, &record, sizeof(record)) == sizeof(record),
                &request)) return 0;
        if (func_8003BF34(&record)) break;
        index++;
    } while (index < 5);
    if (index == 5) {
        if (func_8003C3FC()) {
            func_8003CAF8(0);
            func_8003CAB0(2);
        }
    } else {
        func_8003CAF8(0);
    }
    func_8003C900(&descriptor);
    return 1;
}

#undef ENGINE_CARD_RETRY

extern char D_80056574[];
s32 func_8003E258(const char *);
s32 func_8003C3FC(void);
s32 func_8003CAD8(s32);
s32 func_8003CAB0(s32);
s32 func_8003CAF8(s32);
void func_8003C358(void) {
    s32 ready;
    s32 state;
    /* Preserve the retail counter samples around the BIOS call. */
    (void)D_80034520;
    ready = func_8003E258(D_80056574);
    (void)D_80034520;
    if (ready == 1) {
        func_8003CAD8(2);
        state = 4;
    } else {
        if (func_8003C3FC() == 0) return;
        state = 2;
    }
    func_8003CAB0(state);
    func_8003CAF8(0);
}

void func_8003C3CC(void)
{
}

void func_8003C3D4(void)
{
}

void func_8003C3DC(void)
{
}

s32 func_8003C3E4(s32 arg0)
{
    D_80056564->word14 = 0;
    D_80056564->word10 = arg0;
    return 0;
}

s32 func_8003C3FC(void) {
    s32 temp_v0;

    temp_v0 = D_80056564->word14 + 1;
    D_80056564->word14 = temp_v0;
    return temp_v0 >= D_80056564->word10;
}

s32 func_8003C420(void) {
 func_8002F778(999);
 if (func_8003E1C8(D_800566C4)==1) return 0;
 if (func_8003E1C8(D_800566C8)==1) return 1;
 if (func_8003E1C8(D_800566CC)==1) return 2;
 if (func_8003E1C8(D_800566D0)==1) {func_8003CAB0(16);return 3;}
 return -1;
}

s32 func_8003C4A4(void) {
 s32 result;
 do {
  func_8002F778(999);
  if (func_8003E1C8(D_800566C4)==1) result=0;
  else if (func_8003E1C8(D_800566C8)==1) result=1;
  else if (func_8003E1C8(D_800566CC)==1) result=2;
  else if (func_8003E1C8(D_800566D0)==1) {func_8003CAB0(16);result=3;}
  else result=-1;
 } while (result==-1);
 return result;
}

#include "engine/state_event_test.c"

s32 func_8003C580(void) {
 func_8002F778(999);
 if (func_8003E1C8(D_800566EC)==1) return 0;
 if (func_8003E1C8(D_800566F0)==1) return 1;
 if (func_8003E1C8(D_800566F8)==1) return 2;
 if (func_8003E1C8(D_800566FC)==1) return 3;
 return -1;
}

s32 func_8003C608(void) {
 s32 result;
 do {
  func_8002F778(999);
  if (func_8003E1C8(D_800566EC)==1) result=0;
  else if (func_8003E1C8(D_800566F0)==1) result=1;
  else if (func_8003E1C8(D_800566F8)==1) result=2;
  else if (func_8003E1C8(D_800566FC)==1) result=3;
  else result=-1;
 } while (result==-1);
 return result;
}

void func_8003C69C(void) {
    func_8003E1C8(D_800566EC);
    func_8003E1C8(D_800566F0);
    func_8003E1C8(D_800566F8);
    func_8003E1C8(D_800566FC);
}

s32 BIOS_StrNCmp(const char *, const char *, s32);                      /* extern */
extern char D_80010E88[];

s32 func_8003C6E4(const char *arg0) {
    return BIOS_StrNCmp(D_80010E88, arg0, 0xC) == 0;
}

extern char D_80056584[];
char *BIOS_StrCpy(char *, const char *);
char *BIOS_StrCat(char *, const char *);
EngineDirectoryRecord *func_8003E268(char *, EngineDirectoryRecord *);
EngineDirectoryRecord *func_8003E278(EngineDirectoryRecord *);

/* Append the search suffix, enumerate records, and cap the reported count. */
s32 func_8003C714(const char *path, EngineDirectoryRecord *entries)
{
    char pattern[128];
    s32 count;
    EngineDirectoryRecord *found;

    BIOS_StrCpy(pattern, path);
    BIOS_StrCat(pattern, D_80056584);
    count = 0;
    found = func_8003E268(pattern, entries);
    while (entries == found) {
        count++;
        entries++;
        found = func_8003E278(entries);
    }
    if (count >= 16) count = 15;
    return count;
}

s32 BIOS_StrCmp(char *, char *);
void func_80033FBC(void *, void *, s32);

/* Sort Crash directory entries ahead of other saves and alphabetically. */
void func_8003C7A8(EngineDirectoryRecord *entries, s32 count)
{
    EngineDirectoryRecord temp;
    s32 i, j, is_crash, match;
    char *entry_name;

    for (i = 0; i < count; i++) {
        entry_name = (char *)&entries[i];
        is_crash = BIOS_StrNCmp(D_80010E88, entry_name, 12) == 0;
        for (j = i + 1; j < count; j++) {
            match = BIOS_StrNCmp(D_80010E88, (char *)&entries[j], 12) == 0;
            if (!is_crash) {
                if (match) {
                    continue;
                }
            } else {
                if (!match) {
                    goto swap;
                }
            }
            match = BIOS_StrCmp(entry_name, (char *)&entries[j]);
            if (match > 0) {
            swap:
                func_80033FBC(&entries[i], &temp, 0x14);
                func_80033FBC(&entries[j], &entries[i], 0x14);
                func_80033FBC(&temp, &entries[j], 0x14);
                i--;
                break;
            }
        }
    }
}

s32 func_8003E248(s32);

void func_8003C900(s32 *arg0) {
    s32 temp_a0;

    temp_a0 = *arg0;
    if (temp_a0 >= 0) {
        func_8003E248(temp_a0);
    }
    *arg0 = -1;
}

void func_8003C944(u32 ticks) {
    u32 start = D_80034520;
    /* Preserve the retail unsigned subtraction order. */
    do {
    } while ((u32)(start - D_80034520) < ticks);
}

void func_8003C970(u8 *arg0) {
    u8 *var_a0;
    u8 temp_v1;

    var_a0 = arg0;
    if (*var_a0 != 0) {
        do {
            temp_v1 = *var_a0;
            if ((u32) (temp_v1 - 0x61) < 0x1AU) {
                *var_a0 = temp_v1 + 0xE0;
            }
            var_a0 += 1;
        } while (*var_a0 != 0);
    }
}

s32 func_8003CB88(void);
s32 func_8003C9B8(void)
{
    if (!(func_8003CB88() & 13)) {
        EngineDirectoryState *state;
        func_8003CAF8(1);
        state = (EngineDirectoryState *)D_80056564;
        state->prefix.word14 = 0;
        state->prefix.word10 = 64;
        state->empty_scan_count = 0;
        return 0;
    } else {
        return 1;
    }
}

extern s32 D_800619D4[15];
s32 func_8003CA04(s32 flags)
{
    s32 index;

    D_80056564->word08 = 0;
    D_80056564->word14 = 0;
    for (index = 14; index >= 0; index--) D_800619D4[index] = 0;
    func_8003CAB0(flags);
    return 0;
}

void func_8001A754(s32, s32, void *, s32, s32);
extern u8 D_80056588[];
extern s32 D_800619CC;
void func_8003CA50(void)
{
    s32 channel;
    for (channel = 0; channel < 15; channel++) {
        func_8001A754(D_800619CC, channel << 8, D_80056588, 0x28, 1);
    }
}


s32 func_8003CAB0(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 | D_80056564->word04;
    D_80056564->word04 = temp_a0;
    D_80061978 = temp_a0;
    return 0;
}

s32 func_8003CAD8(s32 arg0)
{
    D_80056564->word04 = ~arg0 & D_80056564->word04;
    return 0;
}

/* The retail reset routine embeds this same mode/flag update. Keep its
 * inline copy and the public setter derived from one implementation. */
static inline s32 engine_set_mode(s32 mode)
{
    s32 flags;

    D_80056564->word00 = mode;
    if (mode >= 0) {
        if (mode < 2 || mode == 4) D_80056564->word18 = 1;
        if (D_80056564->word00 == 0) {
            D_80056564->word04 &= ~1;
        } else {
            goto activate;
        }
    } else {
activate:
        flags = D_80056564->word04 | 1;
        D_80056564->word04 = flags;
        D_80061978 = flags;
    }
    return 0;
}

s32 func_8003CAF8(s32 mode)
{
    return engine_set_mode(mode);
}

s32 func_8003CB74(void)
{
    return D_80056564->word00;
}

s32 func_8003CB88(void)
{
    return D_80056564->word04;
}

s32 func_8003E1A8(u32,s32,s32,void (*)(void));
void func_8003E1F8(void),func_8003E208(void),func_80051454(void),func_8003E198(void);
void func_80051444(s32);
s32 func_8003E1D8(s32);
void func_8003CB9C(void) {
func_8003E1F8();
D_800566C4=func_8003E1A8(0xF4000001,4,0x2000,NULL);
D_800566C8=func_8003E1A8(0xF4000001,32768,0x2000,NULL);
D_800566CC=func_8003E1A8(0xF4000001,256,0x2000,NULL);
D_800566D0=func_8003E1A8(0xF4000001,8192,0x2000,NULL);
D_800566EC=func_8003E1A8(0xF0000011,4,0x2000,NULL);
D_800566F0=func_8003E1A8(0xF0000011,32768,0x2000,NULL);
D_800566F8=func_8003E1A8(0xF0000011,256,0x2000,NULL);
D_800566FC=func_8003E1A8(0xF0000011,8192,0x2000,NULL);
func_8003E208();
VSync(5);
func_80051444(1);
VSync(5);
func_80051454();
VSync(5);
func_8003E198();
VSync(5);
func_8003E1D8(D_800566C4);
func_8003E1D8(D_800566C8);
func_8003E1D8(D_800566CC);
func_8003E1D8(D_800566D0);
func_8003E1D8(D_800566EC);
func_8003E1D8(D_800566F0);
func_8003E1D8(D_800566F8);
func_8003E1D8(D_800566FC);
}

void func_80051464(void);

s32 func_8003CD3C(void) {
    func_80051464();
    return 0;
}

/* Fifteen consecutive words ending at 0x80061A0C. */
extern s32 D_800619D4[15];

void func_8003CD60(s32 flags)
{
    s32 index, value;

    D_80056564->word08 = 0;
    D_80056564->word14 = 0;
    for (index = 14; index >= 0; index--) D_800619D4[index] = 0;
    func_8003CAB0(0);
    engine_set_mode(0);
    value = flags | (D_80056564->word04 & ~63);
    D_80056564->word04 = value;
    D_80061978 = value;
}

/* Six-byte state copied as an unaligned record in retail. */
typedef EngineByteRecord ByteRecord;
extern ByteRecord D_80056590, D_8005703C;

void func_8003CD60(s32);
s32 func_8003D740(char *, char *, ...);

s32 func_8003CE20(void)
{
    EngineState *state = LIBC_Calloc(1, 0x6F4);
    D_80056564 = state;
    if (D_80056568 != 0) {
        state->word04 |= 0x10;
        D_80061978 = state->word04;
        func_8003D740((char *)&D_8005703C, (char *)&D_80056590);
    } else {
        state->word04 &= ~0x10;
    }
    func_8003CD60(4);
    return 0;
}

s32 func_8003CEA8(void)
{
    D_80056568 = ((u32)D_80056564->word04 >> 4) & 1;
    if (D_80056564 != NULL) {
        LIBC_Free(D_80056564);
        D_80056564 = NULL;
    }
    return 0;
}

void BIOS_BZero(void *, s32);
void func_80051484(void), func_80051474(s32, s32, void *);

/* Each event corresponds to one of the four native completion statuses. */
static inline s32 engine_card_status(void)
{
    if (func_8003E1C8(D_800566EC) == 1) return 0;
    if (func_8003E1C8(D_800566F0) == 1) return 1;
    if (func_8003E1C8(D_800566F8) == 1) return 2;
    if (func_8003E1C8(D_800566FC) == 1) return 3;
    return -1;
}

s32 func_8003CEF0(s32 port)
{
    u8 sector[0x80];
    s32 status;

    BIOS_BZero(sector, sizeof(sector));
    func_8003E1C8(D_800566EC);
    func_8003E1C8(D_800566F0);
    func_8003E1C8(D_800566F8);
    func_8003E1C8(D_800566FC);
    func_80051484();
    func_80051474(port, 0, sector);
    do {
        func_8002F778(999);
        status = engine_card_status();
    } while (status == -1);
    if (status == 0) {
        if (sector[0] == 'M' && sector[1] == 'C') return 1;
        else return 0;
    }
    return -1;
}

s32 func_8003D008(void)
{
    D_80056564->word04 &= ~0x20;
    return 0;
}


/* Alias view of the shared flag word; retain the native ordering of state
 * writes and their externally visible shadow store. */

s32 func_8003D028(s32 value)
{
    EngineState *state = D_80056564;

    if (!(state->word04 & 13)) {
        state->word00 = 6;
        engine_flag_shadow[0] = state->word04 |= 1;
        state->word14 = 0;
        state->word10 = 32;
        state->word0C = value;
        return 0;
    } else {
        engine_flag_shadow[0] = state->word04 |= 2;
        return 1;
    }
}
/* Select the directory slot matching the last active save filename. */
s32 func_8003D094(void)
{
    s32 i;

    if (D_80056564->word04 & 13) {
        engine_flag_shadow[0] = D_80056564->word04 |= 2;
        return 1;
    }
    for (i = 0; i < D_80056564->word08; i++) {
        if (BIOS_StrCmp((char *)&D_8005703C,
                (char *)((EngineDirectoryState *)D_80056564)
                    ->records[((EngineDirectoryState *)D_80056564)->slots[i].record_index]
                    .bytes) == 0) {
            break;
        }
    }
    if (i != D_80056564->word08) {
        D_80056564->word0C = i;
        D_80056564->word00 = 6;
        engine_flag_shadow[0] = D_80056564->word04 |= 1;
        D_80056564->word14 = 0;
        D_80056564->word10 = 32;
        return 0;
    } else {
        engine_flag_shadow[0] = D_80056564->word04 |= 2;
        return 1;
    }
}

s32 func_8003D1B4(void) {
    D_8005703C = D_80056590;
    return 0;
}

void func_80051424(s32);

s32 func_8003D1F0(void)
{
    s32 event;

    if (D_80056564 ? (D_80056564->word04 & 16) : D_80056568) {
        return 1;
    }
    if (BIOS_StrCmp((char *)&D_8005703C, (char *)&D_80056590) == 0) {
        return 1;
    }

    func_8003E1C8(D_800566C4);
    func_8003E1C8(D_800566C8);
    func_8003E1C8(D_800566CC);
    func_8003E1C8(D_800566D0);
    func_80051424(0);

again:
    {
        func_8002F778(999);
        if (func_8003E1C8(D_800566C4) == 1) {
            event = 0;
        } else if (func_8003E1C8(D_800566C8) == 1) {
            event = 1;
        } else if (func_8003E1C8(D_800566CC) == 1) {
            event = 2;
        } else if (func_8003E1C8(D_800566D0) == 1) {
            func_8003CAB0(16);
            event = 3;
        } else {
            event = -1;
        }
    }
    if (event == -1) {
        goto again;
    }
    switch (event) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
        return 1;
    default:
        return 1;
    }
}

s32 func_8003D308(void)
{
    s32 event;

    func_8003E1C8(D_800566C4);
    func_8003E1C8(D_800566C8);
    func_8003E1C8(D_800566CC);
    func_8003E1C8(D_800566D0);
    func_80051424(0);

again:
    {
        func_8002F778(999);
        if (func_8003E1C8(D_800566C4) == 1) {
            event = 0;
        } else if (func_8003E1C8(D_800566C8) == 1) {
            event = 1;
        } else if (func_8003E1C8(D_800566CC) == 1) {
            event = 2;
        } else if (func_8003E1C8(D_800566D0) == 1) {
            func_8003CAB0(16);
            event = 3;
        } else {
            event = -1;
        }
    }
    if (event == -1) {
        goto again;
    }
    {
        s32 result = event;
        if (result != 2) {
            result = 0;
        } else {
            result = 1;
        }
        return result;
    }
}
s32 func_8003D3D8(s32 value)
{
    EngineState *state = D_80056564;

    if (!(state->word04 & 13)) {
        state->word00 = 2;
        engine_flag_shadow[0] = state->word04 |= 1;
        state->word14 = 0;
        state->word10 = 32;
        state->word0C = value;
        return 0;
    } else {
        engine_flag_shadow[0] = state->word04 |= 2;
        return 1;
    }
}
s32 func_8003D444(void)
{
    EngineState *state = D_80056564;

    if (state->word00 == 0) {
        state->word00 = 3;
        engine_flag_shadow[0] = state->word04 |= 1;
        state->word14 = 0;
        state->word10 = 3;
        return 0;
    } else {
        engine_flag_shadow[0] = state->word04 |= 2;
        return 1;
    }
}


s32 func_8003D4AC(void) {
    s32 result;
    if (D_80056564) {
        func_8003CD60((D_80056564->word04 & 0x10) | 4);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
