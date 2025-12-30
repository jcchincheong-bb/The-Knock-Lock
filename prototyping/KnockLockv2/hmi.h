#ifndef HMI_H
#define HMI_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "config.h"
#include "hardware.h"
#include "globalVariables.h"

void led_ryg(int rState, int yState, int gState);
void flashGreenTick();
void goodBeep();
void badBeep();
void successSave();
void playbackPattern();
void unlockBox();
void lockBox();

#endif