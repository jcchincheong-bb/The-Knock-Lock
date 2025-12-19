#include <ESP32Servo.h>
#include <Preferences.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>

/*  Authors: Justin Julius Chin Cheong 34140, Abhinav Kothari 33349 
    Project: Knock Pattern Detection using ESP32 + ADXL345
    Features: 
      • Detects knock patterns from acceleration spikes. 
      • Saves & loads target pattern from ESP32 NVS. 
      • Allows ±3 “junk knocks” before and after the correct pattern.
      • Lock out after 5minutes, or when 2 knocks 
*/

// -------------------------------------------------------------
// INLINE ACCELERATION CALC
// -------------------------------------------------------------
inline float accelMagnitudeG(int x, int y, int z) {
  return sqrt(x*x + y*y + z*z) * 0.0039;   // ADXL345 scale factor
}

// -------------------------------------------------------------
// PIN DEFINITIONS
// -------------------------------------------------------------
const int SDA_PIN   = 6;
const int SCL_PIN   = 5;
const int SERVO_EN = 0;
const int SERVO_CONTROL = 1;
const int BUZZER    = 10;
const int RLED      = 3;
const int YLED      = 19;
const int GLED      = 18;
const int BUTTON_PIN = 7;

const float KNOCK_THRESHOLD = 0.2;
const int PATTERN_TIMEOUT   = 3000;
const int MAX_KNOCKS        = 30;
const int MIN_KNOCKS        = 5;
const int KNOCK_TOL         = 150;
const int DEBOUNCE_TIME     = 120;
const int IDLE_RESET_TIME   = 5000;
const int LOCK_OUT_TIME = 300000; // 5 minutes in ms

const int EXTRA_BEFORE = 3;
const int EXTRA_AFTER  = 3;

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

int x, y, z;

// -------------------------------------------------------------
// MODE STATE MACHINE
// -------------------------------------------------------------
enum Mode { MODE_IDLE, MODE_RECORDING };
volatile Mode currentMode = MODE_IDLE;
volatile int STATE = 0; // 0 is locked, 1 is unlocked

// Interrupt flag
volatile bool recordButtonPressed = false;

// -------------------------------------------------------------
// BUTTON INTERRUPT
// -------------------------------------------------------------
void IRAM_ATTR onRecordButton() {
  recordButtonPressed = true;
}

// -------------------------------------------------------------
// LOAD PATTERN FROM NVS
// -------------------------------------------------------------
int loadPatternFromNVS(unsigned long intervals[]) {
  prefs.begin("knocks", true);
  int count = prefs.getInt("count", -1);

  if (count <= 0) {
    prefs.end();
    Serial.println("⚠ No saved pattern in NVS.");
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

// -------------------------------------------------------------
// SETUP
// -------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(SERVO_EN, OUTPUT);
  pinMode(SERVO_CONTROL, OUTPUT);

  Wire.begin(SDA_PIN, SCL_PIN);
  adxl.powerOn();
  adxl.setRangeSetting(2);

  pinMode(BUZZER, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onRecordButton, FALLING);

  patternLength = loadPatternFromNVS(targetPattern);

  ESP32PWM::allocateTimer(0);
  lockServo.setPeriodHertz(50);
  lockServo.attach(SERVO_CONTROL, 500, 2500);
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(0);
  delay(2000);
  lockServo.write(180);
  delay(2000);
  digitalWrite(YLED, HIGH);
  lastKnockTime = millis();

  Serial.println("System Ready.");
}

// -------------------------------------------------------------
// MODE HANDLERS
// -------------------------------------------------------------
void startRecording() {
  Serial.println("\n🎙 Starting NEW recording...");
  // Turn on all LEDs to show shift to recording mode.
  digitalWrite(RLED, HIGH);
  digitalWrite(YLED, HIGH);
  digitalWrite(GLED, HIGH);
  delay(1000); // Short delay
  digitalWrite(RLED, LOW);
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, LOW);
  delay(1000);
  knockCount = 0;
  lastKnockTime = millis();
  digitalWrite(YLED, HIGH);
}

void finishRecording() {
  digitalWrite(YLED, LOW);

  if (knockCount < MIN_KNOCKS) {
    Serial.println("❌ Too few knocks. Discarding.");
    digitalWrite(RLED, HIGH); delay(800); digitalWrite(RLED, LOW);
    return;
  }

  for (int j = 0; j < knockCount - 1; j++) {
    intervals[j] = knockTimes[j + 1] - knockTimes[j];
  }

  Serial.printf("Recorded %d knocks\n", knockCount);
  for (int i = 0; i < knockCount - 1; i++) {
    Serial.printf("%d → %d : %ld ms\n", i+1, i+2, intervals[i]);
  }

  digitalWrite(GLED, HIGH); delay(800); digitalWrite(GLED, LOW);

  savePatternToNVS(intervals, knockCount - 1);
  playbackPattern();
}

void processRecording(float aDynamic, unsigned long now) {

  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    lastKnockTime = now;

    if (knockCount < MAX_KNOCKS) {
      knockTimes[knockCount] = now;
      knockCount++;
      Serial.printf("REC Knock #%d\n", knockCount);
    }
  }

  if (now - lastKnockTime > IDLE_RESET_TIME) {
    finishRecording();
    currentMode = MODE_IDLE;
  }
}

void processNormalKnock(float aDynamic, unsigned long now) {

  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    knockTimes[knockCount] = now;
    knockCount++;
    lastKnockTime = now;
    Serial.printf("Knock #%d\n", knockCount);
  }

  if (knockCount > 1 && (now - lastKnockTime > PATTERN_TIMEOUT)) {
    checkPattern();
    resetPattern();
  }
}

// -------------------------------------------------------------
// CHECK PATTERN
// -------------------------------------------------------------
void checkPattern() {

  if (patternLength <= 0) {
    Serial.println("⚠ No saved pattern.");
    return;
  }

  if (knockCount < 2)
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
    Serial.println("✅ Correct pattern!");
    STATE = 1;
    goodBeep();
    unlockBox();
  } else {
    Serial.println("❌ Wrong pattern.");
    badBeep();
  }
}

// -------------------------------------------------------------
void unlockBox() {
  Serial.println("🔓 Unlocking...");
  digitalWrite(SERVO_EN, HIGH); // Enable power to servo
  lockServo.write(180);         // Unlock servo
  delay(500);
  digitalWrite(SERVO_EN, LOW);  // Disable power to servo
  lockingCheck();
}

void resetPattern() {
  digitalWrite(YLED, HIGH);
  digitalWrite(GLED, LOW);
  digitalWrite(RLED, LOW);
  knockCount = 0;
  lastKnockTime = millis();
  Serial.println("Pattern reset.");
}

// -------------------------------------------------------------
void goodBeep() {
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, HIGH);
  tone(BUZZER, 1000, 150); delay(150);
  tone(BUZZER, 1500, 200); delay(200);
  noTone(BUZZER);
}

void badBeep() {
  digitalWrite(YLED, LOW);
  digitalWrite(RLED, HIGH);
  tone(BUZZER, 400, 200); delay(200);
  tone(BUZZER, 300, 250); delay(250);
  noTone(BUZZER);
}

// -------------------------------------------------------------
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

void playbackPattern() {
  for (int i = 0; i < knockCount - 1; i++) {
    tone(BUZZER, 2000);
    delay(80);
    noTone(BUZZER);
    delay(intervals[i]);
  }
}

void lockingCheck() {
  Serial.println("🔓 Unlocked. Waiting for relock or reprogram...");

  unsigned long startTime = millis();
  int knockCountUnlock = 0;

  while (true) {

    // 🟦 CHECK BUTTON (THIS IS THE FIX)
    if (recordButtonPressed) {
      recordButtonPressed = false;
      Serial.println("🎙 Button pressed while unlocked → start recording");
      currentMode = MODE_RECORDING;
      knockCount = 0;
      lastKnockTime = millis();
      digitalWrite(YLED, HIGH);
      return;   // ⬅ EXIT lockingCheck() BACK TO loop()
    }

    // Read accelerometer
    adxl.readAccel(&x, &y, &z);
    float aMag = accelMagnitudeG(x, y, z);
    float aDynamic = fabs(aMag - 1.0);
    unsigned long now = millis();

    // Knock detection (unlock-state)
    if (aDynamic > KNOCK_THRESHOLD) {
      knockCountUnlock++;
      Serial.printf("Unlock-state knock %d\n", knockCountUnlock);

      if (knockCountUnlock >= 2) {
        STATE = 0;
        break;
      }

      delay(DEBOUNCE_TIME);
    }

    // Auto-lock after 5 minutes
    if (now - startTime >= LOCK_OUT_TIME) {
      Serial.println("⏳ Auto-lock timeout.");
      STATE = 0;
      break;
    }

    delay(5);
  }

  Serial.println("🔒 Locking...");
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(0);
  delay(500);
  digitalWrite(SERVO_EN, LOW);
}


// -------------------------------------------------------------
// MAIN LOOP — NON-BLOCKING
// -------------------------------------------------------------
void loop() {
  // 🟧 ALWAYS READ ACCELEROMETER
  adxl.readAccel(&x, &y, &z);
  float aMag = accelMagnitudeG(x, y, z);
  float aDynamic = fabs(aMag - 1.0);
  unsigned long now = millis();

  // 🟦 BUTTON EVENT
  if (recordButtonPressed) {
    recordButtonPressed = false;

    if (STATE == 1 && currentMode == MODE_IDLE) {
      startRecording();
      currentMode = MODE_RECORDING;
    } else {
      Serial.println("⚠ Cannot record: box must be unlocked.");
    }
  }


  if (currentMode == MODE_RECORDING) {
    processRecording(aDynamic, now);
  } else if (currentMode == MODE_IDLE && STATE == 0) {
    processNormalKnock(aDynamic, now);
  }


  delay(5);
}
