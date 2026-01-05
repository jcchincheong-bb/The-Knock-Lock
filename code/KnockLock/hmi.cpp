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
  tone(BUZZER, 1000, 150);
  delay(150);
  tone(BUZZER, 1500, 200);
  delay(200);
  noTone(BUZZER);
}


// Function to notify in case of incorrect pattern
void badBeep() {
  led_ryg(1, 0, 0);
  tone(BUZZER, 400, 200);
  delay(200);
  tone(BUZZER, 300, 250);
  delay(250);
  noTone(BUZZER);
  led_ryg(0, 1, 0);
}

// Function to validate a successful save
void successSave() {
  if(SERIAL_MONITOR_EN) Serial.println("✅ Recording Saved.");
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
  if(SERIAL_MONITOR_EN) Serial.println("🔊 Playing back pattern...");
  for (int i = 0; i < knockCount - 1; i++) {
    tone(BUZZER, 2000);
    delay(50);
    noTone(BUZZER);
    led_ryg(0, 1, 0);
    delay(intervals[i]);
    led_ryg(0, 0, 0);
  }
  tone(BUZZER, 2000);
  delay(50);
  noTone(BUZZER);
}

// Function to unlock the box
void unlockBox() {
  if (STATE == 1) return;
  if(SERIAL_MONITOR_EN) Serial.println("🔓 Unlocking...");
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(180);
  delay(500);
  digitalWrite(SERVO_EN, LOW);
  led_ryg(0,0,1);
  STATE = 1; 
  knockCount = 0; 
}

// Function to lock the box
void lockBox() {
  if(SERIAL_MONITOR_EN) Serial.println("🔒 Locking...");
  digitalWrite(SERVO_EN, HIGH);
  lockServo.write(0);
  delay(500);
  digitalWrite(SERVO_EN, LOW);
  STATE = 0;
  knockCount = 0;
  lastActivityTime = millis();
}