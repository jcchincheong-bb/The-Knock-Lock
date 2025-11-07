void setup() {
  Serial.begin(9600);  // USB side
  Serial1.begin(9600); // UART on pins 0 (RX) and 1 (TX)
}

void loop() {
  if (Serial.available()) Serial1.write(Serial.read());
  if (Serial1.available()) Serial.write(Serial1.read());
}
