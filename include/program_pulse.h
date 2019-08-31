#ifndef __PULSE_H_INCLUDED_
#define __PULSE_H_INCLUDED_

#include "main.h"



void pulse();
void pulseUpdate();
void pulseSettings(OSCMessage &msg, int addrOffset);
void preparePulse(uint8_t strip_n);
void sendPulseValuesToTouchosc();

#endif