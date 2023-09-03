#ifndef STM32_I2C_H
#define STM32_I2C_H



/******************************************************************************/
void I2C_Init_(unsigned char x);

void IIC0_Start(void);
void IIC0_Stop(void);
unsigned char IIC0_Wait_Ack(void);
void IIC0_Ack(void);
void IIC0_NAck(void);
void IIC0_Send_Byte(unsigned char txd);
unsigned char IIC0_Read_Byte(unsigned char ack);

void IIC1_Start(void);
void IIC1_Stop(void);
unsigned char IIC1_Wait_Ack(void);
void IIC1_Ack(void);
void IIC1_NAck(void);
void IIC1_Send_Byte(unsigned char txd);
unsigned char IIC1_Read_Byte(unsigned char ack);
/******************************************************************************/


#endif
