#include "stm32f4xx.h"
#include "PAJ7620.h"
#include "iic.h"
#include "delay.h"
#include "GPIO.h"

void GPIO_ConfigInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

void LED_Twinkle(u16 Twinkle_Perid ,u8 Twinkle_Times)
{
	u8 Times;
	for(Times=0;Times<Twinkle_Times;Times++)
	{
		LED_ON;
		delay_ms(Twinkle_Perid/2);
		LED_OFF;
		delay_ms(Twinkle_Perid/2);
	}
}
