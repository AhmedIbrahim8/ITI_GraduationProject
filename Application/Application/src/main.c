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
f32 DistanceForward = 0;
f32 DistanceRight = 0;
f32 DistanceLeft = 0;

int main(){


	/* Peripheral Enable Clock */
	Peripheral_EnableClock();

	DCM_Init(Configuration);

	Servo_Init();

	Ultrsonic_Init();

	TIMER_Init(&Timer5_configuration);


	/* Set the PWM For the speed Pin */





	while(1){
//		App_CarMoveForward(80);

		SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
		TIMER_DelayMS(TIMER5_SELECTION,1000);
		Ultrsonic_Trigger();
		DistanceForward = UltrasonicCalculateDistance();
		if(40>(u32)DistanceForward){
			App_CarStop();
			SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);

			Ultrsonic_Trigger();
			DistanceRight = UltrasonicCalculateDistance();
			TIMER_DelayMS(TIMER5_SELECTION,1000);
			SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);

			Ultrsonic_Trigger();
			DistanceLeft = UltrasonicCalculateDistance();
			TIMER_DelayMS(TIMER5_SELECTION,1000);
			SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
			TIMER_DelayMS(TIMER5_SELECTION,1000);
			if(DistanceRight > DistanceLeft ){
				App_CarMoveRight(20);
			}
			else if(DistanceLeft > DistanceRight){
				App_CarMoveLeft(20);
			}

		}
		else if(60>(u32)DistanceForward){
			App_CarMoveForward(20);
		}



//		SERVO_SET_DIRECTION(SERVO_DIRECTION_RIGHT);
//		TIMER_DelayMS(TIMER5_SELECTION,1000);
//		SERVO_SET_DIRECTION(SERVO_DIRECTION_FORWARD);
//		TIMER_DelayMS(TIMER5_SELECTION,1000);
//		SERVO_SET_DIRECTION(SERVO_DIRECTION_LEFT);
//		TIMER_DelayMS(TIMER5_SELECTION,1000);






//		Ultrsonic_Trigger();
//		distance = UltrasonicCalculateDistance();
//		if(5>(u32)distance){
//			App_CarStop();
//		}
//		else if(10>(u32)distance){
//			App_CarMoveForward(20);
//		}
//		else if(20>(u32)distance){
//			App_CarMoveForward(40);
//		}
//		else if(30>(u32)distance){
//			App_CarMoveForward(60);
//		}
//		else if(40>(u32)distance){
//			App_CarMoveForward(80);
//		}
//		else{
//			App_CarMoveForward(100);
//		}


	}


	return 0;
}
