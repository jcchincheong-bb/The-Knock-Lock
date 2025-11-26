#include "servoControl.h"
#include "hardware.h"

void unlockBox() {
    Serial.println("🔓 Unlocking...");
    lockServo.write(180);
    delay(4000);
    Serial.println("🔒 Locking...");
    lockServo.write(0);
}
