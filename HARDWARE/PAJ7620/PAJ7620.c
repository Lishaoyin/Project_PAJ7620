#include "stm32f4xx.h"
#include "iic.h"
#include "PAJ7620.h"
#include "delay.h"

u8 PAJ7620_Gesture1_Data;

void PAJ7620_SendCommand(u8 Address,u8 Command)
{
	IIC_Start();
	IIC_SendData(PAJ7620_ID);
	IIC_SendData(Address);
	IIC_SendData(Command);
	IIC_Stop();
}

u8 PAJ7620_ReadData(u8 Address)
{
	u8 Data;
	IIC_Start();
	IIC_SendData(PAJ7620_ID);
	IIC_SendData(Address);
	delay_us(5);
	IIC_Start();   
	IIC_SendData(PAJ7620_ID|0x01);   //∑¢ÀÕ∂¡√¸¡Ó(Send "Read" Command)
	Data=IIC_RecieveData(NACK);
	IIC_Stop();
	return Data;
}

void PAJ7620_SelectBank(u8 Bank)
{
	PAJ7620_SendCommand(0xef,Bank);
}

void PAJ7620_WakeUp(void)
{
	u8 WakeFlag=0x00;
	while(WakeFlag!=0x20)
	{
		IIC_Start();
		IIC_SendData_NoWait(PAJ7620_ID);
		IIC_Stop();
		delay_ms(5);
		IIC_Start();
		IIC_SendData_NoWait(PAJ7620_ID);
		IIC_Stop();
		PAJ7620_SelectBank(Bank0);
		WakeFlag=PAJ7620_ReadData(0x00);
	}
}

void PAJ7620_Init(u8 PAJ7620InitMode)
{
	u8 Init_ArraySize;
	PAJ7620_WakeUp();
	PAJ7620_SelectBank(Bank0);
	
	if(PAJ7620InitMode==PAJ7620InitMode_Global)
	{
		for(Init_ArraySize=0;Init_ArraySize<51;Init_ArraySize++)
		PAJ7620_SendCommand(PAJ7620Global_InitArray[Init_ArraySize][0],PAJ7620Global_InitArray[Init_ArraySize][1]);
	}
	
	else if(PAJ7620InitMode==PAJ7620InitMode_Gesture)
	{
		for(Init_ArraySize=0;Init_ArraySize<30;Init_ArraySize++)
		PAJ7620_SendCommand(PAJ7620Gesture_InitArray[Init_ArraySize][0],PAJ7620Gesture_InitArray[Init_ArraySize][1]);
	}
	
	else if(PAJ7620InitMode==PAJ7620InitMode_Proximity)
	{
		for(Init_ArraySize=0;Init_ArraySize<35;Init_ArraySize++)
		PAJ7620_SendCommand(PAJ7620Proximity_InitArray[Init_ArraySize][0],PAJ7620Proximity_InitArray[Init_ArraySize][1]);
	}
	
	PAJ7620_SelectBank(Bank0);
}

void PAJ7620_IT1_Cmd(u8 PAJ7620Gesture_IT,FunctionalState NewState)
{
	PAJ7620_SelectBank(Bank0);
	if(NewState==ENABLE) PAJ7620_SendCommand(0x41,0x00|PAJ7620Gesture_IT);
	else if(NewState==DISABLE) PAJ7620_SendCommand(0x41,0xff&(~PAJ7620Gesture_IT));
	PAJ7620_SelectBank(Bank0);
}

void PAJ7620_IT2_Cmd(u8 PAJ7620Gesture_IT,FunctionalState NewState)
{
	PAJ7620_SelectBank(Bank0);
	if(NewState==ENABLE) PAJ7620_SendCommand(0x42,0x00|PAJ7620Gesture_IT);
	else if(NewState==DISABLE) PAJ7620_SendCommand(0x42,0xff&(~PAJ7620Gesture_IT));
	PAJ7620_SelectBank(Bank0);
}

u8 PAJ7620_Gesture1_Detected(void)
{
	u8 Gesture_Data;
	Gesture_Data=PAJ7620_ReadData(0x43);
	PAJ7620_SelectBank(Bank0);
	return Gesture_Data;
}

u8 PAJ7620_Gesture2_Detected(void)
{
	u8 Gesture_Data;
	Gesture_Data=PAJ7620_ReadData(0x44);
	PAJ7620_SelectBank(Bank0);
	return Gesture_Data;
}

