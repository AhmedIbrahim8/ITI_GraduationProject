/**********************************************************/
/*********************** includes section *****************/
/**********************************************************/
#include "STD_Types.h"
#include "BIT_MATH.h"


#include "DCM_Interface.h"

#include "GPT_Interface.h"

#include "Ultrasonic_Interface.h"

#include "SERVO_Interface.h"

#include "LINE_FOLLOWER_INTERFACE.h"

#include "App.h"

/**********************************************************/
/************** lane tracking system project **************/
/**********************************************************/



int main(){


	/*		 Peripheral Enable Clock 			*/
	Peripheral_EnableClock();

	/*		DC motors initialization 			*/
	DCM_Init(Configuration);


	/*		 Timer 5 is used for delay 			*/
	TIMER_Init(&Timer5_configuration);
	/*		 line follower sensors initialization 			*/
	line_follower_init();


	while(1){
		/*	line_follower_flag_right -->this flag is set when right sensor detects lane
		 *  line_follower_flag_left  -->this flag is set when left sensor detects lane
		 */

		if(line_follower_flag_right==1 && line_follower_flag_left==0){
			/*
			 * when left sensor detects lane then car moves in opposite direction
			 */
			App_CarMoveRight(40);
			line_follower_flag_left=0;
			TIMER_DelayMS(TIMER5_SELECTION,400);
			LEFT_LED_INT_ENABLE();

		}
		else if(line_follower_flag_right==0 && line_follower_flag_left==1){
			/*
			 * when right sensor detects lane then car moves in opposite direction
			 */
			App_CarMoveLeft(40);
			line_follower_flag_right=0;
			TIMER_DelayMS(TIMER5_SELECTION,400);
			RIGHT_LED_INT_ENABLE();
		}
		else if(line_follower_flag_right==1 && line_follower_flag_left==1){
			/*
			 * no detection for lane
			 */
			App_CarMoveForward(20);
		}
		else{
			/* If the 2-lanes are detected, it means that, The RC is out the 2-lanes*/
			App_CarStop();
		}




	}


	return 0;
}


