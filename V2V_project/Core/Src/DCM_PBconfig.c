/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCMPBconfig_Program.c                                                 */
/*  Description  :   Configuration File of the GPT  Driver                                 */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   31/10/2023                                                            */
/*******************************************************************************************/












/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "STD_Types.h"
/* Bit Math File */
#include "BIT_MATH.h"

/* RCC Specified Header Files */
#include "DCM_Interface.h"
#include "DCM_Config.h"
#include "DCM_Private.h"

/* Used MCAL Drivers */
#include "GPT_Interface.h"
#include "MGPIO_Interface.h"


DCM_ConfigType Configuration[NUMBER_OF_DC_MOTOR] = {
		{
		 DCM_1_SPEED_TIMER,
		 DCM_1_SPEED_CHANNEL,
		 DCM_1_SPEED_PORT_ID,
		 DCM_1_SPEED_PIN_ID,
		 DCM_1_IN1_PORT_ID,
		 DCM_1_IN1_PIN_ID,
		 DCM_1_IN2_PORT_ID,
		 DCM_1_IN2_PIN_ID
		},

		{
	     DCM_2_SPEED_TIMER,
		 DCM_2_SPEED_CHANNEL,
		 DCM_2_SPEED_PORT_ID,
		 DCM_2_SPEED_PIN_ID,
		 DCM_2_IN1_PORT_ID,
		 DCM_2_IN1_PIN_ID,
		 DCM_2_IN2_PORT_ID,
		 DCM_2_IN2_PIN_ID
		}
};



