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

void i2c2_wait_SI() {
    wait_ms(1);
}

void i2c2_clear_SI() {
	i2c2_conclr(0, 0, 1, 0);
}

void i2c2_set_SI(){
	i2c2_conset(0, 0, 1, 0);
}

//"For Master only functions, write 0x40 to I2CONSET".
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

void i2c2_start(){
	int isInterrupted = LPC_I2C2->I2CONSET & (1 << 3);

	//Before master mode initialisation, set I2CON
	i2c2_conclr(1, 1, 0, 1);
	//Master mode
	i2c2_conset(1, 0, 0, 1);

	if (isInterrupted){
		i2c2_clear_SI();
	}

	i2c2_wait_SI();

	//Clear start bit
	i2c2_conclr(1, 0, 0, 0);

}

void i2c2_stop(){
	// write the stop bit
	i2c2_conset(0, 1, 0, 0);
    i2c2_clear_SI();
}

int i2c2_do_write(int8_t value) {
	LPC_I2C2->I2DAT = value;

    // clear SI to initiate a send
    i2c2_clear_SI();

    // wait and return status
    i2c2_wait_SI();
    return i2c2_status();
}

void i2c2_byte_write(int8_t data){
    int status = i2c2_do_write(data); //Put data on the bus

    switch(status) {
        case 0x18:		//"Slave Address + Write has been transmitted, ACK has been received. The first data byte will be transmitted".
        case 0x28:      //"Data has been transmitted, ACK has been received. If the transmitted data was the lastdata byte then transmit a STOP condition, otherwise transmit the next data byte".
            break;
        case 0x40:      //"Previous state was State 08 or State 10. Slave Address + Read has been transmitted,ACK has been received. Data will be received and ACK returned".
            break;
        default:
            break;
    }

}

int8_t i2c2_byte_read(int last){
    return (i2c2_do_read(last));
}

int8_t i2c2_do_read(int8_t last) {
    // we are in state 0x40 (SLA+R tx'd) or 0x50 (data rx'd and ack)
    if(last) {
        i2c2_conclr( 0, 0, 0, 1); // send a NOT ACK
    }else {
        i2c2_conset(0, 0, 0, 1); // send a ACK
    }

    //Byte is ready to be received
    i2c2_clear_SI();

    //Wait for the byte to arrive
    i2c2_wait_SI();

    // return the data
    return (LPC_I2C2->I2DAT);
}




