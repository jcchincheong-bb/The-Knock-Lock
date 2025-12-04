#include "knockPattern.h"
#include "hardware.h"
#include "buzzerLED.h"
#include <cmath>

extern unsigned long targetPattern[];
extern int patternLength;


constexpr int MAX_KNOCKS = 30;
constexpr int KNOCK_TOL = 150;
constexpr int EXTRA_BEFORE = 3;
constexpr int EXTRA_AFTER  = 3;

int loadPatternFromNVS(unsigned long intervals[]) {
    prefs.begin("knocks", true);
    int count = prefs.getInt("count", -1);
    if (count <= 0) {
        prefs.end();
        Serial.println("⚠ No saved pattern found.");
        return -1;
    }

    for (int i=0; i<count; i++) {
        char key[8];
        sprintf(key,"i%d",i);
        intervals[i] = prefs.getULong(key,0);
    }
    prefs.end();
    Serial.printf("📥 Loaded %d intervals.\n", count);
    return count;
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

bool checkPattern(unsigned long recordedIntervals[], int count) {
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
