/* 
    file: lcd1602.h
    author: pietro levo
*/

#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "stm32f4xx_hal.h"


#define LCD_CLEAR_DISPLAY        0x01 
#define LCD_RETURN_HOME          0x02  
#define LCD_ENTRY_MODE_SET       0x06
#define LCD_DISPLAY_ON           0x0C
#define LCD_FUNCTION_SET         0x38
#define LCD_SET_DDRAM_ADDR       0x80


typedef struct {
    GPIO_TypeDef* RS_Port;
    uint16_t RS_PIN;
    GPIO_TypeDef* E_Port;
    uint16_t E_PIN;
    GPIO_TypeDef* Data_Port[8];
    uint16_t Data_Pin[8];
} LCD1602_HandleTypeDef;


void LCD_Init(LCD1602_HandleTypeDef* lcd);
void LCD_Clear(LCD1602_HandleTypeDef* lcd);
void LCD_SendCmd(LCD1602_HandleTypeDef* lcd, uint8_t cmd);
void LCD_SendData(LCD1602_HandleTypeDef* lcd, uint8_t data);
void LCD_Print(LCD1602_HandleTypeDef* lcd, const char* str);
void LCD_SetCursor(LCD1602_HandleTypeDef* lcd, uint8_t row, uint8_t col);

#endif
