#include <Arduino.h>

enum{
  RedLed = 4,
  GreenLed = 3,
  BlueLed = 2
};

void TimerTwoConfig();
uint16_t GammaCorrection(uint8_t brightness);

uint16_t counter; 
uint16_t BlueBrightness;
unsigned long time_now = 0;

void setup() {
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(BlueLed,OUTPUT);
  TimerTwoConfig();
}

void loop() {
  for (int i = 0; i < 256; i++){
    BlueBrightness = GammaCorrection(i);
    time_now = millis();
    while(millis() < time_now + 10);   
  }
  for (int i = 255; i > 0; i--){
    BlueBrightness = GammaCorrection(i);
    time_now = millis();
    while(millis() < time_now + 10);   
  }  
}

void TimerTwoConfig(){
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  
  TCCR2A |= (1 << WGM21);

  TCCR2B &= ~(1 << CS20);
  TCCR2B |= (1 << CS21);
  TCCR2B &= ~(1 << CS22);
  OCR2A = 25;

  TIMSK2 |= (1 << OCIE2A);

  sei();
}

ISR (TIMER2_COMPA_vect){
  counter++;
  if (counter > 1016){
    counter = 0;
    digitalWrite(BlueLed,HIGH);
  }
  if (counter == BlueBrightness){
    digitalWrite(BlueLed,LOW);
  }

}

uint16_t GammaCorrection(uint8_t brightness){
  uint16_t brightness_squared = pow(brightness,2);
  return brightness_squared >> 6;
}