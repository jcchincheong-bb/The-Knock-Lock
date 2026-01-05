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
  return sqrt(y * y + 2 * z * z) * 0.0039;
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

  // WAKE UP
  handleWakeup();

  // Setup hardware and ADXL
  setupHardware();
  ADXLsetup();

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
  
  // For manual override
  static unsigned long lastPress = 0; 
  static int buttonClickCount = 0;
  int manualOverrideFlag = 0;

  // Only if knock prominent enough
  if (aDynamic > KNOCK_THRESHOLD || recordButtonPressed) {
    lastActivityTime = now;
  }

  // Check battery
  checkBatteryAwake(now);

  // If button for recording pressed
  if (recordButtonPressed) {
    recordButtonPressed = false;

    // Reset counter if too much time passed between clicks
    if (now - lastPress > CLICK_GAP_TIMEOUT) {
      buttonClickCount = 0;
    }

    // Debounce check
    if (now - lastPress < DEBOUNCE_TIME) return;

    buttonClickCount++;
    lastPress = now;

    // And box is unlocked (or locked if DEBUG_MODE is on)
    if (STATE == 1 || DEBUG_MODE == 1) { 
      startRecording();
      now = millis();
    } 
    else {
      if (buttonClickCount >= OVERRIDE_CLICK_COUNT) {
        buttonClickCount = 0;
        manualOverrideFlag = manualOverride();
      }
      
      if (SERIAL_MONITOR_EN && !(manualOverrideFlag)) {
        Serial.println("⚠ Cannot record: box must be unlocked.");
        badBeep();
      }  
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