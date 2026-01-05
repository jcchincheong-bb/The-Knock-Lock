#ifndef USING_NVS_H
#define USING_NVS_H

#include <Arduino.h>
#include <Preferences.h>
#include "config.h"
#include "globalVariables.h"
#include "hardware.h"

int loadPatternFromNVS(unsigned long intervals[]);
void savePatternToNVS(unsigned long intervals[], int count);


#endif