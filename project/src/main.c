//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

int main(void) {
  led_init();
  switch_init();
  buzzer_init();
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}


// LED dimming
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

// Buzz singing 
int second_count = 0;
int i = 0;

int harry_potter_notes[14] = {617, 824, 980, 873, 824, 1234, 1100, 925, 824, 980, 873, 777, 873, 617};
int harry_potter_times[14] = {250, 375, 125, 250, 500, 250, 625, 625, 375, 125, 250, 500, 250, 625};

void play_harry_potter(){
  if(second_count >= harry_potter_times[i]){
    
    second_count = 0;
    if(i >= 14){
      i = 0;
    }
    
    buzzer_set_period(harry_potter_notes[i]);
    i++;
  }
}

// Interrupt Handler
void
__interrupt_vec(WDT_VECTOR) WDT(){      /* 250 interrupts/sec */
  blink_count++;
  if(sw1_down == 1){ //if sw1 pressed
    play_harry_potter();
    
  } else if(sw2_down == 1){ //if sw2 pressed
    play_harry_potter();
    
  } else if(sw3_down == 1){  
    dimLights();
    
  } else if(sw4_down == 1){
    buzzer_off();
    led_off();
    buzzer_set_period(0);
    
  } else {
    buzzer_set_period(0);
  }
}

