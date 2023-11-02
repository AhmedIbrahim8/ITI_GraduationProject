/*******************************************************************************************/
/*  Module       :   EXTI                                                                  */
/*  File Name    :   MEXTI_Private.h                                                    */
/*  Description  :   Header File of the EXTI Driver Private                                */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   12/09/2023                                                            */
/*******************************************************************************************/

#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_
/**************************************************************************/
/* External Interrupt Module Base Address From Programming Manual page 39 */
/* Start from    address                 0x4001 3C00                      */
/*                                       -----------                      */
/* End   at      address                 0x4001 3FFF                      */
/**************************************************************************/
#define   EXTI_BASE_ADDRESS       (0x40013C00)

/**************************************************************************/
/* Typedef for all EXTI Module Register                                   */
/* Reference Manual 10.3.7 EXTI register map Page 212                     */
/**************************************************************************/
typedef struct{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_t;


/* Macro to point to the base address of the NVIC Module */
#define       EXTI          ((volatile EXTI_t*)EXTI_BASE_ADDRESS)

/**************************************************************************/
/* SYSCFG Module Base Address From Programming Manual page 39             */
/* Start from    address                 0x4001 3800                      */
/*                                       -----------                      */
/* End   at      address                 0x4001 3BFF                      */
/**************************************************************************/

#define  SYSCFG_BASE_ADDRESS    0x40013800

/**************************************************************************/
/* Typedef for all SYSCFG Module Register                                 */
/* Reference Manual 7.2.8 SYSCFG register map Page 145                    */
/**************************************************************************/
typedef struct{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 RESERVED[2];
	u32 CMPCR;
}SYSCFG_t;

/* SYSCFG external interrupt configuration register EXTICR                */
/* EXTICR[0] for EXTI0  , EXTI1  , EXTI2  , EXTI3                         */
/* EXTICR[1] for EXTI4  , EXTI5  , EXTI6  , EXTI7                         */
/* EXTICR[3] for EXTI8  , EXTI9  , EXTI10 , EXTI11                        */
/* EXTICR[4] for EXTI12 , EXTI13 , EXTI14 , EXTI15                        */

/* Macro to point to the base address of the SYSCFG Module */
#define  SYSCFG                  ((volatile  SYSCFG_t *)(SYSCFG_BASE_ADDRESS))

#endif /* MNVIC_PRIVATE_H_ */
