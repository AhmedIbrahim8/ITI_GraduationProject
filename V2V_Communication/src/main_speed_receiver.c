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

#include "../include/HIR_Interface.h"

#include "../include/App.h"

/**********************************************************/
/*********************** Global Variables *****************/
/**********************************************************/


int main()
{


	/* Peripheral Enable Clock */
	Peripheral_EnableClock();

	DCM_Init(Configuration);

	IR_RECEIVER_INIT();

	TIMER_Init(&Timer5_configuration);




	while (1)
	{



		while ( received_data  >  70 )
		{
			App_CarMoveForward(20);
		}

		App_CarStop();




	}
	return 0;
}





