/*
 * ULTRASONIC_Program.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Omar Abouzaid
 */

/*Lib Layers*/
#include "STD_Types.h"
#include "BIT_MATH.h"



/*HAL Layers*/
#include "ULTRASONIC_Interface.h"
#include "ULTRASONIC_config.h"
//#include "..\include\ULTRASONIC_private.h"


/*MCAL Layers*/
#include "GPT_Interface.h"
#include "MGPIO_Interface.h"
#include "Delay.h"



void UltraSonic_Init(void)
{
    /*Configure Trig pin as output*/
	MGPIO_SetMode(TRIG_PORT,TRIG_PIN,GENRAL_PURPOSE_OUTPUT_MODE);
	MGPIO_SetOutputPinMode(TRIG_PORT,TRIG_PIN,OUTPUT_PUSH_PULL,OUTPUT_LOW_SPEED_TYPE);
	MGPIO_SetPinValue(TRIG_PORT,TRIG_PIN,PIN_LEVEL_LOW);

    /*Configure echo pin as input*/
	MGPIO_SetMode(ECHO_PORT,ECHO_PIN,INPUT_RESET_STATE);
	MGPIO_SetInputPinMode(ECHO_PORT,ECHO_PIN,PULL_DOWN);
}

void UltraSonic_Send_Pulse(void) {

    // Set trigger pin high for 10 microseconds to generate a pulse
	MGPIO_SetPinValue(TRIG_PORT,TRIG_PIN,PIN_LEVEL_HIGH);
	delay_us(10);
	MGPIO_SetPinValue(TRIG_PORT,TRIG_PIN,PIN_LEVEL_LOW);
}

u32 UltraSonic_Measure_Distance(void){
    // Wait for the echo pin to go high
	volatile u8 Copy_pu8Data=0;


	while(Copy_pu8Data==0){
		MGPIO_GetPinValue(ECHO_PORT,ECHO_PIN,&Copy_pu8Data);
	}

    // Start timer
    volatile u32 start_time = 0;
    while(Copy_pu8Data==1){
        start_time++;
        delay_us(1);
        MGPIO_GetPinValue(ECHO_PORT,ECHO_PIN,&Copy_pu8Data);
    }
    // Calculate distance in centimeters
    volatile u32 distance = (start_time * 0.0343 * 10.7);
    return distance;



}
