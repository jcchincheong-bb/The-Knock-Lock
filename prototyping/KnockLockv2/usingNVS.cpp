#include "usingNVS.h"

// Function to load stored pattern
int loadPatternFromNVS(unsigned long intervals[]) {
  prefs.begin("knocks", true);  

  int count = prefs.getInt("count", -1);
  if (count <= 0) {
    prefs.end();
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern found in NVS.");
    return -1;
  }

  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);
    intervals[i] = prefs.getULong(key, 0);
  }

  prefs.end();
  if(SERIAL_MONITOR_EN) Serial.printf("📥 Loaded %d knock intervals from NVS.\n", count);
  return count;
}

// Function to load saved pattern
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
  if(SERIAL_MONITOR_EN) Serial.println("Pattern saved to NVS!");
}