/*******************************************************************************************/
/*  Module       :   GPT                                                                   */
/*  File Name    :   GPTPBconfig_Program.c                                                 */
/*  Description  :   Configuration File of the GPT  Driver                                 */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   10/10/2023                                                            */
/*******************************************************************************************/












/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

/* RCC Specified Header Files */
#include "../include/GPT_Interface.h"
#include "../include/GPT_Config.h"
#include "../include/GPT_Private.h"


TIMER_configType Timer2_configuration={
	TIMER2_SELECTION,
	TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_ENABLED,
	TIMER_ARR_NOT_BUFFERED,
	TIMER_EGDE_ALIGNED_MODE,
	COUNT_UP
};

TIMER_configType Timer5_configuration={
	TIMER5_SELECTION,
	TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED,
	TIMER_ARR_NOT_BUFFERED,
	TIMER_EGDE_ALIGNED_MODE,
	COUNT_UP
};


TIMER_configType Timer4_configuration={
	TIMER4_SELECTION,
	TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED,
	TIMER_ARR_NOT_BUFFERED,
	TIMER_EGDE_ALIGNED_MODE,
	COUNT_UP
};

