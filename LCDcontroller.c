/******************************************************
* LCD Control c code file				      		            *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

/**
 * Used functions in TextLCD:
 * void lcd_init();
 * void lcd_setText(char* text);
 */
#include "TextLCD.h"
#include "LCDcontroller.h"
#include <stdarg.h>
#include <stdio.h>

void lcd_printf(const char *format, ...){
    //https://stackoverflow.com/questions/3530771/passing-variable-arguments-to-another-function-that-accepts-a-variable-argument
    static int initialized=0;
    char output[34];
    va_list args;

    if(!initialized){
        lcd_init();
        initialized=1;
    }

    va_start(args,format);
    vsnprintf(output, sizeof(output), format, args);
    va_end(args);
    lcd_setText(output);
}
