# makfile configuration
COMMON_OBJECTS  = main.o  # Wdinterrupthandler.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: led.elf 

#additional rules for files
led.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../timerLib/libTimer.a
	
buzzer.elf: ${COMMON_OBJECTS} buzzer.o buzzerMain.o ../timerLib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^


load: led.elf buzzer.elf
	msp430loader.sh led.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

buzzer.o: buzzer.h

switches.o: switches.h led.h

main.o: led.h switches.h led.h

