#ifndef PATTERN_RECORDING_AND_RECOGNITION_H
#define PATTERN_RECORDING_AND_RECOGNITION_H

#include <Arduino.h>
#include "config.h"
#include "hardware.h"
#include "globalVariables.h"
#include "hmi.h"
#include "usingNVS.h"
#include "sleepMode.h"

void checkPattern();
void startRecording();
void finishRecording();
void handleRecording(float aDynamic, unsigned long now);
void handleLockedState(float aDynamic, unsigned long now);
void handleUnlockedState(float aDynamic, unsigned long now);

#endif