#include "gpio.h"

/***************************************************************************/
#define SDA0_IN()  {GPIOB->MODER&=~(3<<(5*2));GPIOB->MODER|=0<<(5*2);}
#define SDA0_OUT() {GPIOB->MODER&=~(3<<(5*2));GPIOB->MODER|=1<<(5*2);}
#define READ_SDA0  (GPIOB->IDR&(1<<5))

#define RCC_IIC_ENABLE    __HAL_RCC_GPIOB_CLK_ENABLE()       /* GPIO端口时钟 */

/* 定义IIC总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
#define GPIO_PORT_IIC     GPIOB                       /* GPIO端口 */
#define RCC_IIC_ENABLE    __HAL_RCC_GPIOB_CLK_ENABLE()       /* GPIO端口时钟 */

#define IIC_SCL0_PIN       GPIO_PIN_4                  /* 连接到SCL时钟线的GPIO */
#define IIC_SDA0_PIN       GPIO_PIN_5                  /* 连接到SDA数据线的GPIO */

#define IIC_SCL1_PIN       GPIO_PIN_6                  /* 连接到SCL时钟线的GPIO */
#define IIC_SDA1_PIN       GPIO_PIN_7                  /* 连接到SDA数据线的GPIO */

#define IIC0_SCL_1  HAL_GPIO_WritePin(GPIOB,IIC_SCL0_PIN,GPIO_PIN_SET)
#define IIC0_SCL_0  HAL_GPIO_WritePin(GPIOB,IIC_SCL0_PIN,GPIO_PIN_RESET)
#define IIC0_SDA_1  HAL_GPIO_WritePin(GPIOB,IIC_SDA0_PIN,GPIO_PIN_SET)
#define IIC0_SDA_0  HAL_GPIO_WritePin(GPIOB,IIC_SDA0_PIN,GPIO_PIN_RESET)

/***************************************************************************/
#define SDA1_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<(7*2);}
#define SDA1_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<(7*2);}
#define READ_SDA1  (GPIOB->IDR&(1<<7))

#define IIC1_SCL_1  HAL_GPIO_WritePin(GPIOB,IIC_SCL1_PIN,GPIO_PIN_SET)
#define IIC1_SCL_0  HAL_GPIO_WritePin(GPIOB,IIC_SCL1_PIN,GPIO_PIN_RESET)
#define IIC1_SDA_1  HAL_GPIO_WritePin(GPIOB,IIC_SDA1_PIN,GPIO_PIN_SET)
#define IIC1_SDA_0  HAL_GPIO_WritePin(GPIOB,IIC_SDA1_PIN,GPIO_PIN_RESET)
/*****************************************************************************/
extern  void delay_s(uint32_t i);
/*****************************************************************************/
void I2C_Init_(unsigned char x)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_IIC_ENABLE;

	if(x==0)
	{
        GPIO_InitStructure.Pin = IIC_SCL0_PIN | IIC_SDA0_PIN;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIO_PORT_IIC, &GPIO_InitStructure);

		HAL_GPIO_WritePin(GPIOB, IIC_SCL0_PIN|IIC_SDA0_PIN,GPIO_PIN_SET);  //SCL和SDA输出高电平
	}
	else
	{
        GPIO_InitStructure.Pin = IIC_SCL1_PIN | IIC_SDA1_PIN;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIO_PORT_IIC, &GPIO_InitStructure);
		HAL_GPIO_WritePin(GPIOB, IIC_SCL1_PIN|IIC_SDA1_PIN,GPIO_PIN_SET);  //SCL和SDA输出高电平
	}
}
/******************************************************************************/
void IIC0_Start(void)
{
	IIC0_SDA_1;
	IIC0_SCL_1;
	delay_s(16);    //延时4时读不出角度，延时8可以读出
	IIC0_SDA_0;
	delay_s(16);
	IIC0_SCL_0;
}
/***************************************************************************/
void IIC0_Stop(void)
{
	IIC0_SCL_0;
	IIC0_SDA_0;
	delay_s(16);
	IIC0_SCL_1;
	IIC0_SDA_1;
	delay_s(16);
}
/***************************************************************************/
//1-fail,0-success
unsigned char IIC0_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
	
	SDA0_IN();
	IIC0_SDA_1;
	IIC0_SCL_1;
	delay_s(8);
	while(READ_SDA0!=0)
	{
		if(++ucErrTime>250)
			{
				SDA0_OUT();
				IIC0_Stop();
				return 1;
			}
	}
	SDA0_OUT();
	IIC0_SCL_0;
	return 0; 
}
/***************************************************************************/
void IIC0_Ack(void)
{
	IIC0_SCL_0;
	IIC0_SDA_0;
	delay_s(16);
	IIC0_SCL_1;
	delay_s(16);
	IIC0_SCL_0;
}
/***************************************************************************/
void IIC0_NAck(void)
{
	IIC0_SCL_0;
	IIC0_SDA_1;
	delay_s(16);
	IIC0_SCL_1;
	delay_s(16);
	IIC0_SCL_0;
}
/***************************************************************************/
void IIC0_Send_Byte(unsigned char txd)
{
	unsigned long i;
	
	IIC0_SCL_0;
	for(i=0;i<8;i++)
	{
		if((txd&0x80)!=0)IIC0_SDA_1;
		else
			IIC0_SDA_0;
		txd<<=1;
		delay_s(16);
		IIC0_SCL_1;
		delay_s(16);
		IIC0_SCL_0;
		delay_s(16);
	}
}
/***************************************************************************/
unsigned char IIC0_Read_Byte(unsigned char ack)
{
	unsigned char i,rcv=0;
	
	SDA0_IN();
	for(i=0;i<8;i++)
	{
		IIC0_SCL_0; 
		delay_s(16);
		IIC0_SCL_1;
		rcv<<=1;
		if(READ_SDA0!=0)rcv++;
		delay_s(8);
	}
	SDA0_OUT();
	if(!ack)IIC0_NAck();
	else
		IIC0_Ack();
	return rcv;
}
/***************************************************************************/
/***************************************************************************/
void IIC1_Start(void)
{
	IIC1_SDA_1;
	IIC1_SCL_1;
	delay_s(16);    //延时4时读不出角度，延时8可以读出
	IIC1_SDA_0;
	delay_s(16);
	IIC1_SCL_0;
}
/***************************************************************************/
void IIC1_Stop(void)
{
	IIC1_SCL_0;
	IIC1_SDA_0;
	delay_s(16);
	IIC1_SCL_1;
	IIC1_SDA_1;
	delay_s(16);
}
/***************************************************************************/
//1-fail,0-success
unsigned char IIC1_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
	
	SDA1_IN();
	IIC1_SDA_1;
	IIC1_SCL_1;
	delay_s(8);
	while(READ_SDA1!=0)
	{
		if(++ucErrTime>250)
			{
				SDA1_OUT();
				IIC1_Stop();
				return 1;
			}
	}
	SDA1_OUT();
	IIC1_SCL_0;
	return 0; 
}
/***************************************************************************/
void IIC1_Ack(void)
{
	IIC1_SCL_0;
	IIC1_SDA_0;
	delay_s(16);
	IIC1_SCL_1;
	delay_s(16);
	IIC1_SCL_0;
}
/***************************************************************************/
void IIC1_NAck(void)
{
	IIC1_SCL_0;
	IIC1_SDA_1;
	delay_s(16);
	IIC1_SCL_1;
	delay_s(16);
	IIC1_SCL_0;
}
/***************************************************************************/
void IIC1_Send_Byte(unsigned char txd)
{
	unsigned long i;
	
	IIC1_SCL_0;
	for(i=0;i<8;i++)
	{
		if((txd&0x80)!=0)IIC1_SDA_1;
		else
			IIC1_SDA_0;
		txd<<=1;
		delay_s(16);
		IIC1_SCL_1;
		delay_s(16);
		IIC1_SCL_0;
		delay_s(16);
	}
}
/***************************************************************************/
unsigned char IIC1_Read_Byte(unsigned char ack)
{
	unsigned char i,rcv=0;
	
	SDA1_IN();
	for(i=0;i<8;i++)
	{
		IIC1_SCL_0; 
		delay_s(16);
		IIC1_SCL_1;
		rcv<<=1;
		if(READ_SDA1!=0)rcv++;
		delay_s(8);
	}
	SDA1_OUT();
	if(!ack)IIC1_NAck();
	else
		IIC1_Ack();
	return rcv;
}
/***************************************************************************/

