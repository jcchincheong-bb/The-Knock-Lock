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
    prefs.begin("knocks", false);
    prefs.putInt("count", count);
    for (int i=0; i<count; i++) {
        char key[8];
        sprintf(key,"i%d",i);
        prefs.putULong(key, intervals[i]);
    }
    prefs.end();
    Serial.println("Pattern saved to NVS!");
}

bool checkKnockPattern(unsigned long recordedIntervals[], int count) {
    if (patternLength <= 0) return false;
    int intervalCount = count;

    bool match = false;
    int minStart = 0;
    int maxStart = intervalCount - patternLength + EXTRA_AFTER;

    for (int offset = 0; offset <= maxStart; offset++) {
        int matched = 0;
        for (int j = 0; j < patternLength; j++) {
            int idx = offset + j;
            if (idx < 0 || idx >= intervalCount) {
                matched = -1; break;
            }
            int diff = abs((int)(recordedIntervals[idx] - targetPattern[j]));
            if (diff <= KNOCK_TOL) matched++;
            else { matched = -1; break; }
        }
        if (matched == patternLength) { match = true; break; }
    }

    return match;
}
