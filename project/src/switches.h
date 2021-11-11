#ifndef switches_included
#define switches_included

#define SWS1 BIT0
#define SWS2 BIT1
#define SWS3 BIT2
#define SWS4 BIT3
#define SWITCHES (SWS1 | SWS2 | SWS3 | SWS4)

void switch_init();
void switch_interrupt_handler();

extern int sw1Down, sw2Down, sw3Down, sw4Down;
extern int oddPress1, oddPress2, oddPress3, oddPress4;

#endif
