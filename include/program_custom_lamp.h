#ifndef __CUSTOMLAMP_H_INCLUDED_
#define __CUSTOMLAMP_H_INCLUDED_

#include<OctoWS2811.h>
#include<FastLED.h>
#include "main.h"
#include "osc.h"
#include "utility_functions.h"

void customLamp();
void customLampUpdate();
void activateDeactivateLamp(int lamp_number);
void setLampAddress(int lamp);
void setCustomlampPreset(uint8_t preset_number);
void allLampsOff();
void allLampsOn();
void updateCustomLampState();

#endif
