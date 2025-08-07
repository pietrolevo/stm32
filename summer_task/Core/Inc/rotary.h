/*
    file: rotary.h
    author: pietro levo
*/

#ifndef __ROTARY_H__
#define __ROTARY_H__

#include "stm32f4xx_hal.h"

#define BUF_LEN 32

void rotaryInit(ADC_HandleTypeDef *hadc);
uint8_t rotaryRead(void);
uint16_t rotaryGetRawADC(void);

#endif