#include "hardware.h"

// --- Pin Definitions ---
// Assigning the specific GPIO numbers for the ESP32-C3
// Communication
const int SDA_PIN = 6;
const int SCL_PIN = 5;
const int WAKE_INT = 4;

// Actuators
const int SERVO_EN = 0;
const int SERVO_CONTROL = 1;

// HMI
const int BUZZER = 10;
const int RLED = 3;
const int YLED = 19;
const int GLED = 18;
const int BUTTON_PIN = 7;
const int BAT_PIN = 2;

// --- Object Definitions ---
ADXL345 adxl;
Servo lockServo;
Preferences prefs;

void setupHardware() {
  // Setup pins
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Battery Pin (ADC)
  pinMode(BAT_PIN, INPUT);

  // Setup Servo motor
  ESP32PWM::allocateTimer(0);
  lockServo.setPeriodHertz(50);
  lockServo.attach(SERVO_CONTROL, 500, 2500);
  pinMode(SERVO_EN, OUTPUT);

  // Enable interrupt on button pin
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onRecordButton, FALLING);

  // Enable interrupt on ADXL Pin
  attachInterrupt(digitalPinToInterrupt(WAKE_INT), onTap, RISING);

  // Test servo motor
  // digitalWrite(SERVO_EN, HIGH);
  // lockServo.write(0);
  // delay(500);
  // digitalWrite(SERVO_EN, LOW);
}

//Function to setup the ADXL sensor with interrupts and sensitivity
void ADXLsetup() {
  Wire.begin(SDA_PIN, SCL_PIN);                                // Start communication via i2c
  adxl.powerOn();                                              // Power the ADXL345 on
  adxl.setRangeSetting(SENSITIVITY);                           // Set up the sensitivity, from config.h
  adxl.setTapDetectionOnXYZ(ADXL_EN_X, ADXL_EN_Y, ADXL_EN_Z);  // Enable individual acceleration sensor
  adxl.setTapThreshold(TAP_THRESHOLD);                         // Set minimum threshold for detecting wakeup
  adxl.setTapDuration(TAP_DURATION);                           // Minimum duration for detecting a wake up
  adxl.setDoubleTapLatency(DOUBLE_TAP_LATENCY);                // Minimum duration between the second tap and first tap
  adxl.setDoubleTapWindow(DOUBLE_TAP_WINDOW);                  // Maximum duration to wait for the second tap
  adxl.singleTapINT(1);                                        // Enable single tap interrupt

  // Disable all other interrupts, until required
  adxl.doubleTapINT(0);
  adxl.FreeFallINT(0);
  adxl.ActivityINT(0);
  adxl.InactivityINT(0);
  adxl.getInterruptSource();  // Reset all interrupt flags
}

void IRAM_ATTR onRecordButton() {
  recordButtonPressed = true;  // Keep the ISR short for better functioning, the actual tasks is done in KnockLock.ino in main loop
}

void IRAM_ATTR onTap() {
  knockDetected = true;  // Enable flag to show knock detected
}
