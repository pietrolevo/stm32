/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include "usart.h"
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_LOOPBACK;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_12TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  if (HAL_CAN_Start(&hcan1) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_CAN_ActivateNotification(&hcan1,
    CAN_IT_ERROR_WARNING |
    CAN_IT_ERROR_PASSIVE |
    CAN_IT_BUSOFF |
    CAN_IT_LAST_ERROR_CODE |
    CAN_IT_ERROR) != HAL_OK) {
      Error_Handler();
  }

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
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

}
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {

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

} 
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan) {
  if(hcan == &hcan1){
    CAN_ErrorHandler(hcan);
  }
}
/* USER CODE END 1 */
