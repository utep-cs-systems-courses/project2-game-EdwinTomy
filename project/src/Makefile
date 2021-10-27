# makfile configuration
COMMON_OBJECTS  = main.o  # Wdinterrupthandler.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: buzzer.elf 

#additional rules for files
#led.elf: ${COMMON_OBJECTS} 
#	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a
	
buzzer.elf: ${COMMON_OBJECTS}  ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: buzzer.elf
	msp430loader.sh  $^
	


clean: rm -f *.o *.elf

buzzer.c: buzzer.h

buzzerMain.c: buzzer.h

