#include <Wire.h>
#include <SparkFun_ADXL345.h>  // SparkFun ADXL345 Library

ADXL345 adxl; // I2C mode

// ---- Pin Definitions ----
const int SDA_PIN = 4;
const int SCL_PIN = 5;
const int WriteButton = 9;

// ---- Knock Detection Parameters ----
const float KNOCK_THRESHOLD = 0.4; // g-force above 1g baseline to register a knock
const int MAX_KNOCKS = 7;
const int DEBOUNCE_TIME = 100;     // ms between valid knocks
const int IDLE_RESET_TIME = 5000;  // ms to reset if no knocks

// ---- Knock Pattern Variables ----
unsigned long knockTimes[MAX_KNOCKS];
int knockCount = 0;
unsigned long lastKnockTime = 0;

void setup() {
  pinMode(WriteButton, INPUT);

  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("Initializing ADXL345...");

  adxl.powerOn();
  adxl.setRangeSetting(2); // ±2g for best sensitivity

  // Optional configuration for better stability
  adxl.setActivityXYZ(1, 1, 1);  // enable activity detection on all axes
  adxl.setActivityThreshold(75); // ~4.7g threshold, can tune if needed

  Serial.println("Knock Detection Ready!");
}

void loop() {
  int x, y, z;
  if(digitalRead(WriteButton)){
    adxl.readAccel(&x, &y, &z);

    // Convert to g units (each LSB ≈ 0.0039g in ±2g mode)
    float xg = x * 0.0039;
    float yg = y * 0.0039;
    float zg = z * 0.0039;

    // Compute total acceleration magnitude
    float aMag = sqrt(xg * xg + yg * yg + zg * zg);
    float aDynamic = abs(aMag - 1.0); // remove gravity (~1g)

    unsigned long now = millis();

    // ---- Knock detection ----
    if (aDynamic > KNOCK_THRESHOLD && now - lastKnockTime > DEBOUNCE_TIME) {
      lastKnockTime = now;

      if (knockCount < MAX_KNOCKS) {
        knockTimes[knockCount] = now;
        knockCount++;

        Serial.print("Knock #");
        Serial.print(knockCount);
        Serial.print(" at ");
        Serial.print(now / 1000.0, 3);
        Serial.println(" s");

        if (knockCount > 1) {
          unsigned long interval = knockTimes[knockCount - 1] - knockTimes[knockCount - 2];
          Serial.print("Interval since last knock: ");
          Serial.print(interval);
          Serial.println(" ms");
        }
      }

      // ---- If max knocks reached, print all intervals ----
      if (knockCount == MAX_KNOCKS) {
        Serial.println("\n=== All knocks detected ===");
        for (int i = 1; i < MAX_KNOCKS; i++) {
          unsigned long interval = knockTimes[i] - knockTimes[i - 1];
          Serial.print("Knock ");
          Serial.print(i);
          Serial.print(" → ");
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(interval);
          Serial.println(" ms");
        }
        Serial.println("===========================\n");

        // Reset for next round
        knockCount = 0;
        lastKnockTime = 0;
      }
    }

    // ---- Idle reset ----
    if (knockCount > 0 && now - lastKnockTime > IDLE_RESET_TIME) {
      Serial.println("No knocks for 5 seconds — resetting.");
      knockCount = 0;
      lastKnockTime = 0;
    }

    delay(10); // small delay for stability
  }
}
