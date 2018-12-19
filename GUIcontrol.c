#include "ButtonControl.h"
#include <stdlib.h>
#include "LCDcontroller.h"
#include "delay.h"
#include "GUIcontrol.h"

void gui_getSettings(Settings *settings){
    settings->period=gui_getValue("Seconds between");
    settings->unixTime=gui_getValue("Enter UNIX time");
    //lcd_printf("Read value.");
    //wait_ms(1000);
    lcd_printf("%i\n%i",settings->period,settings->unixTime);
    //lcd_printf("%ld\n%ld",unixTime,period);
}

int32_t gui_getValue(const char *query){
	int blinkingOn=0;
    int selectedIndex=0;
    char setting[11]="0000000000";
    char settingBlinking[11];
    wait_ms(200);
    timer_init(1,1,0);
    timer_start(1);
    while(1){
        Command command=NONE;
        while(command==NONE){
        	if(timer_getValue(1)>=250000){
        		blinkingOn= !blinkingOn;
        		timer_setValue(1,0);
        		if(blinkingOn){
        			lcd_printf("%s\n     %s",query,setting);
        		 } else {
        			memcpy(settingBlinking,setting,sizeof(settingBlinking));
        			settingBlinking[selectedIndex]=' ';
        		 	lcd_printf("%s\n     %s",query,settingBlinking);
        		 }
        	}
            command=buttons_getCommand();
        }
        switch(command){
            case INC:
                if(setting[selectedIndex]<'9'){
                    setting[selectedIndex]++;
                }
            break;
            case DECR:
                if(setting[selectedIndex]>'0'){
                    setting[selectedIndex]--;
                }
            break;
            case LEFT:
                if(selectedIndex>0){
                    selectedIndex--;
                }
            break;
            case RIGHT:
                if(selectedIndex<9){
                    selectedIndex++;
                }
            break;
            case SUBMIT:
                return atoi(setting);
            break;
        }
    wait_ms(200);
    }
}

//Update display method
