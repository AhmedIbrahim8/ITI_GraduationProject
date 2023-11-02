/*******************************************************************************************/
/*  Module       :   Ultrasonic                                                            */
/*  File Name    :   Ultrasonic.c                                                          */
/*  Description  :   Source File of the Ultrasonic  Driver                                 */
/*  Author       :   Mahmoud Salah                                                         */
/*  Date         :   01/11/2023                                                            */
/*******************************************************************************************/

/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

/* RCC Specified Header Files */
#include "../include/GPT_Interface.h"

#include "../include/MGPIO_Interface.h"
#include "../include/MNVIC_Interface.h"


void Ultrsonic_Init(void) {



	/* Ultra sonic Trigger Pin Initialization */
	MGPIO_SetMode(PORTB, PIN0, GENRAL_PURPOSE_OUTPUT_MODE);
	MGPIO_SetOutputPinMode(PORTB, PIN0, OUTPUT_PUSH_PULL,OUTPUT_MEDIUM_SPEED_TYPE);

	/* Ultra sonic echo Pin Initialization */
	MGPIO_SetMode(PORTA, PIN8, ALTERNATE_FUNCTION_MODE);
	MGPIO_SetAlternativeFuncPin(PORTA, PIN8, AF1_TIM1_TIM2);

	/* Enable the  NVIC for the Timer 1 */
	MNVIC_VoidEnbleInterrupt(EXTINT_TIM1CC_POSITION);
	/* Initialize the ICU Unit of TIMER 1 for the echo Pin of the ultra sonic sensor*/
	voidICU_Init();

}

void Ultrsonic_Trigger(void)
{
	//TIMER_DelayUS(TIMER5_SELECTION,3);

	MGPIO_SetPinValue(PORTB,PIN0,PIN_LEVEL_HIGH);

	TIMER_DelayUS(TIMER5_SELECTION,10);

	MGPIO_SetPinValue(PORTB,PIN0,PIN_LEVEL_LOW);

	TIMER_DelayUS(TIMER5_SELECTION, 250);

}

float UltrasonicCalculateDistance(void)
{
	volatile f32 Local_f32Distance = 0;
	volatile f32 Local_f32Ton = 0;

	Local_f32Ton = f32MeasureTon();

	volatile float speedOfSound = 345.2; // Speed of sound in air in m/s
	volatile float soundTravelTime = (Local_f32Ton / 1000000UL); // Convert pulse width from us to seconds

	Local_f32Distance = ((speedOfSound * soundTravelTime) / 2); // Distance in meters
	return Local_f32Distance * 100; // Distance in meters

}
