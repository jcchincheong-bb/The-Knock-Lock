#include <ESP32Servo.h>
#include <Preferences.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>
#include "config.h"
#include "hardware.h"
#include "hmi.h"
#include "globalVariables.h"
#include "usingNVS.h"
#include "batteryMonitoring.h"
#include "patternRecognitionAndRecording.h"
#include "sleepMode.h"

/* Project: Knock Pattern Detection
   Authors: Abhinav Kothari, Justin Julius Chin Cheong
   Purpose: This project aims at making a knock detection system, which unlocks the box whena  specific knock pattern (made by the user is detected).
   All settings are in config.h
*/

// -------------------------------------------------------------
// HELPER
// -------------------------------------------------------------

inline float accelMagnitudeG(int x, int y, int z) {
  return sqrt(x * x + y * y + z * z) * 0.0039;
}

// -------------------------------------------------------------
// SETUP & LOOP
// -------------------------------------------------------------
void setup() {
  // Enable Serial Monitor if required
  if(SERIAL_MONITOR_EN) {
    Serial.begin(115200);
    Serial.println("Serial monitor enabled!");
  }

  // Setup hardware and ADXL
  setupHardware();
  ADXLsetup();

  // WAKE UP
  handleWakeup();

  // Load pattern
  patternLength = loadPatternFromNVS(targetPattern);
  
  // Reset timers
  unsigned long startT = millis();
  lastKnockTime = startT;
  lastActivityTime = startT;

  if(SERIAL_MONITOR_EN) Serial.println("System Ready.");
  led_ryg(0, 1, 0);
}

void loop() {
  // Read adxl345 values
  adxl.readAccel(&x, &y, &z);
  float aDynamic = fabs(accelMagnitudeG(x, y, z) - 1.0);
  unsigned long now = millis();

  // Only if knock prominent enough
  if (aDynamic > KNOCK_THRESHOLD || recordButtonPressed) {
    lastActivityTime = now;
  }

  // Check battery
  checkBatteryAwake(now);

  // If button for recording pressed
  if (recordButtonPressed) {
    recordButtonPressed = false;
    // And box is unlocked (or even locked if DEBUG_MODE is on)
    if (STATE == DEBUG_MODE || STATE == 1) { 
      startRecording();
        now = millis();
    } else {
      if(SERIAL_MONITOR_EN) Serial.println("⚠ Cannot record: box must be unlocked.");
      badBeep(); 
    }
  }

  // Go to required section
  if (currentMode == MODE_RECORDING) {
    handleRecording(aDynamic, now);
  } 
  else if (STATE == 0) {
    handleLockedState(aDynamic, now);
  } 
  else if (STATE == 1) {
    handleUnlockedState(aDynamic, now);
  }

  delay(5); 
}