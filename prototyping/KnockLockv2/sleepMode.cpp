#include "sleepMode.h"

// -------------------------------------------------------------
// SLEEP LOGIC (With Low Bat Monitor)
// -------------------------------------------------------------
// Function to put controller to sleep, with possibility to wake back up
void goToSleep() {
  led_ryg(0,0,0);
  
  // Check Battery before sleeping
  float batV = getBatteryVoltage();
  bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);

  // Prepare ADXL Wakeup
  adxl.doubleTapINT(1);
  adxl.getInterruptSource();
  esp_deep_sleep_enable_gpio_wakeup(1ULL << WAKE_INT, ESP_GPIO_WAKEUP_GPIO_HIGH);

  if (lowBattery) {
    if(SERIAL_MONITOR_EN) Serial.printf("💤 Low Battery (%.2fV). Blinking and sleeping 4s...\n", batV);
    
    // Blink Red indicating "I'm sleeping but dying"
    digitalWrite(RLED, HIGH);
    delay(100);
    digitalWrite(RLED, LOW);
    
    // Enable Timer Wakeup (4 seconds)
    // This creates the "Blink while sleeping" loop
    esp_sleep_enable_timer_wakeup(4 * 1000000ULL); 
  } else {
    if(SERIAL_MONITOR_EN) Serial.println("💤 Good Battery. Deep Sleep (Waiting for Knock)...");
    // No timer wakeup, sleep indefinitely until knock
  }

  esp_deep_sleep_start();
}

void handleWakeup(){
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_GPIO) {
    // Woke up by ADXL Tap
    digitalWrite(YLED, HIGH); 
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    // Woke up due to low battery
    if(SERIAL_MONITOR_EN) Serial.println("♻ Woke up from Low Bat Timer");
  }
}