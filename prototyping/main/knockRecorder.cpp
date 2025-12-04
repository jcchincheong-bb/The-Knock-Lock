#include "knockRecorder.h"
#include "hardware.h"
#include "knockPattern.h"
#include "buzzerLED.h"

#include <cmath>

extern unsigned long knockTimes[];
extern int knockCount;
extern unsigned long lastKnockTime;

extern unsigned long intervals[];

constexpr float KNOCK_THRESHOLD = 0.15;
constexpr int MAX_KNOCKS = 30;
constexpr int MIN_KNOCKS = 5;
constexpr int DEBOUNCE_TIME = 120;
constexpr int IDLE_RESET_TIME = 5000;


void recordPattern() {
    Serial.println("\nButton pressed — starting recording in 1s...");
    delay(1000);

    digitalWrite(YLED, HIGH);
    knockCount = 0;
    lastKnockTime = millis();
    Serial.println("Recording knocks...");

    while (true) {
        int x, y, z;
        adxl.readAccel(&x, &y, &z);

        float aMag = sqrt(x*x + y*y + z*z) * 0.0039;
        float delta = fabs(aMag - 1.0);
        unsigned long now = millis();

        if (delta > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
            lastKnockTime = now;
            if (knockCount < MAX_KNOCKS) {
                knockTimes[knockCount++] = now;
                Serial.printf("Knock #%d\n", knockCount);
            }
        }

        if (now - lastKnockTime > IDLE_RESET_TIME) break;
        delay(10);
    }

    for (int i = 0; i < knockCount-1; i++)
        intervals[i] = knockTimes[i+1] - knockTimes[i];

    digitalWrite(YLED, LOW);

    if (knockCount < MIN_KNOCKS) {
        Serial.println("ERROR: Too few knocks.");
        LEDError();
        return;
    }

    LEDSuccess();
    savePatternToNVS(intervals, knockCount-1);
    playbackPattern();
}

void playbackPattern() {
    for (int i = 0; i < knockCount-1; i++) {
        tone(BUZZER, 2000, 80);
        noTone(BUZZER);
        delay(intervals[i]);
    }
}
