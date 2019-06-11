#ifndef __BLINK_H_INCLUDED_
#define __BLINK_H_INCLUDED_

#include "main.h"

extern CRGBPalette16 * blink_palette_array[];
extern CRGBPalette16 * active_palette;
extern uint32_t blink_random_time;


void blink();
void blinkUpdate();

#endif
