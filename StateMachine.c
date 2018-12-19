/******************************************************
* Statemachine c code file						      *
*                                                     *
* Authors:  Bert Gereels                              *
*           Klaas Govaerts                            *
*           									      *
******************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(void){
	currentState = INIT;
    while(1){
    	stateMachine();
    }
}

void stateMachine(void){
	switch(currentState){
	case INIT:
		//setRefreshPeriod(20);
		lcd_init();
		i2c2_init();
		if(!initSensors() && i2c2_status() == 0xf8){
			printf("Everything initialized succesfully!\r\n");
			currentState = SETPERIOD;
		}else{
			currentState = INITFAIL;
		}
		break;
	case INITFAIL:
		lcd_printf("Initialisation  failed");
		wait_s(5);
		lcd_cls();
		lcd_printf("Initialisation  retry");
		wait_s(5);
		currentState = INIT;
		break;
	case SETPERIOD:
		setRefreshPeriod(gui_getValue("Seconds between"));
		currentState = SETTIME;
		break;
	case SETTIME:
		timer_init(2,1000000,gui_getValue("Enter UNIX time"));
		currentState = STARTTIMERS;
		break;
	case STARTTIMERS:
		timer_start(2);
		currentState = READSENSORVALUES;
		break;
	case READSENSORVALUES:
		getMeasurements(&meting);
		printMeasurements(&meting);
		char temp[32] = "";
		measurementToString(temp, &meting);
		lcd_printf(temp);
		currentState = IDLE;
		break;
	case IDLE:
		wait_s(refreshPeriod); //wait a second before executing another read
		currentState = READSENSORVALUES;
		break;
	}
}

void setRefreshPeriod(int sec){
	if(sec > 1){
		refreshPeriod = sec;
	}else{
		refreshPeriod = 10;
	}
}



