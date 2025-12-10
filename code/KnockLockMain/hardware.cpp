#include "hardware.h"

// Pins
const int SDA_PIN   = 4;
const int SCL_PIN   = 5;
const int SERVO_PIN = 6;
const int BUZZER    = 10;
const int RLED      = 18;
const int YLED      = 19;
const int GLED      = 3;
const int BUTTON_PIN = 7;

// Define these functions using the extern global variables
extern int knockCount;
extern unsigned long lastKnockTime;

// Objects
ADXL345 adxl;
Servo lockServo;
Preferences prefs;


// Setup function
void setupHardware() {
    Wire.begin(SDA_PIN, SCL_PIN);

    // ADXL345
    adxl.powerOn();
    adxl.setRangeSetting(2);

    // Pins
    pinMode(BUZZER, OUTPUT);
    pinMode(RLED, OUTPUT);
    pinMode(YLED, OUTPUT);
    pinMode(GLED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);

    // Servo
    ESP32PWM::allocateTimer(0);
    lockServo.setPeriodHertz(50);
    lockServo.attach(SERVO_PIN, 500, 2500);
    lockServo.write(0);

    Serial.println("Hardware initialized.");
}

// Add to hardware.cpp

void unlockBox() {
    // Moves servo to a specified unlocked position (e.g., 90 degrees)
    lockServo.write(90);
    digitalWrite(GLED, LOW);
    digitalWrite(YLED, LOW);
    Serial.println("🔐 BOX UNLOCKED!");
}

void resetPattern() {
    knockCount = 0;
    lastKnockTime = millis(); // Reset timer to now
    digitalWrite(RLED, LOW);
    Serial.println("Pattern check complete. Resetting knock count.");
    digitalWrite(YLED,HIGH); // Turn Yellow LED back on to indicate "listening"
}
