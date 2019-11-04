#include "stm32f4xx.h"

#ifndef _DELAY_H
#define _DELAY_H



#endif
void TIM2_Init(void);
void WaitHere(u16 Psc,u32 Arr);
void delay_init(void);
void delay_us(u32 T_us);
void delay_ms(u32 T_ms);
