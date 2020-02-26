#define TIMER_TO_USE_FOR_MILLIS 0
#include <Arduino.h>

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

  // led_pins[0].status = 1;
  // led_pins[1].status = 1;
  // led_pins[2].status = 1;
  // led_pins[3].status = 1;
  // led_pins[4].status = 1;
  // led_pins[5].status = 1;
  // led_pins[6].status = 1;
  // led_pins[7].status = 1;
  // led_pins[8].status = 1;
  // led_pins[9].status = 1;
  // led_pins[10].status = 1;
  // led_pins[11].status = 1;
  // led_pins[12].status = 1;
  // led_pins[13].status = 1;
  // led_pins[14].status = 1;
  // led_pins[15].status = 1;
  // led_pins[16].status = 1;
  // led_pins[17].status = 1;
  // led_pins[18].status = 1;

  TimerOneConfig();
  
}

void loop() {

  for (int i = 0; i < 19; i++){
    led_pins[i].status = 1;
    time_now = millis();
  //   while(millis() < time_now + period){
  //       //wait approx. [period] ms
  //   }
  delay(33000);
  }
  


  // for (int i = 0; i < 19; i++){
  //   led_pins[i].status = 1;
  // }  
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
