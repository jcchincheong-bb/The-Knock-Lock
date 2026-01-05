#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <Arduino.h>
#include "config.h"
// -------------------------------------------------------------
// GLOBALS
// -------------------------------------------------------------
extern unsigned long knockTimes[];
extern unsigned long intervals[];
extern unsigned long targetPattern[];
extern int patternLength;

extern int knockCount;
extern unsigned long lastKnockTime;
extern unsigned long lastActivityTime; 
extern unsigned long lastBatCheck;

extern int x, y, z;

enum Mode { MODE_IDLE, MODE_RECORDING };
extern volatile Mode currentMode;

extern int STATE; 

extern volatile bool recordButtonPressed;

#endif