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

/* DCM Specified Header Files */
#include "../include/DCM_Interface.h"
#include "../include/DCM_Config.h"
#include "../include/DCM_Private.h"


/* Used MCAL Drivers */
#include "../include/GPT_Interface.h"
#include "../include/MGPIO_Interface.h"


void DCM_Init(DCM_ConfigType *Config){
	u8 counter = 0;
	for(counter=0;counter<NUMBER_OF_DC_MOTOR;counter++){
		/* Adjust the DIO Pin for Speed Pin */
		MGPIO_SetMode(Config[counter]->Speed_Port_ID,Config[counter]->Speed_Pin_ID,ALTERNATE_FUNCTION_MODE);
		switch(Config[counter]->Speed_TimerType){
		case TIMER2_SELECTION:
			MGPIO_SetAlternativeFuncPin(Config[counter]->Speed_Port_ID,Config[counter]->Speed_Pin_ID,AF1_TIM1_TIM2);
			break;
		case TIMER3_SELECTION:
		case TIMER4_SELECTION:
		case TIMER5_SELECTION:
			MGPIO_SetAlternativeFuncPin(Config[counter]->Speed_Port_ID,Config[counter]->Speed_Pin_ID,AF2_TIM3_TIM4_TIM5);
			break;
		}

		/* Adjust the pin output for IN1 of Motor Driver */
		MGPIO_SetMode(Config[counter]->IN1_Port_ID,Config[counter]->IN1_Pin_ID,GENRAL_PURPOSE_OUTPUT_MODE);
		MGPIO_SetOutputPinMode(Config[counter]->IN1_Port_ID,Config[counter]->IN1_Pin_ID,OUTPUT_PUSH_PULL,OUTPUT_LOW_SPEED_TYPE);
		MGPIO_SetPinValue(Config[counter]->IN1_Port_ID,Config[counter]->IN1_Pin_ID,PIN_LEVEL_LOW);

		/* Adjust the pin output for IN2 of Motor Driver */
		MGPIO_SetMode(Config[counter]->IN2_Port_ID,Config[counter]->IN2_Pin_ID,GENRAL_PURPOSE_OUTPUT_MODE);
		MGPIO_SetOutputPinMode(Config[counter]->IN2_Port_ID,Config[counter]->IN2_Pin_ID,OUTPUT_PUSH_PULL,OUTPUT_LOW_SPEED_TYPE);
		MGPIO_SetPinValue(Config[counter]->IN2_Port_ID,Config[counter]->IN2_Pin_ID,PIN_LEVEL_LOW);

	}

	/* Set the PWM For the speed Pin */
	TIMER_Init(&Timer2_configuration);

	TIMER_ChannelInit(Config[0]->Speed_TimerType,
			TIMER_CHANNEL_1,
			TIMER_PWM_MODE_1,
			ACTIVE_HIGH,
			TIMER_CHANNEL_ENABLE);
	TIMER_ChannelInit(Config[1]->Speed_TimerType,
			TIMER_CHANNEL_2,
			TIMER_PWM_MODE_1,
			ACTIVE_HIGH,
			TIMER_CHANNEL_ENABLE);

	/* Timer 5 pwm */
	TIMER_SetPrescaler(TIMER5_SELECTION,15);
	TIMER_SetARR(TIMER5_SELECTION,59999);

	TIMER_SetCompareValue(TIMER5_SELECTION,TIMER_CHANNEL_1,9999);
	TIMER_SetCompareValue(TIMER5_SELECTION,TIMER_CHANNEL_2,999);
	TIMER_SetCompareValue(TIMER5_SELECTION,TIMER_CHANNEL_3,5999);
	TIMER_SetCompareValue(TIMER5_SELECTION,TIMER_CHANNEL_4,4999);


	TIMER_Start_Continuous(TIMER5_SELECTION,TIMER_ALL_CHANNELS);
}


void DCM_Rotate(DcMotor_State state,uint8 speed){

}
