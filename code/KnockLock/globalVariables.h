#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <Arduino.h>
#include "config.h"
// -------------------------------------------------------------
// GLOBALS
// -------------------------------------------------------------
extern unsigned long knockTimes[];  // Stores the timings of the knocks when recorded
extern int knockCount; // Counts the knocks when recorded
extern unsigned long intervals[]; // Stores the intervals between the knocks
extern unsigned long targetPattern[]; // Stores the actual pattern saved
extern int patternLength; // The number of intervals in the actual pattern

extern unsigned long lastKnockTime; // Stores the last knock time, useful for time out and recording intervals
extern unsigned long lastActivityTime; // Stores last knock time, useful for sleep mode
extern unsigned long lastBatCheck; // To make sure battery checked in regular intervals

extern int x, y, z; // Stores the accelerations of x,y,z directions

enum Mode { MODE_IDLE, MODE_RECORDING };
extern volatile Mode currentMode; // Mode, if recording or idle

extern volatile int STATE; // State of locked or unlocked

extern volatile bool recordButtonPressed;

extern volatile bool knockDetected;

// -------------------------------------------------------------
// NON-GLOBALS
// -------------------------------------------------------------
// These variables are not global, but there usage explained here for ease

// From patternRecognitionAndRecording.cpp
// patterDiff - saves the difference between the actual pattern and knock done by user
// ok - stores if the pattern is correct or not - pessimitic approach, only becomes true if correct pattern is found. Default is false
// currentWindowCheck - assumed to be true, but if a certain window of knocks is not correct, it is set to false, helps isolate ok to only become true if correct pattern is found
// mistakeCount - keeps count of which mistake we are currently checking, should be always less than ALLOWED_MISTAKES 
// intervalCount - keeps the number of intervals in the recorded pattern, 
#endif