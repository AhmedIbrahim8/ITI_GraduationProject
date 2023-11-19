/*
 * LINE_FOLLOWER_PROGRAM.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Misra
 */

#include "STD_Types.h"
#include "BIT_MATH.h"



#include "MGPIO_Interface.h"
#include "MNVIC_Interface.h"
#include "MEXTI_Interface.h"
#include "GPT_Interface.h"

#include "LINE_FOLLOWER_CONFIG.h"
#include "LINE_FOLLOWER_INTERFACE.h"

#include "DCM_Interface.h"


u8 right_led=0;
u8 middle_led=0;
u8 left_led=0;


u8 line_follower_flag_right=0;
u8 line_follower_flag_left=0;

void RIGHT_LED_FUNCTION(void)
{
//	static u8 counter_r=0;
//	if(counter_r==0)
//	{
//		line_follower_flag_right=1;
//		MEXTI_voidInterruptTrigger(RIGHT_LED_INTERRUPT,EXTI_FALLING_EDGE);
//		counter_r=1;
//
//	}
//	else
//	{
//		line_follower_flag_right=0;
//		MEXTI_voidInterruptTrigger(RIGHT_LED_INTERRUPT,EXTI_RISING_EDGE);
//		counter_r=0;
//	}
	RIGHT_LED_INT_DISABLE();
	line_follower_flag_right=1;

}

void MIDDLE_LED_FUNCTION(void)
{

}

void LEFT_LED_FUNCTION(void)
{
//	static u8 counter_l=0;
//	if(counter_l==0)
//	{
//		line_follower_flag_left=1;
//		MEXTI_voidInterruptTrigger(LEFT_LED_INTERRUPT,EXTI_FALLING_EDGE);
//		counter_l=1;
//
//	}
//	else
//	{
//		line_follower_flag_left=0;
//		MEXTI_voidInterruptTrigger(LEFT_LED_INTERRUPT,EXTI_RISING_EDGE);
//		counter_l=0;
//	}




	LEFT_LED_INT_DISABLE();
	line_follower_flag_left=1;


}


void line_follower_init()
{
	MGPIO_SetMode(RIGHT_LED_PORT,RIGHT_LED_PIN,INPUT_RESET_STATE);
	//MGPIO_SetMode(MIDDLE_LED_PORT,MIDDLE_LED_PIN,INPUT_RESET_STATE);
	MGPIO_SetMode(LEFT_LED_PORT,LEFT_LED_PIN,INPUT_RESET_STATE);

	MGPIO_SetInputPinMode(RIGHT_LED_PORT,RIGHT_LED_PIN,PULL_UP);
	//MGPIO_SetInputPinMode(MIDDLE_LED_PORT,RIGHT_LED_PIN,PULL_UP);
	MGPIO_SetInputPinMode(LEFT_LED_PORT,RIGHT_LED_PIN,PULL_UP);

	MEXTI_voidInterruptSetPort(RIGHT_LED_INTERRUPT,RIGHT_LED_PORT);
	//MEXTI_voidInterruptSetPort(MIDDLE_LED_INTERRUPT,MIDDLE_LED_PORT);
	MEXTI_voidInterruptSetPort(LEFT_LED_INTERRUPT,LEFT_LED_PORT);

	MEXTI_voidInterruptTrigger(RIGHT_LED_INTERRUPT,RIGHT_INTERRUPT_TRIGGER);
	//MEXTI_voidInterruptTrigger(MIDDLE_LED_INTERRUPT,MIDDLE_INTERRUPT_TRIGGER);
	MEXTI_voidInterruptTrigger(LEFT_LED_INTERRUPT,LEFT_INTERRUPT_TRIGGER);

	MEXTI_voidSetCallBack(RIGHT_LED_INTERRUPT,RIGHT_LED_FUNCTION);
	//MEXTI_voidSetCallBack(MIDDLE_LED_INTERRUPT,MIDDLE_LED_FUNCTION);
	MEXTI_voidSetCallBack(LEFT_LED_INTERRUPT,LEFT_LED_FUNCTION);

	RIGHT_LED_INT_ENABLE();
	//MIDDLE_LED_INT_ENABLE();
	LEFT_LED_INT_ENABLE();


	MNVIC_VoidEnbleInterrupt(EXTINT_EXTI15_10_POSITION);

}



void RIGHT_LED_INT_ENABLE(void)
{
	MEXTI_voidInterruptEnableDisable(RIGHT_LED_INTERRUPT,EXTI_ENABLE);
}

void RIGHT_LED_INT_DISABLE(void)
{
	MEXTI_voidInterruptEnableDisable(RIGHT_LED_INTERRUPT,EXTI_DISABLE);
}




void MIDDLE_LED_INT_ENABLE(void)
{
	MEXTI_voidInterruptEnableDisable(MIDDLE_LED_INTERRUPT,EXTI_ENABLE);
}

void MIDDLE_LED_INT_DISABLE(void)
{
	MEXTI_voidInterruptEnableDisable(MIDDLE_LED_INTERRUPT,EXTI_DISABLE);
}






void LEFT_LED_INT_ENABLE(void)
{
	MEXTI_voidInterruptEnableDisable(LEFT_LED_INTERRUPT,EXTI_ENABLE);
}
void LEFT_LED_INT_DISABLE(void)
{
	MEXTI_voidInterruptEnableDisable(LEFT_LED_INTERRUPT,EXTI_DISABLE);
}
