#include <msp430.h>
#include "led.h"
#include "buzzer.h"

int sw1Down = 0;
int sw2Down = 0;
int sw3Down = 0;
int sw4Down = 0;

int currSecond = 0
int harryPotterNotes[14] = {617, 824, 980, 873, 824, 1234, 1100, 925, 824, 980, 873, 777, 873, 617};
int harryPotterTimes[14] = {2, 3, 1, 2, 4, 2, 5, 5, 3, 1, 2, 4, 2, 5};
int harryPotterLen = 14;
int i = 0

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
  
  if((p2val & SWITCHES) == 14){
    sw1Down ^= 1;
    buzzer_init();
  //toggle sw2 on or off
  } else {
    buzzer_set_period(0);
  }
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
  
  secondCount++;
  
  if(sw1Down == 1){ 
    playHarryPotter();
   
  } else if(sw2Down == 1){ 
    playShinjeki();
    
  } else {
    buzzer_set_period(0);
  }
  
} 

void playHarryPotter()
{
  if(currSecond >= harryPotterTimes[i]){
    currSecond = 0;
    if(i >= 26){
      i = 0;
    }
    buzzer_set_period(harryPotterNotes[i]);
    i++;
  }
}

void playShinjeki()
{
  //
}



