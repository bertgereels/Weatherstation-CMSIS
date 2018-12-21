/******************************************************
* LCD Control header file				      		            *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

//Provide interface
/**
 * Print a formatted string to the LCD.
 * The fuction initialises the LCD if necessary.
 *
 * @param format 	A formatted string.
 */
void lcd_printf(const char *format, ...);

#endif
