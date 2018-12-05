#include <stdio.h>
#include <stdlib.h>

#include "LPC17xx.h"
#include "I2C.h"
#include "TSL2561.h"
#include "BME680.h"
#include "SensorControl.h"
#include "TextLCD.h"
#include "StateMachine.h"

int main(void){
	currentState = INIT;
    while(1){
    	stateMachine();
    }
}

void stateMachine(void){
	switch(currentState){
	case INIT:
		setRefreshPeriod(20);
		lcd_init();
		i2c2_init();
		if(!initSensors() && i2c2_status() == 0xf8){
			printf("Everything initialized succesfully!\r\n");
			currentState = SETTIME;
		}else{
			currentState = INITFAIL;
		}
		break;
	case INITFAIL:
		lcd_setText("Initialisation  failed");
		wait_s(5);
		lcd_cls();
		lcd_setText("Initialisation  retry");
		wait_s(5);
		currentState = INIT;
		break;
	case SETPERIOD:
		currentState = SETTIME;
		break;
	case SETTIME:
		currentState = STARTTIMERS;
		break;
	case STARTTIMERS:
		currentState = READSENSORVALUES;
		break;
	case READSENSORVALUES:
		getMeasurements(&meting);
		printMeasurements(&meting);
		char temp[32] = "";
		measurementToString(temp, &meting);
		lcd_setText(temp);
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


