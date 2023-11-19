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
//#include "../include/LINE_FOLLOWER_INTERFACE.h"
//
//#include "../include/App.h"
//
///**********************************************************/
///*********************** Global Variables *****************/
///**********************************************************/
//
//
////lane tracking
//int main(){
//
//
//	/* Peripheral Enable Clock */
//
//
//	Peripheral_EnableClock();
//
//	DCM_Init(Configuration);
//
//	Servo_Init();
//
//	TIMER_Init(&Timer5_configuration);
//
//	//line_follower_init();
//
//
//	SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//	TIMER_DelayMS(TIMER5_SELECTION,1000);
//
//
//	while(1){
//
//		if(line_follower_flag_right==0 && line_follower_flag_left==1){
//			App_CarMoveRight(40);
//			line_follower_flag_left=0;
//			TIMER_DelayMS(TIMER5_SELECTION,400);
//			LEFT_LED_INT_ENABLE();
//
//		}
//		else if(line_follower_flag_right==1 && line_follower_flag_left==0){
//			App_CarMoveLeft(40);
//			line_follower_flag_right=0;
//			TIMER_DelayMS(TIMER5_SELECTION,400);
//			RIGHT_LED_INT_ENABLE();
//		}
//		else if(line_follower_flag_right==0 && line_follower_flag_left==0){
//			App_CarMoveForward(20);
//		}
//		else{
//			App_CarStop();
//		}
//
//
//
//
//
//		////		App_CarMoveForward(80);
//		//
//		//		SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//		//		TIMER_DelayMS(TIMER5_SELECTION,1000);
//		//		Ultrsonic_Trigger();
//		//		DistanceForward = UltrasonicCalculateDistance();
//		//		if(40>(u32)DistanceForward){
//		//			App_CarStop();
//		//			SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
//		//
//		//			Ultrsonic_Trigger();
//		//			DistanceRight = UltrasonicCalculateDistance();
//		//			TIMER_DelayMS(TIMER5_SELECTION,1000);
//		//			SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
//		//
//		//			Ultrsonic_Trigger();
//		//			DistanceLeft = UltrasonicCalculateDistance();
//		//			TIMER_DelayMS(TIMER5_SELECTION,1000);
//		//			SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//		//			TIMER_DelayMS(TIMER5_SELECTION,1000);
//		//			if(DistanceRight > DistanceLeft ){
//		//				App_CarMoveRight(20);
//		//			}
//		//			else if(DistanceLeft > DistanceRight){
//		//				App_CarMoveLeft(20);
//		//			}
//		//
//		//		}
//		//		else if(60>(u32)DistanceForward){
//		//			App_CarMoveForward(20);
//		//		}
//		//
//		//
//		//
//		////		SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
//		////		TIMER_DelayMS(TIMER5_SELECTION,1000);
//		////		SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//		////		TIMER_DelayMS(TIMER5_SELECTION,1000);
//		////		SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
//		////		TIMER_DelayMS(TIMER5_SELECTION,1000);
//		//
//		//
//		//
//		//
//		//
//		//
//		////		Ultrsonic_Trigger();
//		////		distance = UltrasonicCalculateDistance();
//		////		if(5>(u32)distance){
//		////			App_CarStop();
//		////		}
//		////		else if(10>(u32)distance){
//		////			App_CarMoveForward(20);
//		////		}
//		////		else if(20>(u32)distance){
//		////			App_CarMoveForward(40);
//		////		}
//		////		else if(30>(u32)distance){
//		////			App_CarMoveForward(60);
//		////		}
//		////		else if(40>(u32)distance){
//		////			App_CarMoveForward(80);
//		////		}
//		////		else{
//		////			App_CarMoveForward(100);
//		////		}
//
//
//		//		App_CarMoveForward(30);
//		//
//		//		if(line_follower_flag==1)
//		//		{
//		//
//		//			App_CarMoveLeft(30);
//		//			TIMER_DelayMS(TIMER5_SELECTION,500);
//		//			line_follower_flag=0;
//		//			RIGHT_LED_INT_ENABLE();
//		//		}
//		//		else if (line_follower_flag==2)
//		//		{
//		//			App_CarMoveRight(30);
//		//			TIMER_DelayMS(TIMER5_SELECTION,500);
//		//			line_follower_flag=0;
//		//			LEFT_LED_INT_ENABLE();
//		//		}
//		//
//
//	}
//
//
//	return 0;
//}
//
//
//
////end of the code
//
//
//
//
//
//
//
//
//
////
////
////
////int main(){
////
////
////	/* Peripheral Enable Clock */
////
////
////	Peripheral_EnableClock();
////
////	DCM_Init(Configuration);
////
////	Servo_Init();
////
////	Ultrsonic_Init();
////
////	TIMER_Init(&Timer5_configuration);
////
////	line_follower_init();
////
////
////	SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
////	TIMER_DelayMS(TIMER5_SELECTION,1000);
////
////
////	while(1)
////	{
////		SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
////		TIMER_DelayMS(TIMER5_SELECTION,1000);
////
////
////		SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
////		TIMER_DelayMS(TIMER5_SELECTION,1000);
////	}
////
////
////	return 0;
////}
