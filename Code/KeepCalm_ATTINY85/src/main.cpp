#define TIMER_TO_USE_FOR_MILLIS 0
#include <Arduino.h>
#include <avr/sleep.h>

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)

void TimerOneConfig();

typedef struct LED_PINS{
  int high_pin;
  int low_pin;
  volatile uint8_t status;
};

LED_PINS led_pins[19]{
    {0,1,0},{1,0,0},{0,4,0},{4,0,0},
    {2,4,0},{2,0,0},{0,2,0},{3,2,0},{2,3,0},{2,1,0},{1,2,0},
    {3,4,0},{4,3,0},{1,4,0},{4,1,0},{1,3,0},{3,1,0},{0,3,0},{3,0,0}
  };

int period = 1000;
unsigned long time_now = 0;

void setup() {

  adc_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  PORTB = 0;
  DDRB = 0;
  MCUCR |= (1 << PUD);

  TimerOneConfig();
  
}

void loop() {

  for (int i = 0; i < 19; i++){
    led_pins[i].status = 1;
  //  time_now = millis();
  //   while(millis() < time_now + period){
  //       //wait approx. [period] ms
  //   }
  delay(33000);
  }

  for (int i = 0; i < 19; i++){
    led_pins[i].status = 0;
  }
  cli();
  sleep_enable();
  sleep_bod_disable();
  sleep_cpu();
}

void TimerOneConfig(){
  cli();

  TCCR1 = 0;
  TIMSK = 0;

  TCCR1 |= (1 << CTC1);

  TCCR1 |= (1 << CS12);
  TCCR1 |= (1 << CS11);

  OCR1A = 20;
  OCR1C = 20;

  TIMSK |= (1 << OCIE1A);

  sei();
}

ISR (TIM1_COMPA_vect){
  static volatile uint8_t count = 0;

  PORTB = 0;
  DDRB = 0;

  if (count == 19){
    count = 0;
  }

  if (led_pins[count].status == 1){

    DDRB |= (1 << led_pins[count].high_pin);
    DDRB |= (1 << led_pins[count].low_pin);
    PORTB |= (1 << led_pins[count].high_pin);  

  }

  count++;

}
