#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>       // Needed for Serial, digitalWrite, delay, HIGH/LOW
#include <Wire.h>
#include <Preferences.h>
#include <ESP32Servo.h>
#include <SparkFun_ADXL345.h>

extern Preferences prefs;

// Pins
extern const int SDA_PIN;
extern const int SCL_PIN;
extern const int SERVO_PIN;
extern const int BUZZER;
extern const int RLED;
extern const int YLED;
extern const int GLED;
extern const int BUTTON_PIN;

// Objects
extern ADXL345 adxl;
extern Preferences prefs;
extern Servo lockServo;

// Functions
void setupHardware();

#endif
