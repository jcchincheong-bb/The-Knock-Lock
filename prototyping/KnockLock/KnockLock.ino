#include <ESP32Servo.h>
#include <Preferences.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>

/* Project: Knock Pattern Detection (Battery Monitored)
   Authors: Justin Julius Chin Cheong, Abhinav Kothari 
*/

// -------------------------------------------------------------
// PIN DEFINITIONS
// -------------------------------------------------------------
const int SDA_PIN = 6;
const int SCL_PIN = 5;
const int WAKE_INT = 4;

const int SERVO_EN = 0;
const int SERVO_CONTROL = 1;

const int BUZZER = 10;
const int RLED = 3;
const int YLED = 19;
const int GLED = 18;
const int BUTTON_PIN = 7;

// Battery Pin
const int BAT_PIN = 2; 

// -------------------------------------------------------------
// CONSTANTS
// -------------------------------------------------------------
const float KNOCK_THRESHOLD = 0.25; 
const int MAX_KNOCKS = 30;
const int MIN_KNOCKS = 5;
const int KNOCK_TOL = 150;
const int DEBOUNCE_TIME = 150;      
const int PATTERN_TIMEOUT = 2000;   
const int IDLE_RESET_TIME = 5000;   
const int SLEEP_TIMEOUT = 60000;    // 1 Minute

const int EXTRA_BEFORE = 3;
const int EXTRA_AFTER = 3;

// --- BATTERY SETTINGS ---
const float VOLTAGE_MULTIPLIER = 2.47; 
// 30% of 4xAA
const float LOW_BAT_THRESHOLD_V = 4.6; 
const unsigned long BAT_CHECK_INTERVAL = 5000; // Check every 5s while awake

// -------------------------------------------------------------
// GLOBALS
// -------------------------------------------------------------
Servo lockServo;
Preferences prefs;
ADXL345 adxl;

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

void led_ryg(int rState, int yState, int gState) {
  digitalWrite(RLED, rState);
  digitalWrite(YLED, yState);
  digitalWrite(GLED, gState);
}

// -------------------------------------------------------------
// BATTERY FUNCTIONS
// -------------------------------------------------------------
float getBatteryVoltage() {
  // Read millivolts (ESP32C3 internal calibration)
  uint32_t rawMV = analogReadMilliVolts(BAT_PIN);
  
  // Convert to actual battery voltage (Divider Logic)
  float batV = (rawMV * VOLTAGE_MULTIPLIER) / 1000.0;
  
  Serial.printf("Bat: %.2f V\n", batV);
  
  return batV;
}

void checkBatteryAwake(unsigned long now) {
  if (now - lastBatCheck > BAT_CHECK_INTERVAL) {
    lastBatCheck = now;
    if (getBatteryVoltage() < LOW_BAT_THRESHOLD_V) {
      Serial.println("⚠ Low Battery!");
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
int loadPatternFromNVS(unsigned long intervals[]) {
  prefs.begin("knocks", true);
  int count = prefs.getInt("count", -1);
  if (count <= 0) {
    prefs.end();
    return -1;
  }
  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);
    intervals[i] = prefs.getULong(key, 0);
  }
  prefs.end();
  Serial.printf("📥 Loaded %d intervals\n", count);
  return count;
}

void savePatternToNVS(unsigned long intervals[], int count) {
  prefs.begin("knocks", false);
  prefs.putInt("count", count);
  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);
    prefs.putULong(key, intervals[i]);
  }
  prefs.end();
  Serial.println("💾 Pattern saved to NVS");
}

void ADXLsetup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  adxl.powerOn();
  adxl.setRangeSetting(2);
  adxl.setTapDetectionOnXYZ(1, 1, 1);
  adxl.setTapThreshold(40);
  adxl.setTapDuration(20);
  adxl.setDoubleTapLatency(80);
  adxl.setDoubleTapWindow(200);

  adxl.doubleTapINT(0);
  adxl.singleTapINT(0);
  adxl.FreeFallINT(0);
  adxl.ActivityINT(0);
  adxl.InactivityINT(0);
  adxl.getInterruptSource();
}

// -------------------------------------------------------------
// SLEEP LOGIC (With Low Bat Monitor)
// -------------------------------------------------------------
void goToSleep() {
  led_ryg(0,0,0);
  
  // 1. Check Battery before sleeping
  float batV = getBatteryVoltage();
  bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);

  // 2. Prepare ADXL Wakeup
  adxl.doubleTapINT(1);
  adxl.getInterruptSource();
  esp_deep_sleep_enable_gpio_wakeup(1ULL << WAKE_INT, ESP_GPIO_WAKEUP_GPIO_HIGH);

  if (lowBattery) {
    Serial.printf("💤 Low Battery (%.2fV). Blinking and sleeping 4s...\n", batV);
    
    // Blink Red indicating "I'm sleeping but dying"
    digitalWrite(RLED, HIGH);
    delay(100);
    digitalWrite(RLED, LOW);
    
    // Enable Timer Wakeup (4 seconds)
    // This creates the "Blink while sleeping" loop
    esp_sleep_enable_timer_wakeup(4 * 1000000ULL); 
  } else {
    Serial.println("💤 Good Battery. Deep Sleep (Waiting for Knock)...");
    // No timer wakeup, sleep indefinitely until knock
  }

  esp_deep_sleep_start();
}

// -------------------------------------------------------------
// FEEDBACK & SERVO
// -------------------------------------------------------------
void flashGreenTick() {
  bool yellowWasOn = digitalRead(YLED);
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, HIGH);
  delay(50);
  digitalWrite(GLED, LOW);
  if(yellowWasOn) digitalWrite(YLED, HIGH);
}

void goodBeep() {
  led_ryg(0, 0, 1);
  tone(BUZZER, 1000, 150);
  delay(150);
  tone(BUZZER, 1500, 200);
  delay(200);
  noTone(BUZZER);
}

void badBeep() {
  led_ryg(1, 0, 0);
  tone(BUZZER, 400, 200);
  delay(200);
  tone(BUZZER, 300, 250);
  delay(250);
  noTone(BUZZER);
}

void successSave() {
  Serial.println("✅ Recording Saved.");
  led_ryg(0,0,0);
  for(int i=0; i<2; i++){
    led_ryg(0,0,1);
    delay(200);
    led_ryg(0,0,0);
    delay(200);
  }
}

void playbackPattern() {
  Serial.println("🔊 Playing back pattern...");
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

void unlockBox() {
  if (STATE == 1) return;
  Serial.println("🔓 Unlocking...");
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(180);
  delay(500);
  digitalWrite(SERVO_EN, LOW);
  
  STATE = 1; 
  knockCount = 0; 
}

void lockBox() {
  Serial.println("🔒 Locking...");
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
void checkPattern() {
  if (patternLength <= 0) return;
  if (knockCount < MIN_KNOCKS) {
    Serial.println("❌ Too few knocks.");
    badBeep();
    return;
  }
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
      if (idx < 0 || idx >= intervalCount) {
        ok = false; break;
      }
      long diff = labs((long)intervals[idx] - (long)targetPattern[j]);
      if (diff > KNOCK_TOL) {
        ok = false; break;
      }
    }
    if (ok) {
      match = true; break;
    }
  }

  if (match) {
    Serial.println("✅ Pattern Matched!");
    goodBeep();
    unlockBox();
  } else {
    Serial.println("❌ Wrong Pattern.");
    badBeep();
  }
}

void startRecording() {
  Serial.println("\n🎙 Starting NEW recording...");
  led_ryg(1, 1, 1);
  delay(500);
  led_ryg(0, 0, 0);
  delay(500);
  
  knockCount = 0;
  // --- TIMING FIX ---
  unsigned long resetTime = millis();
  lastKnockTime = resetTime;
  lastActivityTime = resetTime;
  // ------------------
  
  currentMode = MODE_RECORDING;
  led_ryg(0, 1, 0); 
}

void finishRecording() {
  if (knockCount < MIN_KNOCKS) {
    Serial.println("❌ Recording Failed: Too few knocks.");
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

void handleRecording(float aDynamic, unsigned long now) {
  if (now - lastKnockTime > IDLE_RESET_TIME) {
    finishRecording();
    return;
  }
  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    flashGreenTick();
    led_ryg(0, 1, 0); 
    if (knockCount < MAX_KNOCKS) {
      knockTimes[knockCount] = now;
      knockCount++;
      lastKnockTime = now;
      Serial.printf("REC Knock #%d\n", knockCount);
    }
  }
}

void handleLockedState(float aDynamic, unsigned long now) {
  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    lastKnockTime = now;
    lastActivityTime = now; 
    flashGreenTick();
    led_ryg(0, 1, 0);
    knockTimes[knockCount] = now;
    knockCount++;
    Serial.printf("Locked Knock #%d\n", knockCount);
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
    Serial.printf("Unlock Knock #%d\n", knockCount);
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
  Serial.begin(115200);
  
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Battery Pin (ADC)
  pinMode(BAT_PIN, INPUT); 

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onRecordButton, FALLING);

  // WAKE UP CHECK
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_GPIO) {
    // Woke up by ADXL Tap
    digitalWrite(YLED, HIGH); 
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    // Woke up by Battery Timer (Low battery loop)
    // We just woke up to blink, but we should also check if we need to stay awake (knock?)
    // Actually, in this loop, we just fall through to loop() which will re-read battery 
    // and go back to sleep if no activity.
    Serial.println("♻ Woke up from Low Bat Timer");
  }

  ADXLsetup();

  ESP32PWM::allocateTimer(0);
  lockServo.setPeriodHertz(50);
  lockServo.attach(SERVO_CONTROL, 500, 2500);
  pinMode(SERVO_EN, OUTPUT);
  
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(0); 
  delay(500);
  digitalWrite(SERVO_EN, LOW);

  patternLength = loadPatternFromNVS(targetPattern);
  
  Serial.println("System Ready.");
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
    if (STATE == 1) { 
      startRecording();
      now = millis(); // TIMING FIX
    } else {
      Serial.println("⚠ Cannot record: box must be unlocked.");
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