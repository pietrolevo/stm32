/* 
    file: lcd1602.c
    author: pietro levo
*/

#include "lcd1602.h"
#include "string.h"

void LCD_Init(LCD1602_HandleTypeDef* lcd) {
    HAL_Delay(50);
    
    LCD_SendCmd(lcd, LCD_FUNCTION_SET);
    HAL_Delay(2);
    LCD_SendCmd(lcd, LCD_DISPLAY_ON);
    HAL_Delay(2);
    LCD_SendCmd(lcd, LCD_CLEAR_DISPLAY);
    HAL_Delay(5);
    LCD_SendCmd(lcd, LCD_RETURN_HOME);
    HAL_Delay(5);
    LCD_SendCmd(lcd, LCD_ENTRY_MODE_SET);

    HAL_Delay(2);
}


void LCD_Clear(LCD1602_HandleTypeDef* lcd) {
    LCD_SendCmd(lcd, LCD_CLEAR_DISPLAY);
    HAL_Delay(2);
}


void LCD_Clearln(LCD1602_HandleTypeDef* lcd, uint8_t row) {
    if (row > 1) return;

    LCD_SetCursor(lcd, row, 0);
    for (uint8_t i = 0; i < 16; i++) {
        LCD_SendData(lcd, ' ');
    }

    LCD_SetCursor(lcd, row, 0);
}


void LCD_SendCmd(LCD1602_HandleTypeDef* lcd, uint8_t cmd) {
    HAL_GPIO_WritePin(lcd->RS_Port, lcd->RS_PIN, GPIO_PIN_RESET);

    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(lcd->Data_Port[i], lcd->Data_Pin[i], (cmd >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}


void LCD_SendData(LCD1602_HandleTypeDef* lcd, uint8_t data) {
    HAL_GPIO_WritePin(lcd->RS_Port, lcd->RS_PIN, GPIO_PIN_SET);

    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(lcd->Data_Port[i], lcd->Data_Pin[i], (data >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(lcd->E_Port, lcd->E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}


void LCD_Printpg(LCD1602_HandleTypeDef* lcd, const char* str) {
    uint8_t row = 0;
    uint8_t col = 0;

    LCD_SetCursor(lcd, row, col);

    while (*str) {
        LCD_SendData(lcd, (uint8_t)(*str));
        str++;
        col++;

        if (col >= 16) {
            row++;
            if (row >= 2) {
                break;
            }
            col = 0;
            LCD_SetCursor(lcd, row, col);
        }
    }
}


void LCD_Println(LCD1602_HandleTypeDef* lcd, uint8_t row, uint8_t col, const char* str) {
    static size_t offset0 = 0;
    static size_t offset1 = 0;
    size_t len = strlen(str);

    size_t *offset;
    if (row == 0) {
        offset = &offset0;
    } else {
        offset = &offset1;
    }

    LCD_SetCursor(lcd, row, col);
    if (len <= COL - col) {
        for (uint8_t i = 0; i < len; i++) {
            LCD_SendData(lcd, (uint8_t)str[i]);
        }

    } else {
        for (uint8_t i = 0; i < (COL - col); i++) {
            size_t index = *offset + i;
            if (index >= len) {
                index -= len;
            }
            LCD_SendData(lcd, (uint8_t)str[index]);
        }

        (*offset)++;
        if (*offset >= len) {
            *offset = 0;
        } 
    }
}


void LCD_SetCursor(LCD1602_HandleTypeDef* lcd, uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : (0x40 + col);
    LCD_SendCmd(lcd, LCD_SET_DDRAM_ADDR | address);
}

