/*
  Knock Sensor (3.3V analog reference version)
*/

const int ledPin = 13;       // LED connected to digital pin 13
const int knockSensor = A0;  // the piezo is connected to analog pin 0
const int threshold = 50;    // lower threshold, since sensitivity increased
int sensorReading = 0;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Use external reference (3.3V connected to AREF pin)
  // analogReference(EXTERNAL);
  Serial.println("Knock sensor using 3.3V analog reference");
}

void loop() {
  sensorReading = analogRead(knockSensor);

  if (sensorReading >= threshold) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.print("Knock!  Value: ");
    Serial.println(sensorReading);
  }

  delay(50);
}
