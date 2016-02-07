

#define TIMER1_PRESCALER  0x03
#define TIMER1_COMPA_VAL  0x61A7  // 16MHZ
//#define TIMER1_COMPA_VAL 0x30D3  // 8MHZ

#include <avr/io.h>

#include "timedJob/timedJob.h"

uint8_t testJobId;

void ToggleLed(uint8_t times){
	if(times % 2)
	{
		// Your Code to turn LED on
	} else {
		// Your Code to turn LED off
	}
}

void init(){
	// Initialize
	timedjob_init();
	
	// Register job.         run infinite,      every second,         start immediately,   reference
	testJobId = timedjob_add(TIMEDJOB_INFINITE, TIMEDJOB_TIME_SECOND, TIMEDJOB_OPT_ACTIVE, &ToogleLED); 

	// Also possible
	// Register job.            run 10 times, every 5 seconds,          start immediately & remove job if finished, reference
        // testJobId = timedjob_add(10,           TIMEDJOB_TIME_SECOND * 5, TIMEDJOB_OPT_ACTIVE | TIMEDJOB_OPT_REMOVE,  &ToogleLED); 
	
	// Enable global interrupts
	sei();
}

int main(void)
{
    init();
	
    while (1) {
	/* your code */
    }
}

