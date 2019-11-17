#include "stm32f4xx.h"



#ifndef _PWMDEVICE_H
#define _PWMDEVICE_H

#define Steering1 0x01
#define Steering2 0x02
#define LED1 0x04
#define LED2 0x08

#endif

extern short Steering_Angle1;
extern short Steering_Angle2;
extern short LED_Brightness;

void Steering_AngleGain(u8 Steeringx,short Angle_Gain);
void LED_BrightnessGain(short Brightness_Gain);

