#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init()
{
  /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
  */

  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}

void buzzer_off()
{
  buzzer_set_period(0);
}

int second_count = 0;
int i = 0;

int harry_potter_notes[14] = {617, 824, 980, 873, 824, 1234, 1100, 925, 824, 980, 873, 777, 873, 617};
int harry_potter_times[14] = {250, 375, 125, 250, 500, 250, 625, 625, 375, 125, 250, 500, 250, 625};

void playHarryPotter(){
  if(second_count >= harry_potter_times[i]){
    
    second_count = 0;
    if(i >= 14){
      i = 0;
    }
    
    buzzer_set_period(harry_potter_notes[i]);
    i++;
  }
}

            
            
            
