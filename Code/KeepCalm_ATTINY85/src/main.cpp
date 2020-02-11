#include <Arduino.h>

void TimerOneConfig();

typedef struct LED_PINS{
  int high_pin;
  int low_pin;
  int status;
};

//  LED_PINS led_pins[19]{
//     {0,1,0},{1,0,0},{0,4,0},{4,0,0},
//     {2,4,0},{2,0,0},{0,2,0},{3,2,0},{2,3,0},{2,1,0},{2,1,0},
//     {3,4,0},{4,3,0},{1,4,0},{4,1,0},{1,3,0},{3,1,0},{0,3,0},{3,0,0}
//   };

 LED_PINS led_pins[19]{
    {1,0,0},{0,1,0},{1,0,0},{0,1,0},{1,0,0},
    {0,1,0},{1,0,0},{0,1,0},{1,0,0},{0,1,0},
    {1,0,0},{0,1,0},{1,0,0},{0,1,0},{1,0,0},
    {0,1,0},{1,0,0},{0,1,0},{1,0,0}
  };


void setup() {
  MCUCR |= (1 << PUD);
  led_pins[0].status = 1;
  led_pins[1].status = 1;
  led_pins[2].status = 1;
  led_pins[3].status = 1;
  led_pins[4].status = 1;
  led_pins[5].status = 1;
  led_pins[6].status = 1;
  led_pins[7].status = 1;
  led_pins[8].status = 1;
  led_pins[9].status = 1;
  led_pins[10].status = 1;
  led_pins[11].status = 1;
  led_pins[12].status = 1;
  led_pins[13].status = 1;
  led_pins[14].status = 1;
  led_pins[15].status = 1;
  led_pins[16].status = 1;
  led_pins[17].status = 1;
  led_pins[18].status = 1;
  led_pins[19].status = 1;
  TimerOneConfig();
}

void loop() {
  uint16_t old_time = 0;

  // for (int i = 0; i < 19; i++){

  //   old_time = millis();
  //   led_pins[i].status = 1; 

  //   if ((millis() - old_time) <= 1000);

  // }

  // for (int i = 0; i < 19; i++){
  //   led_pins[i].status = 1; 
  //   delay(10000);
  // }

  // for (int i = 0; i < 19; i++){
  //   led_pins[i].status = 0; 
  // }

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

  PORTB = 0;
  DDRB = 0;

  if (count == 19){
    count = 0;
  }

  if (led_pins[count].status == 1){

    DDRB |= (1 << led_pins[count].high_pin);
    PORTB |= (1 << led_pins[count].high_pin);  
    DDRB |= (1 << led_pins[count].low_pin);

  }

  count++;

}
