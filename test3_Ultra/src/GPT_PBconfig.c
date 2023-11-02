/* Standard Types File */
#include <GPT_Config.h>
#include <GPT_Private.h>
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

/* RCC Specified Header Files */
#include "../include/GPT_Interface.h"






TIMER_configType Timer5_configuration={
	TIMER5_SELECTION,
		TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED,
	TIMER_ARR_NOT_BUFFERED,
	TIMER_EGDE_ALIGNED_MODE,
	COUNT_UP
};
