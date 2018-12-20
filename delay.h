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


void timer_start(uint8_t number);
uint32_t timer_getValue(uint8_t number);
timer_isValid(uint8_t number);
LPC_TIM_TypeDef* getTimerTypeDef(uint8_t number);

#endif
