/******************************************************
* TSL2561 driver c code file						              *
*                                                     *
* Author:  Bert Gereels                               *
*                                                     *
******************************************************/

#include "TSL2561.h"

// Delay for integration times
#define TSL2561_DELAY_INTTIME_13MS  (15)   ///< Wait 15ms for 13ms integration
#define TSL2561_DELAY_INTTIME_101MS (120)  ///< Wait 120ms for 101ms integration
#define TSL2561_DELAY_INTTIME_402MS (450)  ///< Wait 450ms for 402ms integration

#define TSL2561_AGC_THI_13MS      (4850)    ///< Max value at Ti 13ms = 5047
#define TSL2561_AGC_TLO_13MS      (100)     ///< Min value at Ti 13ms = 100
#define TSL2561_AGC_THI_101MS     (36000)   ///< Max value at Ti 101ms = 37177
#define TSL2561_AGC_TLO_101MS     (200)     ///< Min value at Ti 101ms = 200
#define TSL2561_AGC_THI_402MS     (63000)   ///< Max value at Ti 402ms = 65535
#define TSL2561_AGC_TLO_402MS     (500)     ///< Min value at Ti 402ms = 500

TSL2561IntegrationTime_t _TSL2561IntegrationTime;
TSL2561Gain_t _TSL2561Gain;
float integ_time;
int8_t gain;
uint8_t dt[4];
uint32_t ch0;
uint32_t ch1;
int8_t tsl2561_addr;

void enable(void){
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x00); //0x80 = command bit
    i2c2_byte_write(0x03); //0x03 = Power ON
    i2c2_stop();
}

void disable(void){
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x00); //0x80 = command bit
    i2c2_byte_write(0x00); //0x00 = Power OFF
    i2c2_stop();
}


uint8_t initTSL2561Sensor(TSL2561Addr_t I2C_addr){
	tsl2561_addr = I2C_addr;

    uint8_t data[4];
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x0A); //request sensor ID, used to verify correct initialisation
    data[0] = i2c2_byte_read(0);
    i2c2_stop();

    integ_time = 402.0;
    _TSL2561IntegrationTime = TSL2561_INTEGRATIONTIME_402MS;
    gain = 1;
    _TSL2561Gain = TSL2561_GAIN_1X;

    setIntegrationTime(_TSL2561IntegrationTime);
    setGain(_TSL2561Gain);

    return data[0];
}

void setIntegrationTime(TSL2561IntegrationTime_t time){
    enable();
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x01); //0x01 Timing Control
    i2c2_byte_write(time | TSL2561_GAIN_1X);
    i2c2_stop();
    _TSL2561IntegrationTime = time;
    disable();
}

void setGain(TSL2561Gain_t gain){
    enable();
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x01); //0x01 Timing Control
    i2c2_byte_write(_TSL2561IntegrationTime | gain);
    i2c2_stop();
    _TSL2561Gain = gain;
    disable();
}

void getData (uint16_t *broadband, uint16_t *ir){
    enable();

    /* Wait x ms for ADC to complete */
    wait_ms(TSL2561_DELAY_INTTIME_402MS);

    //--------------------------------------------------------------
    //- Reads a two byte value from channel 0 (visible + infrared) -
    //--------------------------------------------------------------
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x20 | 0x0c); //Address Ch0
    i2c2_stop();
    uint8_t data_to_receive_1[2]; //We expect two data bytes
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1 | 0x01);
    data_to_receive_1[0] = i2c2_byte_read(0); //CH0 lower data register
    data_to_receive_1[1] = i2c2_byte_read(1); //CH0 upper data register
    i2c2_stop();
    uint16_t received_data_1 = ((uint16_t)data_to_receive_1[1] << 8) + data_to_receive_1[0];
    *broadband = received_data_1;

    //----------------------------------------------------
    //- Reads a two byte value from channel 1 (infrared) -
    //----------------------------------------------------
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1);
    i2c2_byte_write(0x80 | 0x20 | 0x0e); //Address Ch1
    i2c2_stop();
    uint8_t data_to_receive_2[2];  //We expect two data bytes
    i2c2_start();
    i2c2_byte_write(tsl2561_addr << 1 | 0x01);
    data_to_receive_2[0] = i2c2_byte_read(0); //CH1 lower data register
    data_to_receive_2[1] = i2c2_byte_read(1); //CH1 upper data register
    i2c2_stop();
    uint16_t received_data_2 = ((uint16_t)data_to_receive_2[1] << 8) + data_to_receive_2[0];
    *ir = received_data_2;

    //Save power
    disable();
}

void getLuminosity (uint16_t *broadband, uint16_t *ir){
    int valid = 0;
    int _agcCheck = 0;

    do {
        uint16_t _b, _ir;
        uint16_t _hi, _lo;
        _hi = TSL2561_AGC_THI_402MS;
        _lo = TSL2561_AGC_TLO_402MS;

        getData(&_b, &_ir);

        /* Run an auto-gain check if we haven't already done so ... */
        if (_agcCheck == 0) {
            if ((_b < _lo) && (_TSL2561Gain == TSL2561_GAIN_1X)) {
                /* Increase the gain and try again */
                setGain(TSL2561_GAIN_16X);
                /* Drop the previous conversion results */
                getData(&_b, &_ir);
                /* Set a flag to indicate we've adjusted the gain */
                _agcCheck = 1;
            } else if ((_b > _hi) && (_TSL2561Gain == TSL2561_GAIN_16X)) {
                /* Drop gain to 1x and try again */
                setGain(TSL2561_GAIN_1X);
                /* Drop the previous conversion results */
                getData(&_b, &_ir);
                /* Set a flag to indicate we've adjusted the gain */
                _agcCheck = 1;
            } else {
                /* Nothing to look at here, keep moving ....
                   Reading is either valid, or we're already at the chips limits */
                *broadband = _b;
                *ir = _ir;
                valid = 1;
            }
        } else {
            /* If we've already adjusted the gain once, just return the new results.
               This avoids endless loops where a value is at one extreme pre-gain,
               and the the other extreme post-gain */
            *broadband = _b;
            *ir = _ir;
            valid = 1;
        }
    } while (valid == 0);
}

float getLux(void){
    double lux0, lux1;
    double ratio;
    double dlux;


    uint16_t x0, x1;
    getLuminosity(&x0, &x1);
    ch0 = x0;
    ch1 = x1;
    lux0 = (double)ch0;
    lux1 = (double)ch1;
    ratio = lux1 / lux0;

    //Algorithm as described in TSL2561 datasheet
    lux0 *= (402.0/(double)integ_time);
    lux1 *= (402.0/(double)integ_time);
    lux0 /= gain;
    lux1 /= gain;
    if (ratio <= 0.5) {
        dlux = 0.03040 * lux0 - 0.06200 * lux0 * pow(ratio,1.4);
    }else if (ratio <= 0.61) {
        dlux = 0.02240 * lux0 - 0.03100 * lux1;
    }else if (ratio <= 0.80) {
        dlux = 0.01280 * lux0 - 0.01530 * lux1;
    }else if (ratio <= 1.30) {
        dlux = 0.00146 * lux0 - 0.00112 * lux1;
    }else {
        dlux = 0;
    }

    disable();
    return (float)dlux;
}
