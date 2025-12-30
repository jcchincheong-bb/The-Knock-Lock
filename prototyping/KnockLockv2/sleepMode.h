#ifndef SLEEP_MODE_H
#define SLEEP_MODE_H

#include <Arduino.h>
#include "config.h"
#include "hardware.h"
#include "globalVariables.h"
#include "batteryMonitoring.h"
#include "hmi.h"

void goToSleep();
void handleWakeup();

#endif