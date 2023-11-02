#include "../include/STD_Types.h"
#include "../include/GPT_Interface.h"
#include "../include/MGPIO_Interface.h"
#include "../include/MRCC_Interface.h"
#include "../include/MNVIC_Interface.h"
#include "../include/GPT_Private.h"

#include "../include/HIR_Interface.h"

#include "../include/MEXTI_Interface.h"

#include "../include/BIT_MATH.h"

#include "../include/Ultrasonic_Interface.h"

float ton;
float total_period;
float duty;
float distance;
int freq;

int main(){
	MRCC_Init();
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	/*timer 1 init*/
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_TIM1);



	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM5);


	/******INIT ULTRASONIC*******/

	Ultrsonic_Init();


	TIMER_Init(&Timer5_configuration);


	while(1){
		Ultrsonic_Trigger();
		distance = UltrasonicCalculateDistance();
		//TIMER_DelayUS(TIMER5_SELECTION, 2000);



	}


}

