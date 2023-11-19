/*******************************************************************************************/
/*  Module       :   MEXTI                                                                  */
/*  File Name    :   MEXTI_Program.c                                                       */
/*  Description  :   Source File of the MNIVC Driver                                       */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   11/09/2023                                                            */
/*******************************************************************************************/


/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
#include "STD_Types.h"
/* Bit Math File */
#include "BIT_MATH.h"

#include "MEXTI_Interface.h"
#include "MEXTI_Config.h"
#include "MEXTI_Private.h"




/********************************************************************************************/
/************************************** Global Variables ************************************/
/********************************************************************************************/
static void (*Global_EXTIPtr[16]) (void)={0};

/********************************************************************************************/
/************************************** APIs Definition *************************************/
/********************************************************************************************/

void MEXTI_voidInterruptSetPort(EXTI_LineType Line,EXTI_SourceInputType SourceInput)
{
	SYSCFG->EXTICR[Line/BIT_NUMBER_4] = ( SYSCFG->EXTICR[Line/BIT_NUMBER_4] \
			                          &~(INTERRUPT_CONFIGURATION_REGISTER_MASK<<((Line%BIT_NUMBER_4)*BIT_NUMBER_4)) ) \
			                          | ( SourceInput<<((Line%BIT_NUMBER_4)*BIT_NUMBER_4) );
}
void MEXTI_voidInterruptEnableDisable(EXTI_LineType Line,EXTI_MaskType MaskType)
{
	switch(MaskType)
	{
	case EXTI_ENABLE:
		SET_BIT(EXTI->IMR,Line);
		break;
	case EXTI_DISABLE:
		CLEAR_BIT(EXTI->IMR,Line);
		break;
	default :
		break;
	}
}

void MEXTI_voidInterruptTrigger(EXTI_LineType Line,EXTI_EdgeType EdgeType)
{
	switch(EdgeType)
	{
	case EXTI_RISING_EDGE:
		SET_BIT(EXTI->RTSR,Line);
		break;
	case EXTI_FALLING_EDGE:
		SET_BIT(EXTI->FTSR,Line);
		break;
	case EXTI_ONCHANGE:
		SET_BIT(EXTI->RTSR,Line);
		SET_BIT(EXTI->FTSR,Line);
		break;
	default:
		break;
	}

}

void MEXTI_voidSwInterrupt(EXTI_LineType Line)
{
	SET_BIT(EXTI->SWIER,Line);
}

void MEXTI_voidSetCallBack(EXTI_LineType Line,void (*ptr)(void))
{
	if(Line < EXTI_NUMBER_16)
	{
		Global_EXTIPtr[Line]=ptr;
	}
	else
	{
		/* DO Nothing */
	}
}

/* ISR of the external interrupt 0 */
void EXTI0_IRQHandler(void){
	if(Global_EXTIPtr[EXTI_LINE_0] == 0){
		/* Do Nothing */
		/* call back function not initialized */
	}
	else
	{
		Global_EXTIPtr[EXTI_LINE_0]();
	}
	/* Clear the pending bit by setting it to one */
	SET_BIT(EXTI->PR,EXTI_LINE_0);
}

/* ISR of the external interrupt 1 */
void EXTI1_IRQHandler(void){
	if(Global_EXTIPtr[EXTI_LINE_1] == 0){
		/* Do Nothing */
		/* call back function not initialized */
	}
	else
	{
		Global_EXTIPtr[EXTI_LINE_1]();
	}
	/* Clear the pending bit by setting it to one */
	SET_BIT(EXTI->PR,EXTI_LINE_1);
}



/* ISR of the external interrupt 2 */
void EXTI2_IRQHandler(void){
	if(Global_EXTIPtr[EXTI_LINE_2] == 0){
		/* Do Nothing */
		/* call back function not initialized */
	}
	else
	{
		Global_EXTIPtr[EXTI_LINE_2]();
	}
	/* Clear the pending bit by setting it to one */
	SET_BIT(EXTI->PR,EXTI_LINE_2);
}

/* ISR of the external interrupt 3 */
void EXTI3_IRQHandler(void){
	if(Global_EXTIPtr[EXTI_LINE_3] == 0){
		/* Do Nothing */
		/* call back function not initialized */
	}
	else
	{
		Global_EXTIPtr[EXTI_LINE_3]();
	}
	/* Clear the pending bit by setting it to one */
	SET_BIT(EXTI->PR,EXTI_LINE_3);
}





/* ISR of the external interrupt 4 */
void EXTI4_IRQHandler(void){
	if(Global_EXTIPtr[EXTI_LINE_4] == 0){
		/* Do Nothing */
		/* call back function not initialized */
	}
	else
	{
		Global_EXTIPtr[EXTI_LINE_4]();
	}
	/* Clear the pending bit by setting it to one */
	SET_BIT(EXTI->PR,EXTI_LINE_4);
}

/* ISR of the external interrupt 5 to 9 */
void EXTI9_5_IRQHandler()
{
	/* In case of External Interrupt line 5 is happened */
	if(GET_BIT(EXTI->PR,EXTI_LINE_5)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_5] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_5]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_5);
		}

	}
	/* In case of External Interrupt line 6 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_6)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_6] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_6]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_6);
		}

	}
	/* In case of External Interrupt line 7 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_7)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_7] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_7]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_7);
		}

	}
	/* In case of External Interrupt line 8 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_8)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_8] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_8]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_5);
		}

	}
	/* In case of External Interrupt line 9 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_9)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_9] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_9]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_9);
		}

	}

}


void EXTI15_10_IRQHandler(void)
{
	/* In case of External Interrupt line 10 is happened */
	if(GET_BIT(EXTI->PR,EXTI_LINE_10)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_10] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_10]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_10);
		}

	}
	/* In case of External Interrupt line 11 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_11)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_11] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_11]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_11);
		}

	}
	/* In case of External Interrupt line 12 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_12)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_12] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_12]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_12);
		}

	}
	/* In case of External Interrupt line 13 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_13)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_13] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_13]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_13);
		}

	}
	/* In case of External Interrupt line 14 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_14)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_14] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_14]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_14);
		}

	}
	/* In case of External Interrupt line 15 is happened */
	else if(GET_BIT(EXTI->PR,EXTI_LINE_15)==1)
	{
		if(Global_EXTIPtr[EXTI_LINE_15] == 0){
			/* Do Nothing */
			/* call back function not initialized */
		}
		else
		{
			Global_EXTIPtr[EXTI_LINE_15]();
			/* Clear the pending bit by setting it to one */
			SET_BIT(EXTI->PR,EXTI_LINE_15);
		}

	}
}
