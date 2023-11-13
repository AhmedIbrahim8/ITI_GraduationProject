/*
 * main_auto.c
 *
 *  Created on: Nov 9, 2023
 *      Author: Misra
 */



#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"


#include "../include/DCM_Interface.h"

#include "../include/GPT_Interface.h"

#include "../include/Ultrasonic_Interface.h"

#include "../include/SERVO_Interface.h"

#include "../include/App.h"

/**********************************************************/
/*********************** Global Variables *****************/
/**********************************************************/
u32 DistanceForward = 0;
u32 DistanceRight = 0;
u32 DistanceLeft = 0;

int main()
{


	/* Peripheral Enable Clock */
	Peripheral_EnableClock();

	DCM_Init(Configuration);

	Servo_Init();

	UltraSonic_Init();

	TIMER_Init(&Timer5_configuration);




	SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
	TIMER_DelayMS(TIMER5_SELECTION,500);
	while (1)
	{
		UltraSonic_Send_Pulse();
		DistanceForward=UltraSonic_Measure_Distance();
		while(DistanceForward < 70)
		{
			App_CarStop();

			UltraSonic_Send_Pulse();
			DistanceForward=UltraSonic_Measure_Distance();


			SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
			TIMER_DelayMS(TIMER5_SELECTION,1000);

			UltraSonic_Send_Pulse();
			DistanceRight=UltraSonic_Measure_Distance();

			SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
			TIMER_DelayMS(TIMER5_SELECTION,1000);

			UltraSonic_Send_Pulse();
			DistanceLeft=UltraSonic_Measure_Distance();

			SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
			TIMER_DelayMS(TIMER5_SELECTION,1000);

			UltraSonic_Send_Pulse();
			DistanceForward=UltraSonic_Measure_Distance();

			if(DistanceForward >70){
				break;
			}
			else if(DistanceRight>DistanceLeft && DistanceRight>70)
			{
				App_CarMoveRight(60);
				TIMER_DelayMS(TIMER5_SELECTION,400);/////////////////////////
			}
			else if(DistanceLeft>DistanceRight && DistanceLeft>70)
			{
				App_CarMoveLeft(60);
				TIMER_DelayMS(TIMER5_SELECTION,400);/////////////////////////
			}

		}


		UltraSonic_Send_Pulse();
		DistanceForward=UltraSonic_Measure_Distance();
		while(DistanceForward > 70){
			UltraSonic_Send_Pulse();
			DistanceForward=UltraSonic_Measure_Distance();
			App_CarMoveForward(25);
		}



	}
	return 0;
}
