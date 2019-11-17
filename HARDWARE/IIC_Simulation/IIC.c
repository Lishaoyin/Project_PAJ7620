#include "stm32f4xx.h"
#include "delay.h"
#include "iic.h"
void IIC_Init(void)
{
	GPIO_InitTypeDef SCL_InitStruct;
	RCC_AHB1PeriphClockCmd(IIC_PeriphClock,ENABLE);
	
	SCL_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	SCL_InitStruct.GPIO_OType=GPIO_OType_PP;
	SCL_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	SCL_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	SCL_InitStruct.GPIO_Pin=IIC_SCL_Pin|IIC_SDA_Pin;
	
	GPIO_Init(IIC_SCL_Port,&SCL_InitStruct);
	SCL_Low;
} 
void SDA_Mode(u8 Mode)
{
	GPIO_InitTypeDef SDA_OutStruct,SDA_InStruct;
	
	SDA_OutStruct.GPIO_Mode=GPIO_Mode_OUT;
	SDA_OutStruct.GPIO_OType=GPIO_OType_PP;
	SDA_OutStruct.GPIO_PuPd=GPIO_PuPd_UP;
	SDA_OutStruct.GPIO_Speed=GPIO_Speed_100MHz;
	SDA_OutStruct.GPIO_Pin=IIC_SDA_Pin;
	
	SDA_InStruct.GPIO_Mode=GPIO_Mode_IN;
	SDA_InStruct.GPIO_PuPd=GPIO_PuPd_UP;
	SDA_InStruct.GPIO_Speed=GPIO_Speed_100MHz;
	SDA_InStruct.GPIO_Pin=IIC_SDA_Pin;
	
	if(Mode==SDA_Mode_Out)
		GPIO_Init(IIC_SDA_Port,&SDA_OutStruct);
	else if(Mode==SDA_Mode_In)
		GPIO_Init(IIC_SDA_Port,&SDA_InStruct);
	SCL_Low;
}
void IIC_Start(void)
{
	SDA_Mode(SDA_Mode_Out);
	SDA_High;
	SCL_High;
	Delay;
	SDA_Low;
	Delay;
	SCL_Low;
	Delay;
}
void IIC_Stop(void)
{
	SDA_Mode(SDA_Mode_Out);
	SDA_Low;
	SCL_High;
	Delay;
	SDA_High;
	Delay;
	SCL_Low;
	Delay;
}
u8 IIC_CheckAck(void)
{
	u8 WaitTime=0;
	SDA_Mode(SDA_Mode_In);
	SCL_High;
	Delay;
	while(SDA_Status)
	{
		if(WaitTime==250) return AckError;
		WaitTime++;
	}
	SCL_Low;
	Delay;
	return AckChecked;
}
void IIC_SendAck(u8 Ack)
{
	Delay;
	SDA_Mode(SDA_Mode_Out);
	if(Ack==ACK) SDA_Low;
	else if(Ack==NACK) SDA_High;
	Delay;
	SCL_High;
	Delay;
	SCL_Low;
	Delay;
}
void IIC_SendData(u8 Data)
{
	u8 n;
	SDA_Mode(SDA_Mode_Out);
	for(n=0x80;n>0;n>>=1)
	{
		if(Data&n) SDA_High;
		else SDA_Low;
		SCL_High;
		Delay;
		SCL_Low;
		Delay;
	}
	while(IIC_CheckAck()==AckError);
}
u8 IIC_RecieveData(u8 Ack)
{
	u8 n,Data=0;
	SDA_Mode(SDA_Mode_In);
	for(n=0x80;n>0;n>>=1)
	{
		SCL_High;
		Delay;
		if(SDA_Status) Data|=n;
		SCL_Low;
		Delay;
	}
	IIC_SendAck(Ack);
	return Data;
}
void IIC_SendData_NoWait(u8 Data)
{
	u8 n;
	SDA_Mode(SDA_Mode_Out);
	for(n=0x80;n>0;n>>=1)
	{
		if(Data&n) SDA_High;
		else SDA_Low;
		SCL_High;
		Delay;
		SCL_Low;
		Delay;
	}
}
u8 IIC_RecieveData_NoAck(void)
{
	u8 n,Data=0;
	SDA_Mode(SDA_Mode_In);
	for(n=0x80;n>0;n>>=1)
	{
		SCL_High;
		Delay;
		if(SDA_Status) Data|=n;
		SCL_Low;
		Delay;
	}
	return Data;
}
