/******************************************************
* GPIO Driver header file				      		            *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef GPIODRIVER_H
#define GPIODRIVER_H
#include <stdint.h>
#include "LPC17xx.h"

enum Buttons {
    SW301 = 5,
    SW304 = 6,
    SW306 = 7,
    SW308 = 8,
    SW310 = 9,
    SW312 = 10,
    SW314 = 11,
    SW316 = 12,

    SW318 = 13,
    SW320 = 14,
    SW322 = 15,
    SW323 = 16,
    SW324 = 17,
    SW325 = 18,
    SW326 = 19,
    SW328 = 20,

    SW302 = 21,
    SW305 = 22,
    SW307 = 23,
    SW309 = 24,
    SW311 = 25,
    SW313 = 26,
    SW315 = 27,
    SW317 = 28,

    SW319 = 29,
    SW321 = 30,
};

//Provide interface
	/**
	 * Initialise a specific mbedPin as GPIO output.
	 *
	 * @param mbedPin	The number of the mbed pin.
	 */
	void mbedPin_init(uint8_t mbedPin);

	
	/**
	 * Write a high voltage to a specific mbedPin.
	 *
	 * @param mbedPin	The number of the mbed pin.
	 */
	void mbedPin_on(uint8_t mbedPin);

	
	/**
	 * Write a low voltage to a specific mbedPin.
	 *
	 * @param mbedPin	The number of the mbed pin.
	 */
	void mbedPin_off(uint8_t mbedPin);

	
	/**
	 * Write a value of choice to a specific mbedPin.
	 *
	 * @param value		The value you want to write.
	 * 					A zero represents a low voltage.
	 *					All other values represent a high voltage.
	 * @param mbedPin	The number of the mbed pin.
	 */
	void mbedPin_write(int value,uint8_t mbedPin);

	
	/**
	 * Initialise a specific lpc pin as GPIO output.
	 *
	 * @param port 		The port number of the lpc pin
	 * 					(Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin
	 * 					(Can range from 0 up to and including 31)
	 */
	void lpcPin_init(uint8_t port, uint8_t pin);

	
	/**
	 * Write a high voltage to a specific lpc pin.
	 *
	 * @param port 		The port number of the lpc pin
	 * 					(Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin
	 * 					(Can range from 0 up to and including 31)
	 */
	void lpcPin_on(uint8_t port, uint8_t pin);

	
	/**
	 * Write a low voltage to a specific lpc pin.
	 *
	 * @param port 		The port number of the lpc pin
	 * 					(Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin
	 * 					(Can range from 0 up to and including 31)
	 */
	void lpcPin_off(uint8_t port, uint8_t pin);

	
	/**
	 * Write a value of choice to a specific lpc pin.
	 *
	 * @param value 	The value you want to write.
	 * 					A zero represents a low voltage
	 *					All other values represent a high voltage.
	 * @param port 		The port number of the lpc pin
	 * 					(Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin
	 * 					(Can range from 0 up to and including 31)
	 */
	void lpcPin_write(int value,uint8_t port, uint8_t pin);

	
	/**
	 * Write to multiple consecutive mbed pins at once.
	 *
	 * @param offset 	The number of the first mbed pin.
	 * @param length 	The amount of consecutive mbed pins.
	 * @param value 	The value you want to write.
	 * 					The LSB will be written to the first mbed pin.
	 */
	void mbedPins_write(uint32_t value,uint8_t offset,uint8_t length);

	
	/**
	 * Initialise multiple consecutive mbed pins as GPIO output at once.
	 *
	 * @param offset 	The number of the first mbed pin.
	 * @param length 	The amount of consecutive mbed pins.
	 */
	void mbedPins_init(uint8_t offset,uint8_t length);

	
	/**
	 * Initialize lpc pin as input.
	 * Pin is input by default, unless previously changed to output mode.
	 *
	 * @param port 		The port number of the lpc pin
	 * 					(Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin
	 * 					(Can range from 0 up to and including 31)
	 */
	void lpcPin_initIn(uint8_t port, uint8_t pin);

	
	/**
	 * Read the logical value of a specific lpc pin.
	 *
	 * @param port 		The port number of the lpc pin
	 * 					(Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin
	 * 					(Can range from 0 up to and including 31)
	 * @return 			1 if high voltage, 0 if low voltage.
	 */
	uint8_t lpcPin_read(uint8_t port, uint8_t pin);

	
	/**
	 * Read the logical value of a specific mbed pin.
	 *
	 * @param mbedPin 	The number of the mbed pin.
	 * @return 			1 if high voltage, 0 if low voltage.
	 */
	uint8_t mbedPin_read(uint8_t mbedPin);

	
//Functions used for internal operation.
	/**
	 * This function translates an mbed pin to it's respective lpc port number.
	 *
	 * @param mbedPin 	The number of the mbed pin.
	 * @return 			The port number of the lpc pin.
	 */
	uint8_t mbedPin_getLPCport(uint8_t mbedPin);

	
	/**
	 * This function translates an mbed pin to it's respective lpc pin number.
	 *
	 * @param mbedPin	The number of the mbed pin.
	 * @return 			The pin number of the lpc pin.
	 */
	uint8_t mbedPin_getLPCpin(uint8_t mbedPin);

	
	/**
	 * Check if a specific mbedPin is a valid GPIO output.
	 *
	 * @param mbedPin	The number of the mbed pin. (Can range from 5 up to and including 32)
	 * @return			True if valid, false if not valid.
	 */
	int mbedPin_isValid(uint8_t mbedPin);

	
	/**
	 * Returns a pointer to a LPC_GPIO_TypeDef for a specific LPC port number.
	 *
	 * @param port 		The lpc port number (Can range from 0 up to and including 4)
	 * @return 			A pointer to the corresponding LPC_GPIO_TypeDef.
	 */
	LPC_GPIO_TypeDef* getGPIOTypeDef(uint8_t port);

	
	/**
	 * Check if port number is valid.
	 *
	 * @param port 		The lpc port number (Can range from 0 up to and including 4)
	 * @return 			True if lpc port number is valid.
	 */
	int lpcPort_isValid(uint8_t port);

	
	/**
	 * Check if pin number is valid.
	 *
	 * @param pin 		The lpc pin number (Can range from 0 up to and including 31)
	 * @return 			True if lpc pin number is valid.
	 */
	int lpcPin_isValid(uint8_t pin);

	
	/**
	 * Check if a lpc port number and pin number are valid.
	 *
	 * @param port 		The port number of the lpc pin (Can range from 0 up to and including 4)
	 * @param pin 		The pin number of the lpc pin (Can range from 0 up to and including 31)
	 * @return 			True if both port number and pin number are valid.
	 */
	int lpcPortPin_isValid(uint8_t port,uint8_t pin);

	
	/**
	 * Return the bit at a given index of an uint32_t.
	 *
	 * @param input 	Any uint32_t.
	 * @param index 	The index of the bit. Index 0 means the LSB.
	 * @return 			Either 0 or 1, based on the bit at given index in the input.
	 */
	uint8_t bitAtRightIndex(uint32_t input,uint8_t index);

#endif
