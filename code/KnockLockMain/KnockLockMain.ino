#include "config.h"
#include "hardware.h"
#include "knockPattern.h"
#include "knockRecorder.h"

// --- GLOBAL VARIABLE DEFINITIONS ---
// These define the memory space for the variables declared as 'extern' elsewhere
unsigned long targetPattern[MAX_KNOCKS];
int patternLength = 0;

unsigned long knockTimes[MAX_KNOCKS];
int knockCount = 0;
unsigned long lastKnockTime = 0;

// This array is used in the knock recorder but defined here for global scope
unsigned long intervals[MAX_KNOCKS]; 
// -----------------------------------


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupHardware();
  patternLength = loadPatternFromNVS(targetPattern);
  digitalWrite(YLED,HIGH);
  Serial.println("System Ready.");
}

void loop() {
  // put your main code here, to run repeatedly:
  int x, y, z;
  adxl.readAccel(&x, &y, &z);

  float aMag = sqrt(
      sq(x * 0.0039) +
      sq(y * 0.0039) +
      sq(z * 0.0039)
  );

  float aDynamic = abs(aMag - 1.0);
  unsigned long now = millis();

  // If button is pressed, start recording
  if (digitalRead(BUTTON_PIN) == HIGH) {
      // Small debounce delay for the button
      delay(50);
      if (digitalRead(BUTTON_PIN) == HIGH) {
          recordPattern();
          resetPattern(); // Reset count after recording
      }
  }

  // Knock detection logic
  if (aDynamic > KNOCK_THRESHOLD) {
    if (now - lastKnockTime > 100) {
      if (knockCount < MAX_KNOCKS) {
          knockTimes[knockCount++] = now;
          lastKnockTime = now;
          Serial.printf("Knock #%d detected.\n", knockCount);
      } else {
          Serial.println("Max knocks reached. Checking pattern.");
          checkPattern();
          resetPattern();
      }
    }
  }

  // Timeout detect → check pattern
  if ((now - lastKnockTime > PATTERN_TIMEOUT) && knockCount > 1) {
    checkPattern();
    resetPattern();
  }

  delay(10);
}