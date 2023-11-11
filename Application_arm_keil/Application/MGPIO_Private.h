/*******************************************************************************************/
/*  Module       :   GPIO                                                                  */
/*  File Name    :   MGPIO_Private.h                                                       */
/*  Description  :   Header File of the GPIO Driver Private                                */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   10/09/2023                                                            */
/*******************************************************************************************/

#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

#include "STD_Types.h"
/**************************************************************************/
/* GPIOA Module Base Address From Reference Manual page 38                */
/* GPIOA is connected to AHB1 Bus                                         */
/* Start from    address                 0x4002 0000                      */
/*                                       -----------                      */
/* End   at      address                 0x4002 03FF                      */

/* GPIOB is connected to AHB1 Bus                                         */
/* Start from    address                 0x4002 0400                      */
/*                                       -----------                      */
/* End   at      address                 0x4002 07FF                      */

/* GPIOC is connected to AHB1 Bus                                         */
/* Start from    address                 0x4002 0800                      */
/*                                       -----------                      */
/* End   at      address                 0x4002 0BFF                      */

/**************************************************************************/
#define  GPIOA_BASE_ADDRESS       (0x40020000)

#define  GPIOB_BASE_ADDRESS       (0x40020400)

#define  GPIOC_BASE_ADDRESS       (0x40020800)


/**************************************************************************/
/* Typedef for all GPIO Module Register                                   */
/* Reference Manual Page 164 8.4.11 GPIO register map                     */
/**************************************************************************/

typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIO_t;


/* Macro to point to the base address of the GPIO Module */
#define       GPIOA          ((volatile GPIO_t*)GPIOA_BASE_ADDRESS)

#define       GPIOB          ((volatile GPIO_t*)GPIOB_BASE_ADDRESS)

#define       GPIOC          ((volatile GPIO_t*)GPIOC_BASE_ADDRESS)








#endif /* MGPIO_PRIVATE_H_ */
