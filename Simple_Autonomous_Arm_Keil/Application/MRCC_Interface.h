/*******************************************************************************************/
/*  Module       :   RCC                                                                   */
/*  File Name    :   MRCC_Interface.h                                                      */
/*  Description  :   Header File of the RCC Interface Driver                               */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   09/09/2023                                                            */
/*******************************************************************************************/


#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_

#include "STD_Types.h"
/*******************************************************************************************/
/***************************** Frequency of the System and Buses ***************************/
/*******************************************************************************************/
#define   SYSTEM_FREQUENCY                                16000000UL
#define   AHB2_FREQUENCY                                  16000000UL
#define   AHB1_FREQUENCY                                  16000000UL
#define   APB1_FREQUENCY                                  8000000UL
#define   APB2_FREQUENCY                                  8000000UL


/*******************************************************************************************/
/* Reference Manual 2.3 Memory map (Page 38)                                               */
/* We have 4 Buses Interface which are :                                                   */
/*                                      - AHB1                                             */
/*                                      - AHB2                                             */
/*                                      - APB1                                             */
/*                                      - APB2                                             */
/* Each Bus connected with some peripherals                                                */
/*******************************************************************************************/
#define  RCC_APB1               0
#define  RCC_APB2               1
#define  RCC_AHB1               2
#define  RCC_AHB2               3


/*******************************************************************************************/
/*********************************** APB1 Peripherals **************************************/
/*******************************************************************************************/
/* Reference Manual page 119                                    */
/* RCC APB1 peripheral clock enable register (RCC_APB1ENR) Bits */
/* Each Peripheral connected to APB1                            */

#define  RCC_APB1_TIM2                            0
#define  RCC_APB1_TIM3                            1
#define  RCC_APB1_TIM4                            2
#define  RCC_APB1_TIM5                            3

#define  RCC_APB1_WWDG                            11

#define  RCC_APB1_SPI2                            14
#define  RCC_APB1_SPI3                            15

#define  RCC_APB1_USART2                          17

#define  RCC_APB1_I2C1                            21
#define  RCC_APB1_I2C2                            22
#define  RCC_APB1_I2C3                            23

#define  RCC_APB1_PWR                             28

/*******************************************************************************************/
/*********************************** APB2 Peripherals **************************************/
/*******************************************************************************************/
/* Reference Manual page 122                                    */
/* RCC APB1 peripheral clock enable register (RCC_APB2ENR) Bits */
/* Each Peripheral connected to APB2                            */

#define  RCC_APB2_TIM1                            0

#define  RCC_APB2_USART1                          4
#define  RCC_APB2_USART6                          5

#define  RCC_APB2_ADC1                            8

#define  RCC_APB2_SDIO                            11
#define  RCC_APB2_SPI1                            12
#define  RCC_APB2_SPI4                            13
#define  RCC_APB2_SYSCFG                          14

#define  RCC_APB2_TIM9                            16
#define  RCC_APB2_TIM10                           17
#define  RCC_APB2_TIM11                           18


/*******************************************************************************************/
/*********************************** AHB1 Peripherals **************************************/
/*******************************************************************************************/
/* Reference Manual page 118                                    */
/* RCC APB1 peripheral clock enable register (RCC_AHB1ENR) Bits */
/* Each Peripheral connected to APB1                            */

#define  RCC_AHB1_GPIOA                          0
#define  RCC_AHB1_GPIOB                          1
#define  RCC_AHB1_GPIOC                          2
#define  RCC_AHB1_GPIOD                          3
#define  RCC_AHB1_GPIOE                          4

#define  RCC_AHB1_GPIOH                          7

#define  RCC_AHB1_CRC                            12

#define  RCC_AHB1_DMA1                           21
#define  RCC_AHB1_DMA2                           22

/*******************************************************************************************/
/*********************************** AHB2 Peripherals **************************************/
/*******************************************************************************************/
/* Reference Manual page 119                                    */
/* RCC APB1 peripheral clock enable register (RCC_AHB2ENR) Bits */
/* Each Peripheral connected to APB1                            */

#define  RCC_AHB2_OTGFS                          7







/*******************************************************************************************/
/*************************************** Clock #s**** **************************************/
/*******************************************************************************************/
#define  RCC_HSI                0
#define  RCC_HSE                1
#define  RCC_PLL                3



/*******************************************************************************************/
/******************************** AHB,APB1,APB2 Prescalers *********************************/
/*******************************************************************************************/
#define  SYSTEM_CLOCK_NOT_DIVIDED       0
#define  SYSTEM_CLOCK_DIVIDED_BY_2      8
#define  SYSTEM_CLOCK_DIVIDED_BY_4      9
#define  SYSTEM_CLOCK_DIVIDED_BY_8      10
#define  SYSTEM_CLOCK_DIVIDED_BY_16     11
#define  SYSTEM_CLOCK_DIVIDED_BY_64     12
#define  SYSTEM_CLOCK_DIVIDED_BY_128    13
#define  SYSTEM_CLOCK_DIVIDED_BY_256    14
#define  SYSTEM_CLOCK_DIVIDED_BY_512    15


#define  AHB_CLOCK_NOT_DIVIDED              0
#define  AHB_CLOCK_DIVIDED_BY_2             4
#define  AHB_CLOCK_DIVIDED_BY_4             5
#define  AHB_CLOCK_DIVIDED_BY_8             6
#define  AHB_CLOCK_DIVIDED_BY_16            7







/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/

void MRCC_Init(void);

void MRCC_Enable_Peripheral(u32 Copy_32Address_Bus,u32 Copy_32peripheral);

void MRCC_Disable_Peripheral(u32 Copy_32Address_Bus,u32 Copy_32peripheral);



#endif /* MRCC_INTERFACE_H_ */
