#include "stm32f4xx.h"
#include "PAJ7620.h"
#include "iic.h"
#include "delay.h"

#ifndef _GPIO_H
#define _GPIO_H

#define PilotLED_ON GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define PilotLED_OFF GPIO_SetBits(GPIOA,GPIO_Pin_4)


#endif

void GPIO_ConfigInit(void);
void TIM4_PWMOUT_GPIOInit(void);
void TIM3_PWMOUT_GPIOInit(void);
