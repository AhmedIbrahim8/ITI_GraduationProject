/*******************************************************************************************/
/*  Module       :   Infrared                                                              */
/*  File Name    :   HIR_Interface.h                                                       */
/*  Description  :   Header File of the HIR Driver Interface                               */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   18/09/2023                                                            */
/*******************************************************************************************/

#ifndef HIR_INTERFACE_H_
#define HIR_INTERFACE_H_






/********************************************************************************************/
/************************************** Masks and Numbers Used  *****************************/
/********************************************************************************************/
#define      HIR_NUMBER_0                                0
#define      HIR_NUMBER_1                                1
#define      HIR_NUMBER_8                                8
#define      HIR_NUMBER_24                               24
#define      HIR_START_TIME_OF_LOGIC_0                   1000
#define      HIR_END_TIME_OF_LOGIC_0                     1500
#define      HIR_START_TIME_OF_LOGIC_1                   2000
#define      HIR_END_TIME_OF_LOGIC_1                     2500

#define      SYSTICK_TIME_START                          40000

#define      HIR_INCREMENT_DATA                          168

#define      HIR_DECREMENT_DATA                          224

#define      HIR_ONE_DATA                                48

#define      HIR_TWO_DATA                                24

#define      HIR_THREE_DATA                              122

#define      HIR_FOUR_DATA                               16


#define 	SPEED_COMMAND								5
#define 	DIRECTION_COMMAND							10
#define 	DISTANCE_COMMAND							15












#if IR_SELECTION == IR_TRANSMITTER

#define IR_TRANSMITTER_PORT				PORTB
#define IR_TRANSMITTER_PIN				PIN8

#define IR_TRANSMITTER_TIMER			TIMER4_SELECTION
#define IR_TRANSMITTER_CHANNEL			TIMER_CHANNEL_3





/*		functions declaration 		*/
void HIR_TRASMITTER_INIT(void);


void IR_SNED_FRAME(u8 address, u8 received_data);
/********************************************************/




#elif (IR_SELECTION == IR_RECEIVER)




#endif


#define  IR_RECEIVER_PORT			PORTC
#define  IR_RECEIVER_PIN			PIN15
#define  IR_RECEIVER_EXTI_LINE		EXTI_LINE_15
#define  IR_RECEIVER_EXTI_PORT		PORTC_PIN
#define  IR_RECEIVER_EXTI_TRIG		EXTI_FALLING_EDGE

extern volatile u8 received_data ;
extern volatile u8 received_command ;

/*		functions declaration 		*/
void IR_RECEIVER_INIT(void);
void GetFrame(void);
void GetData(void);
/********************************************************/







#endif /* HIR_INTERFACE_H_ */
