#include <Arduino.h>

typedef struct LED_PIN{
  int high_pin;
  int low_pin;
};

typedef struct LED_ROW{
  LED_PIN led_pins[8];
  int row_length;
};

LED_ROW led_row[1];

void setup() {
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