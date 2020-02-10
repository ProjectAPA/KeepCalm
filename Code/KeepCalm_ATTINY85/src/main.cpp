#include <Arduino.h>

void TimerOneConfig();

typedef struct LED_PINS{
  int high_pin;
  int low_pin;
  int status;
};

 LED_PINS led_pins[19]{
    {0,1,0},{1,0,0},{0,4,0},{4,0,0},
    {2,4,0},{2,0,0},{0,2,0},{3,2,0},{2,3,0},{2,1,0},{2,1,0},
    {3,4,0},{4,3,0},{1,4,0},{4,1,0},{1,3,0},{3,1,0},{0,3,0},{3,0,0}
  };

void setup() {
  MCUCR |= (1 << PUD);
  TimerOneConfig();

  led_pins[0].status = 1;
  led_pins[1].status = 1;
}

void loop() {
}

void TimerOneConfig(){
  cli();
  TCCR1 = 0;
  TIMSK = 0;

  TCCR1 |= (1 << CTC1);

  TCCR1 |= (1 << CS12);
  TCCR1 |= (1 << CS11);

  OCR1A = 60;
  OCR1C = 60;

  TIMSK |= (1 << OCIE1A);
  sei();
}

ISR (TIM1_COMPA_vect){
  static volatile uint8_t count = 0;
  count++;
  if (count == 20){
    count = 0;
  }
  DDRB = 0;
  PORTB = 0;
  //led_pins[count].status
  if (led_pins[count].status == 1){
    pinMode(led_pins[count].high_pin, OUTPUT);
    pinMode(led_pins[count].low_pin, OUTPUT);
    digitalWrite(led_pins[count].high_pin,HIGH);
    digitalWrite(led_pins[count].low_pin,LOW);
  }
}
