#include "MyProject.h"


/*****************************************************************************/
void TIM3_Encoder_Init(void)
{
}
/*****************************************************************************/
void TIM4_Encoder_Init(void)
{
}
/******************************************************************************/
uint16_t ReadABZ(uint8_t x)
{
	uint16_t  pulse_counter;
	short delta_pluse;
	
	if(x==0)
	{
		pulse_counter = __HAL_TIM_GET_COUNTER(&htim3);
		delta_pluse = (short)pulse_counter - (short)M0.pulse_pre;
		M0.pulse_pre = pulse_counter;
		M0.pulse_total = (M0.pulse_total + delta_pluse) % M0.cpr;
		if(M0.pulse_total<0)M0.pulse_total += M0.cpr;
		return  M0.pulse_total;
	}
	else
	{
		pulse_counter = __HAL_TIM_GET_COUNTER(&htim4);
		delta_pluse = (short)pulse_counter - (short)M1.pulse_pre;
		M1.pulse_pre = pulse_counter;
		M1.pulse_total = (M1.pulse_total + delta_pluse) % M1.cpr;
		if(M1.pulse_total<0)M1.pulse_total += M1.cpr;
		return  M1.pulse_total;
	}
}
/******************************************************************************/
void EXTI_Encoder_Init(uint8_t x)
{

}
//EXTI9_5_IRQHandler() 中断函数在stm32f4xx_it.c文件中
/******************************************************************************/



