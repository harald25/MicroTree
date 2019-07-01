#ifndef __SCANNER_H_INCLUDED_
#define __SCANNER_H_INCLUDED_
#include "main.h"

extern uint8_t tail_length;
void scanner();
void scannerUpdate();
void scannerSettings(OSCMessage &msg, int addrOffset);

#endif
