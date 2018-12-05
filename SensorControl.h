#ifndef SENSORCONTROL_H_
#define SENSORCONTROL_H_

#include "LPC17xx.h"
#include "BME680.h"
#include "TSL2561.h"
#include "delay.h"
#include <string.h>
#include <math.h>

typedef struct{
	int time;
	uint32_t humidity;
	uint32_t pressure;
	uint32_t temperature;
	float lightlevel;
}Measurements;

int initSensors(void);
void getMeasurements(Measurements *structToStoreIn);
void printMeasurements(Measurements *measurementsToPrint);
void measurementToString(char* destination, Measurements *measurement);




#endif
