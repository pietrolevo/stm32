/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */
// callback signature
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *);
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *);
void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *);
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *);
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *);
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *);
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *);
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

