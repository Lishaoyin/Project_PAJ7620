#include "stm32f4xx.h"
#include "PAJ7620.h"
#include "iic.h"
#include "delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "EXTI.h"
int main(void)
{
	delay_init();
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
			LED_ON;
			PAJ7620_Gesture1_Data=0;
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Down)
		{
			LED_Twinkle(500,4);
			PAJ7620_Gesture1_Data=0;
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Left)
		{
			LED_Twinkle(400,5);
			PAJ7620_Gesture1_Data=0;
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Right)
		{
			LED_Twinkle(300,7);
			PAJ7620_Gesture1_Data=0;
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Forward)
		{
			LED_Twinkle(200,10);
			PAJ7620_Gesture1_Data=0;
		}
		else if(PAJ7620_Gesture1_Data&Gesture1_Backward)
		{
			LED_Twinkle(100,20);
			PAJ7620_Gesture1_Data=0;
		}
	}
}
