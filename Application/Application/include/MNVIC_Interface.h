/*******************************************************************************************/
/*  Module       :   NVIC                                                                  */
/*  File Name    :   MNVIC_Interface.h                                                     */
/*  Description  :   Header File of the NVIC Interface Driver                              */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   11/09/2023                                                            */
/*******************************************************************************************/

#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_


/********************************************************************************************/
/************************************** Masks and Numbers Used  *****************************/
/********************************************************************************************/
#define        SCB_AIRCR_GROUP_MASK                   0x00000700
#define        NUMBER_32                                 32
#define        BIT_NUMBER_8                              8
#define        SCB_AIRCR_VECTKEY_NUMBER               0x05FA0000
#define        NVIC_IPR_MASK                          0x0F
#define        BIT_NUMBER_4                              4
#define        BIT_NUMBER_5                              5
#define        BIT_NUMBER_6                              6
#define        BIT_NUMBER_7                              7

/********************************************************************************************/
/************************************** #s used in the Module *******************************/
/********************************************************************************************/
#define  INTERRRUPT_NOT_ACTIVE            0
#define  INTERRUPT_ACTIVE                 1





/********************************************************************************************/
/************************************* Vector Table Positions *******************************/
/********************************************************************************************/
#define    EXTINT_WWDG_POSITION                         0
#define    EXTINT_EXTI16_PVD_POSITION                   1
#define    EXTINT_EXTI21_TAMPSTAMP_POSITION             2
#define    EXTINT_EXTI22_RTCWKUP_POSITION               3
#define    EXTINT_FLASH_POSITION                        4
#define    EXTINT_RCC_POSITION                          5
#define    EXTINT_EXTI0_POSITION                        6
#define    EXTINT_EXTI1_POSITION                        7
#define    EXTINT_EXTI2_POSITION                        8
#define    EXTINT_EXTI3_POSITION                        9
#define    EXTINT_EXTI4_POSITION                        10
#define    EXTINT_DMA1STREAM0_POSITION                  11
#define    EXTINT_DMA1STREAM1_POSITION                  12
#define    EXTINT_DMA1STREAM2_POSITION                  13
#define    EXTINT_DMA1STREAM3_POSITION                  14
#define    EXTINT_DMA1STREAM4_POSITION                  15
#define    EXTINT_DMA1STREAM5_POSITION                  16
#define    EXTINT_DMA1STREAM6_POSITION                  17
#define    EXTINT_ADC_POSITION                          18

#define    EXTINT_EXTI9_5_POSITION                      23
#define    EXTINT_TIM1BRK_TIM9_POSITION                 24
#define    EXTINT_TIM1UP_TIM10_POSITION                 25
#define    EXTINT_TIM1TRIGCOM_TIM11_POSITION            26

#define    EXTINT_TIM1CC_POSITION                       27
#define    EXTINT_TIM2_POSITION                         28
#define    EXTINT_TIM3_POSITION                         29
#define    EXTINT_TIM4_POSITION                         30

#define    EXTINT_I2C1EV_POSITION                       31
#define    EXTINT_I2C1ER_POSITION                       32
#define    EXTINT_I2C2EV_POSITION                       33
#define    EXTINT_I2C2ER_POSITION                       34

#define    EXTINT_SPI1_POSITION                         35
#define    EXTINT_SPI2_POSITION                         36
#define    EXTINT_USART1_POSITION                       37
#define    EXTINT_USART2_POSITION                       38

#define    EXTINT_EXTI15_10_POSITION                    40
#define    EXTINT_EXTI17_POSITION                       41
#define    EXTINT_EXTI18_POSITION                       42


#define    EXTINT_DMA1STREAM7_POSITION                  47
#define    EXTINT_SDIO_POSITION                         49
#define    EXTINT_TIM5_POSITION                         50
#define    EXTINT_SPI3_POSITION                         51

#define    EXTINT_DMA2STREAM0_POSITION                  56
#define    EXTINT_DMA2STREAM1_POSITION                  57
#define    EXTINT_DMA2STREAM2_POSITION                  58
#define    EXTINT_DMA2STREAM3_POSITION                  59
#define    EXTINT_DMA2STREAM4_POSITION                  60

#define    EXTINT_OTGFS_POSTION                         67

#define    EXTINT_DMA2STREAM5_POSITION                  68
#define    EXTINT_DMA2STREAM6_POSITION                  69
#define    EXTINT_DMA2STREAM7_POSITION                  70

#define    EXTINT_USART6_POSITION                       71

#define    EXTINT_I2C3EV_POSITION                       72
#define    EXTINT_I2C3ER_POSITION                       73

#define    EXTINT_FPU_POSITION                          81

#define    EXTINT_SPI4_POSITION                         84
/********************************************************************************************/
/************************************** Types Declaration ***********************************/
/********************************************************************************************/

/* Enumeration for the user to Adjust the number of groups and sub groups */
typedef enum{
	GROUP_16_SUB_NONE=3,
	GROUP_8_SUB_2,
	GROUP_4_SUB_4,
	GROUP_2_SUB_8,
	GROUP_NONE_SUB_16,
}MNVIC_Group_t;








/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Enable the NVIC Bit for the specified Peripheral in the Copy_u8IntPos        */
/********************************************************************************************/
void MNVIC_VoidEnbleInterrupt(u8 Copy_u8IntPos);

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Disable the NVIC Bit for the specified Peripheral in the Copy_u8IntPos       */
/********************************************************************************************/
void MNVIC_VoidDisableInterrupt(u8 Copy_u8IntPos);

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Enable the Peripheral Pending Flag Bit for the specified Peripheral          */
/*             in the Copy_u8IntPos                                                         */
/********************************************************************************************/
void MNVIC_VoidEnableInterruptPending(u8 Copy_u8IntPos);

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Disable the Peripheral Pending Flag Bit for the specified Peripheral         */
/*             in the Copy_u8IntPos                                                         */
/********************************************************************************************/
void MNVIC_VoidDisableInterruptPending(u8 Copy_u8IntPos);

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Checking of the Peripheral Interrupt Active Flag                             */
/********************************************************************************************/
void MNVIC_VoidIsInterruptActive(u8 Copy_u8IntPos,u8 *Copy_Read);

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Adjust the SW Priority of the Specified Peripheral                           */
/********************************************************************************************/
void MNVIC_VoidSetInterruptPriority(u8 Copy_u8IntPos,u8 Copy_u8GroupNum,u8 Copy_u8SubGroupNum);

/********************************************************************************************/
/* This Function responsible for :                                                          */
/*           - Adjust the Group and subgroup for the Interrupts                             */
/********************************************************************************************/
void MNVIC_VoidSetInterruptGroupMode(MNVIC_Group_t GroupSubMode);

#endif /* MNVIC_INTERFACE_H_ */
