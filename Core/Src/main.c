/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "common_inc.h"
#include <string.h>
#include "MyProject.h"
#include "user.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_blink   GPIOD->ODR^=(1<<2)  //PD2

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_SPI3_Init();
  MX_TIM8_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */

    Main();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void commander_run(void)
{
    if(rcv2_flag==1)
    {
        rcv2_flag=0;
        switch(rcv2_buff[0])
        {
            case 'H':
            {
                printf("Hello World!\r\n");
                break;
            }
            case 'A':   //A6.28   设置M0的目标值
                M0.target=atof((const char *)(rcv2_buff+1));
                printf("A=%.2f\r\n",M0.target);
                break;
            case 'B':   //B6.28   设置M1的目标值
                M1.target=atof((const char *)(rcv2_buff+1));
                printf(snd2_buff,"B=%.2f\r\n",M1.target);
                break;

            case 'M':   //设置M0
                switch(rcv2_buff[1])
                {
                    case 'P':   //MP0.5  设置速度环的P参数
                        M0.PID_vel.P=atof((const char *)(rcv2_buff+2));
                        printf("P=%.2f\r\n",M0.PID_vel.P);
                        break;
                    case 'I':   //MI0.2  设置速度环的I参数
                        M0.PID_vel.I=atof((const char *)(rcv2_buff+2));
                        printf(snd2_buff,"I=%.2f\r\n",M0.PID_vel.I);
                        break;
                    case 'V':   //MV  读实时速度
                        printf(snd2_buff,"Vel=%.2f\r\n",M0.shaft_velocity);
                        break;
                    case 'A':   //MA  读绝对角度
                        printf(snd2_buff,"Ang=%.2f\r\n",M0.shaft_angle);
                        break;
                }
                break;

            case 'N':   //设置M1
                switch(rcv2_buff[1])
                {
                    case 'P':   //NP0.5  设置速度环的P参数
                        M1.PID_vel.P=atof((const char *)(rcv2_buff+2));
                        printf(snd2_buff,"P=%.2f\r\n",M1.PID_vel.P);
                        break;
                    case 'I':   //NI0.2  设置速度环的I参数
                        M1.PID_vel.I=atof((const char *)(rcv2_buff+2));
                        printf(snd2_buff,"I=%.2f\r\n",M1.PID_vel.I);
                        break;
                    case 'V':   //NV  读实时速度
                        printf(snd2_buff,"Vel=%.2f\r\n",M1.shaft_velocity);
                        break;
                    case 'A':   //NA  读绝对角度
                        printf(snd2_buff,"Ang=%.2f\r\n",M1.shaft_angle);
                        break;
                }
                break;
        }
        memset(rcv2_buff,0,16);  //USART2_BUFFER_SIZE //清空接收数组,长度覆盖接收的字节数即可
    }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

