#ifndef GPIODRIVER_H
#define GPIODRIVER_H
#include <stdint.h>
#include "LPC17xx.h"

void mbedPin_init(uint8_t mbedPin);
void mbedPin_on(uint8_t mbedPin);
void mbedPin_off(uint8_t mbedPin);
void mbedPin_write(int value,uint8_t mbedPin);
int isValidPin(uint8_t mbedPin);
void LPCpin_init(uint8_t port, uint8_t pin);
void LPCpin_on(uint8_t port, uint8_t pin);
void LPCpin_off(uint8_t port, uint8_t pin);
void LPCpin_write(int value,uint8_t port, uint8_t pin);
uint8_t getLPCport(uint8_t mbedPin);
uint8_t getLPCpin(uint8_t mbedPin);
void mbedPins_write(uint32_t value,uint8_t offset,uint8_t length);
void mbedPins_init(uint8_t offset,uint8_t length);
void LPCpin_initIn(uint8_t port, uint8_t pin);
uint8_t LPCpin_read(uint8_t port, uint8_t pin);
uint8_t mbedPin_read(uint8_t mbedPin);
LPC_GPIO_TypeDef* getGPIOTypeDef(uint8_t port);
int IsValidLpcPort(uint8_t port);
int IsValidLpcPin(uint8_t pin);
int IsValidLpcPortPin(uint8_t port,uint8_t pin);
uint8_t bitAtRightIndex(uint32_t input,uint8_t index);

#endif