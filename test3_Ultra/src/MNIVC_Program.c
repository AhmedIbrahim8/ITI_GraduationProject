/*******************************************************************************************/
/*  Module       :   NVIC                                                                  */
/*  File Name    :   MNVIC_Program.c                                                       */
/*  Description  :   Source File of the MNIVC Driver                                       */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   11/09/2023                                                            */
/*******************************************************************************************/


/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "..\include\STD_Types.h"
/* Bit Math File */
#include "..\include\BIT_MATH.h"

/* RCC Specified Header Files */
#include "..\include\MNVIC_Interface.h"
#include "..\include\MNVIC_Config.h"
#include "..\include\MNVIC_Private.h"

/********************************************************************************************/
/************************************** Global Variables ************************************/
/********************************************************************************************/
/* GroupMode is private variable used in the module only so, it must be static */
static MNVIC_Group_t GroupMode=0;

/********************************************************************************************/
/************************************** APIs Definition *************************************/
/********************************************************************************************/

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Enable the NVIC Bit for the specified Peripheral in the Copy_u8IntPos        */
/* Programming Manual Data Sheet Page 210:                                                  */
/*           - Interrupt set-enable register x (NVIC_ISERx)                                 */
/********************************************************************************************/
void MNVIC_VoidEnbleInterrupt(u8 Copy_u8IntPos)
{
	SET_BIT(NVIC->ISER[Copy_u8IntPos/NUMBER_32],Copy_u8IntPos%NUMBER_32);
}

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Disable the NVIC Bit for the specified Peripheral in the Copy_u8IntPos       */
/* Programming Manual Data Sheet Page 211:                                                  */
/*           - Interrupt set-enable register x (NVIC_ISERx)                                 */
/********************************************************************************************/
void MNVIC_VoidDisableInterrupt(u8 Copy_u8IntPos)
{
	SET_BIT(NVIC->ICER[Copy_u8IntPos/NUMBER_32],Copy_u8IntPos%NUMBER_32);
}
/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Enable the Peripheral Pending Flag Bit for the specified Peripheral          */
/*             in the Copy_u8IntPos                                                         */
/* Programming Manual Data Sheet Page 212:                                                  */
/*           - Interrupt set-enable register x (NVIC_ISERx)                                 */
/********************************************************************************************/
void MNVIC_VoidEnableInterruptPending(u8 Copy_u8IntPos)
{
	SET_BIT(NVIC->ISPR[Copy_u8IntPos/NUMBER_32],Copy_u8IntPos%NUMBER_32);
}

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Disable the Peripheral Pending Flag Bit for the specified Peripheral         */
/*             in the Copy_u8IntPos                                                         */
/* Programming Manual Data Sheet Page 213:                                                  */
/*           - Interrupt set-enable register x (NVIC_ISERx)                                 */
/********************************************************************************************/
void MNVIC_VoidDisableInterruptPending(u8 Copy_u8IntPos)
{
	SET_BIT(NVIC->ICPR[Copy_u8IntPos/NUMBER_32],Copy_u8IntPos%NUMBER_32);
}

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Checking of the Peripheral Interrupt Active Flag                             */
/* Programming Manual Data Sheet Page 214:                                                  */
/*           - Interrupt set-enable register x (NVIC_ISERx)                                 */
/********************************************************************************************/
void MNVIC_VoidIsInterruptActive(u8 Copy_u8IntPos,u8 *Copy_Read)
{
	*Copy_Read = GET_BIT(NVIC->IABR[Copy_u8IntPos/NUMBER_32],Copy_u8IntPos%NUMBER_32);
}

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Adjust the Group and subgroup for the Interrupts                             */
/* Programming Manual Data Sheet Page 41 :                                                  */
/*           - For information about splitting the interrupt priority fields into group     */
/*             priority and subpriority, see Application interrupt and reset control        */
/*             register (AIRCR) on page 228                                                 */
/********************************************************************************************/
void MNVIC_VoidSetInterruptGroupMode(MNVIC_Group_t GroupSubMode)
{
	GroupMode = GroupSubMode;
	/* On writes, write 0x5FA to VECTKEY, otherwise the write is ignored  */
	/* SCB_AIRCR_VECTKEY_NUMBER = 0x05FA 0000                             */
	u32 Local_u32temp = (SCB_AIRCR &~(SCB_AIRCR_GROUP_MASK)) | (GroupSubMode<<BIT_NUMBER_8) | SCB_AIRCR_VECTKEY_NUMBER;
	SCB_AIRCR = Local_u32temp;
}

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Adjust the SW Priority of the Specified Peripheral                           */
/* Programming Manual Data Sheet Page 215:                                                  */
/*           - Interrupt set-enable register x (NVIC_ISERx)                                 */
/********************************************************************************************/
void MNVIC_VoidSetInterruptPriority(u8 Copy_u8IntPos,u8 Copy_u8GroupNum,u8 Copy_u8SubGroupNum)
{
	/* Mask the 4-Bits fist to ensure that all 4-bit are zeros before inserting the value   */
	NVIC->IPR[Copy_u8IntPos] = NVIC->IPR[Copy_u8IntPos] & NVIC_IPR_MASK ;
	/* Peripheral Priority Adjusting is based on the global variable GroupMode because      */
	/* Shifting is dependent on it                                                          */
	/* STM32 is using the last 4-bits in the IPR Register                                   */
	/* Note that IPR is byte accessable                                                     */
	switch(GroupMode)
	{
	/* case 1 : No Sub Group, all 4-bits are for the group                 */
	case GROUP_16_SUB_NONE:
		/* Shifting 4 for only the Group Priority          */
		NVIC->IPR[Copy_u8IntPos] = Copy_u8GroupNum << BIT_NUMBER_4;
		break;
	/* case 2 : The first bit in the last 4-bit is for the subgroup        */
	/*          The three bits in the last 4-bit is for the group priority */
	case GROUP_8_SUB_2:
		/* Shifting 5 for only the Group Priority          */
		/* Shifting 4 for only the SubGroup Priority       */
		NVIC->IPR[Copy_u8IntPos] = (Copy_u8GroupNum << BIT_NUMBER_5) | (Copy_u8SubGroupNum <<BIT_NUMBER_4);
		break;
	/* case 3 : The first two bit in the last 4-bit is for the subgroup     */
	/*          The two bits in the last 4-bit is for the group priority    */
	case GROUP_4_SUB_4:
		/* Shifting 6 for only the Group Priority          */
		/* Shifting 4 for only the SubGroup Priority       */
		NVIC->IPR[Copy_u8IntPos] = (Copy_u8GroupNum << BIT_NUMBER_6) | (Copy_u8SubGroupNum <<BIT_NUMBER_4);
		break;
	/* case 4 : The first three bit in the last 4-bit is for the subgroup    */
	/*          The bit in the last 4-bit is for the group priority          */
	case GROUP_2_SUB_8:
		/* Shifting 7 for only the Group Priority          */
		/* Shifting 4 for only the SubGroup Priority       */
		NVIC->IPR[Copy_u8IntPos] = (Copy_u8GroupNum << BIT_NUMBER_7) | (Copy_u8SubGroupNum <<BIT_NUMBER_4);
		break;
    /* case 5 : No Group, all 4-bits are for the subgroup */
	case GROUP_NONE_SUB_16:
		NVIC->IPR[Copy_u8IntPos] = Copy_u8SubGroupNum << BIT_NUMBER_4;
		break;
	default:
		break;

		/* Do No thing */
	}

}

