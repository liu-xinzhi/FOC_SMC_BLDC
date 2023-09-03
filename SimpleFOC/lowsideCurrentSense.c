#include "MyProject.h"
#include "stdio.h"

/************************************************
电流采样函数
************************************************/
/******************************************************************************/
void Current_calibrateOffsets(MOTORController *M);
/******************************************************************************/
void LowsideCurrentSense(MOTORController *M,float _shunt_resistor, float _gain, int _pinA, int _pinB, int _pinC)
{
	float volts_to_amps_ratio;
	
	M->pinA = _pinA;
	M->pinB = _pinB;
	M->pinC = _pinC;
	
	volts_to_amps_ratio = 1.0f /_shunt_resistor / _gain; // volts to amps
	
	M->gain_a = volts_to_amps_ratio;
	M->gain_b =-volts_to_amps_ratio;
	M->gain_c =-volts_to_amps_ratio;
	
	//printf("gain_a:%.2f,gain_b:%.2f,gain_c:%.2f.\r\n",gain_a,gain_b,gain_c);  //必须屏蔽，这句话打印会导致下面的函数执行不正常，一下午没有找到原因
}
/******************************************************************************/
#define TIM_1_8_PERIOD_CLOCKS 3500
#define TIM1_INIT_COUNT (TIM_1_8_PERIOD_CLOCKS / 2 - 1 * 512)

void ADC_Init_synch(void)
{
//	ADC_Common_Init();          //初始化ADC的引脚和通用配置，设置中断
//	ADC1_DMA_Init();            //配置DMA模式，转换温度检测和vbus，温度检测在simpleFOC中没有使用，开始转换
//	ADC2_TRGO_Init();           //配置
//	ADC3_TRGO_Init();           //配置
	
	//以下几句代码同步TIM1和TIM8，使得相位差90°，参考odrive的start_synchronously函数，v0.5.4版本board.cpp文件第394行，或者v0.5.1版本low_level.cpp文件第222行
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->CNT = TIM1_INIT_COUNT;
	TIM8->EGR |= TIM_EGR_UG;
	TIM8->CNT = 0;
	
//	TIM_Cmd(TIM1, ENABLE);
//	TIM_Cmd(TIM8, ENABLE);
}
/******************************************************************************/
void LowsideCurrentSense_Init(MOTORController *M)
{
	delay(20);
	Current_calibrateOffsets(M); //检测偏置电压，也就是电流0A时的运放输出电压值，理论值=1.65V
}
/******************************************************************************/
// Function finding zero offsets of the ADC
void Current_calibrateOffsets(MOTORController *M)
{
	int i;
	
	M->offset_ia=0;
	M->offset_ib=0;
	M->offset_ic=0;
	// read the adc voltage 1000 times ( arbitrary number )
	for(i=0; i<1000; i++)
	{
		if(_isset(M->pinA)) M->offset_ia += M->phA;
		if(_isset(M->pinB)) M->offset_ib += M->phB;
		if(_isset(M->pinC)) M->offset_ic += M->phC;
		delay(1);
	}
	// calculate the mean offsets
	if(_isset(M->pinA)) M->offset_ia = M->offset_ia/1000;
	if(_isset(M->pinB)) M->offset_ib = M->offset_ib/1000;
	if(_isset(M->pinC)) M->offset_ic = M->offset_ic/1000;
	
	printf("offset_ia:%.4f,offset_ib:%.4f,offset_ic:%.4f.\r\n",M->offset_ia,M->offset_ib,M->offset_ic);
}
/******************************************************************************/
// read all three phase currents (if possible 2 or 3)
PhaseCurrent_s getPhaseCurrents(MOTORController *M)
{
	PhaseCurrent_s current;
	
	current.a = (!_isset(M->pinA)) ? 0 : (M->phA - M->offset_ia)*M->gain_a; // amps
	current.b = (!_isset(M->pinB)) ? 0 : (M->phB - M->offset_ib)*M->gain_b; // amps
	current.c = (!_isset(M->pinC)) ? 0 : (M->phC - M->offset_ic)*M->gain_c; // amps
	
	return current;
}
/******************************************************************************/





