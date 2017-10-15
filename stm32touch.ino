#define TOUCH_DELAY_MICROSECONDS 20

#if defined(ARDUINO_GENERIC_STM32F103C) 
// It looks like channel 15, which on some MCUs goes to PC5, is permanently grounded.
// Using it to ground the ADC saves us an analog pin.
# define GROUNDED_ADC_DEVICE    ADC1
# define GROUNDED_ADC_CHANNEL   15
#else
# define SACRIFICIAL_ANALOG_PIN PA0 // this will be grounded; make sure this doesn't cause a short-circuit
#endif

int32_t touch(int pin, int samples) {
  int32_t total = 0;
  for (int i=0; i<samples; i++) {
    pinMode(pin, INPUT_PULLUP);
#ifdef SACRIFICIAL_ANALOG_PIN    
    pinMode(SACRIFICIAL_ANALOG_PIN, OUTPUT);
    digitalWrite(SACRIFICIAL_ANALOG_PIN, 0);
    delayMicroseconds(TOUCH_DELAY_MICROSECONDS);
    analogRead(SACRIFICIAL_ANALOG_PIN);
#else
    delayMicroseconds(TOUCH_DELAY_MICROSECONDS);
    adc_read(GROUNDED_ADC_DEVICE, GROUNDED_ADC_CHANNEL);
#endif
    pinMode(pin, INPUT_ANALOG);
    total += analogRead(pin);
  }
  return total/4/samples;
}

int32_t reference;

void setup() {
  delay(2000);
  reference = touch(PB1, 500);  
  Serial.println("Reference "+String(reference));
}

void loop() {
  Serial.println(String(touch(PB1, 10)-reference));
  delay(50);
}

