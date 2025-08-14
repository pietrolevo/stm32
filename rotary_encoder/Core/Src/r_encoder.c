/*
    file: r_encoder.c
    author: pietro levo
*/

#include "r_encoder.h"

void RE_init(RE_struct *encoder, TIM_HandleTypeDef *htim) {
    encoder->htim = htim;
    encoder->base_count = 0;
    __HAL_TIM_SET_COUNTER(htim, 0);
    HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
}


uint16_t RE_getRawCount(RE_struct *encoder) {
    return __HAL_TIM_GET_COUNTER(encoder->htim);
}



uint8_t RE_getPos(RE_struct *encoder) {
    uint16_t current_count = __HAL_TIM_GET_COUNTER(encoder->htim);

    if (encoder->base_count == 0) {
        encoder->base_count = current_count;
    }

    int16_t delta = (int16_t)(encoder->base_count - current_count);
    int16_t pos = (delta / TICKS_PER_STEP) + 1;

    if (pos < MIN_P) pos = MIN_P;
    if (pos > MAX_P) pos = MAX_P;

    return (uint8_t)pos;
}


int8_t RE_getDirection(RE_struct *encoder) {
    int8_t dir = 1;
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->htim)) {
        dir = 1;
        return dir;
    } else {
        dir = -1;
        return dir;
    }
}