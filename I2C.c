#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "stdint.h"
#include "stdlib.h"
#endif

#include "I2C.h"

#include <cr_section_macros.h>
#include <stdio.h>
#include <string.h>

void i2c2_conclr(int start, int stop, int interrupt, int acknowledge) {
	LPC_I2C2->I2CONCLR = (start << 5)
                       | (stop << 4)
                       | (interrupt << 3)
                       | (acknowledge << 2);
}

void i2c2_conset(int start, int stop, int interrupt, int acknowledge) {
	LPC_I2C2->I2CONSET = (start << 5)
                       | (stop << 4)
                       | (interrupt << 3)
                       | (acknowledge << 2);
}

int i2c2_wait_SI() {
    int timeout = 0;
    while (!(LPC_I2C2->I2CONSET & (1 << 3))) {
        timeout++;
        if (timeout > 100000) return -1;
    }
    return 0;
}

void i2c2_clear_SI() {
	i2c2_conclr(0, 0, 1, 0);
}

void i2c2_set_SI(){
	i2c2_conset(0, 0, 1, 0);
}

void i2c2_interface_enable(){
	LPC_I2C2->I2CONSET = 0x40;
}

int i2c2_status(){
	return LPC_I2C2->I2STAT;
}

void i2c2_init() {
    //Peripheral Clock Selection
    LPC_SC->PCLKSEL1 &=~ (1<<20)|(1<<21);

    //Configure mbed pins P27 and P28 as i2c2 bus pins
    LPC_PINCON->PINSEL0 &=~ (1<<20);         // Set mbed pin P27 as SCL2
    LPC_PINCON->PINSEL0 |=  (1<<21);         // Set mbed pin P27 as SCL2
    LPC_PINCON->PINSEL0 &=~ (1<<22);         // Set mbed pin P28 as SDA2
    LPC_PINCON->PINSEL0 |=  (1<<23);         // Set mbed pin P28 as SDA2

	//Set pinmode
	LPC_PINCON->PINMODE0 &=~ (1<<20);
	LPC_PINCON->PINMODE0 |=  (1<<21);
	LPC_PINCON->PINMODE0 &=~ (1<<22);
	LPC_PINCON->PINMODE0 |=  (1<<23);

	//SET pinmode_OD
	LPC_PINCON->PINMODE_OD0 |= (1<<10);
    LPC_PINCON->PINMODE_OD1 |= (1<<11);

    // Set the i2c2 Interrupts in the Global Interrupts; active
    //NVIC_EnableIRQ(I2C2_IRQn);

	// give power to the i2c2 hardware
    LPC_SC->PCONP |= (1 << 26);

    //Set frequency - 100kHz
    uint32_t PCLK = SystemCoreClock / 4;
    uint32_t pulse = PCLK / (100000 * 2);
    LPC_I2C2->I2SCLH = pulse;                 // SCL prescaler High register
    LPC_I2C2->I2SCLL = pulse;

    i2c2_conclr(1, 1, 1, 1);
    i2c2_interface_enable();
}

int i2c2_start(){
	int status;
	int isInterrupted = LPC_I2C2->I2CONSET & (1 << 3);

	//Before master mode initialisation, set I2CON
	i2c2_conclr(1, 1, 0, 1);
	//Master mode
	i2c2_conset(1, 0, 0, 1);

	if (isInterrupted){
		i2c2_clear_SI();
	}

	i2c2_wait_SI();
	status = i2c2_status();

	i2c2_conclr(1, 0, 0, 0);

	//printf("Status after starting is:%x\r\n", status);
	return status;
}

int i2c2_stop(){
	int timeout = 0;

	// write the stop bit
	i2c2_conset(0, 1, 0, 0);
    i2c2_clear_SI();

	// wait for STO bit to reset
	while(LPC_I2C2->I2CONSET  & (1 << 4)) {
		timeout ++;
		if (timeout > 100000) return 1;
	}

	return 0;
}

int i2c2_do_write(int value, uint8_t addr) {
    // write the data
	LPC_I2C2->I2DAT = value;

    // clear SI to initiate a send
    i2c2_clear_SI();

    // wait and return status
    i2c2_wait_SI();
    return i2c2_status();
}

int i2c2_byte_write(int data){
    int ack = 0;
    int status = i2c2_do_write(data & 0xFF, 0);

    switch(status) {
        case 0x18:
        case 0x28:      // Master transmit ACKs
            ack = 1;
            break;
        case 0x40:      // Master receive address transmitted ACK
            ack = 1;
            break;
        case 0xB8:      // Slave transmit ACK
            ack = 1;
            break;
        default:
            ack = 0;
            break;
    }

    return ack;
}

int i2c2_byte_read(int last){
	//printf("The status is: %x\r\n", i2c2_status());
    return (i2c2_do_read(last) & 0xFF);
}

int i2c2_do_read(int last) {
    // we are in state 0x40 (SLA+R tx'd) or 0x50 (data rx'd and ack)
    if(last) {
        i2c2_conclr( 0, 0, 0, 1); // send a NOT ACK
    }else {
        i2c2_conset(0, 0, 0, 1); // send a ACK
    }

    // accept byte
    i2c2_clear_SI();

    // wait for it to arrive
    i2c2_wait_SI();

    // return the data
    return (LPC_I2C2->I2DAT & 0xFF);
}




