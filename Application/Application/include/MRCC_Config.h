/*******************************************************************************************/
/*  Module       :   RCC                                                                   */
/*  File Name    :   MRCC_Config.h                                                         */
/*  Description  :   Header File of the RCC Driver Configuration                           */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   09/09/2023                                                            */
/*******************************************************************************************/

#ifndef MRCC_CONFIG_H_
#define MRCC_CONFIG_H_


#define  SYS_CLK                    RCC_HSI

#define  PLL_M_DIVISION             10

#define  PLL_N_MULTIPLICATION       90

#define  PLL_P_DIVISION             2

#define  PLL_CLOCK_COURCE           RCC_HSI

#define  PLL_Q_DIVISION_FOR_USB     4

#define  AHB_CLOCK                  SYSTEM_CLOCK_NOT_DIVIDED

#define  APB1_CLOCK                 AHB_CLOCK_NOT_DIVIDED

#define  APB2_CLOCK                 AHB_CLOCK_NOT_DIVIDED

#endif /* MRCC_CONFIG_H_ */
