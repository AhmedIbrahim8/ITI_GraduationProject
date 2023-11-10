///*
// * OPTO_COUPLER.c
// *
// *  Created on: Nov 9, 2023
// *      Author: Misra
// */
//
//
//
//


/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

#include "../include/OPTO_COUPLER_INTERFACE.h"


/* GPT Specified Header Files */
#include "../include/GPT_Interface.h"
#include "../include/MGPIO_Interface.h"
#include "../include/MEXTI_Interface.h"
#include "../include/MNVIC_Interface.h"


volatile u16 holes_counter=0;
volatile u16 turns=0;

void Counter_holes(void)
{
	holes_counter++;
}

void Counter_reveloution(void)
{
	turns=holes_counter/20;
	//holes_counter=0;
}


void Speed_sensor_Init (void)
{
		MGPIO_SetMode(PORTB,PIN1,INPUT_RESET_STATE);
		MGPIO_SetInputPinMode(PORTB,PIN1,PULL_UP);

		MEXTI_voidInterruptSetPort(EXTI_LINE_1,PORTB_PIN);
		MEXTI_voidInterruptTrigger(EXTI_LINE_1,EXTI_FALLING_EDGE);
		MEXTI_voidSetCallBack(EXTI_LINE_1,Counter_holes);
		MEXTI_voidInterruptEnableDisable(EXTI_LINE_1,EXTI_ENABLE);


		TIMER_Init(&Timer3_configuration);
		TIMER_SetPrescaler(TIMER3_SELECTION,4999);
		TIMER_SetARR(TIMER3_SELECTION,15999);
		TIMER_VoidSetCallBack(TIMER3_SELECTION,Counter_reveloution);
		TIMER_EnableInterrupt(TIMER3_SELECTION,TIMER_UPDATE_INTERRUPT);

		/*      NVIC enable the EXTI15        */
		MNVIC_VoidEnbleInterrupt(EXTINT_EXTI1_POSITION);
		MNVIC_VoidEnbleInterrupt(EXTINT_TIM3_POSITION);
		TIMER_Start_Continuous(TIMER3_SELECTION,TIMER_NO_CHANNELS);
}


//int main()
//{
//	/*      RCC initialization with HSI    */
//	MRCC_Init();
//
//
//	/*		enable tim3 & GPIOB & SYSCFG		*/
//	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_TIM3);
//	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_SYSCFG);
//	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
//
//
//
//	MGPIO_SetMode(PORTB,PIN1,INPUT_RESET_STATE);
//	MGPIO_SetInputPinMode(PORTB,PIN1,PULL_UP);
//
//	MEXTI_voidInterruptSetPort(EXTI_LINE_1,PORTB_PIN);
//	MEXTI_voidInterruptTrigger(EXTI_LINE_1,EXTI_FALLING_EDGE);
//	MEXTI_voidSetCallBack(EXTI_LINE_1,Counter_holes);
//	MEXTI_voidInterruptEnableDisable(EXTI_LINE_1,EXTI_ENABLE);
//
//
//
//	TIMER_Init(&Timer3_configuration);
//	TIMER_SetPrescaler(TIMER3_SELECTION,4999);
//	TIMER_SetARR(TIMER3_SELECTION,15999);
//	TIMER_VoidSetCallBack(TIMER3_SELECTION,Counter_reveloution);
//	TIMER_EnableInterrupt(TIMER3_SELECTION,TIMER_UPDATE_INTERRUPT);
//
//	/*      NVIC enable the EXTI15        */
//	MNVIC_VoidEnbleInterrupt(EXTINT_EXTI1_POSITION);
//	MNVIC_VoidEnbleInterrupt(EXTINT_TIM3_POSITION);
//	TIMER_Start_Continuous(TIMER3_SELECTION,TIMER_NO_CHANNELS);
//
//
//	while(1)
//	{
//
//
//	}
//
//
//}
//
//
//
//
//
