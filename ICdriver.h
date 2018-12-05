#ifndef ICDRIVER_H
#define ICDRIVER_H

#include <stdint.h>

void IC502_init();
void IC502_write(uint8_t value);
void IC501_init(uint8_t value);
void lcd_rs(uint8_t rs);
void lcd_e(uint8_t e);
void lcd_rs_e(uint8_t rs,uint8_t e);

#endif