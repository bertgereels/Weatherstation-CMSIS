#include <stdio.h>
#include <stdlib.h>

#include "LPC17xx.h"
#include "I2C.h"
#include "TSL2561.h"
#include "BME680.h"
#include "SensorControl.h"
#include "LCDcontroller.h"
#include "StateMachine.h"
#include "delay.h"
#include "TimerController.h"
#include "GUIcontrol.h"

int main(void){
	/*
	timer_start(1);
	while(1){
		lcd_printf("%i",timer_getValue(1));
		wait_s(1);
	}*/
	//gui_getValue("Seconds between");
	//gui_getValue("Enter UNIX time");
	/*
	currentState = INIT;
    while(1){
    	stateMachine();
    }*/
	/*
	timer_init(1,1000000,1000);
	//timer_setValue(1,1000);
	timer_start(1);
	lcd_printf("%i",timer_getValue(1));
	wait_s(5);
	lcd_printf("%i",timer_getValue(1));
	wait_s(5);
	lcd_printf("%i",timer_getValue(1));
	*/
	lcd_printf("Begin");//
	//unixTimer_init(1000);
	timer_init(2,1000000,1000);
	lcd_printf("Initialised");
	unixTimer_start();
	lcd_printf("Started");
	lcd_printf("%i",unixTimer_getValue());
	wait_s(5);
	lcd_printf("%i",unixTimer_getValue());
}

void stateMachine(void){
	switch(currentState){
	case INIT:
		//setRefreshPeriod(20);
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
		lcd_printf("Initialisation  retry");
		wait_s(5);
		currentState = INIT;
		break;
	case SETPERIOD:
		setRefreshPeriod(gui_getValue("Seconds between"));
		currentState = SETTIME;
		break;
	case SETTIME:
		unixTimer_init(gui_getValue("Enter UNIX time"));
		currentState = STARTTIMERS;
		break;
	case STARTTIMERS:
		unixTimer_start(2);
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



