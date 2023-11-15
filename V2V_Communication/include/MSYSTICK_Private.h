/*******************************************************************************************/
/*  Module       :   Systick Timer                                                         */
/*  File Name    :   MSYSTICK_Private.c                                                    */
/*  Description  :   Header File of the Private of the Systick Timer Driver                */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   12/09/2023                                                            */
/*******************************************************************************************/

#ifndef MSYSTICK_PRIVATE_H_
#define MSYSTICK_PRIVATE_H_

/* Standard Type File */
#include "..\include\STD_Types.h"

/**************************************************************************/
/* SysTick Module Base Address From Programming Manual page 193           */
/* Start from    address                 0xE000 E010                      */
/*                                       -----------                      */
/* End   at      address                 0xE000 E01F                      */
/**************************************************************************/
#define   SYSTICK_BASE_ADDRESS       (0xE000E010)

/**************************************************************************/
/* Typedef for all SysTick Module Register                                */
/* Reference Manual 4.5.6 SysTick register map Page 251                   */
/**************************************************************************/
typedef struct{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}SYSTICK_t;


/* Macro to point to the base address of the Systick Module */
#define       SYSTICK          ((volatile SYSTICK_t*)SYSTICK_BASE_ADDRESS)

/* Bit Number inside SysTick control and status register */
#define  SYSTICK_ENABLE_BIT                       0
#define  SYSTICK_TICKINT_BIT                      1
#define  SYSTICK_CLKSOURCE_BIT                    2
#define  SYSTICK_COUNTFLAG_BIT                    16

#endif /* MNVIC_PRIVATE_H_ */
