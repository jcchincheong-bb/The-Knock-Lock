#include "hmi.h"

// -------------------------------------------------------------
// FEEDBACK & SERVO
// -------------------------------------------------------------
// Function to easily control the leds
void led_ryg(int rState, int yState, int gState) {
  digitalWrite(RLED, rState);
  digitalWrite(YLED, yState);
  digitalWrite(GLED, gState);
}

// Function to flash green LED
void flashGreenTick() {
  bool yellowWasOn = digitalRead(YLED);
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, HIGH);
  delay(50);
  digitalWrite(GLED, LOW);
  if(yellowWasOn) digitalWrite(YLED, HIGH);
}

// Function to notify in case of correct pattern
void goodBeep() {
  // Sound a good beep
  tone(BUZZER, 1000, 150);
  delay(150);
  tone(BUZZER, 1500, 200);
  delay(200);
  noTone(BUZZER);
  // Also show an LED response - green
  led_ryg(0,0,1);
  delay(500);
  led_ryg(0,0,0);
}


// Function to notify in case of incorrect pattern
void badBeep() {
  // Sound a bad beep
  led_ryg(1, 0, 0);
  tone(BUZZER, 400, 200);
  delay(200);
  tone(BUZZER, 300, 250);
  delay(250);
  noTone(BUZZER);
  // Also show an LED response - red
  led_ryg(0, 1, 0);
}

// Function to validate a successful save
void successSave() {
  if(SERIAL_MONITOR_EN) Serial.println("✅ Recording Saved.");
  // Show an LED response - flash green 2 times
  led_ryg(0,0,0);
  for(int i=0; i<2; i++){
    led_ryg(0,0,1);
    delay(200);
    led_ryg(0,0,0);
    delay(200);
  }
}

// Function to play the recorded pattern back for validation
void playbackPattern() {
  // This acts as a form of verification that the pattern you intenteded was saved
  if(SERIAL_MONITOR_EN) Serial.println("🔊 Playing back pattern...");
  for (int i = 0; i < knockCount - 1; i++) { // Go through the currently recorded pattern
    tone(BUZZER, 2000);
    delay(50);
    noTone(BUZZER);
    led_ryg(0, 1, 0);
    delay(intervals[i]); // Choose delay depending on position
    led_ryg(0, 0, 0);
  }
  tone(BUZZER, 2000);
  delay(50);
  noTone(BUZZER);
}

// Function to unlock the box
void unlockBox() {
  if (STATE == 1) return; // If the box is already unlocked, go back, not usually used, but helps with efficiency if called on accident, saves battery
  if (SERIAL_MONITOR_EN) Serial.println("🔓 Unlocking...");
  lockServo.write(0);
  delay(1000);
  led_ryg(0,0,1);  // Turn green LED on to show box unlocked
  STATE = 1;    // Set state to unlock 
  knockCount = 0; // Reset the knock count
}

// Function to lock the box
void lockBox() {
  if(SERIAL_MONITOR_EN) Serial.println("🔒 Locking...");
  lockServo.write(180);
  delay(1000);
  STATE = 0;  // Set state back to locked
  knockCount = 0; // Reset knock count
  lastActivityTime = millis(); // Set last activity time, so that it can go back to sleep when required, unless another knock detected
}