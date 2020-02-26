#include <Arduino.h>

void TimerZeroConfig();

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

//  LED_PINS led_pins[19]{
//     {1,0,0},{0,1,0},{1,0,0},{0,1,0},{1,0,0},
//     {0,1,0},{1,0,0},{0,1,0},{1,0,0},{0,1,0},
//     {1,0,0},{0,1,0},{1,0,0},{0,1,0},{1,0,0},
//     {0,1,0},{1,0,0},{0,1,0},{1,0,0}
//   };

int period = 1000;
unsigned long time_now = 0;

void setup() {

  PORTB = 0;
  DDRB = 0;
  MCUCR |= (1 << PUD);

  TimerZeroConfig();
  
}

void loop() {

  for (int i = 0; i < 19; i++){
    led_pins[i].status = 1;
    time_now = millis();
    while(millis() < time_now + period){
        //wait approx. [period] ms
    }
  }
  
  // for (int i = 0; i < 19; i++){
  //   led_pins[i].status = 1;
  // }  
}

void TimerZeroConfig(){
  cli();

  TCCR0A = 0;

  TCCR0A |= (1 << WGM01);

  TCCR0B |= (1 << CS01);

  OCR0A  = 20;

  TIMSK |= (1 << OCIE0A);

  sei();
}

ISR (TIM0_COMPA_vect){
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
