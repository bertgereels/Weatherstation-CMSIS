#include "delay.h"

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