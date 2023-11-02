#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"


#include "../include/DCM_Interface.h"

#include "../include/GPT_Interface.h"

#include "../include/Ultrasonic_Interface.h"

#include "../include/App.h"

/**********************************************************/
/*********************** Global Variables *****************/
/**********************************************************/
f32 distance;


int main(){


	/* Peripheral Enable Clock */
	Peripheral_EnableClock();

	DCM_Init(Configuration);

	Ultrsonic_Init();

	TIMER_Init(&Timer5_configuration);
	while(1){

		App_CarMoveForward(100);

//		Ultrsonic_Trigger();
//		distance = UltrasonicCalculateDistance();
//		if(5>(u32)distance){
//			App_CarStop();
//		}
//		else if(10>(u32)distance){
//			App_CarMoveForward(40);
//		}
//		else if(20>(u32)distance){
//			App_CarMoveForward(60);
//		}
//		else if(30>(u32)distance){
//			App_CarMoveForward(80);
//		}
//		else if(40>(u32)distance){
//			App_CarMoveForward(90);
//		}
//		else{
//			App_CarMoveForward(90);
//		}


	}


	return 0;
}
