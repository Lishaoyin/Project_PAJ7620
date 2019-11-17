#include "stm32f4xx.h"
#include "PWMDevice.h"
#include "TIM_PWMOUT.h"

short Steering_Angle1=90;
short Steering_Angle2=90;
short LED_Brightness=50;

void Steering_AngleGain(u8 Steeringx,short Angle_Gain)
{
	if(Steeringx & Steering1) 
	{
		if(Steering_Angle1+Angle_Gain<0 || Steering_Angle1+Angle_Gain>180) return;
		Steering_Angle1=Steering_Angle1+Angle_Gain;
	}
	if(Steeringx & Steering2)
	{		
		if(Steering_Angle2+Angle_Gain<0 || Steering_Angle2+Angle_Gain>180) return;
		Steering_Angle2=Steering_Angle2+Angle_Gain;
	}
}

void LED_BrightnessGain(short Brightness_Gain)
{
	if(LED_Brightness+Brightness_Gain<0 || LED_Brightness+Brightness_Gain>100) return;
	LED_Brightness=LED_Brightness+Brightness_Gain;
}
