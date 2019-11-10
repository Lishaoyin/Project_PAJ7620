#include "stm32f4xx.h"
#include "delay.h"
#include "TIM_PWMOUT.h"
#include "GPIO.h" 

//Init corresponding Timmer & Config PWM output
void TIM_PWMOUT_Init(TIM_TypeDef *TIMx)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;                  //This structure for Timmer
	TIM_OCInitTypeDef  TIM_OCInitStructure;                             //This structure for PWMOUT
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);   
	
	TIM_TimeBaseInitStructure.TIM_Period=0; 	                          //Automatic reload value of counter(Arr)
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;                          //Prescaler value(Psc) Period(us)=(Arr+1)*(Psc+1)/(APB1_Clock Frequence(MHz))
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;       //The Count mode of increase
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStructure);                  //Init the Timmer
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;                     //PWM Mode1
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;              //Config the effective value(High or Low)
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;       //Enable the PWMOUT State
	
	{		
	  TIM_OC2Init(TIMx, &TIM_OCInitStructure);
	  TIM_OC3Init(TIMx, &TIM_OCInitStructure);                            //Init the Timmer PWMOUT            
	  TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable); 
	  TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);                   //Enable the Prescaler of The PWMOUT Channelx
	}
	
	TIMx->CCER&=~(TIM_CCER_CC2E|TIM_CCER_CC3E);                         //Disable All PWMOUT_Channel
	TIM_Cmd(TIMx,ENABLE); 
}

//Set Arr & Psc of the Timmer
void TIM_PWMOUT_SetPeriod(TIM_TypeDef *TIMx,u32 Arr,u32 Psc)
{
	TIM_SetAutoreload(TIMx,Arr-1);
	TIM_PrescalerConfig(TIMx,Psc-1,RESET);
}

//Set DutyCycle of PWM Wave of PWMOUT_Channelx
void TIM_PWMOUT_SetDutyCycle(TIM_TypeDef *TIMx,u8 TIM_PWMOUT_Channelx,float DutyCycle)
{
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel1) TIM_SetCompare1(TIMx,(1-DutyCycle)*TIMx->ARR);
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel2) TIM_SetCompare2(TIMx,(1-DutyCycle)*TIMx->ARR);
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel3) TIM_SetCompare3(TIMx,(1-DutyCycle)*TIMx->ARR);
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel4) TIM_SetCompare4(TIMx,(1-DutyCycle)*TIMx->ARR);
}
	
//Control The PWMOUT_Channelx,ENABLE,PWMOUT_Channelx out,DISABLE,PWMOUT_Channelx none out
void TIM_PWMOUT_ChannelCtrl(TIM_TypeDef *TIMx,u8 TIM_PWMOUT_Channelx,FunctionalState NewState)
{
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel1)
	{
		if(NewState==ENABLE) TIMx->CCER|=TIM_CCER_CC1E;
		else if(NewState==DISABLE) TIMx->CCER&=(~TIM_CCER_CC1E);
	}
	
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel2)
	{
		if(NewState==ENABLE) TIMx->CCER|=TIM_CCER_CC2E;
		else if(NewState==DISABLE) TIMx->CCER&=(~TIM_CCER_CC2E);
	}
	
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel3)
	{
		if(NewState==ENABLE) TIMx->CCER|=TIM_CCER_CC3E;
		else if(NewState==DISABLE) TIMx->CCER&=(~TIM_CCER_CC3E);
	}
	
	if(TIM_PWMOUT_Channelx&TIM_PWMOUT_Channel4)
	{
		if(NewState==ENABLE) TIMx->CCER|=TIM_CCER_CC4E;
		else if(NewState==DISABLE) TIMx->CCER&=(~TIM_CCER_CC4E);
	}
}
