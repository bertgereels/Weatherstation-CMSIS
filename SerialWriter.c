/******************************************************
* SerialWriter c code file				      		          *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

/**
 * Used functions in GPIOdriver:
 * void mbedPin_off(uint8_t mbedPin);
 * void mbedPin_on(uint8_t mbedPin);
 * void mbedPin_write(int value,uint8_t mbedPin);
 *
 */
#include "GPIOdriver.h"

/**
 * Used functions in ICdriver:
 * void IC501_init(uint8_t value);
 */
#include "ICdriver.h"

#include "SerialWriter.h"

/**
 * Used function in delay.h:
 * void wait_us(int us);
 */
#include "delay.h"

enum DataLines {
    BUS_STROBE = 15,
    BUS_DATA = 16,
    BUS_CLOCK = 17,
    BUS_OE = 18,
};

void shiftRegister_init(){
    IC501_init(0);
    mbedPin_off(BUS_DATA);
    mbedPin_off(BUS_CLOCK);
    mbedPin_on(BUS_STROBE);
    mbedPin_on(BUS_OE);
}

void shiftRegister_writeByte(uint8_t byte){
    for(int i=7;i>=0;i--){
    shiftRegister_writeBit(bitAtRightIndex(byte,i));
    }
}

void shiftRegister_write4bits(uint8_t byte){
    shiftRegister_writeByte(byte<<4);
}

void shiftRegister_writeBit(uint8_t bit){
    mbedPin_write(bit,BUS_DATA);
    mbedPin_on(BUS_CLOCK);
    wait_us(1);
    mbedPin_off(BUS_CLOCK);
    wait_us(1);
}
