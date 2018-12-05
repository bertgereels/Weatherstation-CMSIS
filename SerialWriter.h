#ifndef SERIALWRITER_H
#define SERIALWRITER_H

void shiftRegister_init();
void shiftRegister_writeByte(uint8_t byte);
void shiftRegister_write4bits(uint8_t byte);
void shiftRegister_writeBit(uint8_t bit);

#endif