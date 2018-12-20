/******************************************************
* TextLCD header file				      		                *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef MBED_TEXTLCD_H
#define MBED_TEXTLCD_H

    void lcd_init();

    /** Locate to a screen column and row
     *
     * @param column  The horizontal position from the left, indexed from 0
     * @param row     The vertical position from the top, indexed from 0
     */
    void lcd_locate(int column, int row);

    /** Clear the screen and locate to 0,0 */
    void lcd_cls();

    void lcd_character(int column, int row, int c);

    void lcd_setText(char* text);

    int lcd_putc(int value);

    int lcd_address(int column, int row);
    void lcd_writeByte(int value);
    void lcd_writeCommand(int command);
    void lcd_writeData(int data);
#endif
