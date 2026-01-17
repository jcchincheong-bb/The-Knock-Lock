#include "patternRecognitionAndRecording.h"

// -------------------------------------------------------------
// CORE LOGIC
// -------------------------------------------------------------

// Function to check if knock matches stored (now loaded) pattern
void checkPattern() {

  // Check if any pattern is even saved, if not return
  if (patternLength <= 0) {
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern.");
    return;
  }

  if (knockCount < MIN_KNOCKS)
    return;

  // Calculate intervals using knock timings
  int intervalCount = knockCount - 1;

  for (int i = 1; i < knockCount; i++) {
    intervals[i - 1] = knockTimes[i] - knockTimes[i - 1];
  }

  // Actually checking for mistakes
  bool ok = false; // Keep track of a mistake - true means pattern is correct, false means pattern was incorrect
  
  // Check for pattern size before actual checking, to be more efficient 
  int patternDiff = intervalCount - patternLength; // See difference in the knocks recorded vs knocks to be done
  if (patternDiff < 0){
    // Too few knocks 
    ok = false;
    if(SERIAL_MONITOR_EN) Serial.println("Incorrect pattern: Too few knocks");
  }
  else if (patternDiff > ALLOWED_MISTAKES) {
    // Too many mistakes
    ok = false;
    if(SERIAL_MONITOR_EN) Serial.println("Incorrect pattern: Too many mistakes");
  }
  else {
    for(int mistakeCount = 0; mistakeCount <= patternDiff; mistakeCount++){ 
      // Now if there is a mistake (or multiple), slide window to see if the mistake is at the start only, and full correct pattern is to follow. Run it only till the number of mistakes he has made, which is patternDiff
      bool currentWindowCheck = true; // See if pattern play for a specific window
      for(int k = 0; k < patternLength; k++){
        long diff = labs((long)intervals[k+mistakeCount] - (long)targetPattern[k]);

        if(diff > KNOCK_TOL){ // Is difference not tolerable, according to config.h
          currentWindowCheck = false;
          break; // If a mistake then no need to check rest, go to check if mistake is ignored
        }
      }
      if(currentWindowCheck) { // If pattern is correct after some mistakes (less than allowed mistakes)
        ok = true;
        break;
      }
      else{
        if(mistakeCount == patternDiff) { // Check if it is the last tolerable mistake
              if(SERIAL_MONITOR_EN) Serial.println("Incorrect pattern: Wrong difference");
              break;
        }
      }
    }
  }

  if (ok) { // If pattern correct
    if(SERIAL_MONITOR_EN) Serial.println("✅ Correct pattern!");
    goodBeep();
    unlockBox();
  } else { // If pattern not correct
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
  
  // Reset knock count before starting to record
  knockCount = 0;

  unsigned long resetTime = millis(); // Reset timer, to now time the knocks
  lastKnockTime = resetTime;
  lastActivityTime = resetTime;
  
  currentMode = MODE_RECORDING; // Set mode to call correct functions
  led_ryg(0, 1, 0); 
}

// Function to validate recording
void finishRecording() {
  // If too few knocks, do not save pattern
  if (knockCount < MIN_KNOCKS) {
    if(SERIAL_MONITOR_EN) Serial.println("❌ Recording Failed: Too few knocks.");
    badBeep();
  } else {
    // If min knock count reached then save the intervals
    for (int j = 0; j < knockCount - 1; j++) {
      intervals[j] = knockTimes[j + 1] - knockTimes[j];
    }
    patternLength = knockCount - 1; // Stores the number of intervals in pattern
    savePatternToNVS(intervals, patternLength); // Save to non volatile storage
    successSave(); // Indicate user pattern saved
    playbackPattern(); // Verify the knocks by playing it back
    patternLength = loadPatternFromNVS(targetPattern);  // Update patternLength for the new pattern
  }
  currentMode = MODE_IDLE;
  knockCount = 0;
  led_ryg(0, 0, 0); 
}

// Function to deal with recordings
void handleRecording(float aDynamic, unsigned long now) {
  if (now - lastKnockTime > PATTERN_TIMEOUT) { // If not knocked for sometime, start processing the recording, either save or not
    finishRecording(); 
    return;
  }
  if ((knockDetected) && ((now - lastKnockTime) > DEBOUNCE_TIME)) { // if a knock is detected save its time
    flashGreenTick(); // Indicate user a knock was detected
    led_ryg(0, 1, 0); // Show it is still recording 
    if (knockCount < MAX_KNOCKS) { // Check if too many knocks were made
      knockTimes[knockCount] = now;
      knockCount++;
      lastKnockTime = now;
      if(SERIAL_MONITOR_EN) Serial.printf("REC Knock #%d\n", knockCount);
    }
  }
  knockDetected = false;
  adxl.getInterruptSource();
}

// Function to deal with response if system locked
void handleLockedState(float aDynamic, unsigned long now) {
  if (knockDetected && (now - lastKnockTime) > DEBOUNCE_TIME) { // If knock is detected start recording its timing, debounce knock to prevent double knock
    lastKnockTime = now;
    lastActivityTime = now; 
    flashGreenTick(); // Alert user a knock was detected
    led_ryg(0, 1, 0); // Show it is still recording
    knockTimes[knockCount] = now;
    knockCount++; // Count number of knocks
    if(SERIAL_MONITOR_EN) Serial.printf("Locked Knock #%d\n", knockCount);
  } else {
    if(digitalRead(YLED) == LOW) digitalWrite(YLED, HIGH);
  }
  if (knockCount > 0 && (now - lastKnockTime > PATTERN_TIMEOUT)) { // If a long  break with  knocks, start checking the pattern
    checkPattern(); // Check the pattern, if it is correct it goes to unlocked state
    knockCount = 0; // If checked reset for next iteration
    led_ryg(0, 1, 0); // Show it is recording
  }
  if (knockCount == 0 && (now - lastActivityTime > SLEEP_TIMEOUT)) { // If too long a break with no knocks, go to sleep
    goToSleep();
  }
  knockDetected = false;      // Clear flag
  adxl.getInterruptSource();  // Clear interrupt flags to reset interrupt pin
}

// Function to close box when unlocked
void handleUnlockedState(float aDynamic, unsigned long now) {
  led_ryg(0,0,1);
  if (knockDetected && (now - lastKnockTime) > DEBOUNCE_TIME) {  // Detect knock
    lastKnockTime = now;
    lastActivityTime = now;
    knockCount++;
    if(SERIAL_MONITOR_EN) Serial.printf("Unlock Knock #%d\n", knockCount);
    flashGreenTick(); 
    if (knockCount >= KNOCKS_TO_LOCK) { // If certain knocks are detected, lock the box back, set in config.h
      lockBox();
      return; // Exit unlocked state
    }
  }
  knockDetected = false;
  adxl.getInterruptSource();
}

// Function to manual override and unlock the box, only for development stage
int manualOverride() {
    if (SERIAL_MONITOR_EN) Serial.println("🔓 OVERRIDE: Access Granted.");
    
    unlockBox();
    STATE = 1;      // 1 = Unlocked
    currentMode = MODE_IDLE; // Set mode
    
    goodBeep();

    return 1;
}