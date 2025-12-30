#include "hardware.h"

// --- Pin Definitions ---
// Assigning the specific GPIO numbers for the ESP32-C3
const int SDA_PIN       = 6;
const int SCL_PIN       = 5;
const int WAKE_INT      = 4;

const int SERVO_EN      = 0;
const int SERVO_CONTROL = 1;

const int BUZZER        = 10;
const int RLED          = 3;
const int YLED          = 19;
const int GLED          = 18;
const int BUTTON_PIN    = 7;
const int BAT_PIN       = 2; 

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

  // Test servo motor
  // digitalWrite(SERVO_EN, HIGH);
  // lockServo.write(0); 
  // delay(500);
  // digitalWrite(SERVO_EN, LOW);
}

//Function to setup the ADXL sensor with interrupts and sensitivity
void ADXLsetup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  adxl.powerOn();
  adxl.setRangeSetting(SENSITIVITY);
  adxl.setTapDetectionOnXYZ(ADXL_EN_X, ADXL_EN_Y, ADXL_EN_Z);
  adxl.setTapThreshold(TAP_THRESHOLD);
  adxl.setTapDuration(TAP_DURATION);
  adxl.setDoubleTapLatency(DOUBLE_TAP_LATENCY);
  adxl.setDoubleTapWindow(DOUBLE_TAP_WINDOW);

  adxl.doubleTapINT(0);
  adxl.singleTapINT(0);
  adxl.FreeFallINT(0);
  adxl.ActivityINT(0);
  adxl.InactivityINT(0);
  adxl.getInterruptSource();
}

void IRAM_ATTR onRecordButton() {
  recordButtonPressed = true;
}