/******************************************************
* Delay driver header file				      		          *
*                                                     *
* Authors:  Bert Gereels                              *
*           Klaas Govaerts                            *
*           										                      *
******************************************************/

#ifndef DELAY_H_
#define DELAY_H_

#include "LPC17xx.h"

//Provide interface
	/**
	 *  Waits for x amount of seconds
	 *
	 *  @param the amount of seconds to wait
	 */
	void wait_s(int s);

	
	/**
	 *  Waits for x amount of milliseconds
	 *
	 *  @param the amount of milliseconds to wait
	 */
	void wait_ms(int ms);

	
	/**
	 *  Waits for x amount of microseconds
	 *
	 *  @param the amount of mircoseconds to wait
	 */
	void wait_us(int us);

	
	/**
	 * Initialise and start a timer, incrementing every microsecond.
	 * This function will also set the timer value to 0.
	 *
	 * @param number	The number of the timer
	 * 					(From 0 up to and including to 3)
	 * 					Be aware that timer 0 is used as wait timer.
	 */
	void timer_start(uint8_t number);

	
	/**
	 * Get the value of a specific timer.
	 *
	 * @param number	The number of the timer
	 *					(From 0 up to and including to 3)
	 * @return			The timer value stored in TC.
	 * 					(If timer number is valid.)
	 */
	uint32_t timer_getValue(uint8_t number);


//Functions used for internal operation.
	/**
	 * Check if a timer number is valid.
	 *
	 * @param number	The number of the timer (From 0 up to and including to 3)
	 * @return			True if valid timer number.
	 */
	int timer_isValid(uint8_t number);

	
	/**
	 * Returns a pointer to a LPC_TIM_TypeDef for a specific timer number.
	 *
	 * @param number	The number of the timer (From 0 up to and including to 3)
	 * @return			A pointer to the corresponding LPC_TIM_TypeDef.
	 */
	LPC_TIM_TypeDef* getTimerTypeDef(uint8_t number);

#endif
