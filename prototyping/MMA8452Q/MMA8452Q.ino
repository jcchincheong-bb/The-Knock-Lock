#include <Wire.h>
#include "SparkFun_ADXL345.h"

ADXL345 adxl = ADXL345(); // For SPI communication use: ADXL245(10);

// ---- Pin Definitions ----
const int SDA_PIN = 4;
const int SCL_PIN = 5;
const int SERVO   = 6;
const int BUZZER  = 10;

// ---- Knock Detection Parameters ----
const float KNOCK_THRESHOLD = 2.0; // Minimum g-force to register a knock
const int PATTERN_TIMEOUT   = 2000; // ms
const int KNOCK_RESET_TIMEOUT = 5000; // ms
const int MAX_KNOCKS = 10;
const int KNOCK_TOL = 100; // ms

// ---- Knock Pattern Variables ----
unsigned long knockTimes[MAX_KNOCKS];
int knockCount = 0;
unsigned long lastKnockTime = 0;

// ---- Pattern Definition ----
int targetPattern[] = {550, 555, 250, 240, 510, 506};
int patternLength = sizeof(targetPattern) / sizeof(targetPattern[0]);

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);

  adxl.powerOn();
  adxl.setRangeSetting(2);

  adxl.setActivityXYZ(1, 1, 1);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)

  adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setInactivityThreshold(75);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?

  pinMode(SERVO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("Knock Detection Ready!");
}

void loop() {
  int x, y, z;   
  adxl.readAccel(&x, &y, &z);

  // Convert to g-units
  float xg = x * 0.0039;
  float yg = y * 0.0039;
  float zg = z * 0.0039;

  float aMag = sqrt(xg * xg + yg * yg + zg * zg);
  float aDynamic = abs(aMag - 1.0); // remove gravity component
  unsigned long now = millis();

  // Debug
  Serial.print("Dynamic Accel: ");
  Serial.println(aDynamic);

  // Knock detection
  if (aDynamic > KNOCK_THRESHOLD && now - lastKnockTime > 100) {
    lastKnockTime = now;
    if (knockCount < MAX_KNOCKS) {
      knockTimes[knockCount++] = now;
      Serial.print("Knock #"); Serial.println(knockCount);

      if (knockCount > 1) {
        Serial.print("Interval since last knock: ");
        Serial.println(knockTimes[knockCount - 1] - knockTimes[knockCount - 2]);
      }
    }

    if (knockCount >= MAX_KNOCKS) {
      Serial.println("\n=== All 10 knocks detected ===");
      for (int i = 1; i < MAX_KNOCKS; i++) {
        Serial.print("Knock "); Serial.print(i);
        Serial.print(" → "); Serial.print(i + 1);
        Serial.print(": "); Serial.println(knockTimes[i] - knockTimes[i - 1]);
      }
      knockCount = 0;
      lastKnockTime = 0;
    }
  }

  // Idle reset
  if (knockCount > 0 && now - lastKnockTime > KNOCK_RESET_TIMEOUT) {
    Serial.println("No knocks for 5s — resetting.");
    knockCount = 0;
    lastKnockTime = 0;
  }

  delay(10);
}

