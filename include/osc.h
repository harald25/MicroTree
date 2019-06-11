#ifndef __OSC_H_INCLUDED_
#define __OSC_H_INCLUDED_

#include <OSCMessage.h>
#include <SLIPEncodedSerial.h>
#include "utility_functions.h"
#include "main.h"

extern SLIPEncodedSerial SLIPSerial;

void OSCMsgReceive();
void OSCMsgSend(float value);
void OSCMsgSend(char address[18], float value);

#endif
