/******************************************************
* Sensor controller header file						  *
*                                                     *
* Author:  Bert Gereels                               *
*                                                     *
******************************************************/

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

/**
 *  Initializes the TSL2561 sensor and BME680 sensor
 *
 *  @return 1 if init is okay, 0 if init has failed (on one or both sensors)
 */
uint8_t initSensors(void);

/**
 *  Performs 4 measurements (temperature, pressure, humidity and light level).
 *
 *  @param structToStoreIn - Pointer to the struct that stores the 4 measurements.
 */
void getMeasurements(Measurements *structToStoreIn);

/**
 *  Prints the 4 measurements in the console
 *
 *  @param measurementsToPrint - Pointer to the struct in which the 4 measurements are stored.
 */
void printMeasurements(Measurements *measurementsToPrint);

/**
 *  Converts the 4 measurements to a string (char array)
 *
 *  @param destination - Pointer to the char array that will hold the string.
 *  @param measurement - Pointer to the struct in which the 4 measurements are stored.
 */
void measurementToString(char* destination, Measurements *measurement);

#endif
