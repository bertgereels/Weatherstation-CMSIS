#include "TimerDriver.h"
#include "LCDcontroller.h"
#include "LPC17xx.h"

void timer_init(uint8_t number,uint32_t prescale_microseconds,uint32_t initialValue){
	lcd_printf("timer_init called.");

	if(timer_isValid(number)){
		LPC_TIM_TypeDef* timer=getTimerTypeDef(number);
		lcd_printf("%i",timer);

		/*
		//Set counter
		timer->TC = initialValue;
		lcd_printf("2");
		*/

		//Set prescale counter to 0
		timer->PC = 0;
		lcd_printf("3");

		//Set prescale
		timer->PR=((SystemCoreClock / 4) / 1000000)*prescale_microseconds;
		lcd_printf("4");

		//interrupt uitzetten
		timer->MCR &= ~(0x01);
		lcd_printf("5");
	}

	lcd_printf("Executed");
}

void timer_start(uint8_t number){
	if(timer_isValid(number)){
		getTimerTypeDef(number)->TCR = 0x01;
	}
}

uint32_t timer_getValue(uint8_t number){
	if(timer_isValid(number)){
		//Return timer count
		return getTimerTypeDef(number)->TC;
	}
}

void timer_setValue(uint8_t number,uint32_t value){
	if(timer_isValid(number)){
		//set timer count
		getTimerTypeDef(number)->TC=value;
	}
}

int timer_isValid(uint8_t number){
	return (number>=0)||(number<=3);
}

LPC_TIM_TypeDef* getTimerTypeDef(uint8_t number){
	switch(number){
	        case 0:
	            return LPC_TIM0;
	        case 1:
	            return LPC_TIM1;
	        case 2:
	            return LPC_TIM2;
	        case 3:
	            return LPC_TIM3;
	    }
	    return 0;
}
