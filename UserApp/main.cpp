#include "common_inc.h"
#include "Platform/Utils/st_hardware.h"
#include "usart.h"
#include "BLDCDriver.h"
#include "FOCMotor.h"


EncoderAS5047 encoder;

/* Component Definitions -----------------------------------------------------*/
BoardConfig_t boardConfig;

/*****************************
 * *************************************************/
extern void delay_s(uint32_t i);
void commander_run(void);
/******************************************************************************/

FOCModulationType Motor_5008_1,Motor_5600;

uint32_t timecntr_pre=0;
uint32_t time_cntr=0;

float setPoint0=0, setPoint1=0;
/******************************************************************************/

uint32_t timecount(void)
{
    uint32_t  diff,now_us;

    now_us = micros();    //0xFFFFFFFF=4294967295 us=71.5????
    if(now_us>=timecntr_pre)diff = now_us - timecntr_pre;   //us
    else
        diff = 0xFFFFFFFF - timecntr_pre + now_us;
    timecntr_pre = now_us;

    return diff;
}


#include "adc.h"

/* Main Entry ----------------------------------------------------------------*/
void Main()
{

}

//void Main()
//{
//
//    //    HAL_UART_Receive_IT(&huart2, (uint8_t *)&rcv2_cntr, 1);
//    HAL_UART_Receive_DMA(&huart2, (uint8_t*)rcv2_buff, USART2_BUFFER_SIZE);
//    M0.id=0;                     //写结构体的id
//    M1.id=1;
//    strcpy(M0.str, "M0");
//    strcpy(M1.str, "M1");
//
//    delay(200);
//    MagneticSensor_Init();       //初始化编码器
//    LowsideCurrentSense(&M0,0.001f,20, NOT_SET,ADC_CHANNEL_10,ADC_CHANNEL_11);    //采样电阻阻值，运放倍数，A相，B相，C相
//    LowsideCurrentSense(&M1,0.001f,20, NOT_SET,ADC_CHANNEL_13,ADC_CHANNEL_12);    //采样电阻阻值，运放倍数，A相，B相，C相
//    ADC_Init_synch();               //配置ADC，使能TIM1和TIM8，开始采样
//    LowsideCurrentSense_Init(&M0);  //测量偏置电压
//    LowsideCurrentSense_Init(&M1);
//    LPF_init(&M0);               //LPF参数初始化
//    LPF_init(&M1);
//    PID_init(&M0);               //PID参数初始化
//    PID_init(&M1);
//
//    voltage_power_supply = get_vbus_voltage();   //V 电源电压，受电阻精度影响会有0.2V左右的误差
//    printf("vbus=%.2f\r\n",voltage_power_supply);
//
//    M0.voltage_limit = voltage_power_supply/2;      //V，主要为限制电机最大电流
//    M0.pole_pairs=7;                //电机极对数，按照实际设置，虽然可以上电检测但有失败的概率
//    M0.voltage_sensor_align=2.5;    //V 航模电机设置的值小一点比如0.5-1，云台电机设置的大一点比如2-3
//    M0.velocity_limit=20;           //rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
//    M0.current_limit=50;            //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
//    M0.torque_controller=Type_voltage;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
//    M0.controller=Type_torque;      //Type_torque; //Type_velocity;  //Type_angle;
////	M0.PID_d.P=1;              //0.6 电流环PI参数，可以进入 PID_init() 函数中修改其它参数
////	M0.PID_d.I=0.5;            //电流环I参数不太好调试，设置为0只用P参数也可以
////	M0.PID_q.P=1;
////	M0.PID_q.I=0.5;
////	M0.PID_vel.P=0.5;          //0.5, 速度环PI参数，只用P参数方便快速调试
////	M0.PID_vel.I=0.5;          //0.2
////	M0.P_ang.P=20;             //位置环参数，只需P参数，一般不需要改动
////	M0.PID_vel.output_ramp=50; //速度爬升斜率，如果不需要可以设置为0
////	M0.LPF_vel.Tf=0.0001;      //Tf设置小一点，配合爬升斜率设置，速度切换更平稳；如果没有爬升模式的斜率限制，Tf太小电机容易抖动，可设置为0.02。
//    M0.target=0;
//
//    M1.voltage_limit = voltage_power_supply/2;      //V，主要为限制电机最大电流
//    M1.pole_pairs=7;                //电机极对数，按照实际设置，虽然可以上电检测但有失败的概率
//    M1.voltage_sensor_align=0.6;    //V 航模电机设置的值小一点比如0.5-1，云台电机设置的大一点比如2-3
//    M1.velocity_limit=20;           //rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
//    M1.current_limit=50;            //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
//    M1.torque_controller=Type_voltage;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
//    M1.controller=Type_torque;      //Type_torque; //Type_velocity;  //Type_angle;
////	M1.PID_d.P=1;              //0.6 电流环PI参数，可以进入 PID_init() 函数中修改其它参数
////	M1.PID_d.I=0.5;            //电流环I参数不太好调试，设置为0只用P参数也可以
////	M1.PID_q.P=1;
////	M1.PID_q.I=0.5;
////	M1.PID_vel.P=0.5;          //0.5, 速度环PI参数，只用P参数方便快速调试
////	M1.PID_vel.I=0.5;          //0.2
////	M1.P_ang.P=20;             //位置环参数，只需P参数，一般不需要改动
////	M1.PID_vel.output_ramp=50; //速度爬升斜率，如果不需要可以设置为0
////	M1.LPF_vel.Tf=0.0001;      //Tf设置小一点，配合爬升斜率设置，速度切换更平稳；如果没有爬升模式的斜率限制，Tf太小电机容易抖动，可设置为0.02。
//    M1.target=0;
//
//    M0.Index_needsSearch=M0_INDEX;    //如果使用ABZ编码器的Z信号=1
//    M1.Index_needsSearch=M1_INDEX;    //如果使用ABZ编码器的Z信号=1
//    if(M0.Index_needsSearch==1)EXTI_Encoder_Init(0);   //如果使用Z信号，开中断
//    if(M1.Index_needsSearch==1)EXTI_Encoder_Init(1);   //如果使用Z信号，开中断
//    Motor_init(&M0);
//    Motor_init(&M1);
//    Motor_initFOC(&M0, 0,UNKNOWN);  //(0,UNKNOWN);  //(3.25,CW); 第一次先获得偏移角和方向，填入代码编译后再下载，以后可以跳过零点校准。只用AB信号需要每次上电都零点校准。
//    Motor_initFOC(&M1, 0,UNKNOWN);
//    printf("Haptic Control.\r\n");
//
//
////    uint64_t serialNum = GetSerialNumber();
////    uint16_t defaultNodeID = 0;
////
////    encoder.Init();
////
////    //HAL_TIM_Base_Start_IT(&htim1);
////
////
////    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
////    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
////    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
////    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
////    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
////    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
////    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 200);
////    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 300);
////    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 300);
////
////    delay(10);
////    //    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcData, 2);
////    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
////    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 720);
////    HAL_ADCEx_InjectedStart_IT(&hadc1);
//
//
//    for (;;)
//    {
////        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
////        HAL_Delay(100);
////        HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
////        HAL_Delay(100);
//        /**/
//        encoder.update();
////        printf("%.2f,%.2f\n", encoder.GetAngle(), encoder.getVelocity());
//        delay(1);
//
//        printf("%d,%d\n", adcData[0], adcData[1]);
//    }
//}


void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    GPIOB->BSRR = GPIO_PIN_12;
    adcData[0] = hadc->Instance->JDR1;
    adcData[1] = hadc->Instance->JDR2;
    GPIOB->BSRR = GPIO_PIN_12;
}