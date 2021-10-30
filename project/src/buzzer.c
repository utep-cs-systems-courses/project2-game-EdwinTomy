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

// Function that utilizes the buzzer to play the happy birthday song.
void play_harry_potter(int sec_cnt)
{
  sec_cnt++;
  
  if(sec_cnt <= 0){
    buzzer_set_period(0);
    
  } else if(sec_cnt <= 500/2){
    buzzer_set_period(617);
    
  } else if(sec_cnt <= 1250/2){
    buzzer_set_period(824);
    
  } else if(sec_cnt <= 1500/2){
    buzzer_set_period(980);
    
  } else if(sec_cnt <= 2000/2){
    buzzer_set_period(873);
    
  } else if(sec_cnt <= 3000/2){
    buzzer_set_period(824);
    
  } else if(sec_cnt <= 3500/2){
    buzzer_set_period(1234);
    
  } else if(sec_cnt <= 4750/2){
    buzzer_set_period(1100);
    
  } else if(sec_cnt <= 6000/2){
    buzzer_set_period(925);
    
  } else if(sec_cnt <= 4750/2){
    buzzer_set_period(1100);
    
  } else if(sec_cnt <= 6750/2){
    buzzer_set_period(824);
    
  } else if(sec_cnt <= 7000/2){
    buzzer_set_period(980);
    
  } else if(sec_cnt <= 7500/2){
    buzzer_set_period(873);
    
  } else if(sec_cnt <= 8500/2){
    buzzer_set_period(777);
    
  } else if(sec_cnt <= 9000/2){
    buzzer_set_period(873);
    
  } else if(sec_cnt <= 10250/2){
    buzzer_set_period(617);
 
  } else {
    buzzer_set_period(0);
    
  } 
            
            
            
}
