#include <Arduino.h>

enum{
  RedLed = 4,
  GreenLed = 3,
  BlueLed = 2
};

struct counter_options
{
 uint16_t counter_max;
 uint16_t shifted_bits;
};

struct counter_options counter_op[] = {
  {1016,6},
  {255,8},
  {510,7},
  {2032,5},
  {4069,4}
};

void TimerTwoConfig();
uint16_t GammaCorrection(uint8_t brightness);

volatile uint16_t counter; 

uint16_t res = 1;

uint16_t BlueBrightness;
unsigned long time_now = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(BlueLed,OUTPUT);
  TimerTwoConfig();
}

void loop() {
  for (int i = 0; i < 255; i++){
    BlueBrightness = GammaCorrection(i);
    time_now = millis();
    while(millis() < time_now + 20);   
  }
  for (int i = 255; i > 0; i--){
    BlueBrightness = GammaCorrection(i);
    time_now = millis();
    while(millis() < time_now + 20);   
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
  OCR2A = 5;

  TIMSK2 |= (1 << OCIE2A);

  sei();
}
boolean toggle = false;
ISR (TIMER2_COMPA_vect){
  counter++;
  if (counter > counter_op[res].counter_max){
    counter = 0;
    // digitalWrite(BlueLed,HIGH);
    PORTD |= (1 << PORTD2);

  }
  if (counter == BlueBrightness){
    // digitalWrite(BlueLed,LOW);
    PORTD &= ~(1 << PORTD2);
  }
}

uint16_t GammaCorrection(uint8_t brightness){
  uint32_t brightness_squared = pow(brightness,2);
  return brightness_squared >> counter_op[res].shifted_bits;
}