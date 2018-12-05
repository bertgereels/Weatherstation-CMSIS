#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

/**
 *  All the states used in the statemachine
 */
enum State{
    INIT,
	INITFAIL,
    SETPERIOD,
    SETTIME,
    STARTTIMERS,
    READSENSORVALUES,
    IDLE
};


/**
 *  Contains the logic of the statemachine, works with the State enum
 */
void stateMachine(void);

/**
 *  Sets the time between measurements
 *
 *  @param The time between measurements in seconds
 */
void setRefreshPeriod(int sec);

Measurements meting;
enum State currentState;
int8_t refreshPeriod;
int32_t unixTime;

#endif
