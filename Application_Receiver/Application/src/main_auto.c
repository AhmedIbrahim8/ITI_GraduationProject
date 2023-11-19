///*
// * main_auto.c
// *
// *  Created on: Nov 9, 2023
// *      Author: Misra
// */
//
//
//
//#include "../include/STD_Types.h"
//#include "../include/BIT_MATH.h"
//
//
//#include "../include/DCM_Interface.h"
//
//#include "../include/GPT_Interface.h"
//
//#include "../include/Ultrasonic_Interface.h"
//
//#include "../include/SERVO_Interface.h"
//
//#include "../include/App.h"
//
///**********************************************************/
///*********************** Global Variables *****************/
///**********************************************************/
//u32 DistanceForward = 0;
//u32 DistanceRight = 0;
//u32 DistanceLeft = 0;
//
//int main()
//{
//
//
//	/* Peripheral Enable Clock */
//	Peripheral_EnableClock();
//
//	DCM_Init(Configuration);
//
//	Servo_Init();
//
//	UltraSonic_Init();
//
//	TIMER_Init(&Timer5_configuration);
//
//
//
//
//	SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//	TIMER_DelayMS(TIMER5_SELECTION,500);
//	while (1)
//	{
//		UltraSonic_Send_Pulse();
//		DistanceForward=UltraSonic_Measure_Distance();
//		while(DistanceForward < 60)
//		{
//			App_CarStop();
//
//			UltraSonic_Send_Pulse();
//			DistanceForward=UltraSonic_Measure_Distance();
//
//
//			SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
//			TIMER_DelayMS(TIMER5_SELECTION,1000);
//
//			UltraSonic_Send_Pulse();
//			DistanceRight=UltraSonic_Measure_Distance();
//
//			SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
//			TIMER_DelayMS(TIMER5_SELECTION,1000);
//
//			UltraSonic_Send_Pulse();
//			DistanceLeft=UltraSonic_Measure_Distance();
//
//			SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//			TIMER_DelayMS(TIMER5_SELECTION,1000);
//
//			if(DistanceRight>DistanceLeft )
//			{
//				App_CarMoveRight(20);
//				TIMER_DelayMS(TIMER5_SELECTION,1000);/////////////////////////
//			}
//			else
//			{
//				App_CarMoveLeft(20);
//				TIMER_DelayMS(TIMER5_SELECTION,1000);/////////////////////////
//			}
//
//		}
//
//
//		UltraSonic_Send_Pulse();
//		DistanceForward=UltraSonic_Measure_Distance();
//		while(DistanceForward < 80){
//			UltraSonic_Send_Pulse();
//			DistanceForward=UltraSonic_Measure_Distance();
//			App_CarMoveForward(10);
//		}
//
////
////
////		if (DistanceForward< 60)
////		{
////			App_CarStop();
////
////			SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
////			TIMER_DelayMS(TIMER5_SELECTION,500);
////
////			UltraSonic_Send_Pulse();
////			DistanceRight=UltraSonic_Measure_Distance();
////
////			SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
////			TIMER_DelayMS(TIMER5_SELECTION,500);
////
////			UltraSonic_Send_Pulse();
////			DistanceLeft=UltraSonic_Measure_Distance();
////
////			SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
////			TIMER_DelayMS(TIMER5_SELECTION,500);
////
////			if(DistanceRight>DistanceLeft )
////			{
////				App_CarMoveRight(30);
////				TIMER_DelayMS(TIMER5_SELECTION,1000);/////////////////////////
////			}
////			else
////			{
////				App_CarMoveLeft(30);
////				TIMER_DelayMS(TIMER5_SELECTION,1000);/////////////////////////
////			}
////
////		}
////		else
////		{
////			for(u8 i=10;i<30;i++)
////			App_CarMoveForward(i);
////			TIMER_DelayMS(TIMER5_SELECTION,10);
////
////			while(DistanceForward< 60)
////			{
////				UltraSonic_Send_Pulse();
////				DistanceForward=UltraSonic_Measure_Distance();
////			}
////
////		}
//
//	}
//	return 0;
//}
