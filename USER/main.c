#include "stm32f4xx.h"
#include "PAJ7620.h"
#include "iic.h"
#include "delay.h"
#include "GPIO.h"
#include "NVIC.h"
#include "EXTI.h"
#include "TIM_PWMOUT.h"
#include "PWMDevice.h"
int main(void)
{
	delay_init(168);
	NVIC_ConfigInit();
	
	TIM4_PWMOUT_GPIOInit();
	TIM3_PWMOUT_GPIOInit();
	TIM_PWMOUT_Init(TIM4);
	TIM_PWMOUT_Init(TIM3);
	
	EXTI_ConfigInit();
	
	IIC_Init();
	
	PAJ7620_Init(PAJ7620InitMode_Global);
	PAJ7620_Init(PAJ7620InitMode_Gesture);
	PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
	
	TIM_PWMOUT_SetPeriod(TIM4,20000,84);
	TIM_PWMOUT_ChannelCtrl(TIM4,TIM_PWMOUT_Channel2|TIM_PWMOUT_Channel3,ENABLE);
	
	TIM_PWMOUT_SetPeriod(TIM3,100,84);
	TIM_PWMOUT_ChannelCtrl(TIM3,TIM_PWMOUT_Channel1,ENABLE);
	
	GPIO_ConfigInit();
	
	while(1)
	{
		if(PAJ7620_Gesture1_Data&Gesture1_Up)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			
			{
				Steering_AngleGain(Steering2,10);
				TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel2,0.025+0.1*Steering_Angle1/180);
			  TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel3,0.025+0.1*Steering_Angle2/180);
			}
			
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		
		else if(PAJ7620_Gesture1_Data&Gesture1_Down)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			
			{
				Steering_AngleGain(Steering2,-10);
				TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel2,0.025+0.1*Steering_Angle1/180);
			  TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel3,0.025+0.1*Steering_Angle2/180);
			}
			
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		
		else if(PAJ7620_Gesture1_Data&Gesture1_Left)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			
			{
				Steering_AngleGain(Steering1,10);
				TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel2,0.025+0.1*Steering_Angle1/180);
			  TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel3,0.025+0.1*Steering_Angle2/180);
			}
			
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		
		else if(PAJ7620_Gesture1_Data&Gesture1_Right)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			
			{
				Steering_AngleGain(Steering1,-10);
				TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel2,0.025+0.1*Steering_Angle1/180);
			  TIM_PWMOUT_SetDutyCycle(TIM4,TIM_PWMOUT_Channel3,0.025+0.1*Steering_Angle2/180);
			}
			
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		
		else if(PAJ7620_Gesture1_Data&Gesture1_Forward)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			
			{
				LED_BrightnessGain(25);
				TIM_PWMOUT_SetDutyCycle(TIM3,TIM_PWMOUT_Channel1,LED_Brightness/100.0);
			}
			
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		
		else if(PAJ7620_Gesture1_Data&Gesture1_Backward)
		{
			PAJ7620_IT1_Cmd(Gesture_IT1_All,DISABLE);
			
			{
				LED_BrightnessGain(-25);
				TIM_PWMOUT_SetDutyCycle(TIM3,TIM_PWMOUT_Channel1,LED_Brightness/100.0);
			}
			
			PAJ7620_Gesture1_Data=0;
			PAJ7620_IT1_Cmd(Gesture_IT1_All,ENABLE);
		}
		
	}
}
