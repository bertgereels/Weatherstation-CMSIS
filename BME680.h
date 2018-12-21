/******************************************************
* BME680 driver header file						      *
*                                                     *
* Author:  Bert Gereels                               *
*                                                     *
******************************************************/

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

typedef enum {
    BME680_SB_0_59               = 0,
	BME680_SB_62_5               = 1,
	BME680_SB_125                = 2,
	BME680_SB_250                = 3,
	BME680_SB_500                = 4,
	BME680_SB_1000               = 5,
	BME680_SB_10                 = 6,
	BME680_SB_20               	 = 7,
	BME680_SB_0               	 = 8,
}
BME680StandbyPeriod_t;

typedef enum {
    BME680_OS_SKIPPED              = 0,
    BME680_OS_X1            	   = 1,
    BME680_OS_X2            	   = 2,
    BME680_OS_X4            	   = 3,
    BME680_OS_X8            	   = 4,
    BME680_OS_X16            	   = 5,
}
BME680OversamplingValues_t;

typedef enum {
    BME680_FC_0              = 0,
	BME680_FC_1              = 1,
	BME680_FC_3              = 2,
	BME680_FC_7              = 3,
	BME680_FC_15             = 4,
	BME680_FC_31             = 5,
	BME680_FC_63             = 6,
	BME680_FC_127            = 7,
}
BME680FilterCoeff_t;

/**
 *  Initializes the BME680 sensor.
 *
 *  @param I2C_addr - The I2C address.
 *
 *  @return value indicating if the sensor is initialized properly (should be 0 if everything is okay, when something is wrong: 1)
 */
uint8_t initBME680Sensor(BME680Addr_t I2C_addr);

/**
 *  Reads the chip ID of the BME680
 *
 *  @return the chip ID (should be 0x61!)
 */
uint8_t getChipID(void);

/**
 *  Reads the specified register of the BME680
 *
 *  @param reg - The register to read.
 *  @param size - The amount of bytes to read.
 */
void readRegister(uint8_t reg, uint8_t size);


/**
 *  Writes a value to the specified register of the BME680
 *
 *  @param reg - The register to write to.
 *  @param value - The value to write to the register.
 */
void writeRegister(uint8_t reg, uint8_t value);

/**
 *  Sets the sensor to sequential mode
 *  Between measurements the sensor goes into standy-mode
 */
void setSequentialMode(void);

/**
 *  Sets the time inbetween measurements
 *
 *  @param value - The value indicating the time inbetween: Possible values: see BME680StandbyPeriod_t typedef.
 */
void setStandByPeriod(BME680StandbyPeriod_t value);

/**
 *  Sets the oversampling values for temperature, pressure and humidity. This limits the amount of noise.
 *
 *  @param temp - The oversampling value for temperature. Possible values: see BME680OversamplingValues_t typedef.
 *  @param press - The oversampling value for pressure. Possible values: see BME680OversamplingValues_t typedef.
 *  @param humi - The oversampling value for humidity. Possible values: see BME680OversamplingValues_t typedef.
 */
void setOversamplingValues(BME680OversamplingValues_t temp, BME680OversamplingValues_t press, BME680OversamplingValues_t humi);

/**
 * 	This sets the IIR filter coefficients.
 * 	This helps to reduce short-term fluctuations in temperature and pressure data
 *
 *  @param value - The filter coefficient. Possible values: see BME680FilterCoeff_t typedef.
 */
void setIIRfilterCoefficient(BME680FilterCoeff_t value);

/**
 *  Gets the actual temperature value
 *
 * 	@return the temperature value
 */
int32_t getTemperature(void);

/**
 *  Gets the actual temperature value
 *
 * 	@return the temperature value
 */
int32_t getPressure(void);

/**
 *  Gets the actual temperature value
 *
 * 	@return the temperature value
 */
int32_t getHumidity(void);

#endif
