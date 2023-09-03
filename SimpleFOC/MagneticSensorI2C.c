#include "MyProject.h"

/******************************************************************************/
#define  AS5600_Address  0x36
#define  RAW_Angle_Hi    0x0C
//#define  RAW_Angle_Lo    0x0D
/*****************************************************************************/
uint16_t ReadAS5600(uint8_t x)
{
	unsigned char dh,dl;		  	    																 
	
	if(x==0)
	{
		IIC0_Start();
		IIC0_Send_Byte(AS5600_Address<<1);
		IIC0_Wait_Ack();
		IIC0_Send_Byte(RAW_Angle_Hi);
		IIC0_Wait_Ack();
		IIC0_Start();
		IIC0_Send_Byte((AS5600_Address<<1)+1);
		IIC0_Wait_Ack();
		dh=IIC0_Read_Byte(1);   //1-ack for next byte
		dl=IIC0_Read_Byte(0);   //0-end trans
		IIC0_Stop();
	}
	else
	{
		IIC1_Start();
		IIC1_Send_Byte(AS5600_Address<<1);
		IIC1_Wait_Ack();
		IIC1_Send_Byte(RAW_Angle_Hi);
		IIC1_Wait_Ack();
		IIC1_Start();
		IIC1_Send_Byte((AS5600_Address<<1)+1);
		IIC1_Wait_Ack();
		dh=IIC1_Read_Byte(1);   //1-ack for next byte
		dl=IIC1_Read_Byte(0);   //0-end trans
		IIC1_Stop();
	}
	
	return ((dh<<8)+dl);
}
/*****************************************************************************/

