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
/*	while(1)
	{
		if(PAJ7620_Gesture1_Test()&Gesture1_Forward)
		{
			LED_ON;
		}
		if(PAJ7620_Gesture1_Test()&Gesture1_Backward)
		{
			LED_OFF;
		}
	}*/
	while(1);
}
