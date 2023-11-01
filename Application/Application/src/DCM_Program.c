/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCM_Program.c                                                         */
/*  Description  :   Source File of the DCM  Driver                                        */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   31/10/2023                                                            */
/*******************************************************************************************/


/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"




/* Used MCAL Drivers */
#include "../include/GPT_Interface.h"
#include "../include/MGPIO_Interface.h"

/* DCM Specified Header Files */
#include "../include/DCM_Interface.h"
#include "../include/DCM_Config.h"
#include "../include/DCM_Private.h"

void DCM_Init(DCM_ConfigType *Config){
	u8 counter = 0;
	for(counter=0;counter<NUMBER_OF_DC_MOTOR;counter++){
		/* Adjust the DIO Pin for Speed Pin */
		MGPIO_SetMode(Config[counter].Speed_Port_ID,Config[counter].Speed_Pin_ID,ALTERNATE_FUNCTION_MODE);
		switch(Config[counter].Speed_TimerType){
		case TIMER2_SELECTION:
			MGPIO_SetAlternativeFuncPin(Config[counter].Speed_Port_ID,Config[counter].Speed_Pin_ID,AF1_TIM1_TIM2);
			break;
		case TIMER3_SELECTION:
		case TIMER4_SELECTION:
		case TIMER5_SELECTION:
			MGPIO_SetAlternativeFuncPin(Config[counter].Speed_Port_ID,Config[counter].Speed_Pin_ID,AF2_TIM3_TIM4_TIM5);
			break;
		}

		/* Adjust the pin output for IN1 of Motor Driver */
		MGPIO_SetMode(Config[counter].IN1_Port_ID,Config[counter].IN1_Pin_ID,GENRAL_PURPOSE_OUTPUT_MODE);
		MGPIO_SetOutputPinMode(Config[counter].IN1_Port_ID,Config[counter].IN1_Pin_ID,OUTPUT_PUSH_PULL,OUTPUT_LOW_SPEED_TYPE);
		MGPIO_SetPinValue(Config[counter].IN1_Port_ID,Config[counter].IN1_Pin_ID,PIN_LEVEL_LOW);

		/* Adjust the pin output for IN2 of Motor Driver */
		MGPIO_SetMode(Config[counter].IN2_Port_ID,Config[counter].IN2_Pin_ID,GENRAL_PURPOSE_OUTPUT_MODE);
		MGPIO_SetOutputPinMode(Config[counter].IN2_Port_ID,Config[counter].IN2_Pin_ID,OUTPUT_PUSH_PULL,OUTPUT_LOW_SPEED_TYPE);
		MGPIO_SetPinValue(Config[counter].IN2_Port_ID,Config[counter].IN2_Pin_ID,PIN_LEVEL_LOW);

	}

	/* Set the PWM For the speed Pin */
	TIMER_Init(&Timer2_configuration);

	TIMER_ChannelInit(Config[0].Speed_TimerType,
			Config[0].Speed_ChannelType,
			TIMER_PWM_MODE_1,
			ACTIVE_HIGH,
			TIMER_CHANNEL_ENABLE);
	TIMER_ChannelInit(Config[1].Speed_TimerType,
			Config[1].Speed_ChannelType,
			TIMER_PWM_MODE_1,
			ACTIVE_HIGH,
			TIMER_CHANNEL_ENABLE);

	/* Timer 5 pwm */
	TIMER_SetPrescaler(TIMER5_SELECTION,15);
	TIMER_SetARR(TIMER5_SELECTION,19999);

	TIMER_SetCompareValue(Config[0].Speed_TimerType,Config[0].Speed_ChannelType,0);
	TIMER_SetCompareValue(Config[1].Speed_TimerType,Config[1].Speed_ChannelType,0);


}




void DCM_Rotate(DCM_Index DCM_Number,u8 Duty_Cycle,DCM_DirectionType Direction){

	if(DCM_Number == DCM_RIGHT){
		TIMER_Start_Continuous(DCM_1_SPEED_TIMER,DCM_1_SPEED_CHANNEL);
		TIMER_SetDutyCycle(DCM_1_SPEED_TIMER,DCM_1_SPEED_CHANNEL,Duty_Cycle);
		if(Direction == DCM_FORWARD){
			MGPIO_SetPinValue(DCM_1_IN1_PORT_ID,DCM_1_IN1_PIN_ID,PIN_LEVEL_HIGH);
			MGPIO_SetPinValue(DCM_1_IN2_PORT_ID,DCM_1_IN2_PIN_ID,PIN_LEVEL_LOW);
		}
		else if(Direction == DCM_REVERSE){
			MGPIO_SetPinValue(DCM_1_IN1_PORT_ID,DCM_1_IN1_PIN_ID,PIN_LEVEL_LOW);
			MGPIO_SetPinValue(DCM_1_IN2_PORT_ID,DCM_1_IN2_PIN_ID,PIN_LEVEL_HIGH);
		}
	}
	else if(DCM_Number == DCM_LEFT){
		TIMER_Start_Continuous(DCM_2_SPEED_TIMER,DCM_2_SPEED_CHANNEL);
		TIMER_SetDutyCycle(DCM_2_SPEED_TIMER,DCM_2_SPEED_CHANNEL,Duty_Cycle);
		if(Direction == DCM_FORWARD){
			MGPIO_SetPinValue(DCM_2_IN1_PORT_ID,DCM_2_IN1_PIN_ID,PIN_LEVEL_HIGH);
			MGPIO_SetPinValue(DCM_2_IN1_PORT_ID,DCM_2_IN2_PIN_ID,PIN_LEVEL_LOW);
		}
		else if(Direction == DCM_REVERSE){
			MGPIO_SetPinValue(DCM_2_IN1_PORT_ID,DCM_2_IN1_PIN_ID,PIN_LEVEL_LOW);
			MGPIO_SetPinValue(DCM_2_IN1_PORT_ID,DCM_2_IN2_PIN_ID,PIN_LEVEL_HIGH);
		}
	}
}


void DCM_Stop(DCM_Index DCM_Number){

	if(DCM_Number == DCM_RIGHT){
		TIMER_Stop(DCM_1_SPEED_TIMER,DCM_1_SPEED_CHANNEL);

	}
	else if(DCM_Number == DCM_LEFT){
		TIMER_Stop(DCM_2_SPEED_TIMER,DCM_2_SPEED_CHANNEL);

	}
}




