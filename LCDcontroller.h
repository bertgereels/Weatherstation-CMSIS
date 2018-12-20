/******************************************************
* LCD Control header file				      		            *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

/**
 * Print a formatted string to the LCD.
 * Fuction initalises the LCD if necessary.
 * @param format A formatted string.
 */
void lcd_printf(const char *format, ...);
//int countPercent(const char *format);

#endif
