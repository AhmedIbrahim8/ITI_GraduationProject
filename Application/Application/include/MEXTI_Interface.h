/*******************************************************************************************/
/*  Module       :   EXTI                                                                  */
/*  File Name    :   MEXTI_Interface.h                                                     */
/*  Description  :   Header File of the EXTI Interface Driver                              */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   12/09/2023                                                            */
/*******************************************************************************************/

#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_


/********************************************************************************************/
/************************************** Masks and Numbers Used  *****************************/
/********************************************************************************************/
#define    INTERRUPT_CONFIGURATION_REGISTER_MASK         0x0000000F


/********************************************************************************************/
/************************************** #s used in the Module *******************************/
/********************************************************************************************/
#define  BIT_NUMBER_4                          4
#define  EXTI_NUMBER_16                        16

/********************************************************************************************/
/************************************** Types Declaration ***********************************/
/********************************************************************************************/

typedef enum{
	EXTI_LINE_0,
	EXTI_LINE_1,
	EXTI_LINE_2,
	EXTI_LINE_3,
	EXTI_LINE_4,
	EXTI_LINE_5,
	EXTI_LINE_6,
	EXTI_LINE_7,
	EXTI_LINE_8,
	EXTI_LINE_9,
	EXTI_LINE_10,
	EXTI_LINE_11,
	EXTI_LINE_12,
	EXTI_LINE_13,
	EXTI_LINE_14,
	EXTI_LINE_15,
	EXTI_LINE_16,
	EXTI_LINE_17,
	EXTI_LINE_18,
	EXTI_LINE_21=21,
	EXTI_LINE_22=22
}EXTI_LineType;

typedef enum{
	EXTI_RISING_EDGE,
	EXTI_FALLING_EDGE,
	EXTI_ONCHANGE
}EXTI_EdgeType;


typedef enum{
	EXTI_ENABLE,
	EXTI_DISABLE
}EXTI_MaskType;

typedef enum{
	PORTA_PIN,
	PORTB_PIN,
	PORTC_PIN,
	PORTD_PIN,
	PORTE_PIN,
	PORTH_PIN=7
}EXTI_SourceInputType;

/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/

void MEXTI_voidInterruptSetPort(EXTI_LineType Line,EXTI_SourceInputType SourceInput);
void MEXTI_voidInterruptEnableDisable(EXTI_LineType Line,EXTI_MaskType MaskType);
void MEXTI_voidInterruptTrigger(EXTI_LineType Line,EXTI_EdgeType EdgeType);
void MEXTI_voidSetCallBack(EXTI_LineType Line,void (*ptr)(void));

#endif /* MNVIC_INTERFACE_H_ */
