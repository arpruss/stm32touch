#define SACRIFICIAL_ANALOG_PIN PA6 // this will be grounded; make sure this doesn't cause a short-circuit

int32_t touch(int pin, int samples) {
  uint32_t total = 0;
  for (int i=0; i<samples; i++) {
    pinMode(pin, INPUT_PULLUP);
    pinMode(SACRIFICIAL_ANALOG_PIN, OUTPUT);
    digitalWrite(SACRIFICIAL_ANALOG_PIN, 0);
    delayMicroseconds(50);
    analogRead(PSACRIFICIAL_ANALOG_PIN);
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

