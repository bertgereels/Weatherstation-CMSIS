/******************************************************
* TextLCD c code file				                  *
*                                                     *
* Authors:  Klaas Govaerts                            *
* 			Simon Ford                                *
*                                                     *
* Source used:                                        *
* https://os.mbed.com/users/simon/code/TextLCD/       *
*                                                     *
*                                                     *
******************************************************/

#include "TextLCD.h"

/**
 * Used functions in delay.h:
 * void wait_ms(int ms);
 * void wait_us(int us);
 */
#include "delay.h"

/**
 * Used functions in SerialWriter.h:
 * void shiftRegister_init();
 * void shiftRegister_write4bits(uint8_t byte);
 */
#include "SerialWriter.h"

/**
 * Used functions in ICdriver:
 * void lcd_e(uint8_t e);
 * void lcd_rs(uint8_t rs);
 * void lcd_rs_e(uint8_t rs,uint8_t e);
 */
#include "ICdriver.h"

int _LCDcolumn;
int _LCDrow;

enum pins {
    ePin = 8,
    rsPin = 7,
};

void lcd_init() {
    lcd_rs_e(0,1);
    shiftRegister_init();
    //mbedPins_init(15,4); //TODO
    //mbedPin_init(ePin);
    //mbedPin_init(rsPin);

    //mbedPin_on(ePin);
    //mbedPin_off(rsPin);            // command mode

    wait_ms(15);        // Wait 15ms to ensure powered up

    // send "Display Settings" 3 times (Only top nibble of 0x30 as we've got 4-bit bus)
    for (int i=0; i<3; i++) {
        lcd_writeByte(0x3);
        wait_us(1640); // this command takes 1.64ms, so wait for it
    }
    lcd_writeByte(0x2);     // 4-bit mode
    wait_us(40);    // most instructions take 40us

    lcd_writeCommand(0x28); // Function set 001 BW N F - -
    lcd_writeCommand(0x0C);
    lcd_writeCommand(0x6);  // Cursor Direction and Display Shift : 0000 01 CD S (CD 0-left, 1-right S(hift) 0-no, 1-yes
    lcd_cls();
}

void lcd_character(int column, int row, int c) {
    int a = lcd_address(column, row);
    lcd_writeCommand(a);
    lcd_writeData(c);
}

void lcd_cls() {
    lcd_writeCommand(0x01); // cls, and set cursor to 0
    wait_us(1640);     // This command takes 1.64 ms
    lcd_locate(0, 0);
}

void lcd_locate(int column, int row) {
    _LCDcolumn = column;
    _LCDrow = row;
}

int lcd_putc(int value) {
    if (value == '\n') {
        _LCDcolumn = 0;
        _LCDrow++;
        if (_LCDrow >= 2) {
            _LCDrow = 0;
        }
    } else {
        lcd_character(_LCDcolumn, _LCDrow, value);
        _LCDcolumn++;
        if (_LCDcolumn >= 16) {
            _LCDcolumn = 0;
            _LCDrow++;
            if (_LCDrow >= 2) {
                _LCDrow = 0;
            }
        }
    }
    return value;
}

void lcd_setText(char* text){
    lcd_cls();
    for(int i=0;i<34;i++){
        if(text[i]=='\0'){
            break;
        } else {
            lcd_putc((int) text[i]);
        }
    }
}

void lcd_writeByte(int value) {
    //mbedPins_write(value >> 4,15,4); //TODO
    shiftRegister_write4bits(value >> 4);
    //_d = value >> 4;
    wait_us(40); // most instructions take 40us
    //mbedPin_off(ePin);
    lcd_e(0);
    wait_us(40);
    //mbedPin_on(ePin);
    lcd_e(1);
    //mbedPins_write(value >> 0,15,4); //TODO
    shiftRegister_write4bits(value >> 0);
    //_d = value >> 0;
    wait_us(40);
    //mbedPin_off(ePin);
    lcd_e(0);
    wait_us(40);  // most instructions take 40us
    //mbedPin_on(ePin);
    lcd_e(1);
}

void lcd_writeCommand(int command) {
    //mbedPin_off(rsPin);
    lcd_rs(0);
    lcd_writeByte(command);
}

void lcd_writeData(int data) {
    //mbedPin_on(rsPin);
    lcd_rs(1);
    lcd_writeByte(data);
}

int lcd_address(int column, int row) {
    return 0x80 + (row * 0x40) + column;
}
