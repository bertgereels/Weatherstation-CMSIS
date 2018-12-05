#include "ICdriver.h"
#include "GPIOdriver.h"

uint8_t CHARACTER_LCD_RS=0;
uint8_t CHARACTER_LCD_ENABLE=0;

void IC502_init(){
    mbedPins_init(19,4);
}

void IC502_write(uint8_t value){
    mbedPins_write(value,19,4);
}

void IC501_init(uint8_t value){
    mbedPins_init(15,4);
    mbedPins_write(0,15,4);
}

void lcd_rs(uint8_t rs){
    lcd_rs_e(rs,CHARACTER_LCD_ENABLE);
}

void lcd_e(uint8_t e){
    lcd_rs_e(CHARACTER_LCD_RS,e);
}


void lcd_rs_e(uint8_t rs,uint8_t e){
    CHARACTER_LCD_RS=rs;
    CHARACTER_LCD_ENABLE=e;
    IC502_init();
    if((rs)&&(e)){
        IC502_write(6);
    }
    if((rs)&&(!e)){
        IC502_write(7);
    }
    if((!rs)&&(e)){
        //LPCpin_init(1,18);
        //LPCpin_on(1,18);
        IC502_write(4);
    }
    if((!rs)&&(!e)){
        IC502_write(5);
    }
}