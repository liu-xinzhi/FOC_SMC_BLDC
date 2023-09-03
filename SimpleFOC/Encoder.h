#ifndef __ENCODER_LIB_H
#define __ENCODER_LIB_H


#include "stm32f4xx.h"

/******************************************************************************/
/******************************************************************************/
void TIM3_Encoder_Init(void);
void TIM4_Encoder_Init(void);
uint16_t ReadABZ(uint8_t x);
void EXTI_Encoder_Init(uint8_t x);
/******************************************************************************/

#endif
