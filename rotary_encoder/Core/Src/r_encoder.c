/*
    file: r_encoder.c
    author: pietro levo
*/

#include "r_encoder.h"
#include "tim.h"

void RE_init(void) {
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
}

uint8_t RE_getPos(void) {
    uint16_t raw_count = __HAL_TIM_GET_COUNTER(&htim1);

    return raw_count;
}
