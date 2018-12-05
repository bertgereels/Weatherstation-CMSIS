#include "LPC17xx.h"
#include "GPIOdriver.h"

void mbedPin_init(uint8_t mbedPin){
    if(isValidPin(mbedPin)){
        LPCpin_init(getLPCport(mbedPin),getLPCpin(mbedPin));
    }
}

void mbedPin_on(uint8_t mbedPin){
    if(isValidPin(mbedPin)){
        LPCpin_on(getLPCport(mbedPin),getLPCpin(mbedPin));
    }
}

void mbedPin_off(uint8_t mbedPin){
    if(isValidPin(mbedPin)){
        LPCpin_off(getLPCport(mbedPin),getLPCpin(mbedPin));
    }
}

void mbedPin_write(int value,uint8_t mbedPin){
    if(isValidPin(mbedPin)){
        LPCpin_write(value,getLPCport(mbedPin),getLPCpin(mbedPin));
    }
}

int isValidPin(uint8_t mbedPin){
    return (mbedPin>=5&&mbedPin<=32);
}

void LPCpin_init(uint8_t port, uint8_t pin){
    if(IsValidLpcPortPin(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIODIR |= 1 << pin;
        portGPIO->FIOMASK &= ~(1 << pin);
    }
    /*
    switch(port){
        case 0:
            LPC_GPIO0->FIODIR |= 1 << pin;
            LPC_GPIO0->FIOMASK &= ~(1 << pin);
            break;
        case 1:
            LPC_GPIO1->FIODIR |= 1 << pin;
            LPC_GPIO1->FIOMASK &= ~(1 << pin);
            break;
        case 2:
            LPC_GPIO2->FIODIR |= 1 << pin;
            LPC_GPIO2->FIOMASK &= ~(1 << pin);
            break;
  }*/
}

void LPCpin_on(uint8_t port, uint8_t pin){
    if(IsValidLpcPortPin(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIOSET |= 1 << pin;
    }
    /*
    switch(port){
    case 0:
        LPC_GPIO0->FIOSET |= 1 << pin;
        break;
    case 1:
        LPC_GPIO1->FIOSET |= 1 << pin;
        break;
    case 2:
        LPC_GPIO2->FIOSET |= 1 << pin;
        break;
    }*/
}

void LPCpin_off(uint8_t port, uint8_t pin){
    if(IsValidLpcPortPin(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIOCLR |= 1 << pin;
    }
    /*
    switch(port){
        case 0:
            LPC_GPIO0->FIOCLR |= 1 << pin;
            break;
        case 1:
            LPC_GPIO1->FIOCLR |= 1 << pin;
            break;
        case 2:
            LPC_GPIO2->FIOCLR |= 1 << pin;
            break;
        }*/
}

/*
 * Write a single bit
 */
void LPCpin_write(int value,uint8_t port, uint8_t pin){
    if(value){
        LPCpin_on(port,pin);
    } else {
        LPCpin_off(port,pin);
    }
}

uint8_t getLPCport(uint8_t mbedPin){
    static int LPCports[]={-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,0,0,0,0,0,0}; //Source: mbed pins excel file on toledo.
    if(isValidPin(mbedPin)){
        return LPCports[mbedPin];
    } else {
        return -1;
    }
}

uint8_t getLPCpin(uint8_t mbedPin){
    static int LPCpins[]={-1,-1,-1,-1,-1,9,8,7,6,0,1,18,17,15,16,23,24,25,26,30,31,5,4,3,2,1,0,11,10,5,4,29,30}; //Source: mbed pins excel file on toledo.
    if(isValidPin(mbedPin)){
        return LPCpins[mbedPin];
    } else {
        return -1;
    }
}

/**
 * Write with offset
 */
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

/**
 * Initialize with offset
 */
void mbedPins_init(uint8_t offset,uint8_t length){
    for(int i=0;i<=length;i++){
        mbedPin_init(i+offset);
    }
}

/*
 * Initialize port as input. Port is input by default, unless previously changed to write mode.
 */
void LPCpin_initIn(uint8_t port, uint8_t pin){
    if(IsValidLpcPortPin(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        portGPIO->FIODIR &= ~(1 << pin); //Set bit off
        //TODO mask
    }
}

uint8_t LPCpin_read(uint8_t port, uint8_t pin){
    if(IsValidLpcPortPin(port,pin)){
        LPC_GPIO_TypeDef* portGPIO=getGPIOTypeDef(port);
        return bitAtRightIndex(portGPIO->FIOPIN,pin);
    } else {
        return 0;
    }
}

uint8_t mbedPin_read(uint8_t mbedPin){
    return LPCpin_read(getLPCport(mbedPin),getLPCpin(mbedPin));
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

int IsValidLpcPort(uint8_t port){
    return (port>=0)||(port<=4);
}

int IsValidLpcPin(uint8_t pin){
    return (pin>=0)||(pin<32);
}

int IsValidLpcPortPin(uint8_t port,uint8_t pin){
    return IsValidLpcPort(port)&&IsValidLpcPin(pin);
}

uint8_t bitAtRightIndex(uint32_t input,uint8_t index){
    input=input>>index;
    input&=1;
    return input;
}