#include "buzzerLED.h"
#include "hardware.h"

void LEDSuccess() {
    digitalWrite(GLED,HIGH);
    delay(1000);
    digitalWrite(GLED,LOW);
}

void LEDError() {
    digitalWrite(RLED,HIGH);
    delay(1500);
    digitalWrite(RLED,LOW);
}

void goodBeep() {
    digitalWrite(YLED,LOW);
    digitalWrite(GLED,HIGH);
    tone(BUZZER,1000,150); delay(150);
    tone(BUZZER,1500,200); delay(200);
    noTone(BUZZER);
}

void badBeep() {
    digitalWrite(YLED,LOW);
    digitalWrite(RLED,HIGH);
    tone(BUZZER,400,200); delay(200);
    tone(BUZZER,300,250); delay(250);
    noTone(BUZZER);
}
