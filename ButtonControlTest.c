#include "ButtonControl.h"
#include "GPIOdriver.h"
#include "TextLCD.h"
#include <stdio.h>

void testButtons(){
    char output[34];
    lcd_init();
    //Command command=getCommand();
    snprintf(output, sizeof(output), "Value is: %i", mbedPin_read(9) );
    lcd_setText(output);
    
    /*
    lcd_init();
    if(mbedPin_read(9)){
        lcd_setText("Not pressed");
    } else {
        lcd_setText("Pressed");
    }*/
}