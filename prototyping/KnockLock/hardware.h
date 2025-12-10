#ifndef HARDWARE_H
#define HARDWARE_H

// Save the pattern in the inbuilt storage
extern Preferences prefs;

// Pin declarations 
// Communication
extern const int SDA_PIN;
extern const int SCL_PIN;
//Actuator
extern const int SERVO_PIN;
//Output
extern const int BUZZER;
extern const int RLED;
extern const int YLED;
extern const int GLED;

// Objects
extern ADXL345 adxl;
extern Preferences prefs;
extern Servo lockServo;

void setupHardware();

#endif
