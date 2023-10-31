/*******************************************************************************************/
/*  Module       :   GPT                                                                   */
/*  File Name    :   GPT_Private.h                                                         */
/*  Description  :   Private File of the GPT  Driver                                       */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   10/10/2023                                                            */
/*******************************************************************************************/

#ifndef MTIMER_PRIVATE_H_
#define MTIMER_PRIVATE_H_
#include "STD_Types.h"
/**************************************************************************/
/**************************************************************************/
#define  TIMER2_BASE_ADDRESS       (0x40000000)

#define  TIMER3_BASE_ADDRESS       (0x40000400)

#define  TIMER4_BASE_ADDRESS       (0x40000800)

#define  TIMER5_BASE_ADDRESS       (0x40000C00)

#define  TIMER9_BASE_ADDRESS       (0x40014000)

#define  TIMER10_BASE_ADDRESS      (0x40014400)

#define  TIMER11_BASE_ADDRESS      (0x40014800)

/**************************************************************************/
/* Typedef for all GPT Module Register                                   */
/* Reference Manual Page 374 GPT register map                     */
/**************************************************************************/

typedef struct{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 RESERVED1;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 RESERVED2;
	u32 DCR;
	u32 DMAR;
	u32 OR;
}GPT_t;


/* Macro to point to the base address of the GPT Module */
#define       TIMER2          ((volatile GPT_t*)TIMER2_BASE_ADDRESS)

#define       TIMER3          ((volatile GPT_t*)TIMER3_BASE_ADDRESS)

#define       TIMER4          ((volatile GPT_t*)TIMER4_BASE_ADDRESS)

#define       TIMER5          ((volatile GPT_t*)TIMER5_BASE_ADDRESS)

#define       TIMER9          ((volatile GPT_t*)TIMER9_BASE_ADDRESS)

#define       TIMER10         ((volatile GPT_t*)TIMER10_BASE_ADDRESS)

#define       TIMER11         ((volatile GPT_t*)TIMER11_BASE_ADDRESS)


/******************************************************************************/
/******************************* Bit Number ***********************************/
/******************************************************************************/
#define   CKD1                     9
#define   CKD0                     8
#define   ARPE                     7
#define   CMS1                     6
#define   CMS0                     5
#define   DIR                      4
#define   OPM                      3
#define   URS                      2
#define   UDIS                     1
#define   CEN                      0

#define   OC2CE                    15
#define   OC2M2                    14
#define   OC2M1                    13
#define   OC2M0                    12
#define   OC2PE                    11
#define   OC2FE                    10
#define   CC2S1                    9
#define   CC2S0                    8
#define   OC1CE                    7
#define   OC1M2                    6
#define   OC1M1                    5
#define   OC1M0                    4
#define   OC1PE                    3
#define   OC1FE                    2
#define   CC1S1                    1
#define   CC1S0                    0

#define   OC3PE                    3
#define   OC3M0                    4

#define   OC4PE                    11
#define   OC4M0                    12




#define    CC4NP         15
#define    CC4P          13
#define    CC4E          12

#define    CC3NP         11
#define    CC3P          9
#define    CC3E          8

#define    CC2NP         7
#define    CC2P          5
#define    CC2E          4

#define    CC1NP         3
#define    CC1P          1
#define    CC1E          0



#define    TDE           14
#define    CC4DE         12
#define    CC3DE         11
#define    CC2DE         10
#define    CC1DE         9
#define    UDE           8
#define    TIE           6
#define    CC4IE         4
#define    CC3IE         3
#define    CC2IE         2
#define    CC1IE         1
#define    UIE           0
















#define    CC4OF         12
#define    CC3OF         11
#define    CC2OF         10
#define    CC1OF         9
#define    TIF           6
#define    CC4IF         4
#define    CC3IF         3
#define    CC2IF         2
#define    CC1IF         1
#define    UIF           0








#define  TG              6
#define  CC4G            4
#define  CC3G            3
#define  CC2G            2
#define  CC1G            1
#define  UG              0
#endif /* MTIMER_PRIVATE_H_ */
