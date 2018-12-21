/******************************************************
* TextLCD header file				                  *
*                                                     *
* Authors:  Klaas Govaerts                            *
* 			Simon Ford                                *
*                                                     *
* Source used:                                        *
* https://os.mbed.com/users/simon/code/TextLCD/       *
*                                                     *
*                                                     *
******************************************************/

#ifndef MBED_TEXTLCD_H
#define MBED_TEXTLCD_H

//Provide interface
	/**
 	 * Initialise all components needed for communication with the LCD, on the Education Board.
 	 */
    void lcd_init();

    /**
     * Print text to the LCD on the Education board. Keep in mind that the LCD is 16x2.
     * @param text		A null terminated string, that will be written to the LCD.
     */
    void lcd_setText(char* text);


//Functions used for internal operation.
    /**
     * Locate to a screen column and row on the LCD.
     *
     * @param column	Horizontal position. Leftmost index is 0. Value can be between 0 and 15.
     * @param row     	Vertical position. First line has index 0. Value can be between 0 and 1.
     */
    void lcd_locate(int column, int row);


    /**
     * Clear the screen and locate to 0,0 (on the LCD).
     */
    void lcd_cls();

    /**
     * Write a character to a specified location on the LCD.
     *
     * @param column 	Horizontal position. Leftmost index is 0. Value can be between 0 and 15.
     * @param row 		Vertical position. First line has index 0. Value can be between 0 and 1.
     * @param c			The character that will be written to specified position.
     */
    void lcd_character(int column, int row, int c);

    /**
     * Put a character on the next position of the LCD.
     *
     * @param value 	The character that will be written.
     */
    int lcd_putc(int value);

    /**
     * Lookup the address of a specific column and row on the LCD.
     *
     * @param column 	Horizontal position. Leftmost index is 0. Value can be between 0 and 15.
     * @param row 		Vertical position. First line has index 0. Value can be between 0 and 1.
     * @return 			The memory address corresponding to this column and row.
     */
    int lcd_address(int column, int row);

    /**
     * Write a byte to the LCD.
     * Byte will be written as 2 separate nibbles.
     *
     * @param value 	The 8 least significant bits will be written.
     */
    void lcd_writeByte(int value);

    /**
     * Write a command to the LCD.
     *
     * @param command 	Command that will be written to LCD. Refer to the HD44780U datasheet for the syntax.
     */
    void lcd_writeCommand(int command);

    /**
     * Write data to the LCD.
     *
     * @param data 		The data will that will be written to the memory of the LCD.
     */
    void lcd_writeData(int data);
#endif
