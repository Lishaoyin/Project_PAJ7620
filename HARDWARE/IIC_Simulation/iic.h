#include "stm32f4xx.h"
#include "delay.h"
#ifndef _IIC_H
#define _IIC_H

#define IIC_SCL_Port GPIOC
#define IIC_SCL_Pin GPIO_Pin_2
#define IIC_SDA_Port GPIOC
#define IIC_SDA_Pin GPIO_Pin_1
#define IIC_PeriphClock RCC_AHB1Periph_GPIOC

#define SDA_High GPIO_SetBits(IIC_SDA_Port,IIC_SDA_Pin)
#define SDA_Low GPIO_ResetBits(IIC_SDA_Port,IIC_SDA_Pin)
#define SCL_High GPIO_SetBits(IIC_SCL_Port,IIC_SCL_Pin)
#define SCL_Low GPIO_ResetBits(IIC_SCL_Port,IIC_SCL_Pin)
#define SDA_Status GPIO_ReadInputDataBit(IIC_SDA_Port,IIC_SDA_Pin)

#define ACK 1
#define NACK 0
#define AckChecked 1
#define AckError 0
#define SDA_Mode_Out 1
#define SDA_Mode_In 0

#endif
void IIC_Init(void);
void SDA_Mode(u8 Mode);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendData(u8 Data);
u8 IIC_RecieveData(u8 Ack);
void IIC_SendData_NoWait(u8 Data);
u8 IIC_RecieveData_NoAck(void);
u8 IIC_CheckAck(void);
void IIC_SendAck(u8 Ack);
