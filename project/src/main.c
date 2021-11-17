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
int blink_count = 0;

// LED dimming
int dim_count = 0;
int dim_state = 1;
int curr_state = 0;
int main_state = 0;

void dim_lights(){
  P1OUT &= ~LED_RED; //turn off red led
  dim_count++;

  if(dim_count % 250 == 0){
    main_state ^= 1; 
  }

  if(dim_count >= 500){
    dim_state = (dim_state + 1) % 5;
    dim_count = 0;
  }

  //if(main_state == 0){
  //P1OUT &= ~LED_GREEN;
  //return;
  
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
    P1OUT &= ~LED_GREEN; //turn off green led
    break;
  case 3:
    P1OUT |= LED_GREEN; //turn on green led
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
    P1OUT |= LED_GREEN; //turn on green led
    break;
  default:
    break;
  }
}
void dim100(){
  P1OUT |= LED_GREEN;
}

// Buzz singing 
int i = 0;
int song_count = 0;

int harry_potter_notes[14] = {617, 824, 980, 873, 824, 1234, 1100, 925, 824, 980, 873, 777, 873, 617};
int harry_potter_times[14] = {250, 375, 125, 250, 500, 250, 625, 625, 375, 125, 250, 500, 250, 625};

void play_harry_potter(){
  if(song_count >= harry_potter_times[i]){

    song_count = 0;
    i++;
    if(i >= 14){
      i = 0;
    }

    buzzer_set_period(harry_potter_notes[i]);
  }
  song_count++;
}

// Interrupt Handler
void 
__interrupt_vec(WDT_VECTOR) WDT(){      /* 250 interrupts/sec */
  if(sw1_down == 1){ //if sw1 pressed
    buzzer_set_period(0);
    blink_count++;
    blink_count %= 125;
    switching();

  } else if(sw2_down == 1){ //if sw2 pressed
    led_off();
    play_harry_potter();
    
  } else if(sw3_down == 1){  
    buzzer_set_period(0);
    dim_lights();
    
  } else if(sw4_down == 1){
    buzzer_off();
    led_off();
    buzzer_set_period(0);
    
  } else{
    buzzer_off();
    led_off();
    buzzer_set_period(0);
  } 
}
