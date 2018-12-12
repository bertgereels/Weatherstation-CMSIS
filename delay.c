/******************************************************
* Delay driver c code file						 	  *
*                                                     *
* Author:  Bert Gereels                               *
*          Klaas Govaerts                             *
*          										      *
******************************************************/

#include "delay.h"

void wait_s(int s){
    wait_ms(s * 1000); //1s = 1000ms
}


void wait_ms(int ms){
    wait_us(ms * 1000); //1ms = 1000µs
}

void wait_us(int us){
    //Timer standaard op systeemcoreclock/4 = 24MHz
    //Reset de timer
    LPC_TIM0->TCR = 0x02;

    //Prescalar op 24 -> (SystemCoreClock/4)/1000000 = 24
    LPC_TIM0->PR = (SystemCoreClock / 4) / 1000000;

    //Instellen van
    LPC_TIM0->MR0 = us; // match count for 1us * microseconds

    //Start de timer 0
    LPC_TIM0->TCR = 0x01;

    //Stop TC wanneer gematched
    LPC_TIM0->MCR |= 0x02;

    //Clear TC wanneer match
    LPC_TIM0->MCR |= 0x04;

    //interrupt uitzetten
    LPC_TIM0->MCR &= ~(0x01);

    //Wacht tot de timer gestopt is
    while (LPC_TIM0->TCR & 0x01){}
}

/*
void timer_start(uint8_t number){
	if(timer_isValid(number)){
		LPC_TIM_TypeDef* timer=getTimerTypeDef(number);

		//Timer standaard op systeemcoreclock/4 = 24MHz
		//Reset de timer
		timer->TCR = 0x02;

		//Prescalar op 24 -> (SystemCoreClock/4)/1000000 = 24
		timer->PR = (SystemCoreClock / 4) / 1000000;

		//Start de timer
		timer->TCR = 0x01;

		//interrupt uitzetten
		timer->MCR &= ~(0x01);
	}
}*/

void timer_init(uint8_t number,uint32_t prescale_microseconds,uint32_t initialValue){
	if(timer_isValid(number)){
		LPC_TIM_TypeDef* timer=getTimerTypeDef(number);

		//Set counter
		timer->TC = initialValue;

		//Set prescale counter to 0
		timer->PC = 0;

		//Set prescale
		timer->PR=((SystemCoreClock / 4) / 1000000)*prescale_microseconds;

		//interrupt uitzetten
		timer->MCR &= ~(0x01);
	}
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

timer_isValid(uint8_t number){
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
