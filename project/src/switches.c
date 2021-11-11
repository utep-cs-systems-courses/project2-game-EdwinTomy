#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"

char sw1_down;
char sw2_down;
char sw3_down;
char sw4_down;

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}
void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
}
void turnOff(){
  sw1_down &= ~sw1_down;
  sw2_down &= ~sw2_down;
  sw3_down &= ~sw3_down;
  sw4_down &= ~sw4_down;
}
void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  if((p2val & SWITCHES) == 14){ //toggle sw1 on or off
    turnOff();
    sw1_down ^= 1;
  } else if((p2val & SWITCHES) == 13){ //toggle sw2 on or off
    turnOff();
    sw2_down ^= 1;
  } else if((p2val & SWITCHES) == 11){
    turnOff();
    sw3_down ^= 1;
  } else if((p2val & SWITCHES) == 7){
    turnOff();
    sw4_down ^= 1;
  } else {
    buzzer_set_period(0); //if no switches are active
  }
}

/* Switch on P2 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
