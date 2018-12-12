#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include "LPC17xx.h"

void unixTimer_init(uint32_t unixTime);
void unixTimer_start();
uint32_t unixTimer_getValue();

#endif
