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
/* Sentinel values make the first card flags/mode poll register a change. */
s32 D_8005656C = -1;
u32 D_80056570 = 0xFFFFFFFF;


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
s32 VSync(s32);
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

void func_80032FDC(s32, s32, s32);
void *LIBC_Calloc(int, int);
void func_8003D680(s32);
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
extern volatile s32 D_800618D4;
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

#include "ns.h"
#include "render.h"
extern s32 D_800619B4[];
extern s32 D_8006193C[];
extern s32 D_80061940[];
extern s32 D_800618B8[];
extern u32 D_800618DC[];
extern u32 D_80061948[];
ResourceItemListView *func_80015A98(u32 *);
void func_8003D680(s32);
void func_80017790(void);
void func_80026200(s32);
s32 func_80012820(s32);
s32 func_8003D740(char *, char *, ...);
void func_8001BCC8(ResourceItemListView *, s32);
s32 func_80031EB4(void) {
    char buf[32];
    s32 ref;
    s32 mode;
    ResourceItemListView *list;
    s32 *header;
    s32 i;

    D_800619B4[0] = 0;
    switch (D_800566E0->word35D0) {
    case 1:
    case 2:
    case 3:
    case 4:
        func_8003D680(0);
    case 6:
    case 15:
        D_8005C53C->word114 = 0x25;
        break;
    case 5:
    case 8:
    case 12:
    case 13:
    case 14:
        D_8005C53C->word114 = 0x37;
        break;
    default:
        D_8005C53C->word114 = 0x5A;
        break;
    }
    func_80017790();
    switch (D_800566E0->word35D0) {
    case 12:
        ref = func_80012660(D_80056504);
        mode = 1;
        break;
    case 5:
        func_80026200(1);
        ref = func_80012660(D_8005650C);
        mode = 3;
        break;
    case 8:
        ref = func_80012660(D_80056514);
        mode = 3;
        break;
    case 13:
    case 14:
        ref = func_80012660(D_8005651C);
        mode = 1;
        break;
    case 6:
        ref = func_80012660(D_80056524);
        mode = 1;
        break;
    case 15:
        if (D_800618DC[0] == 99 || D_800618DC[0] < 10) {
            if (D_800618DC[0] == 9) {
                ref = func_80012660(D_8005652C);
            } else {
                ref = func_80012660(D_80056534);
            }
        } else if (D_800618DC[0] < 18 || D_800618DC[0] >= 50) {
            ref = func_80012660(D_8005653C);
        } else {
            ref = func_80012660(D_80056544);
        }
        mode = 1;
        break;
    default:
        ref = func_80012660(D_8005654C);
        mode = 0;
        break;
    }
    if (mode == 0) {
        func_80031D50(&ref, 0);
    }
    D_8006193C[0] = 0;
    D_80061940[0] = 0;
    switch (D_800566E0->word35D0) {
    case 1:
    case 2:
    case 3:
    case 4:
        D_800618B8[0] = ~D_800566E0->word35D0;
        break;
    case 5:
    case 6:
    case 8:
    case 12:
    case 13:
    case 14:
    case 15:
        func_80031D50(&ref, mode);
        break;
    default:
        D_800618B8[0] = 0;
        D_800566E0->word359C = 1;
        break;
    }
    D_8006189C[0] |= 0x200000;
    func_8003D740(buf, D_80056554, (u8)func_80012820(D_800566E0->word35D0));
    D_800566E0->word00 = func_80012660(buf);
    if ((D_8006189C[0] & 0x20000) && D_800566E0->word359C != 0) {
        s32 h1;
        list = func_80015A98((s32 *)&D_800566E0->word00);
        header = (s32 *)list->items[0];
        func_80032FDC(D_800566E0->word35D0, 1, 1);
        D_800566E0->word0C = header[0];
        h1 = header[1];
        D_800566E0->word14 = 0;
        D_800566E0->word18 = 0;
        D_800566E0->word10 = h1;
        D_800566E0->word04 = D_800566E0->word0C << 4;
        D_800566E0->word08 = D_800566E0->word10 << 4;
        for (i = 0; i < header[3]; i++) {
            if ((u32)*(s16 *)(list->items[i + 2] + 0x18) <= D_80061948[0]) {
                func_8001BCC8(list, i);
            }
        }
    }
    return 0;
}

void func_80032244(void)
{
    func_8001BA18(func_8001B92C, func_8001D1E0, NULL);
    if(D_800566E0->word359C != 0)
        func_80032FDC(D_800566E0->word35D0, 0, -1);
}

void LIBC_Free(void *);
extern s32 D_80056710;
s32 func_80032298(void)
{
    if(D_800566E0 != NULL) LIBC_Free(D_800566E0);
    D_80056710 = 0;
    return 0;
}


#include "ns.h"
#include "render.h"

void *LIBC_Malloc(u32);
void func_8004025C(s32);
void func_800169F8(void);
extern RenderBuffer *D_80058408;
extern s32 D_8005C54C;

typedef struct EngineGpuRect {
    s16 x, y, w, h;
} EngineGpuRect;

ResourceItemListView *func_80015A98(u32 *);
void func_80040484(EngineGpuRect *, void *);

s32 func_800322CC(s32 level, u8 *image, NsDirectory *dir)
{
    EngineGpuRect rect;
    u16 *buf;
    u16 *clut;
    s32 pass;
    u8 *src;
    s32 strip;
    s32 dx;
    s32 x;
    s32 y;
    u16 *dst;
    s32 row;
    s32 col;

    if (dir->word40C && dir->word410 && dir->word414
        && D_800618D0 != 0x600 && D_800618D0 != 0x200 && D_800618D0 != 0x500
        && (D_800618D0 != 0 || level != 25)) {
        buf = LIBC_Malloc(0x4000);
        func_8004025C(0);
        clut = (u16 *)image;
        for (pass = 0; pass < 2; pass++) {
            src = image + 0x200;
            func_800169F8();
            strip = 0;
            dx = dir->word410 / 2 - 0x100;
            x = D_80058408->drawing.env.clip.x - dx;
            y = D_80058408->drawing.env.clip.y - dir->word414 / 2 + 0x6C;
            for (; strip < dir->word414 / 8; strip++) {
                dst = buf;
                for (row = 0; row < 8; row++) {
                    for (col = 0; col < dir->word410; col++) {
                        *dst++ = clut[*src++];
                    }
                }
                rect.x = x;
                rect.y = y;
                y += 8;
                rect.w = dir->word410;
                rect.h = 8;
                func_80040484(&rect, buf);
                func_8004025C(0);
            }
            func_800172E8();
        }
        D_8005C54C = 2;
        LIBC_Free(buf);
    }
    return -255;
}

/* Upload one 8x16 background tile cell and update its packed CLUT id. */
void func_800324D4(EngineTileCell *cell)
{
    EngineGpuRect rect;

    if (cell->tile_x >= 0 && cell->tile_x < D_800566E0->word0C
        && cell->tile_y >= 0 && cell->tile_y < D_800566E0->word10) {
        cell->clut = *(u32 *)func_80015A98(
            &((u32 *)func_80015A98(&D_800566E0->word00)->items[0])[cell->tile_x + 0x6C]
        )->items[cell->tile_y];
        rect.x = 0x100 + (cell->page << 7) + (cell->x << 3);
        rect.y = (cell->y << 4) + 0x100;
        rect.w = 8;
        rect.h = 16;
        func_80040484(&rect, func_80015A98(
            &((u32 *)func_80015A98(&D_800566E0->word00)->items[0])[cell->tile_x + 0x6C]
        )->items[cell->tile_y] + 4);
    }
}

extern s32 D_800618BC[], D_80061A34;
void func_80024040(s32, s32, s32, s32, s32 *);

/* Finish the pending object request before selecting the next mode. */
__inline__ void func_8003263C(s32 mode)
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
typedef struct EngineSprt16 {
    GpuPacketHeader header;
    s16 x, y;
    u8 u, v;
    u16 clut;
} EngineSprt16;

extern u32 D_800618B0;
void func_8003F8F4(GpuPacketHeader *);
void func_8003F73C(GpuPacketTag *, GpuPacketTag *);
void func_80017448(s32);
void func_80032BB4(EngineMode25State *, s32, s32);
void func_80032DFC(EngineMode25State *, s32, s32);

extern u32 D_8006189C_val __asm__("D_8006189C");

s32 func_800326D8(GpuPacketTag *ot)
{
    char pad[32];
    s32 row;
    s32 col;
    EngineTileCell *cell;
    EngineSprt16 *sprt;
    EngineDrawModePacket *mode_pkt;

    switch ((u32)D_800566E0->word3598) {
    case 0:
        D_800566E0->word35A4 = 0;
        D_800566E0->word35A0 = 0;
    case 1:
        D_80061A34 = 0x120;
        D_8006189C[0] |= 0xC;
        D_800566E0->word3598 = 6;
        if (D_8006189C[0] & 0x20000) {
            func_80032BB4(D_800566E0, D_800566E0->word14, D_800566E0->word18);
            func_80032DFC(D_800566E0, D_800566E0->word14, D_800566E0->word18);
        }
        D_80061A34 = 0x120;
        break;
    case 2:
        D_800566E0->word3598 = 6;
        D_80061A34 = 0x120;
        break;
    }
    if ((D_800618B0 & 0x20000) && D_800566E0->word359C) {
        row = 0;
        cell = D_800566E0->cells;
        do {
            col = 0;
            do {
                sprt = (EngineSprt16 *)D_8005840C->word78;
                D_8005840C->word78 = (s32)(sprt + 1);
                func_8003F8F4(&sprt->header);
                sprt->x = (cell->tile_x << 4) - D_800566E0->word14 - 0x100;
                sprt->y = (cell->tile_y << 4) - D_800566E0->word18 - 0x78;
                sprt->u = cell->x << 4;
                sprt->v = cell->y << 4;
                sprt->header.color[0] = 0x80;
                sprt->header.color[1] = 0x80;
                sprt->header.color[2] = 0x80;
                sprt->clut = D_800566E0->cluts[cell->clut];
                func_8003F73C(ot, (GpuPacketTag *)sprt);
                col++;
                mode_pkt = (EngineDrawModePacket *)D_8005840C->word78;
                D_8005840C->word78 = (s32)(mode_pkt + 1);
                *mode_pkt = D_800566E0->draw_modes[cell->page];
                cell++;
                func_8003F73C(ot, (GpuPacketTag *)mode_pkt);
            } while (col < 33);
            row++;
        } while (row < 16);
    }
    switch ((u32)D_800566E0->word3598) {
    case 3:
        break;
    case 5:
        if (D_80061A34 == 0) {
            D_800566E0->word3598 = 7;
            D_8006189C_val &= ~0xC;
            func_80017448(0xFF);
        }
        break;
    case 6:
        if (D_80061A34 == 0) {
            D_800566E0->word3598 = 3;
        }
        break;
    case 7:
        func_8001BA18(func_8001B92C, func_8001D1E0, NULL);
        if (D_800566E0->word359C != 0) {
            func_80032FDC(D_800566E0->word35D0, 0, -1);
        }
        D_800566E0->word3598 = 1;
        D_800566E0->word35D0 = D_800566E0->word35D4;
        func_80017448(0xFF);
        func_80031EB4();
        return 0;
    }
    if (D_800618D4 != D_800566E0->word35D4) {
        func_8003263C(D_800618D4);
    }
    return 0;
}
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

s32 func_8003F514(s32, s32, s32, s32);
void func_80041054(EngineDrawModePacket *, s32, s32, s32, EngineGpuRect *);

void func_80032BB4(EngineMode25State *state, s32 x, s32 y)
{
    EngineGpuRect rect;
    s32 row;
    s32 col;
    EngineTileCell *cell;
    s32 tx;
    s32 ty;

    func_80032AF4((u32)state->coords);
    state->word3560 = func_8003F514(1, 1, 0x100, 0x100);
    state->word3562 = func_8003F514(1, 1, 0x180, 0x100);
    state->word3564 = func_8003F514(1, 1, 0x200, 0x100);
    state->word3566 = func_8003F514(1, 1, 0x280, 0x100);
    rect.x = 0x100;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    func_80041054(&state->draw_modes[0], 1, 1, state->word3560, &rect);
    rect.x = 0x180;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    func_80041054(&state->draw_modes[1], 1, 1, state->word3562, &rect);
    rect.x = 0x200;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    func_80041054(&state->draw_modes[2], 1, 1, state->word3564, &rect);
    rect.x = 0x280;
    rect.y = 0x100;
    rect.w = 0x100;
    rect.h = 0x100;
    func_80041054(&state->draw_modes[3], 1, 1, state->word3566, &rect);
    tx = x >> 4;
    ty = y >> 4;
    for (row = 0; row < 16; row++) {
        for (col = 0; col < 33; col++) {
            cell = &state->cells[(col << 4) + row];
            cell->tile_x = tx + col;
            cell->tile_y = ty + row;
            cell->x = state->coords[(col << 4) + row].x;
            cell->y = state->coords[(col << 4) + row].y;
            cell->page = state->coords[(col << 4) + row].page;
        }
    }
}

void func_80032DFC(EngineMode25State *state, s32 x, s32 y)
{
    EngineGpuRect rect;
    s32 row;
    s32 col;
    EngineTileCell *cell;
    s32 coord_x;
    s32 coord_y;

    func_8004025C(0);
    for (row = 0; row < 16; row++) {
        for (col = 0; col < 33; col++) {
            if ((x >> 4) + col < D_800566E0->word0C
                && (y >> 4) + row < D_800566E0->word10) {
                cell = &state->cells[(col << 4) + row];
                cell->off_x = x + (col << 4);
                cell->off_y = y + (row << 4);
                cell->clut = *(u32 *)func_80015A98(
                    &((u32 *)func_80015A98(&D_800566E0->word00)->items[0])[(x >> 4) + col + 0x6C]
                )->items[(y >> 4) + row];
                coord_x = state->coords[(col << 4) + row].x;
                coord_y = state->coords[(col << 4) + row].y;
                rect.w = 8;
                rect.h = 16;
                rect.x = (coord_x << 3) + 0x100;
                rect.y = (coord_y << 4) + 0x100;
                func_80040484(&rect, func_80015A98(
                    &((u32 *)func_80015A98(&D_800566E0->word00)->items[0])[(x >> 4) + col + 0x6C]
                )->items[(y >> 4) + row] + 4);
            }
        }
    }
}

typedef struct EngineClutSpan {
    s32 x;
    s32 y;
    s32 count;
} EngineClutSpan;

typedef struct EngineMapHeader {
    s32 count00;
    s32 word04;
    s32 clut_count;
    s32 word0C;
    s32 word10;
    s32 count14;
    EngineClutSpan spans[8];
    s32 pages[46][1];
    s32 words130[32];
    s32 words1B0[32];
} EngineMapHeader;

static __inline__ s32 engine_resource_adjust(s32 *resource, s32 argument, s32 count)
{
    if (*resource != 0x6396347F) {
        if (count > 0) {
            return func_80015118(resource, argument, count);
        } else {
            func_80015458(resource, -count);
        }
    }
    return 0;
}

static __inline__ void engine_update_slot_state(s32 slot, s32 active)
{
    if (active) {
        func_80014514(slot);
        D_800580A4[slot].state = 30;
    } else if (D_800580A4[slot].state == 30) {
        D_800580A4[slot].state = 1;
    }
}

s32 func_80012820(s32);
u16 func_8003F338(void *, s32, s32);
void func_8001767C(void *);

void func_80032FDC(s32 mode, s32 arg1, s32 count)
{
    char name[16];
    s32 ref;
    ResourceItemListView *list;
    EngineMapHeader *header;
    EngineClutSpan *span;
    s32 span_offset;
    s32 clut_count;
    s32 i;
    s32 end;
    s32 page_idx;
    u8 *clut_data;
    EngineState *entry;

    *(EngineByteRecord *)name = *(EngineByteRecord *)D_8005655C;
    name[0] = func_80012820(mode);
    ref = func_80012660((u8 *)name);
    engine_resource_adjust(&ref, arg1, count);
    list = func_80015A98((u32 *)&ref);
    header = (EngineMapHeader *)list->items[0];
    if (count > 0) {
        span = header->spans;
        span_offset = 0;
        clut_count = header->clut_count;
        for (i = 0; i < clut_count;) {
            ref = header->pages[i / 120][0];
            engine_resource_adjust(&ref, arg1, count);
            if (clut_count - i < 120) {
                end = clut_count;
            } else {
                end = i + 120;
            }
            for (; i < end; i++, span_offset++) {
                page_idx = i / 120;
                clut_data = func_80015A98((u32 *)&((EngineMapHeader *)list->items[0])->pages[page_idx][0])->items[i % 120];
                if (span_offset >= span->count) {
                    span++;
                    span_offset = 0;
                }
                D_800566E0->cluts[i] = func_8003F338(clut_data, span->x, span_offset + span->y);
            }
            engine_resource_adjust(&ref, arg1, -count);
        }
        func_80014514(9);
        D_800580A4[9].state = 30;
        func_80014514(10);
        D_800580A4[10].state = 30;
        func_80014514(13);
        D_800580A4[13].state = 30;
        engine_update_slot_state(8, clut_count > 160);
        engine_update_slot_state(12, clut_count > 288);
        engine_update_slot_state(14, clut_count > 416);
    }
    for (i = 0; i < header->count00; i++) {
        engine_resource_adjust(&header->words1B0[i], arg1, count);
    }
    for (i = 0; i < header->count14; i++) {
        entry = (EngineState *)engine_resource_adjust(&header->words130[i], arg1, count);
        if (arg1 != 0 && count > 0 && entry->word08 == 2) {
            func_8001767C(entry);
        }
    }
}
void func_80033464(void)
{
}
#include "engine/func_8003346C.c"
void func_80033490(void *a, void *b, void *c, u32 color)
{
}
void func_80033498(void)
{
}

