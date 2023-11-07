/*
 * Servo_Program.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Omar Abouzaid
 */

/*Lib Layers*/
#include "..\include\STD_Types.h"
#include "..\include\BIT_MATH.h"

/*MCAL Layers*/
#include "..\include\GPT_Interface.h"
#include "..\include\MGPIO_Interface.h"

/*HAL Layers*/
#include "..\include\SERVO_Interface.h"
#include "..\include\SERVO_config.h"
#include "..\include\SERVO_private.h"

void Servo_Init(void)
{
   /*Set pin for PWM */
	MGPIO_SetMode(SERVO_PWM_PORT,SERVO_PWM_PIN,ALTERNATE_FUNCTION_MODE);
	MGPIO_SetAlternativeFuncPin(SERVO_PWM_PORT,SERVO_PWM_PIN,AF1_TIM1_TIM2);

	//TIMER_Init(&Timer2_configuration);


	/*Select Channel for Timer2 */
	TIMER_ChannelInit(SERVO_TIMER,
			SERVO_CHANNEL,
			TIMER_PWM_MODE_1,
			ACTIVE_HIGH,
			TIMER_CHANNEL_ENABLE);


	/* Timer 2 pwm */

//	TIMER_SetPrescaler(SERVO_TIMER,15);
//
//	TIMER_SetARR(SERVO_TIMER,19999);

	TIMER_SetCompareValue(SERVO_TIMER,SERVO_CHANNEL,1700);


	TIMER_Start_Continuous(SERVO_TIMER,SERVO_CHANNEL);

}

void SERVO_SET_DIRECTION (Servo_Direction Copy_u8_direction)
{

	switch (Copy_u8_direction)
	{
	case 0 :TIMER_SetCompareValue(SERVO_TIMER,SERVO_CHANNEL,700);break;
	case 1 :TIMER_SetCompareValue(SERVO_TIMER,SERVO_CHANNEL,1700);break;
	case 2 :TIMER_SetCompareValue(SERVO_TIMER,SERVO_CHANNEL,2600);break;
	}
}


