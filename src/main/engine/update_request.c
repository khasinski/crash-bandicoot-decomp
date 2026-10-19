/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

/* Storage is owned by engine/state. */

void Midi_SetStateStopped(void) {
    if (gp_card_chan == 0) gp_card_chan = 1;
}
