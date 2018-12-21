/******************************************************
* TSL2561 driver header file						              *
*                                                     *
* Author:  Bert Gereels                               *
*                                                     *
******************************************************/

#ifndef TSL2561_H_
#define TSL2561_H_

#include "LPC17xx.h"
#include "I2C.h"
#include "delay.h"
#include <math.h>

typedef enum {
    TSL2561_GND_ADDR              = 0x29,    //Addr -> GND
	TSL2561_NC_ADDR               = 0x39,    //Addr -> not connected (floating)
    TSL2561_VCC_ADDR              = 0x49,    //Addr -> VCC
}
TSL2561Addr_t;

typedef enum {
    TSL2561_INTEGRATIONTIME_402MS = 0x02     // 402ms most accurate
}
TSL2561IntegrationTime_t;

typedef enum {
    TSL2561_GAIN_1X               = 0x00,    // No gain
    TSL2561_GAIN_16X              = 0x10,    // 16x gain
}
TSL2561Gain_t;

/**
 *  Initializes the TSL2561 sensor.
 *
 *  @param I2C_addr - The I2C address.
 *
 *  @return value indicating if the sensor is initialized properly (should be 8a if everything is okay)
 */
uint8_t initTSL2561Sensor(TSL2561Addr_t I2C_addr);

/**
 *	Enables the TSL2561 sensor by setting control bits to 0x03.
 */
void enable(void);

/**
 *  Disables the TSL2561 sensor by setting control bits to 0x00.
 */
void disable(void);

/**
 *  Sets the TSL2561 sensor integration time.
 *
 *  @param time - The new integration time value, stored in a typedef. More time = more light to capture = more accurate measurement.
 */
void setIntegrationTime(TSL2561IntegrationTime_t time);


/**
 *  Sets the TSL2561 sensor gain.
 *
 *  @param gain - The new gain value, stored in a typedef.
 */
void setGain(TSL2561Gain_t gain);

/**
 *  Reads luminosity on both channels of the TSL2561.
 *
 *  @param  broadband - Pointer to a uint16_t we will fill with a sensor
 *                    reading from the IR+visible light diode.
 *  @param  ir - Pointer to a uint16_t we will fill with a sensor the
 *             IR-only light diode.
 */
void getData (uint16_t *broadband, uint16_t *ir);

/**
 *  Gets the broadband (mixed lighting) and IR only values from the TSL2561.
 *
 *  @param  broadband - Pointer to a uint16_t we will fill with a sensor
 *                    reading from the IR+visible light diode.
 *  @param  ir - Pointer to a uint16_t we will fill with a sensor the
 *             IR-only light diode.
 */
void getLuminosity (uint16_t *broadband, uint16_t *ir);

/**
 *  Reads lux from TSL2561 sensor.
 *
 *  @return the lux value
 */
float getLux(void);



#endif
