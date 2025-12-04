#include "hardware.h"
#include "knockRecorder.h"
#include "knockPattern.h"
#include "servoControl.h"
#include "buzzerLED.h"

unsigned long knockTimes[30];
unsigned long intervals[29];
int knockCount = 0;
unsigned long lastKnockTime = 0;

unsigned long targetPattern[30];
int patternLength = 0;

void setup() {
    Serial.begin(115200);
    setupHardware();
    patternLength = loadPatternFromNVS(targetPattern);
    digitalWrite(YLED,HIGH);
    Serial.println("System Ready.");
}

void loop() {
    int x,y,z;
    adxl.readAccel(&x,&y,&z);

    float aMag = sqrt(sq(x*0.0039)+sq(y*0.0039)+sq(z*0.0039));
    float aDynamic = abs(aMag-1.0);
    unsigned long now = millis();

    if (aDynamic>0.15 && now-lastKnockTime>120) {
        knockTimes[knockCount++] = now;
        lastKnockTime = now;
        Serial.printf("Knock #%d\n", knockCount);
    }

    if ((now-lastKnockTime>5000) && knockCount>1) {
        bool correct = checkKnockPattern(knockTimes, knockCount-1);
        if(correct) { 
            goodBeep(); unlockBox(); 
        }
        else {
            badBeep();
            Serial.println("Wrong pattern!");
        }
        knockCount = 0;
        lastKnockTime = 0;
    }

    if(digitalRead(BUTTON_PIN)==HIGH) {
        while(digitalRead(BUTTON_PIN)==HIGH){}
        recordPattern();
    }

    delay(10);
}
