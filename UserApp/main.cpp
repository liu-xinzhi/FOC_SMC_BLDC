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
//    M0.id = 0; //д�ṹ���id
//    M1.id = 1;
//    strcpy(M0.name, "M0");
//    strcpy(M1.name, "M1");
//
//    delay(200);
//    //��ʼ��������
//    M0.MagneticSensor_Init();
//    M1.MagneticSensor_Init();
//
//    //����ƫ�õ�ѹ
//    M0_CurrentSence.init();
//    M1_CurrentSence.init();
//
//    //V ��Դ��ѹ���ܵ��辫��Ӱ�����0.2V���ҵ����
//    M0.driver->voltage_power_supply = 12;
//    M1.driver->voltage_power_supply = 12;
//
////    printf("vbus=%.2f\r\n",M0.driver->voltage_power_supply);
//
//    M0.voltage_limit = M0.driver->voltage_power_supply / 2;      //V����ҪΪ���Ƶ��������
//    M0.pole_pairs=7;                //���������������ʵ�����ã���Ȼ�����ϵ��⵫��ʧ�ܵĸ���
//    M0.voltage_sensor_align=2.5;    //V ��ģ������õ�ֵСһ�����0.5-1����̨������õĴ�һ�����2-3
//    M0.velocity_limit=20;           //rad/s �Ƕ�ģʽʱ�������ת�٣�����ģʽ���ٶ�ģʽ��������
//    M0.current_limit=50;            //A��foc_current��dc_currentģʽ���Ƶ���������Ϊ0���ٶ�ģʽ��λ��ģʽ������
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
////	M0.PID_d.P=1;              //0.6 ������PI���������Խ��� PID_init() �������޸���������
////	M0.PID_d.I=0.5;            //������I������̫�õ��ԣ�����Ϊ0ֻ��P����Ҳ����
////	M0.PID_q.P=1;
////	M0.PID_q.I=0.5;
////	M0.PID_velocity.P=0.5;          //0.5, �ٶȻ�PI������ֻ��P����������ٵ���
////	M0.PID_velocity.I=0.5;          //0.2
////	M0.P_ang.P=20;             //λ�û�������ֻ��P������һ�㲻��Ҫ�Ķ�
////	M0.PID_velocity.output_ramp=50; //�ٶ�����б�ʣ��������Ҫ��������Ϊ0
////	M0.LPF_vel.Tf=0.0001;      //Tf����Сһ�㣬�������б�����ã��ٶ��л���ƽ�ȣ����û������ģʽ��б�����ƣ�Tf̫С������׶�����������Ϊ0.02��
//    M0.target=0;
//
//    M1.voltage_limit =  M1.driver->voltage_power_supply / 2;      //V����ҪΪ���Ƶ��������
//    M1.pole_pairs=7;                //���������������ʵ�����ã���Ȼ�����ϵ��⵫��ʧ�ܵĸ���
//    M1.voltage_sensor_align=0.6;    //V ��ģ������õ�ֵСһ�����0.5-1����̨������õĴ�һ�����2-3
//    M1.velocity_limit=20;           //rad/s �Ƕ�ģʽʱ�������ת�٣�����ģʽ���ٶ�ģʽ��������
//    M1.current_limit=50;            //A��foc_current��dc_currentģʽ���Ƶ���������Ϊ0���ٶ�ģʽ��λ��ģʽ������
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
////	M1.PID_d.P=1;              //0.6 ������PI���������Խ��� PID_init() �������޸���������
////	M1.PID_d.I=0.5;            //������I������̫�õ��ԣ�����Ϊ0ֻ��P����Ҳ����
////	M1.PID_q.P=1;
////	M1.PID_q.I=0.5;
////	M1.PID_velocity.P=0.5;          //0.5, �ٶȻ�PI������ֻ��P����������ٵ���
////	M1.PID_velocity.I=0.5;          //0.2
////	M1.P_ang.P=20;             //λ�û�������ֻ��P������һ�㲻��Ҫ�Ķ�
////	M1.PID_velocity.output_ramp=50; //�ٶ�����б�ʣ��������Ҫ��������Ϊ0
////	M1.LPF_vel.Tf=0.0001;      //Tf����Сһ�㣬�������б�����ã��ٶ��л���ƽ�ȣ����û������ģʽ��б�����ƣ�Tf̫С������׶�����������Ϊ0.02��
//    M1.target=0;
//
////    M0.Index_needsSearch=M0_INDEX;    //���ʹ��ABZ��������Z�ź�=1
////    M1.Index_needsSearch=M1_INDEX;    //���ʹ��ABZ��������Z�ź�=1
////    if(M0.Index_needsSearch==1)EXTI_Encoder_Init(0);   //���ʹ��Z�źţ����ж�
////    if(M1.Index_needsSearch==1)EXTI_Encoder_Init(1);   //���ʹ��Z�źţ����ж�
//
//    M0_Sensor.Init();
//    M1_Sensor.Init();
//
//    M0.init();
//    M1.init();
//    M0.initFOC(0,UNKNOWN);  //(0,UNKNOWN);  //(3.25,CW); ��һ���Ȼ��ƫ�ƽǺͷ�������������������أ��Ժ�����������У׼��ֻ��AB�ź���Ҫÿ���ϵ綼���У׼��
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
            // �۲�Ƕȱ仯�����ڵ���
            printf("%.2f, %.2f\r\n", M0.shaft_angle,M1.shaft_angle);
        }
//        commander_run();

        M0.move(setPoint0);
        setPoint0 = 1*(M1.shaft_angle - M0.shaft_angle);   //��������������߿�������
        if (setPoint0 > M0.voltage_limit/2)
            setPoint0 = M0.voltage_limit/2;
        else if(setPoint0 < -M0.voltage_limit/2)
            setPoint0 = -M0.voltage_limit/2;
        M0.loopFOC();

        M1.move(setPoint1);
        setPoint1 = 1*(M0.shaft_angle - M1.shaft_angle);

        // ���Ʋ�ֵ�������ֵ̫������ͨ��һ�°ѵ�ѹ����
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
//            case 'A':   //A6.28   ����M0��Ŀ��ֵ
//                M0.target=atof((const char *)(rcv2_buff+1));
//                printf("A=%.2f\r\n",M0.target);
//                break;
//            case 'B':   //B6.28   ����M1��Ŀ��ֵ
//                M1.target=atof((const char *)(rcv2_buff+1));
//                printf("B=%.2f\r\n",M1.target);
//                break;
//
//            case 'M':   //����M0
//                switch(rcv2_buff[1])
//                {
//                    case 'P':   //MP0.5  �����ٶȻ���P����
//                        M0.PID_velocity.P=atof((const char *)(rcv2_buff+2));
//                        printf("P=%.2f\r\n",M0.PID_velocity.P);
//                        break;
//                    case 'I':   //MI0.2  �����ٶȻ���I����
//                        M0.PID_velocity.I=atof((const char *)(rcv2_buff+2));
//                        printf("I=%.2f\r\n",M0.PID_velocity.I);
//                        break;
//                    case 'V':   //MV  ��ʵʱ�ٶ�
//                        printf("Vel=%.2f\r\n",M0.shaft_velocity);
//                        break;
//                    case 'A':   //MA  �����ԽǶ�
//                        printf("Ang=%.2f\r\n",M0.shaft_angle);
//                        break;
//                }
//                break;
//
//            case 'N':   //����M1
//                switch(rcv2_buff[1])
//                {
//                    case 'P':   //NP0.5  �����ٶȻ���P����
//                        M1.PID_velocity.P=atof((const char *)(rcv2_buff+2));
//                        printf("P=%.2f\r\n",M1.PID_velocity.P);
//                        break;
//                    case 'I':   //NI0.2  �����ٶȻ���I����
//                        M1.PID_velocity.I=atof((const char *)(rcv2_buff+2));
//                        printf("I=%.2f\r\n",M1.PID_velocity.I);
//                        break;
//                    case 'V':   //NV  ��ʵʱ�ٶ�
//                        printf("Vel=%.2f\r\n",M1.shaft_velocity);
//                        break;
//                    case 'A':   //NA  �����ԽǶ�
//                        printf("Ang=%.2f\r\n",M1.shaft_angle);
//                        break;
//                }
//                break;
//        }
//        memset(rcv2_buff,0,16);  //USART2_BUFFER_SIZE //��ս�������,���ȸ��ǽ��յ��ֽ�������
//    }
//}

//! tim1����Ϊ�������ģʽ��һ������update���Σ�ÿ(2+1)�δ���һ�Σ����Խ����жϵ�Ƶ��Ϊ16KHz��
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(((ADC2->SR & ADC_SR_JEOC) == ADC_SR_JEOC)&&((ADC3->SR & ADC_SR_JEOC) == ADC_SR_JEOC))
    {
        ADC2->SR = ~ADC_SR_JEOC;
        ADC3->SR = ~ADC_SR_JEOC;
        if((TIM1->CR1 & TIM_CR1_DIR)==0)   //=0Ϊ��������,�ϱ�Ϊ���±�Ϊ��,��ʱ����������Ƶ��8KHz
        {
            M0_CurrentSence.phB = (float)ADC2->JDR1 *3.3f/4096;
            M0_CurrentSence.phC = (float)ADC3->JDR1 *3.3f/4096;
        }
    }
    if(((ADC2->SR & ADC_SR_EOC) == ADC_SR_EOC)&&((ADC3->SR & ADC_SR_EOC) == ADC_SR_EOC))
    {
        ADC2->SR = ~ADC_SR_EOC;
        ADC3->SR = ~ADC_SR_EOC;
        if((TIM8->CR1 & TIM_CR1_DIR)==0)   //=0Ϊ��������,�ϱ�Ϊ���±�Ϊ��,��ʱ����������Ƶ��8KHz
        {
            M1_CurrentSence.phB = (float)ADC2->DR *3.3f/4096;
            M1_CurrentSence.phC = (float)ADC3->DR *3.3f/4096;
        }
    }
}