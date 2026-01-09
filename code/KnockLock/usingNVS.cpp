#include "usingNVS.h"

// Function to load stored pattern
int loadPatternFromNVS(unsigned long intervals[]) {
  prefs.begin("knocks", true);   // Start communication, reading only

  int count = prefs.getInt("count", -1); // Gets count, if no count saved, sets default to -1 which is not possible normally
  if (count <= 0) { // Checking if no count was saved, in which case sets default value less than 0
    prefs.end(); // End communication reading storage, as if no count then no interval too
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern found in NVS.");
    return -1;
  }

  // Read intervals from storage
  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i); // Read values
    intervals[i] = prefs.getULong(key, 0);
  }

  prefs.end(); // End communication reading storage
  if(SERIAL_MONITOR_EN) Serial.printf("📥 Loaded %d knock intervals from NVS.\n", count);
  return count;
}

// Function to load saved pattern
void savePatternToNVS(unsigned long intervals[], int count) {
  prefs.begin("knocks", false);  // Start communication, Read and Write mode

  prefs.putInt("count", count); // Store count of intervals

  // Store each interval
  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);     // keys: i0, i1, i2...
    prefs.putULong(key, intervals[i]);
  }

  prefs.end(); // End communication reading storage
  if(SERIAL_MONITOR_EN) Serial.println("Pattern saved to NVS!");
}