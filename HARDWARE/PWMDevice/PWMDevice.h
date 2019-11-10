#include "stm32f4xx.h"



#ifndef _PWMDEVICE_H
#define _PWMDEVICE_H

#define Steering1 0x01
#define Steering2 0x02
#define LED1 0x04
#define LED2 0x08

#endif

extern u32 Steering_Angle1;
extern u32 Steering_Angle2;
extern u32 LED_Brightness1;
extern u32 LED_Brightness2;

void Steering_AngleGain(u8 Steeringx,float Angle_Gain);
void LED_BrightnessGain(u8 LEDx,u32 Brightness_Gain);

