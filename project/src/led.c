#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init()
{
  P1DIR |= LEDS; 
  led_update();
}

void led_update()
{
  P1OUT &= ~LEDS;
}

void turnRed(int state)
{
  switch(state){
  case 0:
    P1OUT &= ~LED_RED;
    break;
  case 1:
    P1OUT |= LED_RED;
    break;
  default:
    P1OUT |= LEDS;
    break;
  }
}

void turnGreen(int state)
{
  switch(state){
  case 0:
    P1OUT &= ~LED_GREEN;
    break;
  case 1:
    P1OUT |= LED_GREEN;
    break;
  default:
    P1OUT |= LEDS;
    break;
  }
}
