#include "stm32f4xx.h"
#include "delay.h"

void TIM2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period = 1; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=1;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM2
}

void WaitHere(u16 Psc,u32 Arr)
{
	TIM_PrescalerConfig(TIM2,Psc,RESET);
	TIM_SetAutoreload(TIM2,Arr);
	
	while(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==RESET);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
}


void delay_init(void)
{
	TIM2_Init();
}

void delay_us(u32 T_us)
{
	TIM_Cmd(TIM2,ENABLE);
	WaitHere(84,T_us);
	TIM_Cmd(TIM2,DISABLE);
}

void delay_ms(u32 T_ms)
{
	TIM_Cmd(TIM2,ENABLE);
	WaitHere(8400,T_ms*10);
	TIM_Cmd(TIM2,DISABLE);
}
