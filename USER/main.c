#include "stm32f4xx.h"
#include "PAJ7620.h"
#include "iic.h"
#include "delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "EXTI.h"
int main(void)
{
	delay_init(168);
	NVIC_ConfigInit();
	GPIO_ConfigInit();
	EXTI_ConfigInit();
	IIC_Init();
	PAJ7620_Init(PAJ7620InitMode_Global);
	PAJ7620_Init(PAJ7620InitMode_Gesture);
	LED_OFF;
	PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
	while(1)
	{
		if(PAJ7620_Gesture1_Data&Gesture1_Up)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			LED_Twinkle(1000,1);
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Down)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
		  LED_Twinkle(1000,1);
			LED_Twinkle(1000,1);
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Left)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			LED_Twinkle(200,5);
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Right)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			LED_Twinkle(200,5);
			delay_ms(500);
			LED_Twinkle(200,5);
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Forward)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			LED_Twinkle(100,10);
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Backward)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			LED_Twinkle(100,10);
			delay_ms(500);
			LED_Twinkle(100,10);
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
	}
}
