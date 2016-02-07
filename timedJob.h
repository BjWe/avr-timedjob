/*
 * timedJob.h
 *
 * Created: 10.01.2013 23:47:02
 *  Author: Bjoern
 */ 


#ifndef TIMEDJOB_H_
#define TIMEDJOB_H_

#define TIMEDJOB_MAX_ENTRIES 16

#define TIMEDJOB_OPT_INUSE   1
#define TIMEDJOB_OPT_REMOVE  2
#define TIMEDJOB_OPT_ACTIVE  4

#define TIMEDJOB_INFINITE    0
#define TIMEDJOB_TIME_100MS  1
#define TIMEDJOB_TIME_SECOND 10

#define ENABLE_COMPA_INT   TIMSK1 |= (1<<OCIE1A)
#define DISABLE_COMPA_INT  TIMSK1 &= ~(1<<OCIE1A)

typedef void (*jobf_t)(uint8_t);

extern void timedjob_init();
extern uint8_t timedjob_add(uint8_t times, uint16_t interval100ms, uint8_t opts, jobf_t func);
extern void timedjob_start(uint8_t jobid);
extern void timedjob_stop(uint8_t jobid);
extern void timedjob_remove(uint8_t jobid);
extern void timedjob_set_interval(uint8_t jobid, uint16_t interval100ms);
extern uint8_t timedjob_running(uint8_t jobid);

typedef struct{
	uint8_t cOpts;
	uint16_t cInterval;
	uint16_t cIntervalCount;
	uint8_t cTimes;
	uint8_t cTimesCount;
	jobf_t cFunction;
} job_t;




#endif /* TIMEDJOB_H_ */