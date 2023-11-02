/*******************************************************************************************/
/*  Module       :   NVIC                                                                  */
/*  File Name    :   MNVICRCC_Private.h                                                    */
/*  Description  :   Header File of the NVIC Driver Private                                */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   11/09/2023                                                            */
/*******************************************************************************************/

#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_
/**************************************************************************/
/* NVIC Module Base Address From Programming Manual page 193              */
/* Start from    address                 0xE000 E100                      */
/*                                       -----------                      */
/* End   at      address                 0xE000 E4EF                      */
/**************************************************************************/
#define   NVIC_BASE_ADDRESS       (0xE000E100)

/**************************************************************************/
/* Typedef for all NVIC Module Register                                   */
/* Reference Manual 4.3.11 NVIC register map Page 220                     */
/**************************************************************************/
typedef struct{
	u32 ISER[8];
	u32 RESERVED1[24];
	u32 ICER[8];
	u32 RESERVED2[24];
	u32 ISPR[8];
	u32 RESERVED3[24];
	u32 ICPR[8];
	u32 RESERVED4[24];
	u32 IABR[8];
	u32 RESERVED5[56];
	u8  IPR[240];
	u32 RESERVED6[580];
	u32 STIR;

}NVIC_t;


/* Macro to point to the base address of the NVIC Module */
#define       NVIC          ((volatile NVIC_t*)NVIC_BASE_ADDRESS)

/* Macro to point to the Application interrupt and reset control register of the System Control BLock Module */
#define       SCB_AIRCR       *((volatile u32*)(0xE000ED00+0x0C))



#endif /* MNVIC_PRIVATE_H_ */
