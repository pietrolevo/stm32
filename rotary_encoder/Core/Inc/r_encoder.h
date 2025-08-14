/*
    file: r_encoder.h
    author: pietro levo
*/

#ifndef __R_ENCODER_H__
#define __R_ENCODER_H__

#include "stm32f4xx_hal.h"

void RE_init(void);
uint16_t RE_getRawCount(void);
uint8_t RE_getPos(void);
int8_t RE_getDirection(void);


#endif