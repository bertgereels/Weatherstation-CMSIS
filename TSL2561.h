#ifndef TSL2561_H_
#define TSL2561_H_

#include "LPC17xx.h"
#include "I2C.h"
#include "delay.h"
#include <math.h>

typedef enum {
    TSL2561_INTEGRATIONTIME_13MS  = 0x00,    // 13.7ms
    TSL2561_INTEGRATIONTIME_101MS = 0x01,    // 101ms
    TSL2561_INTEGRATIONTIME_402MS = 0x02     // 402ms
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
 *  @return value indicating if the sensor is initialized propery (should be 8a if everything is okay)
 */
uint8_t initTSL2561Sensor();

/**
 *	Enables the TSL2561 sensor by setting control bits to 0x03.
 */
void enable();

/**
 *  Disables the TSL2561 senso by setting control bits to 0x00.
 */
void disable();

/**
 *  Sets the TSL2561 sensor integration time.
 *
 *  @param The new integration time value, stored in a typedef. More time = more light to capture = more accurate measurement.
 */
void setIntegrationTime(TSL2561IntegrationTime_t time);


/**
 *  Sets the TSL2561 sensor gain.
 *
 *  @param The new gain value, stored in a typedef.
 */
void setGain(TSL2561Gain_t gain);

/**
 *  Reads the TSL2561 timing register.
 *
 *  @return the value of the TSL2561 timing register
 */
uint8_t readTimingReg(void);

/**
 *  Reads luminosity on both channels of the TSL2561.
 */
void getData (uint16_t *broadband, uint16_t *ir);

/**
 *  Gets the broadband (mixed lighting) and IR only values from the TSL2561.
 *
 *  @param  broadband Pointer to a uint16_t we will fill with a sensor
 *                    reading from the IR+visible light diode.
 *  @param  ir Pointer to a uint16_t we will fill with a sensor the
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
