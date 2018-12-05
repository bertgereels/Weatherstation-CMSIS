#ifndef BME680_H_
#define BME680_H_

#include "LPC17xx.h"
#include "I2C.h"
#include "delay.h"
#include <string.h>
#include <math.h>

int initBME680Sensor(void);
int getChipID(void);
void readRegister(int reg, int size);
void writeRegister(int reg, int value);
void setSequentialMode(void);
void setWakePeriod(int value);
void setOversamplingTemperature(int value);
void setOversamplingPressure(int value);
void setOversamplingHumidity(int value);
void setIIRfilterCoefficient(int value);
void runGasConversion();
void setHeaterProfile(int value);
void setGasWaitTime(int setPoint, int time, int multiplication);
void setMode(int mode);
int32_t getCompensatedTemperature(void);
uint32_t getUncompensatedTemp1Data(void);
int32_t getCompensatedPressure(void);
uint32_t getUncompensatedPressureData(void);
int32_t getCompensatedHumidity(void);
uint32_t getUncompensatedHumidityData(void);

#endif
