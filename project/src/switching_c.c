#include <msp430.h>
#include "led.h"

extern int blink_count;

void switching(){
  
  if(blink_count <= 125){
    P1OUT ^= LED_GREEN;
  }
  
  if(blink_count <= 62){
    P1OUT ^= LED_RED;
  }
  
}
