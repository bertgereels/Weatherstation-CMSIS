#include "ButtonControl.h"
#include "GPIOdriver.h"

enum Command getCommand(){
    for(int i=INC; i<=SUBMIT; i++){ //Check all possible commands
        if(!mbedPin_read(i)){
            return (enum Command) i;
        }
    }
    return NONE;
}
