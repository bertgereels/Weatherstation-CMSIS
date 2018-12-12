#include "TimerDriver.h"
#include "LCDcontroller.h"

void unixTimer_init(uint32_t unixTime){
	lcd_printf("UnixTimer init called.");
	timer_init(2,1000000,unixTime);
}
void unixTimer_start(){
	timer_start(2); //Second timer is unix Timer
}
uint32_t unixTimer_getValue(){
	return timer_getValue(2);
}
