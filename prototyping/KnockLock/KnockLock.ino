#include <ESP32Servo.h>
#include <Preferences.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>
#include "config.h"
#include "hardware.h"

/* Project: Knock Pattern Detection (Battery Monitored)
   Authors: Justin Julius Chin Cheong, Abhinav Kothari 
*/


// -------------------------------------------------------------
// GLOBALS
// -------------------------------------------------------------
unsigned long knockTimes[MAX_KNOCKS];
unsigned long intervals[MAX_KNOCKS];
unsigned long targetPattern[MAX_KNOCKS];
int patternLength = 0;

int knockCount = 0;
unsigned long lastKnockTime = 0;
unsigned long lastActivityTime = 0; 
unsigned long lastBatCheck = 0;

int x, y, z;

enum Mode { MODE_IDLE, MODE_RECORDING };
volatile Mode currentMode = MODE_IDLE;

// STATE: 0 = Locked, 1 = Unlocked
int STATE = 0; 

volatile bool recordButtonPressed = false;

// -------------------------------------------------------------
// ISR & HELPERS
// -------------------------------------------------------------
void IRAM_ATTR onRecordButton() {
  recordButtonPressed = true;
}

inline float accelMagnitudeG(int x, int y, int z) {
  return sqrt(x * x + y * y + z * z) * 0.0039;
}

// Just a function to easily control the leds
void led_ryg(int rState, int yState, int gState) {
  digitalWrite(RLED, rState);
  digitalWrite(YLED, yState);
  digitalWrite(GLED, gState);
}

// -------------------------------------------------------------
// BATTERY FUNCTIONS
// -------------------------------------------------------------

// Function get battery voltage and hence interpret charging
float getBatteryVoltage() {
  // Read millivolts (ESP32C3 internal calibration)
  uint32_t rawMV = analogReadMilliVolts(BAT_PIN);
  
  // Convert to actual battery voltage (Divider Logic)
  float batV = (rawMV * VOLTAGE_MULTIPLIER) / 1000.0;
  
  // Serial.printf("Bat: %.2f V\n", batV);
  
  return batV;
}

// Function to check battery while system is awake
void checkBatteryAwake(unsigned long now) {
  if (now - lastBatCheck > BAT_CHECK_INTERVAL) {
    lastBatCheck = now;
    if (getBatteryVoltage() < LOW_BAT_THRESHOLD_V) {
      if(SERIAL_MONITOR_EN) Serial.println("⚠ Low Battery!");
      // Quick Red Flash
      digitalWrite(RLED, HIGH);
      delay(100); 
      digitalWrite(RLED, LOW);
      // Restore Yellow if we are in Locked/Listening mode
      if (STATE == 0 && currentMode == MODE_IDLE) {
         digitalWrite(YLED, HIGH);
      }
    }
  }
}

// -------------------------------------------------------------
// NVS & SETUP
// -------------------------------------------------------------

// Function to load stored pattern
int loadPatternFromNVS(unsigned long intervals[]) {
  prefs.begin("knocks", true);  

  int count = prefs.getInt("count", -1);
  if (count <= 0) {
    prefs.end();
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern found in NVS.");
    return -1;
  }

  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);
    intervals[i] = prefs.getULong(key, 0);
  }

  prefs.end();
  if(SERIAL_MONITOR_EN) Serial.printf("📥 Loaded %d knock intervals from NVS.\n", count);
  return count;
}

// Function to load saved pattern
void savePatternToNVS(unsigned long intervals[], int count) {
  prefs.begin("knocks", false);  // RW mode

  // store count
  prefs.putInt("count", count);

  // store each interval
  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);     // keys: i0, i1, i2...
    prefs.putULong(key, intervals[i]);
  }

  prefs.end();
  if(SERIAL_MONITOR_EN) Serial.println("Pattern saved to NVS!");
}

// -------------------------------------------------------------
// SLEEP LOGIC (With Low Bat Monitor)
// -------------------------------------------------------------
// Function to put controller to sleep, with possibility to wake back up
void goToSleep() {
  led_ryg(0,0,0);
  
  // Check Battery before sleeping
  float batV = getBatteryVoltage();
  bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);

  // Prepare ADXL Wakeup
  adxl.doubleTapINT(1);
  adxl.getInterruptSource();
  esp_deep_sleep_enable_gpio_wakeup(1ULL << WAKE_INT, ESP_GPIO_WAKEUP_GPIO_HIGH);

  if (lowBattery) {
    if(SERIAL_MONITOR_EN) Serial.printf("💤 Low Battery (%.2fV). Blinking and sleeping 4s...\n", batV);
    
    // Blink Red indicating "I'm sleeping but dying"
    digitalWrite(RLED, HIGH);
    delay(100);
    digitalWrite(RLED, LOW);
    
    // Enable Timer Wakeup (4 seconds)
    // This creates the "Blink while sleeping" loop
    esp_sleep_enable_timer_wakeup(4 * 1000000ULL); 
  } else {
    if(SERIAL_MONITOR_EN) Serial.println("💤 Good Battery. Deep Sleep (Waiting for Knock)...");
    // No timer wakeup, sleep indefinitely until knock
  }

  esp_deep_sleep_start();
}

// -------------------------------------------------------------
// FEEDBACK & SERVO
// -------------------------------------------------------------
// Function to flash green LED
void flashGreenTick() {
  bool yellowWasOn = digitalRead(YLED);
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, HIGH);
  delay(50);
  digitalWrite(GLED, LOW);
  if(yellowWasOn) digitalWrite(YLED, HIGH);
}

// Function to notify in case of correct pattern
void goodBeep() {
  tone(BUZZER, 1000, 150);
  delay(150);
  tone(BUZZER, 1500, 200);
  delay(200);
  noTone(BUZZER);
}


// Function to notify in case of incorrect pattern
void badBeep() {
  led_ryg(1, 0, 0);
  tone(BUZZER, 400, 200);
  delay(200);
  tone(BUZZER, 300, 250);
  delay(250);
  noTone(BUZZER);
  led_ryg(0, 1, 0);
}

// Function to validate a successful save
void successSave() {
  if(SERIAL_MONITOR_EN) Serial.println("✅ Recording Saved.");
  led_ryg(0,0,0);
  for(int i=0; i<2; i++){
    led_ryg(0,0,1);
    delay(200);
    led_ryg(0,0,0);
    delay(200);
  }
}

// Function to play the recorded pattern back for validation
void playbackPattern() {
  if(SERIAL_MONITOR_EN) Serial.println("🔊 Playing back pattern...");
  for (int i = 0; i < knockCount - 1; i++) {
    tone(BUZZER, 2000);
    delay(50);
    noTone(BUZZER);
    led_ryg(0, 1, 0);
    delay(intervals[i]);
    led_ryg(0, 0, 0);
  }
  tone(BUZZER, 2000);
  delay(50);
  noTone(BUZZER);
}

// Function to unlock the box
void unlockBox() {
  if (STATE == 1) return;
  if(SERIAL_MONITOR_EN) Serial.println("🔓 Unlocking...");
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(180);
  delay(500);
  digitalWrite(SERVO_EN, LOW);
  led_ryg(0,0,1);
  STATE = 1; 
  knockCount = 0; 
}

// Function to lock the box
void lockBox() {
  if(SERIAL_MONITOR_EN) Serial.println("🔒 Locking...");
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(0);
  delay(500);
  digitalWrite(SERVO_EN, LOW);
  STATE = 0;
  knockCount = 0;
  lastActivityTime = millis();
}

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

  int maxStart = intervalCount - patternLength + EXTRA_AFTER;
  bool match = false;

  for (int offset = 0; offset <= maxStart; offset++) {
    bool ok = true;

    for (int j = 0; j < patternLength; j++) {
      int idx = offset + j;
      if (idx < 0 || idx >= intervalCount) { ok = false; break; }

      // <<-- FIX: use signed subtraction and labs() to avoid abs() ambiguity
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

void handleUnlockedState(float aDynamic, unsigned long now) {
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

// -------------------------------------------------------------
// SETUP & LOOP
// -------------------------------------------------------------
void setup() {
  if(SERIAL_MONITOR_EN) Serial.begin(115200);


  // Setup hardware
  setupHardware();


  // WAKE UP CHECK
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_GPIO) {
    // Woke up by ADXL Tap
    digitalWrite(YLED, HIGH); 
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    // Woke up due to low battery
    if(SERIAL_MONITOR_EN) Serial.println("♻ Woke up from Low Bat Timer");
  }
  
  // Setup ADXL
  ADXLsetup();

  // Enable interrupt on button pin
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onRecordButton, FALLING);

  patternLength = loadPatternFromNVS(targetPattern);
  
  if(SERIAL_MONITOR_EN) Serial.println("System Ready.");
  led_ryg(0, 1, 0); 
  
  // Reset timers
  unsigned long startT = millis();
  lastKnockTime = startT;
  lastActivityTime = startT;
}

void loop() {
  adxl.readAccel(&x, &y, &z);
  float aDynamic = fabs(accelMagnitudeG(x, y, z) - 1.0);
  unsigned long now = millis();

  if (aDynamic > KNOCK_THRESHOLD || recordButtonPressed) {
    lastActivityTime = now;
  }

  // --- BATTERY CHECK (Awake) ---
  checkBatteryAwake(now);
  // -----------------------------

  if (recordButtonPressed) {
    recordButtonPressed = false;
    if (STATE == 0) { 
      startRecording();
        now = millis(); // TIMING FIX
    } else {
      if(SERIAL_MONITOR_EN) Serial.println("⚠ Cannot record: box must be unlocked.");
      badBeep(); 
    }
  }

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