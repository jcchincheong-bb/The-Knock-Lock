#include <ESP32Servo.h>
#include <Preferences.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>  // SparkFun ADXL345 Library

/*
  Authors: Justin Julius Chin Cheong 34140, Abhinav Kothari 33349
  Project: Knock Pattern Detection using ESP32 + ADXL345

  Features:
    • Detects knock patterns from acceleration spikes.
    • Saves & loads target pattern from ESP32 NVS.
    • Allows ±3 “junk knocks” before and after the correct pattern.
*/

// ---------------------- CONSTANTS ----------------------
const int SDA_PIN   = 4;
const int SCL_PIN   = 5;
const int SERVO_PIN = 6;
const int BUZZER    = 10;
const int RLED      = 18;
const int YLED      = 19;
const int GLED      = 3;

const float KNOCK_THRESHOLD = 0.4;  // g-force above baseline
const int PATTERN_TIMEOUT   = 3000;
const int MAX_KNOCKS        = 30;
const int KNOCK_TOL         = 150;  // ms tolerance

// Allow junk knocks
const int EXTRA_BEFORE = 3;   // allow 3 knocks before valid sequence
const int EXTRA_AFTER  = 3;   // allow 3 knocks after valid sequence

// ---------------------- VARIABLES ----------------------
Servo lockServo;
Preferences prefs;
ADXL345 adxl = ADXL345();

unsigned long knockTimes[MAX_KNOCKS];
int knockCount = 0;
unsigned long lastKnockTime = 0;

unsigned long targetPattern[MAX_KNOCKS];
int patternLength = 0;

// -------------------------------------------------------
// LOAD PATTERN FROM EEPROM
// -------------------------------------------------------
int loadPatternFromNVS(unsigned long intervals[]) {
  prefs.begin("knocks", true);  

  int count = prefs.getInt("count", -1);
  if (count <= 0) {
    prefs.end();
    Serial.println("⚠ No saved pattern found in NVS.");
    return -1;
  }

  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);
    intervals[i] = prefs.getULong(key, 0);
  }

  prefs.end();
  Serial.printf("📥 Loaded %d knock intervals from NVS.\n", count);
  return count;
}

// -------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("\nInitializing ADXL345...");
  
  Wire.begin(SDA_PIN, SCL_PIN);
  adxl.powerOn();
  adxl.setRangeSetting(2);

  pinMode(BUZZER, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);

  patternLength = loadPatternFromNVS(targetPattern);

  digitalWrite(YLED, HIGH);
  Serial.println("System Ready.");

  ESP32PWM::allocateTimer(0);
  lockServo.setPeriodHertz(50);
  lockServo.attach(SERVO_PIN, 500, 2500);
  lockServo.write(0);
}

// -------------------------------------------------------
void loop() {
  int x, y, z;
  adxl.readAccel(&x, &y, &z);

  float aMag = sqrt(
      sq(x * 0.0039) +
      sq(y * 0.0039) +
      sq(z * 0.0039)
  );

  float aDynamic = abs(aMag - 1.0);
  unsigned long now = millis();

  if (aDynamic > KNOCK_THRESHOLD) {
    if (now - lastKnockTime > 100) {
      knockTimes[knockCount++] = now;
      lastKnockTime = now;
      Serial.printf("Knock #%d detected.\n", knockCount);
    }
  }

  // Timeout detect → check pattern
  if ((now - lastKnockTime > PATTERN_TIMEOUT) && knockCount > 1) {
    checkPattern();
    resetPattern();
  }

  delay(10);
}

// -------------------------------------------------------
void checkPattern() {
  if (patternLength <= 0) {
    Serial.println("⚠ No valid pattern loaded.");
    return;
  }

  if (knockCount < 2) return;

  // Convert times → intervals
  int intervals[MAX_KNOCKS];
  for (int i = 1; i < knockCount; i++) {
    intervals[i - 1] = knockTimes[i] - knockTimes[i - 1];
    Serial.printf("Interval %d: %d ms\n", i - 1, intervals[i - 1]);
  }

  int intervalCount = knockCount - 1;

  bool match = false;

  // ---------------------------------------------------
  // Sliding window with tolerance, allowing junk knocks
  // ---------------------------------------------------
  int minStart = max(0, -EXTRA_BEFORE);
  int maxStart = intervalCount - patternLength + EXTRA_AFTER;

  for (int offset = 0; offset <= maxStart; offset++) {

    int matched = 0;
    for (int j = 0; j < patternLength; j++) {
      int idx = offset + j;

      // out of recorded bounds? invalid
      if (idx < 0 || idx >= intervalCount) {
        matched = -1;
        break;
      }

      int diff = abs(intervals[idx] - (int)targetPattern[j]);
      if (diff <= KNOCK_TOL) {
        matched++;
      } else {
        matched = -1;
        break;
      }
    }

    if (matched == patternLength) {
      match = true;
      break;
    }
  }

  if (match) {
    Serial.println("✅ Correct knock pattern detected!");
    goodBeep();
    unlockBox();
  } else {
    Serial.println("❌ Pattern incorrect.");
    badBeep();
  }
}

// -------------------------------------------------------
void unlockBox() {
  Serial.println("🔓 Unlocking...");
  lockServo.write(180);
  delay(4000);
  Serial.println("🔒 Locking...");
  lockServo.write(0);
}

// -------------------------------------------------------
void resetPattern() {
  digitalWrite(YLED, HIGH);
  digitalWrite(GLED, LOW);
  digitalWrite(RLED, LOW);
  knockCount = 0;
  lastKnockTime = 0;
  Serial.println("Pattern reset.");
}

// -------------------------------------------------------
void goodBeep() {
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, HIGH);
  tone(BUZZER, 1000, 150); delay(150);
  tone(BUZZER, 1500, 200); delay(200);
  noTone(BUZZER);
}

// -------------------------------------------------------
void badBeep() {
  digitalWrite(YLED, LOW);
  digitalWrite(RLED, HIGH);
  tone(BUZZER, 400, 200); delay(200);
  tone(BUZZER, 300, 250); delay(250);
  noTone(BUZZER);
}
