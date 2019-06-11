#ifndef __THEATERCHASE_H_INCLUDE_
#define __THEATERCHASE_H_INCLUDE_
#include "main.h"

enum chase_mode { REGULAR, RAINBOW_CHASE};
extern chase_mode c_mode;
extern uint8_t pixel_width;
extern uint8_t pixel_distance;

void theaterChase();
void theaterChaseUpdate();

#endif
