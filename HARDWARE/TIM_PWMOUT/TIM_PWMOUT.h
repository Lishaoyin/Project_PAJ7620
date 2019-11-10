#include "stm32f4xx.h"

#ifndef _TIM_PWMOUT_H
#define _TIM_PWMOUT_H

#define TIM_PWMOUT_Channel1 0x01
#define TIM_PWMOUT_Channel2 0x02
#define TIM_PWMOUT_Channel3 0x04
#define TIM_PWMOUT_Channel4 0x08




#endif 

void TIM_PWMOUT_GPIO_Init(void);
void TIM_PWMOUT_Init(TIM_TypeDef *TIMx);
void TIM_PWMOUT_SetPeriod(TIM_TypeDef *TIMx,u32 Arr,u32 Psc);
void TIM_PWMOUT_SetDutyCycle(TIM_TypeDef *TIMx,u8 TIM_PWMOUT_Channelx,float DutyCycle);
void TIM_PWMOUT_ChannelCtrl(TIM_TypeDef *TIMx,u8 TIM_PWMOUT_Channelx,FunctionalState NewState);
