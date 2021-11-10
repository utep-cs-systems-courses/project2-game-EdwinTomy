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

int blink_count = 0;
int dim_state = 1;
int curr_state = 0;

void dimLights(){
  blink_count++;
  
  if(blink_count >= 500){
    dim_state = (dim_state + 1) % 5;
    blink_count = 0;
  }
  
  curr_state = (curr_state + 1) % 4;
  switch(dim_state){
    case 0: led_off; break;
    case 1: dim25(curr_state); break;
    case 2: dim50(curr_state); break;
    case 3: dim75(curr_state); break;
    case 4: dim100(); break;
    default: break;
  }
}

void dim25(int state){
  switch(state){
  case 0:
  case 1:
  case 2:
    P1OUT &= ~LED_GREEN; //turn off led_green
    break;
  case 3:
    P1OUT |= LED_GREEN; //turn on led_green
    break;
  default:
    break;
  }
  
}

void dim50(int state){
  switch(state){
  case 0:
  case 1:
    P1OUT &= ~LED_GREEN;
    break;
  case 2:
  case 3:
    P1OUT |= LED_GREEN;
  default:
    break;
  }
}
void dim75(int state){
  switch(state){
  case 0:
    P1OUT &= ~LED_GREEN;
    break;
  case 1:
  case 2:
  case 3:
    P1OUT |= LED_GREEN; //turn on led_green
    break;
  default:
    break;
  }
}

void dim100(){
  P1OUT |= LED_GREEN;
}
