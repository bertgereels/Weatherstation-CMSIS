/******************************************************
* IC Driver header file				      		              *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef ICDRIVER_H
#define ICDRIVER_H

#include <stdint.h>

//Provide interface
	/**
	 * Initialise pins 19,20,21 and 22 as GPIO output.
	 * Those pins are needed for communication with IC502 on the Education Board.
	 */
	void IC502_init();

	/**
	 * Write a value to IC502 on the MBED education board.
	 * The 4 least significant bits will be written.
	 */
	void IC502_write(uint8_t value);

	/**
	 * Initialise pins 15,16,17 and 18 as GPIO output.
	 * Those pins are needed for communication with IC501 on the Education Board.
	 */
	void IC501_init(uint8_t value);

	/**
	 * Write a value to the RS input of the LCD.
	 * Before calling this function, call IC502_init.
	 * @param rs The desired RS input of the LCD.
	 */
	void lcd_rs(uint8_t rs);

	/**
	 * Write a value to the ENABLE input of the LCD.
	 * Before calling this function, call IC502_init.
	 * @param e The desired ENABLE input of the LCD.
	 */
	void lcd_e(uint8_t e);

//Functions used for internal operation.
	/**
	 * Write a value to both the RS and ENABLE input of the LCD.
	 * Before calling this function, call IC502_init.
	 * @param rs The desired RS input of the LCD.
	 * @param e The desired ENABLE input of the LCD.
	 */
	void lcd_rs_e(uint8_t rs,uint8_t e);

#endif
