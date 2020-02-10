#include <Arduino.h>

void TimerOneConfig();

typedef struct LED_PIN{
  int high_pin;
  int low_pin;
};

typedef struct LED_ROW{
  LED_PIN led_pins[8];
  int row_length;
};

LED_ROW led_row[3];

void setup() {
  MCUCR |= (1 << PUD);

  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  delay(1000);
  digitalWrite(0, LOW);
  TimerOneConfig();
  LED_ROW led_row[]{
    {{{0,1},{1,0},{0,4},{4,0}},4},
    {{{2,4},{2,0},{0,2},{3,2},{2,3},{2,1},{2,1}},7},
    {{{3,4},{4,3},{1,4},{4,1},{1,3},{3,1},{0,3},{3,0}},8}
  };
}

void loop() {
  int test = led_row[0].led_pins[0].high_pin;
  test++;
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
  static volatile uint8_t row = 0;
  static volatile uint8_t pin = 0;
  count++;
  DDRB = 0;
  PORTB  |= 0b0011111;
  if (pin < led_row[row].row_length){
  }
  digitalWrite(led_row[row].led_pins[pin].high_pin,HIGH);
  digitalWrite(led_row[row].led_pins[pin].low_pin,LOW);

}
