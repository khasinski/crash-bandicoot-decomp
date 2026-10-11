/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.21 */
#include "common.h"

/*
 * Heap allocator. Each block is preceded by a header word; LIBC_Free marks a
 * block free by setting that word's low bit.
 */

void *LIBC_Malloc(int size);
void *func_80011870(void *ptr, int size);
void BIOS_BZero(void *dst, int len);
void BIOS_BCopy(void *src, void *dst, int len);

extern s32 *D_80056598, *D_800565A8;
extern u32 D_800565A0;
extern s32 D_800565B0;
extern u32 *D_800577BC,*D_80057F38;

s32 func_8001177C(u32 amount) {
    u32 maximum;
    s32 available, words, next_size;
    if (amount) {
        maximum=amount;
        if (D_800565A0>=amount) maximum=D_800565A0;
        else amount=D_800565A0;
        available=(D_800565A8-D_80056598)*4-8;
        if (available >= (s32)maximum) amount=maximum;
        else if (available < (s32)amount) return -1;
    } else {amount=0;if (D_80056598>=D_800565A8) return -1;}
    words=(s32)amount;
    words=words<0?words+3:words;
    next_size=(s32)(amount+4);
    words >>= 2;
    D_80056598[words]=-2;
    D_80056598[-1]=amount|1;
    D_80056598 += next_size/4;
    return 0;
}

void *func_80011870(void *ptr,s32 requested) {
    void *result;
    u32 size=((u32)requested+3)&~3;
    u32 *header=(u32 *)ptr-1;
    u32 first_length=*header;
    u32 length;
    u32 *cursor,*next;
    u32 total,extra,next_length,initial;
    if(first_length==(u32)-2) return NULL;
    initial=first_length&~1;
    if(initial<size) {
        cursor=header;
        total=initial;
        do {
            next=cursor+(*cursor>>2);
            next_length=next[1];
            cursor=next+1;
            if(next_length!=(u32)-2) {
                if(!(next_length&1)) break;
            } else {
                extra=size-total;
                /* Retail compares available words to a byte count here. */
                if((u32)((u32 *)D_800565A8-cursor-4)<extra) break;
                next[1]=extra|1;
                D_80056598=(s32 *)(cursor+(extra>>2));
                *D_80056598=-2;
                D_80056598++;
            }
            *header+=*cursor&~1;
            total+=*cursor&~1;
        } while(total<size);
    }
    length=*header;
    if(size<(length&~3)) {
        header[(s32)size/4+1]=((length&~1)-size)-4;
        header[(s32)size/4+1]|=1;
        *header=size|(*header&1);
    } else {result=ptr;if((length&~1)<size){ptr=NULL;goto returned;}return result;}
returned:
    return ptr;
}

void func_80011A18(s32 *base,u32 size) {
    D_80056598=base;
    *base=0;
    base += size>>2;
    D_800565A8=base+1;
    D_800565A0=size-4;
    D_800565B0=0;
}

void *LIBC_Malloc(s32 requested) {
    s32 passes=2;
    s32 size;
    u32 *scan;
    s32 first_length;
    u32 tagged,length,next_length,combined;
    u32 *next,*advance,*following;
    size=requested;size+=3;size&=~3;
    if(D_800565B0==0) {
        if(D_80056598<D_800565A8) {
            *D_80056598=-2;
            D_800577BC=(u32 *)D_80056598;
            D_80056598++;
            if(func_8001177C(size)==0) {
                D_800565B0=1;
                D_80057F38=D_800577BC;
                goto start;
            }
            return NULL;
        }
        return NULL;
    }
start:
    scan=D_80057F38;
    D_800577BC=scan;
    goto scan_block;
free_block:
    {
        length=*D_800577BC;
        if(tagged<length) {
            u32 *block=D_800577BC;
            u32 *tail=(u32 *)(((size/4)*4)+(u32)block);
            *++tail=(length-(u32)size)-4;
            *block=size;
            goto found;
        }
        if(length<(u32)size) {
            next=D_800577BC+(length>>2);
            next_length=next[1];
            following=next+1;
            if(next_length==(u32)-2) {
                *D_800577BC=next_length;
                D_80056598=(s32 *)(D_800577BC+1);
            } else if(next_length&1) {
                combined=length+4;
                combined+=next_length&~1;
                *D_800577BC=combined;
            } else {
                D_800577BC=following;
            }
        }
        goto again;
    }
allocated_block:
    next_length=*D_800577BC;
    if(next_length!=(u32)-2) {
        advance=D_800577BC+(next_length>>2)+1;
        goto advance_scan;
    }
    passes--;
    if(passes<=0) {
        if(func_8001177C(size)!=0) return NULL;
        goto again;
    }
    advance=D_80057F38;
advance_scan:
    D_800577BC=advance;
again:
    scan=D_800577BC;
scan_block:
    first_length=*scan;
    if(!(first_length&1)) goto allocated_block;
    tagged=size|1;
    if((u32)first_length!=tagged) goto free_block;
    *scan=first_length&~1;
found:
    return D_800577BC+1;
}

void LIBC_Free(void *ptr)
{
    ((int *)ptr)[-1] |= 1;
}

void *LIBC_Realloc(void *ptr, int size)
{
    void *res;

    if (!ptr) {
        res = LIBC_Malloc(size);
    } else {
        /* This single-iteration scope reproduces the retail register lifetimes.
         * The retail zero-size path frees ptr without defining the result.
         */
        do {
            if (size) {
                res = func_80011870(ptr, size);
                if (res) {
                    return res;
                }
                res = LIBC_Malloc(size);
                if (res) {
                    BIOS_BCopy(ptr, res, size);
                    LIBC_Free(ptr);
                }
            } else {
                LIBC_Free(ptr);
            }
        } while (0);
    }
    return res;
}

void *LIBC_Calloc(int count, int size)
{
    int len;
    void *res;

    len = size * count;
    res = LIBC_Malloc(len);
    if (!res)
        return 0;
    BIOS_BZero(res, len);
    return res;
}
