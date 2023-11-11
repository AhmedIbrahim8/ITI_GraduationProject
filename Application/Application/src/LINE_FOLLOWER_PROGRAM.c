/*
 * LINE_FOLLOWER_PROGRAM.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Misra
 */

/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

/* Used MCAL Drivers */
#include "../include/MGPIO_Interface.h"
#include "../include/MNVIC_Interface.h"
#include "../include/MEXTI_Interface.h"
#include "../include/GPT_Interface.h"


/* LINE_FOLLOWER Specified Header Files */
#include "../include/LINE_FOLLOWER_CONFIG.h"
#include "../include/LINE_FOLLOWER_INTERFACE.h"
#include "../include/LINE_FOLLOWER_CONFIG.h"
#include "../include/LINE_FOLLOWER_INTERFACE.h"




#include "../include/DCM_Interface.h"


/**********************************************************/
/*********************** Global variables *****************/
/**********************************************************/
u8 right_led=0;
u8 middle_led=0;
u8 left_led=0;

u8 line_follower_flag_right=0;
u8 line_follower_flag_left=0;
/************************************************************/
/*
 * @brief   this function is called is ISR when right sensor detects lane
 * @retval  no return
 */
void RIGHT_LED_FUNCTION(void)
{
	RIGHT_LED_INT_DISABLE();
	line_follower_flag_right=1;
}


/*
 * @brief   this function is called is ISR when left sensor detects lane
 * @retval  no return
 */
void LEFT_LED_FUNCTION(void)
{

	LEFT_LED_INT_DISABLE();
	line_follower_flag_left=1;
}


/*
 * @brief   this function initializes the 2 line followers sensors used in the project
 * @retval  no return
 */
void line_follower_init()
{
	/*		GPIO initialization		*/
	MGPIO_SetMode(RIGHT_LED_PORT,RIGHT_LED_PIN,INPUT_RESET_STATE);
	MGPIO_SetMode(LEFT_LED_PORT,LEFT_LED_PIN,INPUT_RESET_STATE);

	MGPIO_SetInputPinMode(RIGHT_LED_PORT,RIGHT_LED_PIN,PULL_DOWN);
	MGPIO_SetInputPinMode(LEFT_LED_PORT,LEFT_LED_PIN,PULL_DOWN);

	/*		EXTI initialization		*/
	MEXTI_voidInterruptSetPort(RIGHT_LED_INTERRUPT,RIGHT_LED_PORT);
	MEXTI_voidInterruptSetPort(LEFT_LED_INTERRUPT,LEFT_LED_PORT);

	MEXTI_voidInterruptTrigger(RIGHT_LED_INTERRUPT,RIGHT_INTERRUPT_TRIGGER);
	MEXTI_voidInterruptTrigger(LEFT_LED_INTERRUPT,LEFT_INTERRUPT_TRIGGER);

	MEXTI_voidSetCallBack(RIGHT_LED_INTERRUPT,RIGHT_LED_FUNCTION);
	MEXTI_voidSetCallBack(LEFT_LED_INTERRUPT,LEFT_LED_FUNCTION);

	/*		EXTI interrupt enabled 		*/
	RIGHT_LED_INT_ENABLE();
	LEFT_LED_INT_ENABLE();

	/*		NVIC enabled		*/
	MNVIC_VoidEnbleInterrupt(EXTINT_EXTI15_10_POSITION);

}



/*
 * @brief   this function enables the EXTI interrupt for right sensor
 * @retval  no return
 */
void RIGHT_LED_INT_ENABLE(void)
{
	MEXTI_voidInterruptEnableDisable(RIGHT_LED_INTERRUPT,EXTI_ENABLE);
}

/*
 * @brief   this function disables the EXTI interrupt for right sensor
 * @retval  no return
 */
void RIGHT_LED_INT_DISABLE(void)
{
	MEXTI_voidInterruptEnableDisable(RIGHT_LED_INTERRUPT,EXTI_DISABLE);
}








/*
 * @brief   this function enables the EXTI interrupt for left sensor
 * @retval  no return
 */
void LEFT_LED_INT_ENABLE(void)
{
	MEXTI_voidInterruptEnableDisable(LEFT_LED_INTERRUPT,EXTI_ENABLE);
}

/*
 * @brief   this function disables the EXTI interrupt for right sensor
 * @retval  no return
 */
void LEFT_LED_INT_DISABLE(void)
{
	MEXTI_voidInterruptEnableDisable(LEFT_LED_INTERRUPT,EXTI_DISABLE);
}
