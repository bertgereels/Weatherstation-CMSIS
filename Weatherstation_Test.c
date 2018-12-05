//
//
//#include "LPC17xx.h"
//#include "I2C.h"
//#include "TSL2561.h"
//#include "BME680.h"
//#include "SensorControl.h"
//#include "TextLCD.h"
//
//#include <cr_section_macros.h>
//#include <stdio.h>
//#include <string.h>
//
//
//
//int main(void) {
//	lcd_init();
//
////	//I2C
//	i2c2_init();
//	printf("The I2C status is: %x\n", i2c2_status());
//
//	if(!initSensors()){
//		printf("Sensors initialized succesfully!\r\n");
//	}
//
//	Measurements meting;
//	getMeasurements(&meting);
//	printMeasurements(&meting);
//
//	char temperatuur[8];
//	sprintf(temperatuur,"%lu", meting.temperature);
//
//	lcd_setText(temperatuur);
////
////	uint8_t data[4];
////	i2c2_start();
////	i2c2_byte_write(0xA0);
////	i2c2_byte_write(0x01);
////	data[0] = i2c2_byte_read(0);
////	i2c2_stop();
////
////	printf("The data that was read is: %x\r\n", data[0]);
//
//	return 0;
//}
//
