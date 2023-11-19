/*******************************************************************************************/
/*  Module       :   APP                                                                   */
/*  File Name    :   APP.h                                                                 */
/*  Description  :   Header File of the App                                                */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   01/11/2023                                                            */
/*******************************************************************************************/


#include "MRCC_Interface.h"

#include "App.h"

void Peripheral_EnableClock(void){
	MRCC_Init();
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_TIM1);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM2);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM3);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM4);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM5);


	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOC);


	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_SYSCFG);
}
