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
  return abs(z); // Calculate magnitude using relevant axis, for g, multiply this by 0.0039 (from datasheet) 
}

// -------------------------------------------------------------
// SETUP & LOOP
// -------------------------------------------------------------
void setup() {
  if(SERIAL_MONITOR_EN) { // Enable Serial Monitor if required (can be changed in config.h)
    Serial.begin(115200);
    Serial.println("Serial monitor enabled!");
  }

  setupHardware(); // Setup hardware, all the pins modes and objects

  handleWakeup(); //Check reason for waking up, and go accordingly.
  // In case of checking battery and flashing led, it only does that and goes back to deep sleep
  // If due to double knock, it goes through to normal setup to start listening for knocks

  ADXLsetup();                  // Setup ADXL
  digitalWrite(SERVO_EN, HIGH); // Turn servo On

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
  unsigned long now = millis();
  
  // For manual override
  static unsigned long lastPress = 0; 
  static int buttonClickCount = 0;
  int manualOverrideFlag = 0;
  //int interruptFlag = 0;  // Flag to disable single tap interrupt if required

  // Only if knock prominent enough
  if (knockDetected || recordButtonPressed) {
    lastActivityTime = now;
  }

  // Check battery
  checkBatteryAwake(now);

  // If no button pressed for a while, turn interrupt back on to detect taps
    if (now - lastPress > CLICK_GAP_TIMEOUT) {
      buttonClickCount = 0;
      adxl.singleTapINT(1);
    }

  // If button for recording pressed
  if (recordButtonPressed) {
    recordButtonPressed = false;

    // Reset counter if too much time passed between clicks
    if (now - lastPress > CLICK_GAP_TIMEOUT) {
      buttonClickCount = 0;
      adxl.singleTapINT(1);
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
      adxl.singleTapINT(0); // Disable single tap interrupt, to allow override to be able to be detected even with vibrations
      if (buttonClickCount >= OVERRIDE_CLICK_COUNT) {
        buttonClickCount = 0;
        adxl.singleTapINT(1);
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
    handleRecording(0.0, now);
  } 
  else if (STATE == 0) {
    handleLockedState(0.0, now);
  } 
  else if (STATE == 1) {
    handleUnlockedState(0.0, now);
  }

  delay(5); 
}