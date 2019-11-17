#include "stm32f4xx.h"
#include "EXTI.h"
#include "GPIO.h"
#include "PAJ7620.h"
#include "delay.h"
void EXTI_ConfigInit(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource2);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!= RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
	  PAJ7620_Gesture1_Data=PAJ7620_Gesture1_Detected();
	}
	PilotLED_ON;
	delay_ms(100);
	PilotLED_OFF;
}
