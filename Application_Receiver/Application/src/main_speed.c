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
//#include "../include/OPTO_COUPLER_INTERFACE.h"
//
//#include "../include/HIR_Interface.h"
//
//#include "../include/App.h"
//
///**********************************************************/
///*********************** Global Variables *****************/
///**********************************************************/
//
//
//
//
//
//
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
////	Speed_sensor_Init();
//
//	TIMER_Init(&Timer5_configuration);
//
//	HIR_TRASMITTER_INIT();
//
//
//
//	UltraSonic_Init();
//
//	Servo_Init();
//
//
//	SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//	TIMER_DelayMS(TIMER5_SELECTION,500);
//
//
//	//App_CarMoveForward(50);			//70 pwm = 8 turns per second
//
//	while (1)
//	{
//
//
//		UltraSonic_Send_Pulse();
//		DistanceForward=UltraSonic_Measure_Distance();
//		while(DistanceForward < 70)
//		{
//			App_CarStop();
//
//			UltraSonic_Send_Pulse();
//			DistanceForward=UltraSonic_Measure_Distance();
//
//			IR_SNED_FRAME(5,DistanceForward);
//			TIMER_DelayMS(TIMER5_SELECTION,100);
//
//		}
//
//
//		UltraSonic_Send_Pulse();
//		DistanceForward=UltraSonic_Measure_Distance();
//		while(DistanceForward > 70){
//			UltraSonic_Send_Pulse();
//			DistanceForward=UltraSonic_Measure_Distance();
//
//			IR_SNED_FRAME(5,DistanceForward);
//			TIMER_DelayMS(TIMER5_SELECTION,100);
//
//			App_CarMoveForward(25);
//		}
//
//
//
//	}
//	return 0;
//}
//
