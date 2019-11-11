#include "stm32f4xx.h"
#include "PWMDevice.h"
#include "TIM_PWMOUT.h"

short Steering_Angle1=90;
short Steering_Angle2=90;
u32 LED_Brightness1=0;
u32 LED_Brightness2=0;

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

void LED_BrightnessGain(u8 LEDx,u32 Brightness_Gain)
{
	if(LEDx & LED1) LED_Brightness1=LED_Brightness1+Brightness_Gain;
	if(LEDx & LED2) LED_Brightness2=LED_Brightness1+Brightness_Gain;
}
