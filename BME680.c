/******************************************************
* BME680 driver c code file						      *
*                                                     *
* Author:  Bert Gereels                               *
*                                                     *
******************************************************/

#include "BME680.h"

#define BME680_SLEEP_MODE               (0x00)
#define BME680_FORCED_MODE              (0x01)
#define BME680_PARALLEL_MODE            (0x02)
#define BME680_SEQUENTIAL_MODE          (0x03)
#define BME680_GAS_PROFILE_TEMPERATURE_MIN  (200)
#define BME680_GAS_PROFILE_TEMPERATURE_MAX  (400)
#define BME680_GAS_RANGE_RL_LENGTH      (16)
#define BME680_SIGN_BIT_MASK            (0x08)
#define BME680_MAX_HUMIDITY_VALUE       (102400)
#define BME680_MIN_HUMIDITY_VALUE       (0)

//Calibration Data
int8_t  par_T3;/**<calibration T3 data*/
int8_t  par_P3;/**<calibration P3 data*/
int8_t  par_P6;/**<calibration P6 data*/
int8_t  par_P7;/**<calibration P7 data*/
uint8_t  par_P10;/**<calibration P10 data*/
int8_t  par_H3;/**<calibration H3 data*/
int8_t  par_H4;/**<calibration H4 data*/
int8_t  par_H5;/**<calibration H5 data*/
uint8_t  par_H6;/**<calibration H6 data*/
int8_t  par_H7;/**<calibration H7 data*/
int8_t  par_GH1;/**<calibration GH1 data*/
uint8_t  res_heat_range;/**<resistance calculation*/
int8_t  res_heat_val; /**<correction factor*/
int8_t  range_switching_error;/**<range switching error*/
int16_t par_GH2;/**<calibration GH2 data*/
uint16_t par_T1;/**<calibration T1 data*/
int16_t par_T2;/**<calibration T2 data*/
uint16_t par_P1;/**<calibration P1 data*/
int16_t par_P2;/**<calibration P2 data*/
int16_t par_P4;/**<calibration P4 data*/
int16_t par_P5;/**<calibration P5 data*/
int16_t par_P8;/**<calibration P8 data*/
int16_t par_P9;/**<calibration P9 data*/
uint16_t par_H1;/**<calibration H1 data*/
uint16_t par_H2;/**<calibration H2 data*/
int32_t t_fine;/**<calibration T_FINE data*/
int8_t  par_GH3;/**<calibration GH3 data*/

static const int BME680_BIT_MASK_H1_DATA = 0x0F;

static const int DIG_T2_LSB_REG = 1;
static const int DIG_T2_MSB_REG = 2;
static const int DIG_T3_REG = 3;
static const int DIG_P1_LSB_REG = 5;
static const int DIG_P1_MSB_REG = 6;
static const int DIG_P2_LSB_REG = 7;
static const int DIG_P2_MSB_REG = 8;
static const int DIG_P3_REG = 9;
static const int DIG_P4_LSB_REG = 11;
static const int DIG_P4_MSB_REG = 12;
static const int DIG_P5_LSB_REG = 13;
static const int DIG_P5_MSB_REG = 14;
static const int DIG_P7_REG = 15;
static const int DIG_P6_REG = 16;
static const int DIG_P8_LSB_REG = 19;
static const int DIG_P8_MSB_REG = 20;
static const int DIG_P9_LSB_REG = 21;
static const int DIG_P9_MSB_REG = 22;
static const int DIG_P10_REG = 23;
static const int DIG_H2_MSB_REG = 25;
static const int DIG_H2_LSB_REG = 26;
static const int DIG_H1_LSB_REG = 26;
static const int DIG_H1_MSB_REG  = 27;
static const int DIG_H3_REG = 28;
static const int DIG_H4_REG = 29;
static const int DIG_H5_REG = 30;
static const int DIG_H6_REG = 31;
static const int DIG_H7_REG = 32;
static const int DIG_T1_LSB_REG = 33;
static const int DIG_T1_MSB_REG = 34;
static const int DIG_GH2_LSB_REG = 35;
static const int DIG_GH2_MSB_REG = 36;
static const int DIG_GH1_REG = 37;
static const int DIG_GH3_REG = 38;

int8_t bme680_addr;
uint8_t data[30];

uint8_t initBME680Sensor(BME680Addr_t I2C_addr){
	bme680_addr = I2C_addr;

	int statuscode = 0;

    if (getChipID() != 0x61){
        printf("No 0x61!\r\n");
        statuscode = 1;
    }

    uint8_t cali[41];
    readRegister(0x89, 25);
    memcpy(cali, data, 25);
    readRegister(0xE1, 16);
    memcpy(cali + 25, data, 16);

    /* read temperature calibration*/
    par_T1 = (cali[DIG_T1_MSB_REG] << 8) | cali[DIG_T1_LSB_REG];
    par_T2 = (cali[DIG_T2_MSB_REG] << 8) | cali[DIG_T2_LSB_REG];
    par_T3 = cali[DIG_T3_REG];

    /* read pressure calibration*/
    par_P1 = (cali[DIG_P1_MSB_REG] << 8) | cali[DIG_P1_LSB_REG];
    par_P2 = (cali[DIG_P2_MSB_REG] << 8) | cali[DIG_P2_LSB_REG];
    par_P3 = cali[DIG_P3_REG];
    par_P4 = (cali[DIG_P4_MSB_REG] << 8) | cali[DIG_P4_LSB_REG];
    par_P5 = (cali[DIG_P5_MSB_REG] << 8) | cali[DIG_P5_LSB_REG];
    par_P6 = cali[DIG_P6_REG];
    par_P7 = cali[DIG_P7_REG];
    par_P8 = (cali[DIG_P8_MSB_REG] << 8) | cali[DIG_P8_LSB_REG];
    par_P9 = (cali[DIG_P9_MSB_REG] << 8) | cali[DIG_P9_LSB_REG];
    par_P10 = cali[DIG_P10_REG];

    /* read humidity calibration*/
    par_H1 = (cali[DIG_H1_MSB_REG] << 4) | (cali[DIG_H1_LSB_REG] & BME680_BIT_MASK_H1_DATA);
    par_H2 = (cali[DIG_H2_MSB_REG] << 4) | (cali[DIG_H2_LSB_REG] >> 4);
    par_H3 = cali[DIG_H3_REG];
    par_H4 = cali[DIG_H4_REG];
    par_H5 = cali[DIG_H5_REG];
    par_H6 = cali[DIG_H6_REG];
    par_H7 = cali[DIG_H7_REG];

    /* read gas calibration*/
    par_GH1 = cali[DIG_GH1_REG];
    par_GH2 = (cali[DIG_GH2_MSB_REG] <<8) | cali[DIG_GH2_LSB_REG];
    par_GH3 = cali[DIG_GH3_REG];

    /**<resistance calculation*/
    readRegister(0x02, 1);
    res_heat_range = (data[0] >> 4) & 0x03;

    /**<correction factor*/
    readRegister(0x00, 1);
    res_heat_val = data[0];

    /**<range switching error*/
    readRegister(0x04, 1);
    range_switching_error = (data[0] & 0xF0) >> 4;

    setSequentialMode();

    printf("The statuscode is %d\r\n", statuscode);
    return statuscode;
}

uint8_t getChipID(){
    readRegister(0xD0, 1);
    return data[0];
}

void readRegister(uint8_t reg, uint8_t size){
    i2c2_start();
    i2c2_byte_write(bme680_addr << 1); //1byte
    i2c2_byte_write(reg);
    i2c2_stop();
    i2c2_start();
    i2c2_byte_write(bme680_addr << 1 | 0x01);

    int i = 0;
    for (; i< size -1; i++){
        data[i] = i2c2_byte_read(0);
    }
    data[i] = i2c2_byte_read(1);
    i2c2_stop();
}

void writeRegister(uint8_t reg, uint8_t value){
	i2c2_start();
	i2c2_byte_write(bme680_addr << 1);
	i2c2_byte_write(reg);
	i2c2_byte_write(value);
    i2c2_stop();
}

void setSequentialMode(){
    //Set stand-by time between measurements
	setStandByPeriod(BME680_FC_1);

    //Set oversampling for T, P, H
    setOversamplingValues(BME680_OS_X2,BME680_OS_X16,BME680_OS_X1);

    //SetIIR filter for pressure & temperature
    setIIRfilterCoefficient(BME680_FC_1);

    //Set mode to sequential mode
    //Set mode<1:0> to 0b11
    readRegister(0x74,1);
    data[0] = (data[0] & 0xFC) | (3 & 0x03);
    writeRegister(0x74, data[0]);
}

void setStandByPeriod(BME680StandbyPeriod_t value){
    readRegister(0x71,1);
    data[0] = (data[0] & 0x7F) | ((value & 0x0F) >> 3);
    writeRegister(0x71, data[0]);

    readRegister(0x75,1);
    data[0] = (data[0] & 0x1F) | ((value & 0x07) << 5);
    writeRegister(0x75, data[0]);
}

void setOversamplingValues(BME680OversamplingValues_t temp, BME680OversamplingValues_t press, BME680OversamplingValues_t humi){
	//Set oversampling value for temperature
    readRegister(0x74,1);
    data[0] = (data[0] & 0x1F) | ((temp & 0x07) << 5);
    writeRegister(0x74, data[0]);

    //Set oversampling value for pressure
    readRegister(0x74,1);
    data[0] = (data[0] & 0xE3) | ((press & 0x07) << 2);
    writeRegister(0x74, data[0]);

    //Set oversampling value for humidity
    readRegister(0x72,1);
    data[0] = (data[0] & 0xF8) | (humi & 0x07);
    writeRegister(0x72, data[0]);
}

void setIIRfilterCoefficient(BME680FilterCoeff_t value){
    readRegister(0x75,1);
    data[0] = (data[0] & 0xE3) | ((value & 0x07) << 2);
    writeRegister(0x75, data[0]);
}


int32_t getTemperature(){
    readRegister(0x22 + 0 * 0x11, 3);
    uint32_t v_uncomp_temperature_u32 =  (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);

    int32_t var1 = ((int32_t)v_uncomp_temperature_u32 >> 3) - ((int32_t)(par_T1 << 1));
    int32_t var2 = (var1 * (int32_t) par_T2) >> 11;
    int32_t var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)(par_T3 << 4))) >> 14;
    t_fine = var2 + var3;
    return ((t_fine * 5) + 128) >> 8;
}

int32_t getPressure(){
    readRegister(0x1F + 0* 0x11, 3);
    uint32_t v_uncomp_pressure_u32 = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);

    int32_t var1 = (((int32_t)t_fine) >> 1) - 64000;
    int32_t var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) * (int32_t)par_P6) >> 2;
    var2 = var2 + ((var1 * (int32_t)par_P5) << 1);
    var2 = (var2 >> 2) + ((int32_t)par_P4 << 16);
    var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) *
             ((int32_t)par_P3 << 5)) >> 3) +
           (((int32_t)par_P2 * var1) >> 1);
    var1 = var1 >> 18;
    var1 = ((32768 + var1) * (int32_t)par_P1) >> 15;
    int32_t pressure_comp = 1048576 - v_uncomp_pressure_u32;
    pressure_comp = (int32_t)((pressure_comp - (var2 >> 12)) * ((int32_t)3125));
    int32_t var4 = (1 << 31);
    if (pressure_comp >= var4)
        pressure_comp = ((pressure_comp / (int32_t)var1) << 1);
    else
        pressure_comp = ((pressure_comp << 1) / (int32_t)var1);
    var1 = ((int32_t)par_P9 * (int32_t)(((pressure_comp >> 3) *
                                         (pressure_comp >> 3)) >> 13)) >> 12;
    var2 = ((int32_t)(pressure_comp >> 2) *
            (int32_t)par_P8) >> 13;
    int32_t var3 = ((int32_t)(pressure_comp >> 8) * (int32_t)(pressure_comp >> 8) *
                    (int32_t)(pressure_comp >> 8) *
                    (int32_t)par_P10) >> 17;

    pressure_comp = (int32_t)(pressure_comp) + ((var1 + var2 + var3 +
                    ((int32_t)par_P7 << 7)) >> 4);

    return pressure_comp;
}

int32_t getHumidity(){
    readRegister(0x25 + 0* 0x11, 2);
    uint32_t v_uncomp_humidity_u32 =  (data[0] << 8) | data[1];

    int32_t temp_scaled = (t_fine * 5 + 128) >> 8;
    int32_t var1 = (int32_t)v_uncomp_humidity_u32 -
                   ((int32_t)((int32_t)par_H1 << 4)) -
                   (((temp_scaled * (int32_t)par_H3) /
                     ((int32_t)100)) >> 1);

    int32_t var2 = ((int32_t)par_H2 *
                    (((temp_scaled * (int32_t)par_H4) /
                      ((int32_t)100)) + (((temp_scaled *
                                           ((temp_scaled * (int32_t)par_H5) /
                                            ((int32_t)100))) >> 6) / ((int32_t)100)) + (int32_t)(1 << 14))) >> 10;

    int32_t var3 = var1 * var2;

    int32_t var4 = ((((int32_t)par_H6) << 7) +
                    ((temp_scaled * (int32_t)par_H7) /
                     ((int32_t)100))) >> 4;

    int32_t var5 = ((var3 >> 14) * (var3 >> 14)) >> 10;
    int32_t var6 = (var4 * var5) >> 1;

    int32_t humidity_comp = (var3 + var6) >> 12;
    if (humidity_comp > BME680_MAX_HUMIDITY_VALUE)
        humidity_comp = BME680_MAX_HUMIDITY_VALUE;
    else if (humidity_comp < BME680_MIN_HUMIDITY_VALUE)
        humidity_comp = BME680_MIN_HUMIDITY_VALUE;

    return humidity_comp;
}

