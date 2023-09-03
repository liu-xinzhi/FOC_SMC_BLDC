#ifndef MYPROJECT_H
#define MYPROJECT_H

/* Includes ------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "i2c_software.h"
#include "spi3.h"
#include "adc.h"
#include "tim.h"
#include "math.h"
#include "spi.h"

#include "Ctrl/Utils/foc_utils.h"
#include "MagneticSensor.h"
#include "Encoder.h"
#include "Sensor.h"
#include "BLDCMotor.h"
#include "FOCMotor.h"
#include "lowpass_filter.h"
#include "pid.h"
#include "CurrentSense.h"
#include "lowsideCurrentSense.h"

#define M0_Disable   HAL_TIM_Base_DeInit(&htim1)        //关闭M0输出，关闭后上臂输出高电平，下臂低电平
#define M1_Disable   HAL_TIM_Base_DeInit(&htim8)        //关闭M1输出，关闭后上臂输出高电平，下臂低电平

//SPI接口用GPIO1做为CS0引脚，GPIO2做为CS1引脚，同时接两个SPI接口的编码器必须型号一致
//I2C接口用M0的A/B为SCL0/SDA0，M1的A/B为SCL1/SDA1
//设置使用的编码器为1，不使用的为0

#define M0_AS5600    1      //编码器类型，只能选一
#define M0_AS5047P   0
#define M0_TLE5012B  0
#define M0_MA730     0
#define M0_MT6701    0
#define M0_ABZ       0      //ABZ需要设置下面的CPR
#define M0_INDEX     0      //Z信号使用=1，不使用=0
#define M0_ABZ_CPR   4000   //如果用ABZ信号，需要准确设置ABZ的CPR。AS5047P=4000，TLE5012B=16384

#define M1_AS5600    0      //编码器类型，只能选一
#define M1_AS5047P   1
#define M1_TLE5012B  0
#define M1_MA730     0
#define M1_MT6701    0
#define M1_ABZ       0      //ABZ需要设置下面的CPR
#define M1_INDEX     0      //Z信号使用=1，不使用=0
#define M1_ABZ_CPR   4000   //如果用ABZ信号，需要准确设置ABZ的CPR。AS5047P=4000，TLE5012B=16384

#endif

/*
ABZ信号分为：不用Z信号和使用Z信号，
1、不使用Z信号，只有AB信号，输出的是相对角度，电机每次上电机械角度为0，但是电角度不确定，
   所以每次都需要校准，而且每次校准的零点偏移值都不一样。
2、使用Z信号，零点校准的偏移值固定，但每次上电都需要找机械零点，也就是Z的过零点。

所以ABZ信号的优点，接口简单统一，方便使用各种不同的电机，缺点是每次上电都需要校准的过程，
*/


