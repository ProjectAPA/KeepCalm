#include <Arduino.h>
#include <math.h>

volatile int Dac[2];
volatile uint8_t* Port[] = { &OCR1A, &OCR1B };
volatile int Cycle = 0;

uint16_t GammaCorrection(uint8_t brightness);

// Overflow interrupt
ISR (TIMER1_OVF_vect) {
  static int rem[2];
  for (int chan=0; chan<2; chan++) {
    int remain;
    if (Cycle == 0) remain = Dac[chan]; else remain = rem[chan];
    if (remain >= 256) { *Port[chan] = 255; remain = remain - 256; }
    else { *Port[chan] = remain; remain = 0; }
    rem[chan] = remain;
  }
  Cycle = (Cycle + 1) & 0x0F;
}

void analogWrite12 (int chan, int value) {
  cli(); Dac[chan] = value; sei();
}

void setup() {
  // Timer/Counter1 doing PWM on OC1A (PB1) and OC1B (PB4)
  TCCR1 = 1<<PWM1A | 1<<COM1A0 | 1<<CS10;
  GTCCR = 1<<PWM1B | 1<<COM1B0;
  TIMSK = TIMSK | 1<<TOIE1;
  pinMode(1, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop () {
  for (int i = 0; i < 255; i++) {
    analogWrite12(0,GammaCorrection(i));
    delayMicroseconds(15686);
  } 
  for (int i = 0; i <= 125; i++) {
    // int led_sin = ((cos(i*0.1)+1)*127);
    int led_sin = ((cos(i*0.1)+1.4)*106);
    analogWrite12(0,GammaCorrection(led_sin));
    delayMicroseconds(32000);
  }   
  for (int i = 255; i >= 0; i--) {
    analogWrite12(0,GammaCorrection(i));
    delayMicroseconds(15686);
  }      
}

uint16_t GammaCorrection(uint8_t brightness){
  uint32_t brightness_squared = pow(brightness,2);
  return brightness_squared >> 4;
}