#ifndef BATTERY_MONITORING_H
#define BATTERY_MONITORING_H

#include <Arduino.h>
#include <Preferences.h>
#include "config.h"
#include "globalVariables.h"
#include "hardware.h"

float getBatteryVoltage();
void checkBatteryAwake(unsigned long now);

#endif