#include "common_inc.h"
#include "st_hardware.h"

/* Component Definitions -----------------------------------------------------*/

BLDCMotor M0(7), M1(7);
InlineCurrentSense M0_CurrentSence(0.001f,20, NOT_SET,ADC_CHANNEL_10,ADC_CHANNEL_11);
InlineCurrentSense M1_CurrentSence(0.001f,20, NOT_SET,ADC_CHANNEL_13,ADC_CHANNEL_12);

//EncoderAS5600 M0_Sensor;
EncoderAS5600 M0_Sensor;
EncoderAS5047 M1_Sensor;

/*****************************
 * *************************************************/
extern void delay_s(uint32_t i);
void commander_run();
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
#include "usart.h"

/* Main Entry ----------------------------------------------------------------*/

void Main()
{
    for (;; )
    {
        printf("1\r\n");
    }

//    HAL_UART_Receive_DMA(&huart2, (uint8_t*)rcv2_buff, USART2_BUFFER_SIZE);
//    M0.id = 0; //写结构体的id
//    M1.id = 1;
//    strcpy(M0.name, "M0");
//    strcpy(M1.name, "M1");
//
//    delay(200);
//    //初始化编码器
//    M0.MagneticSensor_Init();
//    M1.MagneticSensor_Init();
//
//    //测量偏置电压
//    M0_CurrentSence.init();
//    M1_CurrentSence.init();
//
//    //V 电源电压，受电阻精度影响会有0.2V左右的误差
//    M0.driver->voltage_power_supply = 12;
//    M1.driver->voltage_power_supply = 12;
//
////    printf("vbus=%.2f\r\n",M0.driver->voltage_power_supply);
//
//    M0.voltage_limit = M0.driver->voltage_power_supply / 2;      //V，主要为限制电机最大电流
//    M0.pole_pairs=7;                //电机极对数，按照实际设置，虽然可以上电检测但有失败的概率
//    M0.voltage_sensor_align=2.5;    //V 航模电机设置的值小一点比如0.5-1，云台电机设置的大一点比如2-3
//    M0.velocity_limit=20;           //rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
//    M0.current_limit=50;            //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
//    /**
//     *     voltage, //!< Torque control using voltage
//     *     dc_current, //!< Torque control using DC current (one current magnitude)
//     *     foc_current //!< torque control using dq currents
//     * */
//    M0.torque_controller=foc_current;  //Type_dc_current;//  Type_foc_current;  //Type_voltage;
//    /**
//     *     torque,//!< Torque control
//     *     velocity,//!< Velocity motion control
//     *     angle,//!< Position/angle motion control
//     *     velocity_openloop,
//     *     angle_openloop
//     * */
//    M0.controller=torque;
////	M0.PID_d.P=1;              //0.6 电流环PI参数，可以进入 PID_init() 函数中修改其它参数
////	M0.PID_d.I=0.5;            //电流环I参数不太好调试，设置为0只用P参数也可以
////	M0.PID_q.P=1;
////	M0.PID_q.I=0.5;
////	M0.PID_velocity.P=0.5;          //0.5, 速度环PI参数，只用P参数方便快速调试
////	M0.PID_velocity.I=0.5;          //0.2
////	M0.P_ang.P=20;             //位置环参数，只需P参数，一般不需要改动
////	M0.PID_velocity.output_ramp=50; //速度爬升斜率，如果不需要可以设置为0
////	M0.LPF_vel.Tf=0.0001;      //Tf设置小一点，配合爬升斜率设置，速度切换更平稳；如果没有爬升模式的斜率限制，Tf太小电机容易抖动，可设置为0.02。
//    M0.target=0;
//
//    M1.voltage_limit =  M1.driver->voltage_power_supply / 2;      //V，主要为限制电机最大电流
//    M1.pole_pairs=7;                //电机极对数，按照实际设置，虽然可以上电检测但有失败的概率
//    M1.voltage_sensor_align=0.6;    //V 航模电机设置的值小一点比如0.5-1，云台电机设置的大一点比如2-3
//    M1.velocity_limit=20;           //rad/s 角度模式时限制最大转速，力矩模式和速度模式不起作用
//    M1.current_limit=50;            //A，foc_current和dc_current模式限制电流，不能为0。速度模式和位置模式起作用
//    /**
//     *     voltage, //!< Torque control using voltage
//     *     dc_current, //!< Torque control using DC current (one current magnitude)
//     *     foc_current //!< torque control using dq currents
//     * */
//    M1.torque_controller=foc_current;
//    /**
//     *     torque,//!< Torque control
//     *     velocity,//!< Velocity motion control
//     *     angle,//!< Position/angle motion control
//     *     velocity_openloop,
//     *     angle_openloop
//     * */
//    M1.controller=torque;
////	M1.PID_d.P=1;              //0.6 电流环PI参数，可以进入 PID_init() 函数中修改其它参数
////	M1.PID_d.I=0.5;            //电流环I参数不太好调试，设置为0只用P参数也可以
////	M1.PID_q.P=1;
////	M1.PID_q.I=0.5;
////	M1.PID_velocity.P=0.5;          //0.5, 速度环PI参数，只用P参数方便快速调试
////	M1.PID_velocity.I=0.5;          //0.2
////	M1.P_ang.P=20;             //位置环参数，只需P参数，一般不需要改动
////	M1.PID_velocity.output_ramp=50; //速度爬升斜率，如果不需要可以设置为0
////	M1.LPF_vel.Tf=0.0001;      //Tf设置小一点，配合爬升斜率设置，速度切换更平稳；如果没有爬升模式的斜率限制，Tf太小电机容易抖动，可设置为0.02。
//    M1.target=0;
//
////    M0.Index_needsSearch=M0_INDEX;    //如果使用ABZ编码器的Z信号=1
////    M1.Index_needsSearch=M1_INDEX;    //如果使用ABZ编码器的Z信号=1
////    if(M0.Index_needsSearch==1)EXTI_Encoder_Init(0);   //如果使用Z信号，开中断
////    if(M1.Index_needsSearch==1)EXTI_Encoder_Init(1);   //如果使用Z信号，开中断
//
//    M0_Sensor.Init();
//    M1_Sensor.Init();
//
//    M0.init();
//    M1.init();
//    M0.initFOC(0,UNKNOWN);  //(0,UNKNOWN);  //(3.25,CW); 第一次先获得偏移角和方向，填入代码编译后再下载，以后可以跳过零点校准。只用AB信号需要每次上电都零点校准。
//    M1.initFOC(0,UNKNOWN);
//    printf("Haptic Control.\r\n");


//    uint64_t serialNum = GetSerialNumber();
//    uint16_t defaultNodeID = 0;
//
//    encoder.Init();
//
//    //HAL_TIM_Base_Start_IT(&htim1);
//
//
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
//    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
//    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 200);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 300);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 300);
//
//    delay(10);
//    //    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcData, 2);
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 720);
//    HAL_ADCEx_InjectedStart_IT(&hadc1);

    while(0)
    {
        time_cntr +=timecount();
        if(time_cntr>=500000)  //us
        {
            time_cntr=0;
            HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
            // 观察角度变化，便于调试
            printf("%.2f, %.2f\r\n", M0.shaft_angle,M1.shaft_angle);
        }
//        commander_run();

        M0.move(setPoint0);
        setPoint0 = 1*(M1.shaft_angle - M0.shaft_angle);   //两个电机的三相线可以随便接
        if (setPoint0 > M0.voltage_limit/2)
            setPoint0 = M0.voltage_limit/2;
        else if(setPoint0 < -M0.voltage_limit/2)
            setPoint0 = -M0.voltage_limit/2;
        M0.loopFOC();

        M1.move(setPoint1);
        setPoint1 = 1*(M0.shaft_angle - M1.shaft_angle);

        // 限制差值，否则差值太大电机“通”一下把电压拉低
        if (setPoint1 > M1.voltage_limit / 2)
            setPoint1 = M1.voltage_limit / 2;
        else if(setPoint1 < -M1.voltage_limit / 2)
            setPoint1 = -M1.voltage_limit / 2;
        M1.loopFOC();
    }

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
}

//void commander_run()
//{
//    if(rcv2_flag==1)
//    {
//        rcv2_flag=0;
//        switch(rcv2_buff[0])
//        {
//            case 'H':
//            {
//                printf("Hello World!\r\n");
//                break;
//            }
//            case 'A':   //A6.28   设置M0的目标值
//                M0.target=atof((const char *)(rcv2_buff+1));
//                printf("A=%.2f\r\n",M0.target);
//                break;
//            case 'B':   //B6.28   设置M1的目标值
//                M1.target=atof((const char *)(rcv2_buff+1));
//                printf("B=%.2f\r\n",M1.target);
//                break;
//
//            case 'M':   //设置M0
//                switch(rcv2_buff[1])
//                {
//                    case 'P':   //MP0.5  设置速度环的P参数
//                        M0.PID_velocity.P=atof((const char *)(rcv2_buff+2));
//                        printf("P=%.2f\r\n",M0.PID_velocity.P);
//                        break;
//                    case 'I':   //MI0.2  设置速度环的I参数
//                        M0.PID_velocity.I=atof((const char *)(rcv2_buff+2));
//                        printf("I=%.2f\r\n",M0.PID_velocity.I);
//                        break;
//                    case 'V':   //MV  读实时速度
//                        printf("Vel=%.2f\r\n",M0.shaft_velocity);
//                        break;
//                    case 'A':   //MA  读绝对角度
//                        printf("Ang=%.2f\r\n",M0.shaft_angle);
//                        break;
//                }
//                break;
//
//            case 'N':   //设置M1
//                switch(rcv2_buff[1])
//                {
//                    case 'P':   //NP0.5  设置速度环的P参数
//                        M1.PID_velocity.P=atof((const char *)(rcv2_buff+2));
//                        printf("P=%.2f\r\n",M1.PID_velocity.P);
//                        break;
//                    case 'I':   //NI0.2  设置速度环的I参数
//                        M1.PID_velocity.I=atof((const char *)(rcv2_buff+2));
//                        printf("I=%.2f\r\n",M1.PID_velocity.I);
//                        break;
//                    case 'V':   //NV  读实时速度
//                        printf("Vel=%.2f\r\n",M1.shaft_velocity);
//                        break;
//                    case 'A':   //NA  读绝对角度
//                        printf("Ang=%.2f\r\n",M1.shaft_angle);
//                        break;
//                }
//                break;
//        }
//        memset(rcv2_buff,0,16);  //USART2_BUFFER_SIZE //清空接收数组,长度覆盖接收的字节数即可
//    }
//}

//! tim1配置为中央对齐模式，一个周期update两次，每(2+1)次触发一次，所以进入中断的频率为16KHz，
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(((ADC2->SR & ADC_SR_JEOC) == ADC_SR_JEOC)&&((ADC3->SR & ADC_SR_JEOC) == ADC_SR_JEOC))
    {
        ADC2->SR = ~ADC_SR_JEOC;
        ADC3->SR = ~ADC_SR_JEOC;
        if((TIM1->CR1 & TIM_CR1_DIR)==0)   //=0为递增计数,上臂为低下臂为高,此时采样，进入频率8KHz
        {
            M0_CurrentSence.phB = (float)ADC2->JDR1 *3.3f/4096;
            M0_CurrentSence.phC = (float)ADC3->JDR1 *3.3f/4096;
        }
    }
    if(((ADC2->SR & ADC_SR_EOC) == ADC_SR_EOC)&&((ADC3->SR & ADC_SR_EOC) == ADC_SR_EOC))
    {
        ADC2->SR = ~ADC_SR_EOC;
        ADC3->SR = ~ADC_SR_EOC;
        if((TIM8->CR1 & TIM_CR1_DIR)==0)   //=0为递增计数,上臂为低下臂为高,此时采样，进入频率8KHz
        {
            M1_CurrentSence.phB = (float)ADC2->DR *3.3f/4096;
            M1_CurrentSence.phC = (float)ADC3->DR *3.3f/4096;
        }
    }
}