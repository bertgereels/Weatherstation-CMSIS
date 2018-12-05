#include "ICdriver.h"
#include "delay.h"

void lcd_rs_e_test(){
        while(1){
        lcd_rs_e(0,0);
        wait_ms(1000);
        lcd_rs(1);
        wait_ms(1000);
        lcd_rs(0);
        wait_ms(1000);
        lcd_e(1);
        wait_ms(1000);
        lcd_e(0);
        wait_ms(1000);
    }
}