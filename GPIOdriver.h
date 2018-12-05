#ifndef GPIODRIVER_H
#define GPIODRIVER_H
#include <stdint.h>
#include "LPC17xx.h"

enum Buttons {
    SW301 = 5,
    SW304 = 6,
    SW306 = 7,
    SW308 = 8,
    SW310 = 9,
    SW312 = 10,
    SW314 = 11,
    SW316 = 12,

    SW318 = 13,
    SW320 = 14,
    SW322 = 15,
    SW323 = 16,
    SW324 = 17,
    SW325 = 18,
    SW326 = 19,
    SW328 = 20,

    SW302 = 21,
    SW305 = 22,
    SW307 = 23,
    SW309 = 24,
    SW311 = 25,
    SW313 = 26,
    SW315 = 27,
    SW317 = 28,

    SW319 = 29,
    SW321 = 30,
};

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