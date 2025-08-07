/* 
    file: rotary.c
    author: pietro levo
*/

#include "rotary.h"

volatile uint16_t adc_buf[BUF_LEN];
volatile uint16_t rawValue = 0;
volatile uint8_t position = 0;

void rotaryInit(ADC_HandleTypeDef *hadc) {
    HAL_ADC_Start_DMA(hadc, (uint32_t*) adc_buf, BUF_LEN);
}


uint16_t rotaryGetRawADC(void) {
    uint32_t sum = 0;
    for (int i = 0; i < BUF_LEN; i++) {
        sum += adc_buf[i];
    }
    rawValue = sum / BUF_LEN;
    return rawValue;
}


uint8_t rotaryRead(void) {
    rawValue = rotaryGetRawADC();
    position = (((rawValue * 9) + 2047) / 4095) + 1;
    return position;
}