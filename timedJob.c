/*
 * timedjob.c
 *
 * Created: 10.01.2013 23:19:13
 *  Author: Bjoern
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Global.h"
#include "timedjob.h"

static job_t timedjoblist[TIMEDJOB_MAX_ENTRIES];

void timedjob_init(void)
{
	
	//OCR1AH = (uint8_t) TIMER1_COMPA_VAL >> 8;
	//OCR1AL = (uint8_t) TIMER1_COMPA_VAL;
	
	OCR1A = TIMER1_COMPA_VAL;
	
	TCCR1A = 0;
	TCCR1B = TIMER1_PRESCALER;
	
	for(uint8_t i = 0; i < TIMEDJOB_MAX_ENTRIES; i++)
	{
		timedjoblist[i].cOpts = 0;
	}
	
	ENABLE_COMPA_INT;
}

uint8_t timedjob_running(uint8_t jobid){
	if((timedjoblist[jobid].cOpts & (TIMEDJOB_OPT_INUSE | TIMEDJOB_OPT_ACTIVE)) == (TIMEDJOB_OPT_INUSE | TIMEDJOB_OPT_ACTIVE)){
		return 1;
	}
	return 0;
}

uint8_t timedjob_add(uint8_t times, uint16_t interval100ms, uint8_t opts, jobf_t func)
{
	for(uint8_t i = 0; i < TIMEDJOB_MAX_ENTRIES; i++)
	{
		if(~timedjoblist[i].cOpts & TIMEDJOB_OPT_INUSE)
		{
			timedjoblist[i].cOpts = TIMEDJOB_OPT_INUSE | opts;
			timedjoblist[i].cTimes = times;
			timedjoblist[i].cTimesCount = 0;
			timedjoblist[i].cInterval = interval100ms;
			timedjoblist[i].cIntervalCount = 0;
			timedjoblist[i].cFunction = func;
			
			return i;
		}
	}
	
	return 0xFF;
}

void timedjob_start(uint8_t jobid)
{
	timedjoblist[jobid].cOpts |= TIMEDJOB_OPT_ACTIVE;
}

void timedjob_stop(uint8_t jobid)
{
	timedjoblist[jobid].cOpts &= ~TIMEDJOB_OPT_ACTIVE;
}

void timedjob_remove(uint8_t jobid)
{
	if(jobid > TIMEDJOB_MAX_ENTRIES)
	  return;
	  
	timedjoblist[jobid].cOpts &= ~TIMEDJOB_OPT_INUSE;
}

void timedjob_set_interval(uint8_t jobid, uint16_t interval100ms)
{
	timedjoblist[jobid].cInterval = interval100ms;
}

ISR(TIMER1_COMPA_vect, ISR_NOBLOCK)
{
	DISABLE_COMPA_INT;
	TCNT1H = 0;
	TCNT1L = 0;

	for(uint8_t i = 0; i < TIMEDJOB_MAX_ENTRIES; i++)
	{
		if(timedjob_running(i))
		{
			timedjoblist[i].cIntervalCount++;
			if(timedjoblist[i].cIntervalCount == timedjoblist[i].cInterval)
			{
				timedjoblist[i].cIntervalCount = 0;
				timedjoblist[i].cTimesCount++;
				if((timedjoblist[i].cTimesCount == timedjoblist[i].cTimes) && (timedjoblist[i].cTimes > 0))
				{
					if(timedjoblist[i].cOpts & TIMEDJOB_OPT_REMOVE)
						timedjoblist[i].cOpts &= ~TIMEDJOB_OPT_INUSE;
					else
						timedjoblist[i].cOpts &= ~TIMEDJOB_OPT_ACTIVE;
				}
				timedjoblist[i].cFunction(timedjoblist[i].cTimesCount);
			}
		}
	}
	ENABLE_COMPA_INT;
}