/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gpu.h"
#include "resource.h"

#ifdef NON_MATCHING

/* The candidate has instruction Levenshtein distance 42. The retail function
 * uses a 64-byte stack frame and different registers for its bucket cursors.
 * Retail has an eight-byte GPU rectangle at 0x80056420: {0, 0, 256, 128}.
 * Its data ownership must be reconciled before enabling this branch.
 */
typedef ResourceEntry Entry;
typedef ResourceHeader Header;
typedef ResourceSlot Slot;
typedef ResourceBucket Bucket;
typedef ResourceHandler Handler;
extern Slot D_8005C554[],D_800580A0[];
extern Slot *D_8005CFAC;
extern Bucket **D_8005C530;
extern Slot **D_8005CFBC;
extern Handler D_800514EC[];
extern u32 D_8005728C[];
GpuRect D_80056420={0,0,256,128};


void func_80040484(GpuRect *,Header *);
u8 *func_80012F10(s32 index) {
 Slot *request=&D_8005C554[index],*slot;
 Header *header;
 Bucket *bucket;
 u32 *id_pointer;
 u32 i;
 s32 texture,quotient;
 Entry *entry;
 s32 (*callback)(Entry *);
 if(D_8005CFAC==request)D_8005CFAC=NULL;
 header=request->header;
 request->state=30;
 switch(header->kind) {
 case 0:
 bucket=D_8005C530[(header->entries[0]->id>>15)&255];
 i=0;
 if(header->count) {
 id_pointer=&bucket->id;
again_zero:
 entry=request->header->entries[i];
 while(*id_pointer!=entry->id) {id_pointer+=2;bucket++;}
 bucket->entry=(u32)entry;
 request->references++;
 callback=D_800514EC[entry->kind].callback;
 i++;
 if(callback)callback(entry);
 request->references--;
 if(i<request->header->count)goto again_zero;

 }
 break;
 case 1: {
 Slot *texture_slot;
 texture=func_8001439C();
 if(texture==-12) {
 texture=15;
 /* Retail skips initialization of texture_slot on this failure path. */
 if(request->references==0)goto texture_done;
 }
 texture_slot=&D_800580A0[texture];
 quotient=texture/4;
 D_80056420.x=(texture-quotient*4)<<8;
 D_80056420.y=quotient<<7;
 func_80040484(&D_80056420,request->header);
 texture_slot->state=20;
 texture_slot->word18=request->header->id;
 texture_slot->id=request->id;
 texture_slot->mapping=(u32 *)func_80015978(texture_slot->word18);
 *texture_slot->mapping=(u32)texture_slot->base;
texture_done:
 request->state=1;
 D_8005CFBC[request->id>>1]=texture_slot;
 return (u8 *)(texture*2);
 }
 case 3:
 case 4:
 header=request->header;
 bucket=D_8005C530[(header->entries[0]->id>>15)&255];
 slot=request->slot;
 i=0;
 if(header->count) {
 id_pointer=&bucket->id;
 do {
 u8 *data;
 entry=header->entries[i];
 data=entry->data;
 while(*id_pointer!=entry->id){id_pointer+=2;bucket++;}
 if(i==0) {
 if(request->header->kind==4)
 D_8005728C[slot->word08]=*id_pointer;
 else
 D_8005728C[slot->word08]=0x6396347F;
 }
 bucket->entry=(u32)((((s32)data-(s32)request->header+(s32)slot->base)*4)|0x80000002);
 callback=D_800514EC[entry->kind].callback;
 i++;
 if(callback)callback(entry);
 header=request->header;
 } while(i<header->count);
 }
 slot->state=20;
 request->state=1;
 D_8005CFBC[request->id>>1]=slot;
 return slot->base;
 }
 request->state=20;
 return (u8 *)request->header;
}

#else

INCLUDE_ASM("asm/USA/main/nonmatchings/ns/resource_process", func_80012F10);

#endif
