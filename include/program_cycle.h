#ifndef __CYCLE_H_INCLUDE_
#define __CYCLE_H_INCLUDE_
#include "main.h"

enum cycle_mode { RAINBOW, GRADIENT };
enum cycle_order { START_TO_END, WAVE };
extern cycle_order order;
extern cycle_mode mode;

extern CRGBPalette16 * cycle_palette_array[];
extern CRGBPalette16 * active_cycle_palette;

void cycleUpdate();
void cycle(cycle_mode c_mode = RAINBOW, cycle_order c_order = START_TO_END);

#endif
