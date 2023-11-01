#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/MRCC_Interface.h"
#include "../include/DCM_Interface.h"

#include "../include/GPT_Interface.h"


int main(){
	MRCC_Init();

	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM2);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM5);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);

	DCM_Init(Configuration);


	TIMER_Init(&Timer5_configuration);
	while(1){

		DCM_Rotate(DCM_RIGHT,50,DCM_FORWARD);
		TIMER_DelayMS(TIMER5_SELECTION,5000);

		DCM_Stop(DCM_RIGHT);
		TIMER_DelayMS(TIMER5_SELECTION,1000);


		DCM_Rotate(DCM_RIGHT,50,DCM_REVERSE);
		TIMER_DelayMS(TIMER5_SELECTION,5000);


		DCM_Rotate(DCM_RIGHT,90,DCM_FORWARD);
		TIMER_DelayMS(TIMER5_SELECTION,5000);

		DCM_Stop(DCM_RIGHT);
		TIMER_DelayMS(TIMER5_SELECTION,1000);


		DCM_Rotate(DCM_RIGHT,90,DCM_REVERSE);
		TIMER_DelayMS(TIMER5_SELECTION,5000);



	}


	return 0;
}
