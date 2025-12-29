#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include <Wire.h>
#include <Preferences.h>
#include <ESP32Servo.h>
#include <SparkFun_ADXL345.h>
#include "config.h"
#include "globalVariables.h"

// --- Pin Declarations ---

// For communication (i2c))
extern const int SDA_PIN;
extern const int SCL_PIN;
// For wake up from ADXL to MCU
extern const int WAKE_INT;

// For servo control - actuator
extern const int SERVO_EN;
extern const int SERVO_CONTROL;

// For HMI - Outputs
extern const int BUZZER;
extern const int RLED;
extern const int YLED;
extern const int GLED;
// For HMI - Inputs
extern const int BUTTON_PIN;

// For battery
extern const int BAT_PIN;

// --- Shared Hardware Objects ---
extern ADXL345 adxl;
extern Servo lockServo;
extern Preferences prefs;

// --- Function Prototypes ---
void setupHardware();
void ADXLsetup();
void IRAM_ATTR onRecordButton();

#endif