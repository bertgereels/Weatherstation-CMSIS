#include "LPC17xx.h"
#include "SensorControl.h"

#include <cr_section_macros.h>

int initSensors(void){
	if((initTSL2561Sensor() == 0x8a) && initBME680Sensor() ){
		return 1;
	}

	return 0;
}



void getMeasurements(Measurements *structToStoreIn){
	structToStoreIn->lightlevel = getLux();
	wait_ms(100);
	structToStoreIn->humidity = getHumidity()/1024;
	structToStoreIn->pressure = getPressure();
	structToStoreIn->temperature = getTemperature()/100;
}

void printMeasurements(Measurements *measurementsToPrint){
	printf("Illuminance: %+7.2f [Lux]\r\n", measurementsToPrint->lightlevel);
    printf("Temperature value: %d C\r\n", measurementsToPrint->temperature);
    printf("Pressure value: %d Pa\r\n", measurementsToPrint->pressure);
    printf("Humidity value: %d %rH\r\n", measurementsToPrint->humidity);
}

void measurementToString(char* destination, Measurements *measurement){
    sprintf(destination,"%dC  %dPa\n%drH %+7.2flx",
            measurement->temperature,
            measurement->pressure,
            measurement->humidity,
            measurement->lightlevel
    );
}


