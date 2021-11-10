#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include "led.h"

int blink_count = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){      /* 250 interrupts/sec */
  blink_count++;
  if(sw1_down == 1){ //if sw1 pressed
    play_harry_potter();
  }else if(sw2_down == 1 ){ //if sw2 pressed
    play_harry_potter();
  }else if(sw3_down == 1){  
    dimLights();
  }else if(sw4_down ==1){
    buzzer_off();
    led_off();
    buzzer_set_period(0);
  }else{
    buzzer_set_period(0);
  }
}
