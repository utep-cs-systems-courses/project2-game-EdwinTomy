#include <msp430.h>
#include "led.h"

void led_init()
{
  P2DIR |= LEDS;            // Set LEDS to be outputs 
  P2OUT &= ~LED_GREEN;      // Turn off green LED
  P2OUT |= LED_RED;         // Turn on red LED
}

void led_off()
{
  P2OUT &= ~LED_GREEN;
  P2OUT &= ~LED_RED;
}
