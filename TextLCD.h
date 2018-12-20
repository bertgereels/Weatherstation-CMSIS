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
 	 * Initialise all compontents needed for communication with the LCD, on the mbed Education board.
 	 */
    void lcd_init();

    /**
     * Print a text to the LCD.
     * @param text A null terminated string, that will be written to the LCD.
     */
    void lcd_setText(char* text);


//Functions used for internal operation.
    /** Locate to a screen column and row on the LCD.
     *
     * @param column  The horizontal position from the left, indexed from 0
     * @param row     The vertical position from the top, indexed from 0
     */
    void lcd_locate(int column, int row);


    /**
     * Clear the screen and locate to 0,0 (on the LCD).
     */
    void lcd_cls();

    /**
     * Write a character to a specified location on the LCD.
     * @param column The column of the character
     * @param row The row of the character
     * @param c The character that will be written to specified position.
     */
    void lcd_character(int column, int row, int c);

    /**
     * Put a charcter on the next position of the LCD.
     * @param c The character that will be written.
     */
    int lcd_putc(int value);

    /**
     * Lookup the address of a specifc column and row on the LCD.
     * @param column The column of the character (Can be between 0 and 15).
     * @param row The row of the character (Can be between 0 and 1).
     * @return The memory address corresponding to this column and row.
     */
    int lcd_address(int column, int row);

    /**
     * Write a byte to the LCD.
     */
    void lcd_writeByte(int value);

    /**
     * Write a command to the LCD.
     */
    void lcd_writeCommand(int command);

    /**
     * Write data to the LCD.
     */
    void lcd_writeData(int data);
#endif
