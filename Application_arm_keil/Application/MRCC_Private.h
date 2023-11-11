/*******************************************************************************************/
/*  Module       :   RCC                                                                   */
/*  File Name    :   MRCC_Private.h                                                        */
/*  Description  :   Header File of the RCC Driver Private                                 */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   09/09/2023                                                            */
/*******************************************************************************************/


#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_

#include "STD_Types.h"
/**************************************************************************/
/* RCC Module Base Address From Reference Manual page 38                  */
/* RCC is connected to AHB1 Bus                                           */
/* Start from    address                 0x4002 3800                      */
/*                                       -----------                      */
/* End   at      address                 0x4002 3BFF                      */
/**************************************************************************/
#define   RCC_BASE_ADDRESS       (0x40023800)

/**************************************************************************/
/* Typedef for all RCC Module Register                                    */
/* Reference Manual Page 137 6.3.22 RCC register map                      */
/**************************************************************************/
typedef struct{
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 RESERVED1;
	u32 RESERVED2;
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 RESERVED3;
	u32 RESERVED4;
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 RESERVED5;
	u32 RESERVED6;

	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 RESERVED7;
	u32 RESERVED8;
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 RESERVED9;
	u32 RESERVED10;
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 RESERVED11;
	u32 RESERVED12;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 RESERVED13;
	u32 RESERVED14;
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;

	u32 RESERVED15;
	u32 RCC_DCKCFGR;



}RCC_t;


/* Macro to point to the base address of the RCC Module */
#define       RCC          ((volatile RCC_t*)RCC_BASE_ADDRESS)


/* Macros for the RCC Control Register Bits */
#define  CR_HSION            0
#define  CR_HSIRDY           1

#define  CR_HSITRIM0         3
#define  CR_HSITRIM1         4
#define  CR_HSITRIM2         5
#define  CR_HSITRIM3         6
#define  CR_HSITRIM4         7

#define  CR_HSICAL0          8
#define  CR_HSICAL1          9
#define  CR_HSICAL2          10
#define  CR_HSICAL3          11
#define  CR_HSICAL4          12
#define  CR_HSICAL5          13
#define  CR_HSICAL6          14
#define  CR_HSICAL7          15

#define  CR_HSEON            16
#define  CR_HSERDY           17
#define  CR_HSEBYP           18
#define  CR_CSSON            19

#define  CR_PLLON            24
#define  CR_PLLRDY           25
#define  CR_PLLI2SON         26
#define  CR_PLLI2SRDY        27

/* Bits for PLL Configuration Register */
#define  PLLQ3               27
#define  PLLQ2               26
#define  PLLQ1               25
#define  PLLQ0               24
#define  PLLSRC              22
#define  PLLP1               17
#define  PLLP0               16
#define  PLLN8               14
#define  PLLN7               13
#define  PLLN6               12
#define  PLLN5               11
#define  PLLN4               10
#define  PLLN3               9
#define  PLLN2               8
#define  PLLN1               7
#define  PLLN0               6
#define  PLLM5               5
#define  PLLM4               4
#define  PLLM3               3
#define  PLLM2               2
#define  PLLM1               1
#define  PLLM0               0


/* Bits for Clock Configuration Register */
#define  MCO21               31
#define  MCO20               30
#define  MCO2PRE2            29
#define  MCO2PRE1            28
#define  MCO2PRE0            27
#define  MCO1PRE2            26
#define  MCO1PRE1            25
#define  MCO1PRE0            24
#define  I2SSC               23
#define  MCO11               22
#define  MCO10               21
#define  RTCPRE4             20
#define  RTCPRE3             19
#define  RTCPRE2             18
#define  RTCPRE1             17
#define  RTCPRE0             16
#define  PPRE22              15
#define  PPRE21              14
#define  PPRE20              13
#define  PPRE12              12
#define  PPRE11              11
#define  PPRE10              10
#define  HPRE3               7
#define  HPRE2               6
#define  HPRE1               5
#define  HPRE0               4
#define  SWS1                3
#define  SWS0                2
#define  SW1                 1
#define  SW0                 0


#define  BUS_PRESCALER_MASK   0xFFFF030F



/* Macros for the RCC Configuration Register Bit1 and Bit0 */
#define  SWITCH_HSI       0
#define  SWITCH_HSE       1
#define  SWITCH_PLL       2

#define  CLOCK_SWITCH_MASK         0xFFFFFFFC


#endif /* MRCC_PRIVATE_H_ */
