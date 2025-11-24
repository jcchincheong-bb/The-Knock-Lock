#include <Wire.h>
#include <Preferences.h>
#include <SparkFun_ADXL345.h>

ADXL345 adxl;
Preferences prefs;

// -------------------------------------------------------------
// Pin Definitions
// -------------------------------------------------------------
const int SDA_PIN = 4;
const int SCL_PIN = 5;

const int BUTTON_PIN = 7;
const int PIEZO_PIN  = 10;

const int LED_YELLOW = 19;
const int LED_GREEN  = 3;
const int LED_RED    = 18;

// -------------------------------------------------------------
// Knock Detection Parameters
// -------------------------------------------------------------
const float KNOCK_THRESHOLD = 0.15;   // LOWER = more sensitive
const int MAX_KNOCKS = 30;
const int MIN_KNOCKS = 5;
const int DEBOUNCE_TIME = 120;
const int IDLE_RESET_TIME = 5000;

// -------------------------------------------------------------
unsigned long knockTimes[MAX_KNOCKS];
unsigned long intervals[MAX_KNOCKS-1];
int knockCount = 0;
unsigned long lastKnockTime = 0;

// -------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);

  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);

  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("Initializing ADXL345...");
  adxl.powerOn();
  adxl.setRangeSetting(2);

  Serial.println("Ready.");
}

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
  Serial.println("Pattern saved to NVS!");
}


// -------------------------------------------------------------
void playbackPattern() {
  for (int i = 0; i < knockCount-1; i++) {
    unsigned long interval = intervals[i];

    tone(PIEZO_PIN, 2000);
    delay(80);
    noTone(PIEZO_PIN);

    delay(interval);
  }
}

// -------------------------------------------------------------
void recordPattern() {
  Serial.println("\nButton pressed — starting recording in 1s...");
  delay(1000);

  digitalWrite(LED_YELLOW, HIGH);

  knockCount = 0;
  lastKnockTime = millis();

  Serial.println("Recording knocks...");

  while (true) {

    // Read accelerometer
    int x, y, z;
    adxl.readAccel(&x, &y, &z);

    // Convert to g
    float aMag = sqrt(x*x + y*y + z*z) * 0.0039;
    float delta = fabs(aMag - 1.0);

    unsigned long now = millis();

    // Detect knock
    if (delta > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
      lastKnockTime = now;

      if (knockCount < MAX_KNOCKS) {
        knockTimes[knockCount] = now;
        knockCount++;

        Serial.print("Knock #");
        Serial.println(knockCount);
      }
    }

    // Idle timeout
    if (now - lastKnockTime > IDLE_RESET_TIME)
      break;

    delay(10);
  }

  for(int j = 0; j < knockCount-1; j++){
    intervals[j] = knockTimes[j+1]-knockTimes[j];
  }

  digitalWrite(LED_YELLOW, LOW);

  // Validate
  if (knockCount < MIN_KNOCKS) {
    Serial.println("ERROR: Too few knocks.");
    digitalWrite(LED_RED, HIGH);
    delay(1500);
    digitalWrite(LED_RED, LOW);
    return;
  }

  Serial.print("Recorded ");
  Serial.print(knockCount);
  Serial.println(" knocks.");
  Serial.println("Intervals: ");
  for(int i = 0; i < knockCount-1; i++){
    Serial.printf("%d -> %d : %ld \n",i+1,i+2,intervals[i]);
  }

  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
  digitalWrite(LED_GREEN, LOW);

  savePatternToNVS(intervals, knockCount - 1);
  playbackPattern();
}

// -------------------------------------------------------------
void loop() {

  if (digitalRead(BUTTON_PIN) == HIGH) {
    // wait for release to avoid double-trigger
    while (digitalRead(BUTTON_PIN) == HIGH) {}
    recordPattern();
  }
}
