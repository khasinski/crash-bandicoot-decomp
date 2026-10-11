#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 pad00[4];u16 word04;} Context;
typedef struct {u8 pad00[0x2FC];u32 flags;} Data;
typedef struct {u8 pad00[0x10];Data *data;} Root;
extern Root *D_80057914;
extern Context *D_8005C53C;
extern u16 D_8005E348[];

void func_8001B458(s32 tag)
{
    u16 *entry = D_8005E348;
    u16 *free_entry = NULL;
    tag = (tag >> 8) | (D_8005C53C->word04 << 9);
    if(!(D_80057914->data->flags & 0x2000)) {
        while(*entry != 0) {
            if(*entry == (tag & 0xFFFF)) return;
            if(*entry == 1) free_entry = entry;
            entry++;
        }
        if(free_entry == NULL) free_entry = entry;
        *free_entry = tag;
    }
}

void func_8001B4F0(s32 tag)
{
    u16 *entry = D_8005E348;
    tag = (tag >> 8) | (D_8005C53C->word04 << 9);
    if(D_8005E348[0] != 0) {
        do {
            if(*entry == (tag & 0xFFFF)) {
                if(entry[1] != 0) *entry = 1;
                else *entry = 0;
                return;
            }
            entry++;
        } while(*entry != 0);
    }
}
