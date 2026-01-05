#include "patternRecognitionAndRecording.h"

// -------------------------------------------------------------
// CORE LOGIC
// -------------------------------------------------------------

// Function to check if knock matches stored (now loaded) pattern
void checkPattern() {

  if (patternLength <= 0) {
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern.");
    return;
  }

  if (knockCount < 5)
    return;

  int intervalCount = knockCount - 1;

  for (int i = 1; i < knockCount; i++) {
    intervals[i - 1] = knockTimes[i] - knockTimes[i - 1];
  }

  int idx;
  int maxStart = intervalCount - patternLength + ALLOWED_MISTAKES;
  bool match = false;

  for (int offset = 0; offset <= maxStart; offset++) {
    bool ok = true;

    for (int j = 0; j < patternLength; j++) {
      idx = offset + j;
      if (idx < 0 || idx >= intervalCount) { ok = false; break; }

      long diff = labs((long)intervals[idx] - (long)targetPattern[j]);
      if (diff > KNOCK_TOL) { ok = false; break; }
    }

    if (ok) { match = true; break; }
  }

  if (match) {
    if(SERIAL_MONITOR_EN) Serial.println("✅ Correct pattern!");
    STATE = 1;
    goodBeep();
    unlockBox();
  } else {
    if(SERIAL_MONITOR_EN) Serial.println("❌ Wrong pattern.");
    badBeep();
  }
}

// Function to actually record knocks
void startRecording() {
  if(SERIAL_MONITOR_EN) Serial.println("\n🎙 Starting NEW recording...");
  led_ryg(1, 1, 1);
  delay(500);
  led_ryg(0, 0, 0);
  delay(500);
  
  knockCount = 0;

  unsigned long resetTime = millis();
  lastKnockTime = resetTime;
  lastActivityTime = resetTime;
  
  currentMode = MODE_RECORDING;
  led_ryg(0, 1, 0); 
}

// Function to validate recording
void finishRecording() {
  if (knockCount < MIN_KNOCKS) {
    if(SERIAL_MONITOR_EN) Serial.println("❌ Recording Failed: Too few knocks.");
    badBeep();
  } else {
    for (int j = 0; j < knockCount - 1; j++) {
      intervals[j] = knockTimes[j + 1] - knockTimes[j];
    }
    patternLength = knockCount - 1;
    savePatternToNVS(intervals, patternLength);
    successSave();
    playbackPattern();
  }
  currentMode = MODE_IDLE;
  knockCount = 0;
  led_ryg(0, 0, 0); 
}

// Function to deal with recordings
void handleRecording(float aDynamic, unsigned long now) {
  if (now - lastKnockTime > IDLE_RESET_TIME) {
    finishRecording();
    return;
  }
  if ((aDynamic > KNOCK_THRESHOLD) && ((now - lastKnockTime) > DEBOUNCE_TIME)) {
    flashGreenTick();
    led_ryg(0, 1, 0); 
    if (knockCount < MAX_KNOCKS) {
      knockTimes[knockCount] = now;
      knockCount++;
      lastKnockTime = now;
      if(SERIAL_MONITOR_EN) Serial.printf("REC Knock #%d\n", knockCount);
    }
  }
}

// Function to deal with response if system locked
void handleLockedState(float aDynamic, unsigned long now) {
  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    lastKnockTime = now;
    lastActivityTime = now; 
    flashGreenTick();
    led_ryg(0, 1, 0);
    knockTimes[knockCount] = now;
    knockCount++;
    if(SERIAL_MONITOR_EN) Serial.printf("Locked Knock #%d\n", knockCount);
  } else {
    if(digitalRead(YLED) == LOW) digitalWrite(YLED, HIGH);
  }
  if (knockCount > 0 && (now - lastKnockTime > PATTERN_TIMEOUT)) {
    checkPattern();
    knockCount = 0; 
    led_ryg(0, 1, 0); 
  }
  if (knockCount == 0 && (now - lastActivityTime > SLEEP_TIMEOUT)) {
    goToSleep();
  }
}

// Function to close box when unlocked
void handleUnlockedState(float aDynamic, unsigned long now) {
  led_ryg(0,0,1);
  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    lastKnockTime = now;
    lastActivityTime = now;
    knockCount++;
    if(SERIAL_MONITOR_EN) Serial.printf("Unlock Knock #%d\n", knockCount);
    flashGreenTick(); 
    if (knockCount >= 2) {
      lockBox();
      return;
    }
  }
}

int manualOverride() {
    if (SERIAL_MONITOR_EN) Serial.println("🔓 OVERRIDE: Access Granted.");
    
    unlockBox();
    STATE = 1;      // 1 = Unlocked
    currentMode = MODE_IDLE; 
    
    goodBeep();

    return 1;
}