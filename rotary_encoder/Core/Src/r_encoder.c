/*
    file: r_encoder.c
    author: pietro levo
*/

#include "r_encoder.h"
#include "tim.h"

#define MIN_P 1
#define MAX_P 10

void RE_init(void) {
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
}


uint16_t RE_getRawCount(void) {
    return __HAL_TIM_GET_COUNTER(&htim1);
}


uint8_t RE_getPos(void) {
    uint16_t raw_count = __HAL_TIM_GET_COUNTER(&htim1);
    raw_count = - raw_count;
    uint16_t pos = (raw_count / 8) + 1;

    if (pos < MIN_P || (pos > MAX_P && (RE_getDirection == (int8_t)-1))) pos = MIN_P;
    if (pos > MAX_P) pos = MAX_P;

    return (uint8_t)pos;
}


int8_t RE_getDirection(void) {
    int8_t dir = 1;
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1)) {
        dir = 1;
        return dir;
    } else {
        dir = -1;
        return dir;
    }
}