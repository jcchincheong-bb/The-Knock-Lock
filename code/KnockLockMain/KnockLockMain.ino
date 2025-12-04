void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupHardware();
  patternLength = loadPatternFromNVS(targetPattern);
  digitalWrite(YLED,HIGH);
  Serial.println("System Ready.");
}

void loop() {
  // put your main code here, to run repeatedly:
  int x, y, z;
  adxl.readAccel(&x, &y, &z);

  float aMag = sqrt(
      sq(x * 0.0039) +
      sq(y * 0.0039) +
      sq(z * 0.0039)
  );

  float aDynamic = abs(aMag - 1.0);
  unsigned long now = millis();

  if (aDynamic > KNOCK_THRESHOLD) {
    if (now - lastKnockTime > 100) {
      knockTimes[knockCount++] = now;
      lastKnockTime = now;
      Serial.printf("Knock #%d detected.\n", knockCount);
    }
  }
  // Timeout detect → check pattern
  if ((now - lastKnockTime > PATTERN_TIMEOUT) && knockCount > 1) {
    checkPattern();
    resetPattern();
  }
  delay(10);
}
