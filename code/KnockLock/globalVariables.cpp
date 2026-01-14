#include "globalVariables.h"

// -------------------------------------------------------------
// GLOBALS
// -------------------------------------------------------------
unsigned long knockTimes[MAX_KNOCKS];
unsigned long intervals[MAX_KNOCKS];
unsigned long targetPattern[MAX_KNOCKS];
int patternLength = 0;

int knockCount = 0;
unsigned long lastKnockTime = 0;
unsigned long lastActivityTime = 0; 
unsigned long lastBatCheck = 0;

int x, y, z;

volatile Mode currentMode = MODE_IDLE;

// STATE: 0 = Locked, 1 = Unlocked
volatile int STATE = 0; 

volatile bool recordButtonPressed = false;

volatile bool knockDetected = false;