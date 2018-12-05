#ifndef I2C_H_
#define I2C_H_

#include "LPC17xx.h"
#include "delay.h"

/**
 *  Initializes the I2C2 engine
 */
void i2c2_init(void);

/**
 *	Controls the I2CONCLR register.
 *	Setting a bit in this register clears it in the I2C control register.
 *
 *  @param The new start bit value
 *  @param The new stop bit value
 *  @param The new interrupt bit value
 *  @param The new acknowledge bit value
 */
void i2c2_conclr(int, int, int, int);

/**
 *	Controls the I2CONSETregister.
 *	Setting a bit in this register sets it in the I2C control register.
 *
 *  @param The new start bit value
 *  @param The new stop bit value
 *  @param The new interrupt bit value
 *  @param The new acknowledge bit value
 */
void i2c2_conset(int, int, int, int);

/**
 *  Wait until SI bit is set.
 */
void i2c2_wait_SI(void);

/**
 *  Sets the SI bit in the I2CONCLR register, this clears it in I2C control register.
 */
void i2c2_set_SI(void);

/**
 *  Clears the SI bit in the I2CONCLR register.
 */
void i2c2_clear_SI(void);

/**
 *  Enables the I2C2 interface.
 */
void i2c2_interface_enable(void);

/**
 *  Gets the current status of the I2C2 engine
 *
 *  @return the status of the I2C2 engine (should be interpreted as a hex value!)
 */
int i2c2_status(void);

/**
 *  Starts the I2C2 engine
 */
void i2c2_start(void);

/**
 *  Stops the I2C2 engine
 */
void i2c2_stop(void);

/**
 *  Writes the data to the I2DAT shift register
 *	I2DAT is a shift register that puts byte bit by bit on the bus, from right to left (MSB first).
 *
 *	@param The value (data) that should be put on the bus.
 *
 *	@return The status of the I2C2 engine (should be interpreted as a hex value!)
 */
int i2c2_do_write(int8_t value);

/**
 *	Puts a single byte on the I2C bus
 *
 *  @param The data to put on the bus.
 *
 */
void i2c2_byte_write(int8_t data);

/**
 *	Reads data from the I2DAT shift register.
 *
 *  @param Indicator if this is the last byte to receive.
 *
 */
int8_t i2c2_do_read(int8_t last);

/**
 *	Reads a single byte from the I2C bus
 *
 *  @param Indicator to know if this is the last byte to read from the bus
 */
int8_t i2c2_byte_read(int last);


#endif
