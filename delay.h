#ifndef DELAY_H_
#define DELAY_H_

#include "LPC17xx.h"

void wait_s(int s);
void wait_ms(int ms);
void wait_us(int us);

void timer_init(uint8_t number,uint32_t prescale_microseconds,uint32_t initialValue);
void timer_start(uint8_t number);
uint32_t timer_getValue(uint8_t number);
void timer_setValue(uint8_t number,uint32_t value);
timer_isValid(uint8_t number);
LPC_TIM_TypeDef* getTimerTypeDef(uint8_t number);

#endif
