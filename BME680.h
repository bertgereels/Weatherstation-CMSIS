#ifndef BME680_H_
#define BME680_H_

#include "LPC17xx.h"
#include "I2C.h"
#include "delay.h"
#include <string.h>
#include <math.h>

typedef enum {
    BME680_GND_ADDR              = 0x76,    //SDO -> GND
	BME680_NC_ADDR               = 0x77,    //SDO -> not connected (floating)
}
BME680Addr_t;

int initBME680Sensor(BME680Addr_t I2C_addr);
int getChipID(void);
void readRegister(int reg, int size);
void writeRegister(int reg, int value);
void setSequentialMode(void);
void setStandByPeriod(int value);
void setOversamplingValues(int temp, int press, int humi);
void enableGasConversion(void);
void setHeaterSetPoints(int value);
void setGasWaitTime(int setPoint, int time, int multiplication);
void setIIRfilterCoefficient(int value);

int32_t getTemperature(void);
int32_t getPressure(void);
int32_t getHumidity(void);

#endif
