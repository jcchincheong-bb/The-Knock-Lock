#include "sleepMode.h"

// -------------------------------------------------------------
// SLEEP LOGIC
// -------------------------------------------------------------
// Function to put controller to sleep, with possibility to wake back up
void goToSleep() {
  led_ryg(0,0,0); // Turn off all LEDs before sleeping
  
  // Check Battery before sleeping
  float batV = getBatteryVoltage();
  bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);

  digitalWrite(SERVO_EN, LOW); // Turn servo off the save battery

  // Prepare ADXL Wakeup
  adxl.singleTapINT(0); // No need for single tap interrupt any,ore
  adxl.doubleTapINT(1); // Interrupt for double tap on, which wakes up the MCU up
  adxl.getInterruptSource(); // Clear the interrupt flags
  esp_deep_sleep_enable_gpio_wakeup(1ULL << WAKE_INT, ESP_GPIO_WAKEUP_GPIO_HIGH); // Set the GPU pin connected to interrupt as wake up

  if (lowBattery) { // If battery is to low, while sleeping set a timer to wake up and indicate battery status. When battery not low no need to set timer interrupt
    if(SERIAL_MONITOR_EN) Serial.printf("💤 Low Battery (%.2fV). Blinking and sleeping 4s...\n", batV);
    
    // Blink Red indicating "I'm sleeping but dying"
    led_ryg(1,0,0);
    delay(100);
    led_ryg(0,0,0);
    
    // Enable Timer Wakeup
    esp_sleep_enable_timer_wakeup(FLASHING_TIME * 1000000ULL); 
  } else {
    if(SERIAL_MONITOR_EN) Serial.println("💤 Good Battery. Deep Sleep (Waiting for Knock)...");
    // No timer wakeup, sleeps indefinitely until knock
  }
  esp_deep_sleep_start();
}

// Function to realize reason for wake up, and do tasks accordingly
void handleWakeup(){
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_GPIO) {
    // Woke up by ADXL Tap, that means some one wants to get in the box probably
    digitalWrite(YLED, HIGH); 
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    // Woke up due to low battery, need to indicate using battery
    if(SERIAL_MONITOR_EN) Serial.println("♻ Woke up from Low Bat Timer");
    goToSleep(); // This has the code to check battery status again and indicate led signal accordingly
  }
}