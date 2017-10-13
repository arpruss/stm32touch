int32_t touch(int pin, int samples) {
  uint32_t total = 0;
  for (int i=0; i<samples; i++) {
    pinMode(pin, INPUT_PULLUP);
    pinMode(PA6, OUTPUT);
    digitalWrite(PA6, 0);
    delayMicroseconds(50);
    analogRead(PA6);
    pinMode(pin, INPUT_ANALOG);
    total += analogRead(pin);
  }
  return total/samples;
}

int32_t reference;

void setup() {
  delay(2000);
  reference = touch(PA7, 500);  
  Serial.println("Reference "+String(reference));
}

void loop() {
  Serial.println(String(touch(PA7, 10)-reference));
  delay(50);
}
