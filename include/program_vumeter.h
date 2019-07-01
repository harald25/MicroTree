#ifndef __VUMETER_H_INCLUDED_
#define __VUMETER_H_INCLUDED_


// #include <Wire.h>
// #include <SPI.h>
#include "main.h"

extern float vumeter_smoothing_coeff_positive; // experiment with different coefficients; --> 0.0 < smoothing_coeff < 1.0
extern float vumeter_smoothing_coeff_negative;
enum spectrum_mode { RAINBOW, GRADIENT};
extern spectrum_mode spec_mode;

void vumeter();
void vumeterUpdate();
void computeVerticalLevels();
unsigned int xy(unsigned int x, unsigned int y);

#endif
