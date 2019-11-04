#include "stm32f4xx.h"
#include "PAJ7620.h"
#include "iic.h"
#include "delay.h"

#ifndef _GPIO_H
#define _GPIO_H

#define LED_OFF GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define LED_ON GPIO_ResetBits(GPIOC,GPIO_Pin_0)


#endif

void GPIO_ConfigInit(void);
void LED_Twinkle(u16 Twinkle_Perid ,u8 Twinkle_Times);
