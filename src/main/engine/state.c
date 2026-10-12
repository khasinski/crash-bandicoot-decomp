#include "common.h"
#include "engine_ticks.h"
#define CRASH_ENGINE_STATE_STORAGE
#include "engine_state.h"
#include "resource.h"
#include "gool.h"

/* GCC_VERSION: 2.6.3 */



/* Mode request and the eight-byte name/format records at 0x80056500. */
s32 D_80056500 = 1;
char D_80056504[8] = "0b_pZ";
char D_8005650C[8] = "0c_pZ";
char D_80056514[8] = "0d_pZ";
char D_8005651C[8] = "0e_pZ";
char D_80056524[8] = "0f_pZ";
char D_8005652C[8] = "1e_pZ";
char D_80056534[8] = "1a_pZ";
char D_8005653C[8] = "2b_pZ";
char D_80056544[8] = "3a_pZ";
char D_8005654C[8] = "0a_pZ";
char D_80056554[8] = "%cMapP";
char D_8005655C[8] = "0MapP";

/* Retail initial value at 0x80056564 is zero; preserve its .sdata placement. */
EngineState *D_80056564 = NULL;
/* Preserved render-state flag, initial retail value 1 at 0x80056568. */
s32 D_80056568 = 1;
extern s32 D_80061978;


/* File cleanup requests and lifecycle entry points. */
typedef EngineFileRequest FileRequest;
s32 func_8003CEF0(s32);
s32 func_8003CAD8(s32);
s32 func_8003CAF8(s32);
s32 func_8003C9B8(void);
s32 func_8003C3FC(void);
s32 func_8003CA04(s32);
s32 func_8003CAB0(s32);
void func_8003C900(s32 *);
s32 CORE_VSync(s32);
s32 func_8003E288(char *);
s32 func_8003E1C8(s32);
s32 func_8002F778(s32);

/* Traversal storage and lifecycle share the recovered engine globals. */
#include "object_links.h"

/* GCC_VERSION: 2.6.3 */
typedef EngineMode25State State;
/* Real zero-initialized storage at 0x80056678..0x800566C4.
 * Unidentified words retain address names; the two typed owners are shared
 * with object_defaults and update_request. */
asm(".globl D_80056678, D_8005667C, D_80056680, D_80056684, D_80056688, D_8005668C, D_80056690, D_80056694, D_80056698, D_8005669C, D_800566A0, D_800566A4, D_800566A8, D_800566AC, D_800566B0, D_800566B4, D_800566B8, D_800566BC, D_800566C0");
s32 D_80056678;
u32 D_8005667C;
u32 D_80056680;
u32 D_80056684;
u32 D_80056688;
u32 D_8005668C;
u32 D_80056690;
u32 D_80056694;
u32 D_80056698;
u32 D_8005669C;
u32 D_800566A0;
u32 D_800566A4;
u32 D_800566A8;
u32 D_800566AC;
u32 D_800566B0;
GoolDefaultsObject *D_800566B4;
u32 D_800566B8, D_800566BC;
s32 D_800566C0;

/* Real engine globals in retail address order, 0x800566C4..0x800566FC.
 * The state and grid pointers retain their recovered pointer types. */
asm(".globl D_800566C4, D_800566C8, D_800566CC, D_800566D0, D_800566D4, D_800566D8, D_800566DC, D_800566E0, D_800566E4, D_800566E8, D_800566EC, D_800566F0, D_800566F4, D_800566F8, D_800566FC");
s32 D_800566C4;
s32 D_800566C8;
s32 D_800566CC;
s32 D_800566D0;
s32 D_800566D4;
s32 D_800566D8;
s32 D_800566DC;
State *D_800566E0;
s32 D_800566E4;
s32 D_800566E8;
s32 D_800566EC;
s32 D_800566F0;
s32 *D_800566F4;
s32 D_800566F8;
s32 D_800566FC;

extern void func_80032FDC(s32, s32, s32);
extern void *LIBC_Calloc(int, int);
extern void func_8003D680(s32);
extern s32 D_80056710;
s32 func_80031BAC(void)
{
    State *state;
    if(D_80056710 == 25) {
        state = LIBC_Calloc(1, sizeof(State));
        D_800566E0 = state;
        if(state == NULL) func_8003D680(-1);
    }
    return 0;
}

extern u32 D_800618D0;
extern s32 D_800618D4;
extern u32 D_8006194C[];
s32 func_80031EB4(void);

extern s32 D_8006189C[];

/* Apply a pending mode request and initialise the recovered mode-state words. */
s32 func_80031BF8(void)
{
    s32 request;
    u32 value;
    EngineMode25State *reset_state, *requested_state;
    u32 selection;
    request = D_80056500;
    D_80056500 = 0;
    D_80056678 = request;
    if (D_80056710 == 25) {
        D_8006189C[0] = (D_8006189C[0] & 0xFFFE3FF0) | 0x20000;
        if (request == 0) {
            value = D_800618D0;
            switch (value) {
            case 0: case 0x100: case 0x300: case 0x400:
                (D_800566E0)->word35D0 = (D_800566E0)->word35D4 = D_800618D4;
                selection = D_8006194C[0];
                (D_800566E0)->word3598 = 1;
                (D_800566E0)->word35A4 = selection;
                (D_800566E0)->word35A0 = selection;
                break;
            case 0x600:
                reset_state = D_800566E0;
                value = 5;
                goto set_value;
            case 0x200:
                reset_state = D_800566E0;
                value = 12;
set_value:
                D_800618D4 = value;
                reset_state->word35D4 = value;
                reset_state->word35D0 = value;
                value = 1;
                reset_state->word3598 = value;
                break;
            }
        } else {
            D_800618D4 = 10;
            requested_state = D_800566E0;
            requested_state->word35D4 = 10;
            requested_state->word35D0 = 10;
            requested_state->word3598 = 0;
        }
        func_80031EB4();
    }
    return 0;
}

s32 func_80015118(s32 *, s32, s32);
s32 func_80015458(s32 *, s32);
void func_80025A60(ResourceItemListView *, u8 *, s32, s32);
extern s32 D_80056400, D_8005640C;
extern s32 D_8006189C[];
extern ResourceSlotStateView D_800580A4[];

/* Change mode flags, recycle pending texture slots 8..14, and initialise
 * the item selected by the resource metadata before releasing the reference. */
void func_80031D50(s32 *reference, s32 mode)
{
    s32 index;
    ResourceItemListView *resource;
    D_80056400 = 0;
    D_8005640C = -1;
    func_8001BA18(func_8001B92C, func_8001D1E0, NULL);
    switch (mode) {
    case 0:
        D_8006189C[0] = (D_8006189C[0] & 0xFFFE3FF0) | 0x20000;
        D_800566E0->word359C = 1;
        break;
    case 1:
        D_8006189C[0] = 0xFFFF;
        D_800566E0->word359C = 0;
        for (index = 8; index < 15; index++) {
            if (D_800580A4[index].state == 30)
                D_800580A4[index].state = 1;
        }
        break;
    case 3:
        D_8006189C[0] = 0x2FFFC;
        D_800566E0->word359C = 1;
        break;
    }
    resource = (ResourceItemListView *)func_80015118(reference, 1, 1);
    func_80025A60(resource,
        resource->items[((ResourceItemSelection *)resource->items[0])->word204], 0, 2);
    func_80015458(reference, 1);
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80031EB4);

void func_80032244(void)
{
    func_8001BA18(func_8001B92C, func_8001D1E0, NULL);
    if(D_800566E0->word359C != 0)
        func_80032FDC(D_800566E0->word35D0, 0, -1);
}

extern void LIBC_Free(void *);
extern s32 D_80056710;
s32 func_80032298(void)
{
    if(D_800566E0 != NULL) LIBC_Free(D_800566E0);
    D_80056710 = 0;
    return 0;
}


INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800322CC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800324D4);
extern s32 D_800618BC[], D_80061A34;
void func_80024040(s32, s32, s32, s32, s32 *);

/* Finish the pending object request before selecting the next mode. */
void func_8003263C(s32 mode)
{
    s32 zero;

    if (D_80056400 && D_800618BC[0]) {
        zero = 0;
        func_80024040(0, D_800618BC[0], 0xC00, 1, &zero);
        D_8005640C = -1;
        D_80056400 = 0;
    }
    D_80061A34 = -256;
    D_800618D4 = mode;
    D_800566E0->word35D4 = mode;
    D_800566E0->word3598 = 5;
}
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800326D8);
/* Fill 16 rows by 33 columns of three-word coordinate/page entries. */
void func_80032AF4(u32 base_address)
{
    s32 simple_row;
    s32 right_half;
    s32 column;
    s32 y;
    s32 row;
    s32 page;
    s32 index;
    s32 x;
    s32 byte_offset;
    void *entry;

    row = 0;
    do {
        column = 0;
        simple_row = row < 15;
        index = row;
next_column:
        if (simple_row) {
            if (column < 0x1E) {
                right_half = column >= 0xF;
                x = column + right_half;
                y = row;
                page = right_half;
            } else {
                x = row + 0x20;
                y = column - 0x1E;
                page = 2;
            }
        } else {
            page = 3;
            x = (column % 15) + 0x30;
            y = column / 15;
        }
        byte_offset = index * 3;
        column += 1;
        byte_offset = byte_offset << 2;
        entry = (void *)(byte_offset + base_address);
        *(s32 *)((u8 *)entry + 0x0) = x;
        *(s32 *)((u8 *)entry + 0x4) = y;
        *(s32 *)((u8 *)entry + 0x8) = page;
        index += 0x10;
        if (column < 0x21) {
            goto next_column;
        }
        row += 1;
    } while (row < 0x10);
}

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80032BB4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80032DFC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80032FDC);
void func_80033464(void)
{
}
#include "func_8003346C.c"
void func_80033490(void *a, void *b, void *c, u32 color)
{
}
void func_80033498(void)
{
}
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800334A0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033878);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F18);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F38);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F58);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F78);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033F98);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80033FBC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034230);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034250);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034270);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034290);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800342B0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800342D8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034504);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034520);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034524);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034580);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003460C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80034B08);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800351C8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035370);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800353B0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035438);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035898);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80035E10);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80036340);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80036BF4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80036D9C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800375EC);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80037D50);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003864C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003899C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800389A8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80038AC4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80038DF8);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003905C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_800390D0);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003913C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_80039BD4);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003A144);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003A76C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003A94C);
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003AA7C);

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

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003AC2C);

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
        CORE_VSync(60);
        retries = 0;
        do {
            status = func_8003E288(request->path);
            CORE_VSync(20);
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

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003AF24);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003B5E0);

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003B74C);

extern char D_80056574[], D_8005657C[];
extern char D_80010E78[], D_80010E88[], D_80010E98[], D_80010EB0[];
extern EngineByteRecord D_8005703C;
extern s32 D_80061974;
extern u32 D_800619D0;
s32 func_8003D740(char *, char *, ...);
void func_8003D730(char *, s32);
char *BIOS_StrCpy(char *, const char *);
s32 func_8003E218(char *, s32), func_8003E238(s32, void *, s32);
s32 func_8003C6E4(const char *), func_8003CAF8(s32), func_8003CAD8(s32);
void func_8003B74C(char *, s32);
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
            CORE_VSync(20);
            if (!ENGINE_CARD_WRITE_RETRY(({
                    s32 status = func_8003E288(path);
                    CORE_VSync(20);
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
        counter = ((EngineDirectoryState *)D_80056564)->word20 - 1;
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
            CORE_VSync(20);
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

#include "checksum.c"

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

#include "state_event_test.c"

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

INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003C7A8);

extern s32 func_8003E248(s32);

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
        state->word1C = 0;
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
CORE_VSync(5);
func_80051444(1);
CORE_VSync(5);
func_80051454();
CORE_VSync(5);
func_8003E198();
CORE_VSync(5);
func_8003E1D8(D_800566C4);
func_8003E1D8(D_800566C8);
func_8003E1D8(D_800566CC);
func_8003E1D8(D_800566D0);
func_8003E1D8(D_800566EC);
func_8003E1D8(D_800566F0);
func_8003E1D8(D_800566F8);
func_8003E1D8(D_800566FC);
}

extern void func_80051464(void);

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
extern s32 engine_flag_shadow[] __asm__("D_80061978");

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
INCLUDE_ASM("asm/USA/main/nonmatchings/engine/state", func_8003D094);

s32 func_8003D1B4(void) {
    D_8005703C = D_80056590;
    return 0;
}

s32 BIOS_StrCmp(char *, char *);
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
