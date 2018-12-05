#ifndef I2C_H_
#define I2C_H_

#include "LPC17xx.h"



/**
 *  Initializes the I2C2 engine
 */
void i2c2_init(void);

/**
 *	Controls the I2CONCLR register
 *
 *  @param The new start bit value
 *  @param The new stop bit value
 *  @param The new interrupt bit value
 *  @param The new acknowledge bit value
 */
void i2c2_conclr(int, int, int, int);

/**
 *	Controls the I2CONSETregister
 *
 *  @param The new start bit value
 *  @param The new stop bit value
 *  @param The new interrupt bit value
 *  @param The new acknowledge bit value
 */
void i2c2_conset(int, int, int, int);

//todo
int i2c2_wait_SI(void);

/**
 *  Sets the SI bit in the I2CONCLR register
 */
void i2c2_set_SI(void);

/**
 *  Clears the SI bit in the I2CONCLR register
 */
void i2c2_clear_SI(void);

/**
 *  Enables the I2C2 interface
 */
void i2c2_interface_enable(void);

/**
 *  Gets the current status of the I2C2 engine
 */
int i2c2_status(void);

/**
 *  Starts the I2C2 engine
 */
int i2c2_start(void);

/**
 *  Stops the I2C2 engine
 */
int i2c2_stop(void);

//todo
int i2c2_do_write(int value, uint8_t addr);

/**
 *	Puts a single byte on the I2C bus
 *
 *  @param The data to put on the bus
 */
int i2c2_byte_write(int data);


int i2c2_do_read(int last);

/**
 *	Reads a single byte from the I2C bus
 *
 *  @param Indicator to know if this is the last byte to read from the bus
 */
int i2c2_byte_read(int last);


#endif
