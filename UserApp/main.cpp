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
//    M0.id=0;                     //д�ṹ���id
//    M1.id=1;
//    strcpy(M0.str, "M0");
//    strcpy(M1.str, "M1");
//
//    delay(200);
//    MagneticSensor_Init();       //��ʼ��������
//    LowsideCurrentSense(&M0,0.001f,20, NOT_SET,ADC_CHANNEL_10,ADC_CHANNEL_11);    //����������ֵ���˷ű�����A�࣬B�࣬C��
//    LowsideCurrentSense(&M1,0.001f,20, NOT_SET,ADC_CHANNEL_13,ADC_CHANNEL_12);    //����������ֵ���˷ű�����A�࣬B�࣬C��
//    ADC_Init_synch();               //����ADC��ʹ��TIM1��TIM8����ʼ����
//    LowsideCurrentSense_Init(&M0);  //����ƫ�õ�ѹ
//    LowsideCurrentSense_Init(&M1);
//    LPF_init(&M0);               //LPF������ʼ��
//    LPF_init(&M1);
//    PID_init(&M0);               //PID������ʼ��
//    PID_init(&M1);
//
//    voltage_power_supply = get_vbus_voltage();   //V ��Դ��ѹ���ܵ��辫��Ӱ�����0.2V���ҵ����
//    printf("vbus=%.2f\r\n",voltage_power_supply);
//
//    M0.voltage_limit = voltage_power_supply/2;      //V����ҪΪ���Ƶ��������
//    M0.pole_pairs=7;                //���������������ʵ�����ã���Ȼ�����ϵ��⵫��ʧ�ܵĸ���
//    M0.voltage_sensor_align=2.5;    //V ��ģ������õ�ֵСһ�����0.5-1����̨������õĴ�һ�����2-3
//    M0.velocity_limit=20;           //rad/s �Ƕ�ģʽʱ�������ת�٣�����ģʽ���ٶ�ģʽ��������
//    M0.current_limit=50;            //A��foc_current��dc_currentģʽ���Ƶ���������Ϊ0���ٶ�ģʽ��λ��ģʽ������
//    M0.torque_controller=Type_voltage;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
//    M0.controller=Type_torque;      //Type_torque; //Type_velocity;  //Type_angle;
////	M0.PID_d.P=1;              //0.6 ������PI���������Խ��� PID_init() �������޸���������
////	M0.PID_d.I=0.5;            //������I������̫�õ��ԣ�����Ϊ0ֻ��P����Ҳ����
////	M0.PID_q.P=1;
////	M0.PID_q.I=0.5;
////	M0.PID_vel.P=0.5;          //0.5, �ٶȻ�PI������ֻ��P����������ٵ���
////	M0.PID_vel.I=0.5;          //0.2
////	M0.P_ang.P=20;             //λ�û�������ֻ��P������һ�㲻��Ҫ�Ķ�
////	M0.PID_vel.output_ramp=50; //�ٶ�����б�ʣ��������Ҫ��������Ϊ0
////	M0.LPF_vel.Tf=0.0001;      //Tf����Сһ�㣬�������б�����ã��ٶ��л���ƽ�ȣ����û������ģʽ��б�����ƣ�Tf̫С������׶�����������Ϊ0.02��
//    M0.target=0;
//
//    M1.voltage_limit = voltage_power_supply/2;      //V����ҪΪ���Ƶ��������
//    M1.pole_pairs=7;                //���������������ʵ�����ã���Ȼ�����ϵ��⵫��ʧ�ܵĸ���
//    M1.voltage_sensor_align=0.6;    //V ��ģ������õ�ֵСһ�����0.5-1����̨������õĴ�һ�����2-3
//    M1.velocity_limit=20;           //rad/s �Ƕ�ģʽʱ�������ת�٣�����ģʽ���ٶ�ģʽ��������
//    M1.current_limit=50;            //A��foc_current��dc_currentģʽ���Ƶ���������Ϊ0���ٶ�ģʽ��λ��ģʽ������
//    M1.torque_controller=Type_voltage;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
//    M1.controller=Type_torque;      //Type_torque; //Type_velocity;  //Type_angle;
////	M1.PID_d.P=1;              //0.6 ������PI���������Խ��� PID_init() �������޸���������
////	M1.PID_d.I=0.5;            //������I������̫�õ��ԣ�����Ϊ0ֻ��P����Ҳ����
////	M1.PID_q.P=1;
////	M1.PID_q.I=0.5;
////	M1.PID_vel.P=0.5;          //0.5, �ٶȻ�PI������ֻ��P����������ٵ���
////	M1.PID_vel.I=0.5;          //0.2
////	M1.P_ang.P=20;             //λ�û�������ֻ��P������һ�㲻��Ҫ�Ķ�
////	M1.PID_vel.output_ramp=50; //�ٶ�����б�ʣ��������Ҫ��������Ϊ0
////	M1.LPF_vel.Tf=0.0001;      //Tf����Сһ�㣬�������б�����ã��ٶ��л���ƽ�ȣ����û������ģʽ��б�����ƣ�Tf̫С������׶�����������Ϊ0.02��
//    M1.target=0;
//
//    M0.Index_needsSearch=M0_INDEX;    //���ʹ��ABZ��������Z�ź�=1
//    M1.Index_needsSearch=M1_INDEX;    //���ʹ��ABZ��������Z�ź�=1
//    if(M0.Index_needsSearch==1)EXTI_Encoder_Init(0);   //���ʹ��Z�źţ����ж�
//    if(M1.Index_needsSearch==1)EXTI_Encoder_Init(1);   //���ʹ��Z�źţ����ж�
//    Motor_init(&M0);
//    Motor_init(&M1);
//    Motor_initFOC(&M0, 0,UNKNOWN);  //(0,UNKNOWN);  //(3.25,CW); ��һ���Ȼ��ƫ�ƽǺͷ�������������������أ��Ժ�����������У׼��ֻ��AB�ź���Ҫÿ���ϵ綼���У׼��
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