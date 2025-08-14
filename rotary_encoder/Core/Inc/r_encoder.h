/*
    file: r_encoder.h
    author: pietro levo
*/

#ifndef __R_ENCODER_H__
#define __R_ENCODER_H__

#include "stm32f4xx_hal.h"

#define MIN_P 1
#define MAX_P 10
#define TICKS_PER_STEP 8

typedef struct {
    TIM_HandleTypeDef *htim;
    uint16_t base_count;
} RE_struct;

void RE_init(RE_struct *encoder, TIM_HandleTypeDef *htim);
uint16_t RE_getRawCount(RE_struct *encoder);
uint8_t RE_getPos(RE_struct *encoder);
int8_t RE_getDirection(RE_struct *encoder);


#endif