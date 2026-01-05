#include "batteryMonitoring.h"

// -------------------------------------------------------------
// BATTERY FUNCTIONS
// -------------------------------------------------------------

// Function get battery voltage and hence interpret charging
float getBatteryVoltage() {
  // Read millivolts (ESP32C3 internal calibration)
  uint32_t rawMV = analogReadMilliVolts(BAT_PIN);
  
  // Convert to actual battery voltage (Divider Logic)
  float batV = (rawMV * VOLTAGE_MULTIPLIER) / 1000.0;
  
  // Serial.printf("Bat: %.2f V\n", batV);
  
  return batV;
}

// Function to check battery while system is awake
void checkBatteryAwake(unsigned long now) {
  if (now - lastBatCheck < BAT_CHECK_INTERVAL) {
    return;
  }
  else {
    lastBatCheck = now;
    if (getBatteryVoltage() < LOW_BAT_THRESHOLD_V) {
      if(SERIAL_MONITOR_EN) Serial.println("⚠ Low Battery!");
      // Quick Red Flash
      digitalWrite(RLED, HIGH);
      delay(100); 
      digitalWrite(RLED, LOW);
      // Restore Yellow if we are in Locked/Listening mode
      if (STATE == 0 && currentMode == MODE_IDLE) {
         digitalWrite(YLED, HIGH);
      }
    }
  }
}