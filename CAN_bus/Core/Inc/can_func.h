/*
    file: can_func.h
    author: pietro levo
*/

#ifndef __CAN_FUNC_H__
#define __CAN_FUNC_H__

#include "main.h"

extern CAN_TxHeaderTypeDef TxHeader;
extern uint8_t TxData[8];
extern uint32_t TxMailbox;

extern CAN_RxHeaderTypeDef RxHeader;
extern uint8_t RxData[8];
extern uint8_t data_avlble;

void CAN_ErrorHandler(CAN_HandleTypeDef *hcan);

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan);
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan);

#endif