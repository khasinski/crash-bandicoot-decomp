/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
extern s16 D_80056EBC[];

/* Wait for a pending fade, then request the selected sequence. Tagged
 * references contain an ID; resolved references point to a handle whose
 * second word is the ID. The fourth fade argument is retained as observed
 * at this call site, although the current callee consumes three words. */
void Midi_OpenAndPlay();
void SsSepSetDecrescendo();


void Midi_Update(s32 *reference) {
 s16 countdown;
 s32 key,ready,state;
 if(gp_card_chan!=0) {
  if(gp_card_chan==4 && (gp_midi_seq_num==0 || (countdown=gp_midi_seq_num-1,gp_midi_seq_num=countdown,countdown==0)))gp_card_chan=1;
  state=gp_card_chan;
  if(state==3) {
   key=*reference;
   if(key&1) {
    if(D_80056650!=key)goto change;
    goto finish;
   }
   if(D_80056650!=((s32 *)key)[1]) {
change:
    if(D_8005666C==0 && D_80056658!=-1 && gp_midi_vab_id==0) {
     SsSepSetDecrescendo(gp_midi_vol,D_80056EBC[0],(s32)(D_80056648<<16)>>23,30);
     gp_midi_seq_num=30;gp_midi_vab_id=reference;gp_card_chan=4;return;
    }
   }
   state=gp_card_chan;
  }
finish:
  ready=state<3;
  if(ready && state>0)Midi_OpenAndPlay(reference);
 }
}
