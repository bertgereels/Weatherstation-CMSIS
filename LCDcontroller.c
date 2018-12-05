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
    
    //int formatSpecifiers=countPercent(format);
    va_start(args,format);
    vsnprintf(output, sizeof(output), format, args);
    va_end(args);
    lcd_setText(output);
}

/*
int countPercent(const char *format){
    int number=0;
    for(int i=0;;i++){
        if(format[i]=='%'){
            number++;
        }
        if(format[i]=='\0'){
            break;
        }
    }
    return number;
}*/