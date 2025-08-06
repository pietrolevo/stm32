/* 
    file: lcd1602.c
    author: pietro levo
*/

#include "lcd1602.h"

void LCD_Init(LCD1602_HandleTypeDef* lcd) {
    HAL_Delay(50);
    
    LCD_SendCmd(lcd, LCD_FUNCTION_SET);
    LCD_SendCmd(lcd, LCD_DISPLAY_ON);
    LCD_SendCmd(lcd, LCD_CLEAR_DISPLAY);
    LCD_SendCmd(lcd, LCD_ENTRY_MODE_SET);

    HAL_Delay(2);
}


void LCD_Clear(LCD1602_HandleTypeDef* lcd) {
    LCD_SendCmd(lcd, LCD_CLEAR_DISPLAY);
    HAL_Delay(2);
}


void LCD_SendCmd(LCD1602_HandleTypeDef* lcd, uint8_t cmd) {
    HAL_GPIO_WritePin(lcd->RS_Port, lcd->RS_Pin, GPIO_PIN_RESET);

    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(lcd->Data_Port[i], lcd->Data_Pin[i], (cmd >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}


void LCD_SendData(LCD1602_HandleTypeDef* lcd, uint8_t data) {
    HAL_GPIO_WritePin(lcd->RS_Port, lcd->RS_Pin, GPIO_PIN_SET);

    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(lcd->Data_Port[i], lcd->Data_Pin[i], (data >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}


void LCD_Print(LCD1602_HandleTypeDef* lcd, const char* str) {
    while (*str) {
        LCD_SendData(lcd, (uint8_t)(*str));
        str++;
    }
}


void LCD_SetCursor(LCD1602_HandleTypeDef* lcd, uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : (0x40 + col);
    LCD_SendCmd(lcd, LCD_SET_DDRAM_ADDR | address);
}

