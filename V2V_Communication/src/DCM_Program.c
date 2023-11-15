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
/************************************************************/











/*
 * @brief   this function is used to initialize the right and left DC motors
 * @param   Config is a struct of type @DCM_ConfigType
 * @retval  no return
 */
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



	/* Timer 2 pwm */
	TIMER_SetPrescaler(TIMER2_SELECTION,15);
	TIMER_SetARR(TIMER2_SELECTION,19999);

	TIMER_SetCompareValue(Config[0].Speed_TimerType,Config[0].Speed_ChannelType,0);
	TIMER_SetCompareValue(Config[1].Speed_TimerType,Config[1].Speed_ChannelType,0);

	TIMER_Start_Continuous(DCM_1_SPEED_TIMER,DCM_1_SPEED_CHANNEL);
	TIMER_Start_Continuous(DCM_2_SPEED_TIMER,DCM_2_SPEED_CHANNEL);


}




/*
 * @brief   this function is used to rotate the motor with specific speed and direction
 * @param   DCM_Number specifies the motor number of type @DCM_Index
 * @param   Duty_Cycle specifies the motor duty cycle of type @u8
 * @param   Direction  specifies the motor direction  of type @DCM_DirectionType
 * @retval  no return
 */
void DCM_Rotate(DCM_Index DCM_Number,u8 Duty_Cycle,DCM_DirectionType Direction){

	if(DCM_Number == DCM_RIGHT){
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






/*
 * @brief   this function is used to stop the motor
 * @param   DCM_Number specifies the motor number of type @DCM_Index
 * @retval  no return
 */
void DCM_Stop(DCM_Index DCM_Number){

	if(DCM_Number == DCM_RIGHT){
		TIMER_SetDutyCycle(DCM_1_SPEED_TIMER,DCM_1_SPEED_CHANNEL,1);

	}
	else if(DCM_Number == DCM_LEFT){
		TIMER_SetDutyCycle(DCM_2_SPEED_TIMER,DCM_2_SPEED_CHANNEL,1);

	}
}




/*
 * @brief   this function is used to move the car forward
 * @param   Speed specifies the speed of the car and this variable of type @u8
 * @retval  no return
 */
void App_CarMoveForward(u8 Speed){
	DCM_Rotate(DCM_RIGHT,Speed,DCM_FORWARD);
	DCM_Rotate(DCM_LEFT,Speed,DCM_FORWARD);
}


/*
 * @brief   this function is used to move the car in reverse direction
 * @param   Speed specifies the speed of the car and this variable of type @u8
 * @retval  no return
 */
void App_CarMoveReverse(u8 Speed){
	DCM_Rotate(DCM_RIGHT,Speed,DCM_REVERSE);
	DCM_Rotate(DCM_LEFT,Speed,DCM_REVERSE);
}




/*
 * @brief   this function is used to move the car right
 * @param   Speed specifies the speed of the car and this variable of type @u8
 * @retval  no return
 */
void App_CarMoveRight(u8 Speed){
	DCM_Rotate(DCM_RIGHT,Speed,DCM_REVERSE);
	DCM_Rotate(DCM_LEFT,Speed,DCM_FORWARD);
}





/*
 * @brief   this function is used to move the car left
 * @param   Speed specifies the speed of the car and this variable of type @u8
 * @retval  no return
 */
void App_CarMoveLeft(u8 Speed){
	DCM_Rotate(DCM_RIGHT,Speed,DCM_FORWARD);
	DCM_Rotate(DCM_LEFT,Speed,DCM_REVERSE);
}




/*
 * @brief   this function is used to move the car around
 * @param   Speed specifies the speed of the car and this variable of type @u8
 * @retval  no return
 */
void App_CarMoveAround(u8 Speed){
	DCM_Rotate(DCM_RIGHT,Speed,DCM_FORWARD);
	DCM_Rotate(DCM_LEFT,Speed,DCM_REVERSE);
}





/*
 * @brief   this function is used to stop the car
 * @param   Speed specifies the speed of the car and this variable of type @u8
 * @retval  no return
 */
void App_CarStop(){
	DCM_Stop(DCM_LEFT);
	DCM_Stop(DCM_RIGHT);
}


