/******************************************************
* GPIO Driver c code file				      		            *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#include "LPC17xx.h"
#include "GPIOdriver.h"

void mbedPin_init(uint8_t mbedPin){
    if(mbedPin_isValid(mbedPin)){
        lpcPin_init(mbedPin_getLPCport(mbedPin),mbedPin_getLPCpin(mbedPin));
    }
}

void mbedPin_on(uint8_t mbedPin){
    if(mbedPin_isValid(mbedPin)){
        lpcPin_on(mbedPin_getLPCport(mbedPin),mbedPin_getLPCpin(mbedPin));
    }
}

void mbedPin_off(uint8_t mbedPin){
    if(mbedPin_isValid(mbedPin)){
        lpcPin_off(mbedPin_getLPCport(mbedPin),mbedPin_getLPCpin(mbedPin));
    }
}

void mbedPin_write(int value,uint8_t mbedPin){
    if(mbedPin_isValid(mbedPin)){
        lpcPin_write(value,mbedPin_getLPCport(mbedPin),mbedPin_getLPCpin(mbedPin));
    }
}

int mbedPin_isValid(uint8_t mbedPin){
    return (mbedPin>=5&&mbedPin<=32);
}

void lpcPin_init(uint8_t port, uint8_t pin){
    if(lpcPortPin_isValid(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIODIR |= 1 << pin;
        portGPIO->FIOMASK &= ~(1 << pin);
    }
}

void lpcPin_on(uint8_t port, uint8_t pin){
    if(lpcPortPin_isValid(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIOSET |= 1 << pin;
    }
}

void lpcPin_off(uint8_t port, uint8_t pin){
    if(lpcPortPin_isValid(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIOCLR |= 1 << pin;
    }
}


void lpcPin_write(int value,uint8_t port, uint8_t pin){
    if(value){
        lpcPin_on(port,pin);
    } else {
        lpcPin_off(port,pin);
    }
}

uint8_t mbedPin_getLPCport(uint8_t mbedPin){
    static int LPCports[]={-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,0,0,0,0,0,0}; //Source: mbed pins excel file on toledo.
    if(mbedPin_isValid(mbedPin)){
        return LPCports[mbedPin];
    } else {
        return -1;
    }
}

uint8_t mbedPin_getLPCpin(uint8_t mbedPin){
    static int LPCpins[]={-1,-1,-1,-1,-1,9,8,7,6,0,1,18,17,15,16,23,24,25,26,30,31,5,4,3,2,1,0,11,10,5,4,29,30}; //Source: mbed pins excel file on toledo.
    if(mbedPin_isValid(mbedPin)){
        return LPCpins[mbedPin];
    } else {
        return -1;
    }
}

void mbedPins_write(uint32_t value,uint8_t offset,uint8_t length){
    for(int i=0;i<length;i++){
        uint32_t mask=1<<i;
        if(value&mask){ //Select bit i and check if it's true or false
            mbedPin_on(i+offset);
        } else {
            mbedPin_off(i+offset);
        }
    }
}

void mbedPins_init(uint8_t offset,uint8_t length){
    for(int i=0;i<=length;i++){
        mbedPin_init(i+offset);
    }
}

void lpcPin_initIn(uint8_t port, uint8_t pin){
    if(lpcPortPin_isValid(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIODIR &= ~(1 << pin); //Set bit off
    }
}

uint8_t lpcPin_read(uint8_t port, uint8_t pin){
    if(lpcPortPin_isValid(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        return bitAtRightIndex(portGPIO->FIOPIN,pin);
    } else {
        return 0;
    }
}

uint8_t mbedPin_read(uint8_t mbedPin){
    return lpcPin_read(mbedPin_getLPCport(mbedPin),mbedPin_getLPCpin(mbedPin));
}

LPC_GPIO_TypeDef* getGPIOTypeDef(uint8_t port){
    switch(port){
        case 0:
            return LPC_GPIO0;
        case 1:
            return LPC_GPIO1;
        case 2:
            return LPC_GPIO2;
        case 3:
            return LPC_GPIO3;
        case 4:
            return LPC_GPIO4;
    }
    return 0;
}

int lpcPort_isValid(uint8_t port){
    return (port>=0)||(port<=4);
}

int lpcPin_isValid(uint8_t pin){
    return (pin>=0)||(pin<32);
}

int lpcPortPin_isValid(uint8_t port,uint8_t pin){
    return lpcPort_isValid(port)&&lpcPin_isValid(pin);
}

uint8_t bitAtRightIndex(uint32_t input,uint8_t index){
    input=input>>index;
    input&=1;
    return input;
}
