/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "stdio.h"

#define BUFFER_SIZE  128

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

extern volatile uint8_t rxLen;
extern uint8_t rx_buffer[BUFFER_SIZE];

/* USER CODE END Includes */

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/******************************************************************************/
#define USART2_BUFFER_SIZE 256
/******************************************************************************/
extern char snd2_buff[USART2_BUFFER_SIZE];
extern char rcv2_buff[USART2_BUFFER_SIZE];
extern unsigned long rcv2_cntr;
extern unsigned long rcv2_flag;
/******************************************************************************/
void USART2_SendDMA(uint32_t len);
/******************************************************************************/

/* USER CODE END Private defines */

void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */

extern void (*OnRecvEnd)(uint8_t *data, uint16_t len);
void Uart_SetRxCpltCallBack(void(*xerc)(uint8_t *, uint16_t));

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

