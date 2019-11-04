#include "stm32f4xx.h"
#include "iic.h"
#include "delay.h"

#ifndef _PAJ7620_H
#define _PAJ7620_H

#define PAJ7620_ID 0x73<<1
#define Bank0 0x00
#define Bank1 0x01
#define PAJ7620InitMode_Global 0x01
#define PAJ7620InitMode_Gesture 0x02
#define PAJ7620InitMode_Proximity 0x03

#define Gesture1_Up 0x01
#define Gesture1_Down 0x02
#define Gesture1_Left 0x04
#define Gesture1_Right 0x08
#define Gesture1_Forward 0x10
#define Gesture1_Backward 0x20
#define Gesture1_Clockwise 0x40
#define Gesture1_AntiClockwise 0x80
#define Gesture1_All 0xff
#define Gesture2_Wave 0x01

#define Gesture_IT1_Up 0x01
#define Gesture_IT1_Down 0x02
#define Gesture_IT1_Left 0x04
#define Gesture_IT1_Right 0x08
#define Gesture_IT1_Forward 0x10
#define Gesture_IT1_Backward 0x20
#define Gesture_IT1_Clockwise 0x40
#define Gesture_IT1_AntiClockwise 0x80
#define Gesture_IT1_All 0xff
#define Gesture_IT2_Wave 0x01


#endif

extern const unsigned char PAJ7620Global_InitArray[][2];
extern const unsigned char PAJ7620Gesture_InitArray[][2];
extern const unsigned char PAJ7620Proximity_InitArray[][2];

void PAJ7620_SendCommand(u8 Address,u8 Command);
u8 PAJ7620_ReadData(u8 Address);
void PAJ7620_SelectBank(u8 Bank);
void PAJ7620_WakeUp(void);
void PAJ7620_Init(u8 PAJ7620InitMode);
void PAJ7620_IT1_Cmd(u8 PAJ7620Gesture_IT,FunctionalState NewState);
void PAJ7620_IT2_Cmd(u8 PAJ7620Gesture_IT,FunctionalState NewState);
u8 PAJ7620_Gesture1_Test(void);
u8 PAJ7620_Gesture2_Test(void);
