/******************************************************
* SerialWriter header file				      		          *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef SERIALWRITER_H
#define SERIALWRITER_H

//Provide interface
	/**
	 * Initialise pins 15,16,17 and 18 as GPIO output.
	 * Function also enables the output of IC508
	 * (this is a shift register on the Education Board).
	 */
	void shiftRegister_init();

	/**
	 * Write 4 bits (=a nibble) to IC508.
	 * The nibble will be written to BUS_D7...BUS_D4. (See schematics)
	 *
	 * @param byte 		The 4 least significant bits of the input will be written.
	 */
	void shiftRegister_write4bits(uint8_t byte);

//Functions used for internal operation.
	/**
	 * Write a byte to IC508.
	 *
	 * @param byte 		The byte that will be written.
	 */
	void shiftRegister_writeByte(uint8_t byte);

	/**
	 * Write a single bit to IC508.
	 *
	 * @param value 	The value you want to write. A zero represents a low voltage, all other values represent a high voltage.
	 */
	void shiftRegister_writeBit(uint8_t bit);

#endif
