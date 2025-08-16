/*
    file: can_func.c
    author: pietro levo
*/

#include "can_func.h"
#include "usart.h"
#include "can.h"
#include "main.h"
#include <stdio.h>

CAN_TxHeaderTypeDef TxHeader;
uint8_t TxData[8];
uint32_t TxMailbox;

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
uint8_t data_avlble;



void CAN_ErrorHandler(CAN_HandleTypeDef *hcan) {
    char buf[20];
    uint32_t error = HAL_CAN_GetError(hcan);

    #define tmp_printf(X)                                           \
    do {                                                                   \
        HAL_UART_Transmit(&huart1, (uint8_t *)(X), strlen(X), HAL_MAX_DELAY); \
        HAL_UART_Transmit(&huart1, (uint8_t *)("\r\n"), strlen("\r\n"), HAL_MAX_DELAY); \
    } while (0)
 
    if (error & HAL_CAN_ERROR_EWG)
        tmp_printf("Protocol Error Warning");
    if (error & HAL_CAN_ERROR_EPV)
        tmp_printf("Error Passive");
    if (error & HAL_CAN_ERROR_BOF)
        tmp_printf("Bus-off Error");
    if (error & HAL_CAN_ERROR_STF)
        tmp_printf("Stuff Error");
    if (error & HAL_CAN_ERROR_FOR)
        tmp_printf("Form Error");
    if (error & HAL_CAN_ERROR_ACK)
        tmp_printf("ACK Error");
    if (error & HAL_CAN_ERROR_BR)
        tmp_printf("Bit Recessive Error");
    if (error & HAL_CAN_ERROR_BD)
        tmp_printf("Bit Dominant Error");
    if (error & HAL_CAN_ERROR_CRC)
        tmp_printf("CRC Error");
    if (error & HAL_CAN_ERROR_RX_FOV0)
        tmp_printf("FIFO0 Overrun");
    if (error & HAL_CAN_ERROR_RX_FOV1)
        tmp_printf("FIFO1 Overrun");
    if (error & HAL_CAN_ERROR_TX_ALST0)
        tmp_printf("Mailbox 0 TX failure (arbitration lost)");
    if (error & HAL_CAN_ERROR_TX_TERR0)
        tmp_printf("Mailbox 0 TX failure (tx error)");
    if (error & HAL_CAN_ERROR_TX_ALST1)
        tmp_printf("Mailbox 1 TX failure (arbitration lost)");
    if (error & HAL_CAN_ERROR_TX_TERR1)
        tmp_printf("Mailbox 1 TX failure (tx error)");
    if (error & HAL_CAN_ERROR_TX_ALST2)
        tmp_printf("Mailbox 2 TX failure (arbitration lost)");
    if (error & HAL_CAN_ERROR_TX_TERR2)
        tmp_printf("Mailbox 2 TX failure (tx error)");
    if (error & HAL_CAN_ERROR_TIMEOUT)
        tmp_printf("Timeout Error");
    if (error & HAL_CAN_ERROR_NOT_INITIALIZED)
        tmp_printf("Peripheral not initialized");
    if (error & HAL_CAN_ERROR_NOT_READY)
        tmp_printf("Peripheral not ready");
    if (error & HAL_CAN_ERROR_NOT_STARTED)
        tmp_printf("Peripheral not strated");
    if (error & HAL_CAN_ERROR_PARAM)
        tmp_printf("Parameter Error");
     
    uint16_t rec = (uint16_t)((hcan->Instance->ESR && CAN_ESR_REC_Msk) >> CAN_ESR_REC_Pos);
    uint16_t tec = (uint16_t)((hcan->Instance->ESR && CAN_ESR_TEC_Msk) >> CAN_ESR_TEC_Pos);

    sprintf(buf,"rec %u, tec %u",rec,tec);
    tmp_printf(buf);

    HAL_CAN_ResetError(hcan);
}



void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
        Error_Handler();
    }
    data_avlble = 1;
}


/*void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {

}
void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan) {

}
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan) {

}
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan) {

}
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan) {

}
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan) {

}*/


void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan) {
  if(hcan == &hcan1){
    CAN_ErrorHandler(hcan);
  }
}
