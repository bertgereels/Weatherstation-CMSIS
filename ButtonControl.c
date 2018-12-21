/******************************************************
* Button Control c code file				      		        *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#include "ButtonControl.h"

/**
 * Used functions in GPIOdriver are:
 * uint8_t mbedPin_read(uint8_t mbedPin);
 */
#include "GPIOdriver.h"

Command buttons_getCommand(){
    for(int i=INC; i<=SUBMIT; i++){ //Check all possible commands
        if(!mbedPin_read(i)){
            return (Command) i;
        }
    }
    return NONE;
}
