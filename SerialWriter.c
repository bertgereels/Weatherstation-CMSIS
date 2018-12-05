#include "GPIOdriver.h"
#include "ICdriver.h"
#include "SerialWriter.h"
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
    wait_us(10);
    mbedPin_off(BUS_CLOCK);
    wait_us(10);
}