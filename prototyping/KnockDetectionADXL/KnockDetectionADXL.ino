#include <ESP32Servo.h>

#include <Wire.h>
#include <SparkFun_ADXL345.h>  // SparkFun ADXL345 Library


/*
  Authors: Justin Julius Chin Cheong 34140, Abhinav Kothari 33349
  Project: Knock Pattern Detection using ESP32 + ADXL345
  Description:
    Detects specific knock patterns based on acceleration spikes.
    If no knock is detected for 5 seconds after the last one, resets detection.
*/

// --- Servo ----
Servo lockServo;

// ---- Sensor ----
ADXL345 adxl = ADXL345();  // Use for I2C communication

// ---- Pin Definitions ----
const int SDA_PIN = 4;
const int SCL_PIN = 5;
const int SERVO_PIN = 6;
const int BUZZER  = 10;
const int RLED = 3;
const int YLED = 18;
const int GLED = 19;

// ---- Knock Detection Parameters ----
const float KNOCK_THRESHOLD = 0.4;     // g-force above 1g baseline to count as a knock
const int PATTERN_TIMEOUT   = 3000;    // ms: time to check pattern after last knock
const int MAX_KNOCKS = 10;
const int KNOCK_TOL = 100;             // ms tolerance for pattern matching

// ---- Knock Pattern Variables ----
unsigned long knockTimes[MAX_KNOCKS];
int knockCount = 0;
unsigned long lastKnockTime = 0;

// ---- Pattern Definition ----
int targetPattern[] = {460, 430, 260, 190, 440, 430};
int patternLength = sizeof(targetPattern) / sizeof(targetPattern[0]);

// ---------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Initializing ADXL345...");
  Wire.begin(SDA_PIN, SCL_PIN);

  adxl.powerOn();
  adxl.setRangeSetting(2 ); // ±2g for better sensitivity

  pinMode(BUZZER, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);

  digitalWrite(YLED, HIGH);

  Serial.println("Knock Detection Ready!");

  // Servo Setup
  ESP32PWM::allocateTimer(0);
  lockServo.setPeriodHertz(50); // standard 50 Hz servo
  lockServo.attach(SERVO_PIN, 500, 2500); // min/max pulse width for most servos
  lockServo.write(0); // locked position
}

// ---------------------------------------------------
void loop() {
  int x, y, z;
  adxl.readAccel(&x, &y, &z);

  // Convert to g-units (each LSB = 3.9 mg in ±2g mode)
  float xg = x * 0.0039;
  float yg = y * 0.0039;
  float zg = z * 0.0039;

  // Compute total acceleration magnitude
  float aMag = sqrt(xg * xg + yg * yg + zg * zg);
  float aDynamic = abs(aMag - 1.0); // subtract gravity

  unsigned long now = millis();

  // ---- Knock Detection ----
  if (aDynamic > KNOCK_THRESHOLD) {
    if (now - lastKnockTime > 100) { // debounce
      knockTimes[knockCount++] = now;
      lastKnockTime = now;
      Serial.print("Knock #");
      Serial.println(knockCount);

      if (knockCount == 1)
        Serial.println("First knock detected!");

      // When enough knocks are recorded, check pattern
      if (knockCount >= 10) {
        checkPattern();
        resetPattern();
      }
    }
  }

  // ---- 3s pattern timeout ----
  if ((now - lastKnockTime > PATTERN_TIMEOUT) && knockCount > 1) {
    checkPattern();
    resetPattern();
  }

  delay(10);
}

// ---------------------------------------------------
void checkPattern() {
  if (knockCount < 2) return;

  int intervals[MAX_KNOCKS];
  for (int i = 1; i < knockCount; i++) {
    intervals[i - 1] = knockTimes[i] - knockTimes[i - 1];
    Serial.print("Knock Interval: ");
    Serial.println(intervals[i - 1]);
  }

  bool match = false;
  int diff;

  // ---- Sliding window pattern check ----
  if (knockCount - 1 >= patternLength) {
    for (int offset = 0; offset <= knockCount - 1 - patternLength; offset++) {
      bool segmentMatch = true;

      for (int j = 0; j < patternLength; j++) {
        diff = abs(intervals[offset + j] - targetPattern[j]);
        Serial.print("Interval diff (offset ");
        Serial.print(offset);
        Serial.print(", step ");
        Serial.print(j);
        Serial.print("): ");
        Serial.println(diff);

        if (diff > KNOCK_TOL) {
          segmentMatch = false;
          break;
        }
      }

      if (segmentMatch) {
        match = true;
        break;
      }
    }
  }

  if (match) {
    Serial.println("✅ Correct knock pattern detected!");
    goodBeep();
    unlockBox();
  } else {
    Serial.println("❌ Wrong pattern");
    badBeep();
  }
}

// ---------------------------------------------------
void unlockBox() {
  Serial.println("🔓 Unlocking...");
  lockServo.write(180); // Move servo to unlock position
  delay(4000);
  Serial.println("🔒 Locking again...");
  lockServo.write(0); // Back to locked position
}

// ---------------------------------------------------
void resetPattern() {
  digitalWrite(YLED, HIGH);
  digitalWrite(GLED, LOW);
  digitalWrite(RLED, LOW);
  knockCount = 0;
  lastKnockTime = 0;
  Serial.println("Pattern reset.");
}

// ---------------------------------------------------
// Success beep (pleasant)
void goodBeep() {
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, HIGH);
  tone(BUZZER, 1000, 150);
  delay(150);
  tone(BUZZER, 1500, 200);
  delay(200);
  noTone(BUZZER);
}

// ---------------------------------------------------
// Error beep (less pleasant)
void badBeep() {
  digitalWrite(YLED, LOW);
  digitalWrite(RLED, HIGH);
  tone(BUZZER, 400, 200);
  delay(200);
  tone(BUZZER, 300, 250);
  delay(250);
  noTone(BUZZER);
}
