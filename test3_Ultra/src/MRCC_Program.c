/*******************************************************************************************/
/*  Module       :   RCC                                                                   */
/*  File Name    :   MRCC_Program.c                                                        */
/*  Description  :   Source File of the RCC Driver                                         */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   09/09/2023                                                            */
/*******************************************************************************************/



/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

/* RCC Specified Header Files */
#include "../include/MRCC_Interface.h"
#include "../include/MRCC_Config.h"
#include "../include/MRCC_Private.h"


/********************************************************************************************/
/************************************** APIs Definition *************************************/
/********************************************************************************************/


void MRCC_Init(void)
{
	/* In case External Clock   */
#if (SYS_CLK == RCC_HSE)
	/* Set the HSE ON Bit in the control register */
	SET_BIT(RCC->RCC_CR,CR_HSEON);
	/* Wait till HSE Ready bit flag equal 1 which means HSE is Ready */
	while(!(GET_BIT(RCC->RCC_CR,CR_HSERDY)));
	/* Switch to HSE Clock */
	RCC->RCC_CFGR = ( RCC->RCC_CFGR & CLOCK_SWITCH_MASK ) | (SWITCH_HSE);
	/* In case of Internal Clock */
#elif (SYS_CLK == RCC_HSI)
	/* Set the HSI ON Bit in the control register */
	SET_BIT(RCC->RCC_CR,CR_HSION);
	/* Wait till HSI Ready bit flag equal 1 which means HSI is Ready */
	while(!(GET_BIT(RCC->RCC_CR,CR_HSIRDY)));
	/* Switch to HSI Clock */
	RCC->RCC_CFGR = ( RCC->RCC_CFGR & CLOCK_SWITCH_MASK ) | (SWITCH_HSI);
	/* In case of PLL Clock      */
#elif (SYS_CLK == RCC_PLL)
	/* Make Sure that PLL is Off to write on the PLL Configuration Register */
	CLEAR_BIT(RCC->RCC_CR,CR_PLLON);
	/* Adjust :
	 * 1- PLL Clock Source
	 *     HSI : 0
	 *     HSE : 1
	 * 2- Division factor for the main PLL (PLL)
	 *    and audio PLL (PLLI2S) input clock
	 * 3- Main PLL (PLL) multiplication factor for VCO
	 * 4- PLLP: Main PLL (PLL) division factor for main system clock
	 * 5- Main PLL (PLL) division factor for USB OTG FS, SDIO
	 *    and random number generator clocks                           */
	RCC->RCC_PLLCFGR = (PLL_CLOCK_COURCE        << PLLSRC)\
			          |(PLL_M_DIVISION          << PLLM0 )\
					  |(PLL_N_MULTIPLICATION    << PLLN0 )\
					  |(PLL_P_DIVISION          << PLLP0 )\
					  |(PLL_Q_DIVISION_FOR_USB  << PLLQ0 );


	/* Set the PLL ON Bit in the control register */
	SET_BIT(RCC->RCC_CR,CR_PLLON);
	/* Wait till PLL Ready bit flag equal 1 which means PLL is Ready */
	while(!(GET_BIT(RCC->RCC_CR,CR_PLLRDY)));
	/* Switch to PLL Clock */
	RCC->RCC_CFGR = ( RCC->RCC_CFGR & CLOCK_SWITCH_MASK ) | (SWITCH_PLL);

#endif
	/* Adjust AHB , APB1 , APB2 Clock */
	RCC->RCC_CFGR = (RCC->RCC_CFGR & BUS_PRESCALER_MASK) \
			       |(AHB_CLOCK   << HPRE0 )\
				   |(APB1_CLOCK  << PPRE10)\
				   |(APB2_CLOCK  << PPRE20);
}



/* Function Responsible for : enable the clock for the peripheral */
void MRCC_Enable_Peripheral(u32 Copy_32Address_Bus,u32 Copy_32peripheral)
{
	/* Switch case for the address bus type    */
	/* We have 4 Buses Type which are :        */
	/*    - APB1                               */
	/*    - APB2                               */
	/*    - AHB1                               */
	/*    - AHB2                               */
	switch(Copy_32Address_Bus)
	{
	/* In case of APB1 Bus, we access the APB1 Enable Register */
	case RCC_APB1:
		/* Set the peripheral bit to enable the clock for the module */
		SET_BIT(RCC->RCC_APB1ENR,Copy_32peripheral);
		break;
		/* In case of APB2 Bus, we access the APB1 Enable Register */
	case RCC_APB2:
		/* Set the peripheral bit to enable the clock for the module */
		SET_BIT(RCC->RCC_APB2ENR,Copy_32peripheral);
		break;
		/* In case of AHB1 Bus, we access the APB1 Enable Register */
	case RCC_AHB1:
		/* Set the peripheral bit to enable the clock for the module */
		SET_BIT(RCC->RCC_AHB1ENR,Copy_32peripheral);
		break;
		/* In case of AHB2 Bus, we access the APB1 Enable Register */
	case RCC_AHB2:
		/* Set the peripheral bit to enable the clock for the module */
		SET_BIT(RCC->RCC_AHB2ENR,Copy_32peripheral);
		break;
	default:
		break;

	}
}



/* Function Responsible for : disable the clock for the peripheral */
void MRCC_Disable_Peripheral(u32 Copy_32Address_Bus,u32 Copy_32peripheral)
{
	/* Switch case for the address bus type    */
	/* We have 4 Buses Type which are :        */
	/*    - APB1                               */
	/*    - APB2                               */
	/*    - AHB1                               */
	/*    - AHB2                               */
	switch(Copy_32Address_Bus)
	{
	/* In case of APB1 Bus, we access the APB1 Enable Register */
	case RCC_APB1:
		/* Set the peripheral bit to enable the clock for the module */
		CLEAR_BIT(RCC->RCC_APB1ENR,Copy_32peripheral);
		break;
		/* In case of APB2 Bus, we access the APB1 Enable Register */
	case RCC_APB2:
		/* Set the peripheral bit to enable the clock for the module */
		CLEAR_BIT(RCC->RCC_APB2ENR,Copy_32peripheral);
		break;
		/* In case of AHB1 Bus, we access the APB1 Enable Register */
	case RCC_AHB1:
		/* Set the peripheral bit to enable the clock for the module */
		CLEAR_BIT(RCC->RCC_AHB1ENR,Copy_32peripheral);
		break;
		/* In case of AHB2 Bus, we access the APB1 Enable Register */
	case RCC_AHB2:
		/* Set the peripheral bit to enable the clock for the module */
		CLEAR_BIT(RCC->RCC_AHB2ENR,Copy_32peripheral);
		break;
	default:
		break;

	}
}

