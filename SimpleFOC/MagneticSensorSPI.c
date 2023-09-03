#include "MyProject.h"

/*****************************************************************************/
#define GPIO_PORT_SPI     GPIOA                       /* GPIO端口 */
#define RCC_IIC_ENABLE    __HAL_RCC_GPIOB_CLK_ENABLE()       /* GPIO端口时钟 */

#define IIC_SPICS0_PIN       GPIO_PIN_0                  /* 连接到SCL时钟线的GPIO */
#define IIC_SPICS1_PIN       GPIO_PIN_1                  /* 连接到SDA数据线的GPIO */

#define  SPI_CS0_L   HAL_GPIO_WritePin(GPIO_PORT_SPI, IIC_SPICS0_PIN,GPIO_PIN_RESET)
#define  SPI_CS0_H   HAL_GPIO_WritePin(GPIO_PORT_SPI, IIC_SPICS0_PIN,GPIO_PIN_SET)
#define  SPI_CS1_L   HAL_GPIO_WritePin(GPIO_PORT_SPI, IIC_SPICS1_PIN,GPIO_PIN_RESET)
#define  SPI_CS1_H   HAL_GPIO_WritePin(GPIO_PORT_SPI, IIC_SPICS1_PIN,GPIO_PIN_SET)

#define  SPI3_TX_OFF() {GPIOC->MODER&=~(3<<(12*2));GPIOC->MODER|=0<<(12*2);}  //PC12(MOSI)输入浮空
#define  SPI3_TX_ON()  {GPIOC->MODER&=~(3<<(12*2));GPIOC->MODER|=2<<(12*2);}  //PC12(MOSI)复用推挽输出
/******************************************************************************/
/******************************************************************************/
void delay_s(uint32_t i)
{
	while(i--);
}
/*****************************************************************************/
uint16_t ReadAS5047P(uint8_t x)
{
	uint16_t u16Data;
	
	if(x==0)SPI_CS0_L;
	else  SPI_CS1_L;
	SPIx_ReadWriteByte(0xFFFF);
	if(x==0)SPI_CS0_H;
	else  SPI_CS1_H;
	delay_s(16);  //1us，实际测试延时4读不出角度，延时8可以
	
	if(x==0)SPI_CS0_L;
	else  SPI_CS1_L;
	u16Data = SPIx_ReadWriteByte(0);
	if(x==0)SPI_CS0_H;
	else  SPI_CS1_H;
	delay_s(16);  //1us
	
	return u16Data;
}
/******************************************************************************/
uint16_t ReadTLE5012B(uint8_t x)
{
	uint16_t u16Data;
	
	if(x==0)SPI_CS0_L;
	else  SPI_CS1_L;
	SPIx_ReadWriteByte(0x8020);
	SPI3_TX_OFF();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();  //Twr_delay=130ns min，实际测试不加延时也可以
	u16Data = SPIx_ReadWriteByte(0xffff);
	
	if(x==0)SPI_CS0_H;
	else  SPI_CS1_H;
	SPI3_TX_ON();
	
	return(u16Data);
}
/*****************************************************************************/
//SPI不能用mode1，否则角度读出在0——180°，少了1个bit
uint16_t ReadMA730(uint8_t x)
{
	uint16_t u16Data;
	
	if(x==0)SPI_CS0_L;
	else  SPI_CS1_L;
	u16Data = SPIx_ReadWriteByte(0);
	if(x==0)SPI_CS0_H;
	else  SPI_CS1_H;
	
	return u16Data;
}
/******************************************************************************/
uint16_t ReadMT6701(uint8_t x)
{
	uint16_t u16Data;
	
	if(x==0)SPI_CS0_L;
	else  SPI_CS1_L;
	u16Data = SPIx_ReadWriteByte(0);
	if(x==0)SPI_CS0_H;
	else  SPI_CS1_H;
	
	return (u16Data&0xFFFC);
}
/*****************************************************************************/

