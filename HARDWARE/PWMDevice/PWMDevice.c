#include "stm32f4xx.h"
#include "PWMDevice.h"
#include "TIM_PWMOUT.h"

u32 Steering_Angle1=0;
u32 Steering_Angle2=90;
u32 LED_Brightness1=0;
u32 LED_Brightness2=0;

void Steering_AngleGain(u8 Steeringx,float Angle_Gain)
{
	if(Steeringx & Steering1) Steering_Angle1=Steering_Angle1+Angle_Gain;
	if(Steeringx & Steering2) Steering_Angle2=Steering_Angle2+Angle_Gain;
}

void LED_BrightnessGain(u8 LEDx,u32 Brightness_Gain)
{
	if(LEDx & LED1) LED_Brightness1=LED_Brightness1+Brightness_Gain;
	if(LEDx & LED2) LED_Brightness2=LED_Brightness1+Brightness_Gain;
}
