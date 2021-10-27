#include <msp430.h>
#include "led.h"
#include "buzzer.h"

ifButton1 = 0;
ifButton2 = 0;
ifButton3 = 0;
ifButton4 = 0;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  
  // Update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES);  // If switch up, sense down
  P2IES &= (p2val | ~SWITCHES);   // If switch down, sense up
  
  return p2val;
}

void switch_init()
{
  // Setup switch
  P2REN |= SWITCHES;   // Enables resistors for switches
  P2IE |= SWITCHES;   // Enable interrupts from switches
  P2OUT |= SWITCHES;   // Pull-ups for switches
  P2DIR &= ~SWITCHES;   // Set switches' bits for input
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  int prev1 = sw1Down;
  int prev2 = sw2Down;
  int prev3 = sw3Down;
  int prev4 = sw4Down;
  
  sw1Down = (p2val & SW1) ? 0 : 1;
  sw2Down = (p2val & SW2) ? 0 : 1;
  sw3Down = (p2val & SW3) ? 0 : 1;
  sw4Down = (p2val & SW4) ? 0 : 1;

  
 
}


void __interrupt_vec(PORT2_VECTOR) PORT_2()
{
  if (P2IFG & SWITCHES) {   // Did a button cause this interrupt?
    P2IFG &= ~SWITCHES;   // Clear pending sw interrupts
    switch_interrupt_handler();   // Single handler for all switches
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  static int blink_count = 0;
  
  switch (blink_count) { 
  
  case 6: 
    blink_count = 0;
    P2OUT |= LED_RED;
    break;
    
  default:
    blink_count ++;
    if (!buttonDown) P2OUT &= ~LED_RED; /* don't blink off if button is down */
  }
  
  
} 
