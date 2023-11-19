/*******************************************************************************************/
/*  Module       :   Infrared                                                              */
/*  File Name    :   HIR_Program.c                                                         */
/*  Description  :   Source File of the HIR Driver                                         */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   18/09/2023                                                            */
/*******************************************************************************************/

#include "..\include\STD_Types.h"
#include "..\include\BIT_MATH.h"

#include "..\include\MRCC_Interface.h"
#include "..\include\MEXTI_Interface.h"
#include "..\include\MNVIC_Interface.h"
#include "..\include\MSYSTICK_Interface.h"
#include "..\include\MGPIO_Interface.h"
#include "../include/GPT_Interface.h"

#include "..\include\HIR_Private.h"
#include "..\include\HIR_Config.h"
#include "..\include\HIR_Interface.h"





#if IR_SELECTION == IR_TRANSMITTER
/********************************************************/
/*		HIR frame generator	based on NEC protocol		*/
/********************************************************/
/*		functions definition		*/



static void HIR_SEND_START_BIT(void);
static void HIR_HIGH_BIT(void);
static void HIR_LOW_BIT(void);

void HIR_TRASMITTER_INIT(void)
{
	MGPIO_SetMode(IR_TRANSMITTER_PORT,IR_TRANSMITTER_PIN,ALTERNATE_FUNCTION_MODE);
	MGPIO_SetAlternativeFuncPin(IR_TRANSMITTER_PORT,IR_TRANSMITTER_PIN,AF2_TIM3_TIM4_TIM5);

	TIMER_Init(&Timer4_configuration);
	TIMER_ChannelInit(IR_TRANSMITTER_TIMER,
			IR_TRANSMITTER_CHANNEL,
			TIMER_PWM_MODE_1,
			ACTIVE_HIGH,
			TIMER_CHANNEL_ENABLE);

	TIMER_SetPrescaler(IR_TRANSMITTER_TIMER,14);
	TIMER_SetARR(IR_TRANSMITTER_TIMER,27);

	TIMER_SetCompareValue(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL,13);


	SYSTICK_voidInit();

}





// this function sends start bit according to NEC protocol which is 9ms high then 4.5ms low
void HIR_SEND_START_BIT(void)
{
	TIMER_Start_Continuous(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
	TIMER_DelayUS(TIMER5_SELECTION,9000);
	TIMER_Stop(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
	TIMER_DelayUS(TIMER5_SELECTION,4500);
}

// this function sends high bit according to NEC protocol which is 560us high then 1687us low
void HIR_HIGH_BIT(void)
{
	TIMER_Start_Continuous(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
	TIMER_DelayUS(TIMER5_SELECTION,560);
	TIMER_Stop(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
	TIMER_DelayUS(TIMER5_SELECTION,1687);
}

// this function sends low bit according to NEC protocol which is 560us high then 560us low
void HIR_LOW_BIT(void)
{
	TIMER_Start_Continuous(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
	TIMER_DelayUS(TIMER5_SELECTION,560);
	TIMER_Stop(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
	TIMER_DelayUS(TIMER5_SELECTION,560);
}

// this function is responsible for sending the whole frame of NEC protocol
void IR_SNED_FRAME(u8 address, u8 received_data)
{
	u8 address_inverse = 0, received_data_inverse = 0;
	// start bit
	HIR_SEND_START_BIT();

	// address sent
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(address, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();

		if (i == 0)
		{
			break;
		}
	}

	// address inverse sent
	address_inverse = (~address);
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(address_inverse, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();
		if (i == 0)
		{
			break;
		}
	}

	// received_data sent
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(received_data, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();
		if (i == 0)
		{
			break;
		}
	}

	// received_data inverse sent
	received_data_inverse = (~received_data);
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(received_data_inverse, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();
		if (i == 0)
		{
			break;
		}
	}

	TIMER_Stop(IR_TRANSMITTER_TIMER,IR_TRANSMITTER_CHANNEL);
}
//
///********************************************************/
///********************************************************/
///********************************************************/
///********************************************************/
///*		simple program to send frame over IR transmitter		*/
//int main()
//{
//	// RCC initialization
//	MRCC_INIT();
//	MRCC_ENABLE_PERIPHERAL(RCC_APB1, RCC_APB1_TIM2);
//	MRCC_ENABLE_PERIPHERAL(RCC_AHB1, RCC_AHB1_GPIOAEN);
//
//	// systick initialization
//	MSYSTICK_voidInit();
//
//	// set the pin that is responsible for PWM generation with 38KHZ
//	MGPIO_SetMode(PORTA, PIN3, ALT_FUNC);
//	MGPIO_PinAlternateFunction(PORTA, PIN3, AF1);
//
//	// timer initialization
//	TIMER_Init(&Timer_configuration);
//	TIMER_SetPrescaler(TIMER2_SELECTION, 14);
//	TIMER_SetARR(TIMER2_SELECTION, 27);
//	TIMER_SetCompareValue(TIMER2_SELECTION, TIMER_CHANNEL_4, 13);
//
//	while (1)
//	{
//		IR_SNED_FRAME(0, 5);
//		MSYSTICK_voidDelayms(2000);
//	}
//	return 0;
//}
//
//

#elif IR_SELECTION == IR_RECEIVER


/********************************************************************************************/
/************************************** Global Variables ************************************/
/********************************************************************************************/
/* Variable to indicate the start of the IR Protocol */
volatile u8 flag=HIR_NUMBER_0;

/* Variable as a counter to count through the array  */
volatile u8 counter=HIR_NUMBER_0;
/* Protocol Time Frame */
static volatile u32 ProtocolFrame[50]={HIR_NUMBER_0};
/* Variable for the received_data received */
volatile u8 received_data =0;
volatile u8 received_command =0;






/********************************************************************************************/
/************************************** APIs Definition *************************************/
/********************************************************************************************/
/* This Function will be called when the external interrupt happened */
void GetFrame(void)
{
	/* If it is the start of the protocol */
	if(flag == HIR_NUMBER_0)
	{
		SYSTICK_voidCtrlIntState(SYSTICK_ENABLE_EXCEPTION_REQUEST);
		SYSTICK_voidStart(SYSTICK_TIME_START);
		/* Start of the protocol is happened so, flag value will be changed */
		flag=HIR_NUMBER_1;
	}
	/* In case it is not the start of the frame  */
	else
	{
		/* Get the time value and put it into the protocol variable at specific counter value */
		ProtocolFrame[counter]=SYSTICK_u32GetElapsedTime();
		/* Start the systick again to get the time between the next bit in the frame */
		SYSTICK_voidStart(SYSTICK_TIME_START);
		/* Increment the counter to the next location in the protocol array variable */
		counter++;
	}
}


/* This Function will be called when the systick interrupt happened */
/* indicating the end of the protocol frame  */
void GetData(void)
{


	/* i is a counter */
	u8 i;
	/* Zero to the flag for the next start of the frame */
	flag=HIR_NUMBER_0;
	/* Zero to the counter to the next start of the frame */
	counter=HIR_NUMBER_0;


	/*		received_command checking		*/
	for(i=HIR_NUMBER_0;i<HIR_NUMBER_8;i++)
	{
		/* In case of the zero bit */
		if((ProtocolFrame[HIR_NUMBER_8-i]>=HIR_START_TIME_OF_LOGIC_0) && (ProtocolFrame[HIR_NUMBER_8-i]<=HIR_END_TIME_OF_LOGIC_0))
		{
			CLEAR_BIT(received_command,i);
		}
		/* Incase of the one bit */
		else if((ProtocolFrame[HIR_NUMBER_8-i]>=HIR_START_TIME_OF_LOGIC_1) && (ProtocolFrame[HIR_NUMBER_8-i]<=HIR_END_TIME_OF_LOGIC_1))
		{
			SET_BIT(received_command,i);
		}
	}
	/********************************************/

	/*		received_data checking		*/
	if (SPEED_COMMAND==received_command)
	{
		for(i=HIR_NUMBER_0;i<HIR_NUMBER_8;i++)
		{
			/* In case of the zero bit */
			if((ProtocolFrame[HIR_NUMBER_24-i]>=HIR_START_TIME_OF_LOGIC_0) && (ProtocolFrame[HIR_NUMBER_24-i]<=HIR_END_TIME_OF_LOGIC_0))
			{
				CLEAR_BIT(received_data,i);
			}
			/* Incase of the one bit */
			else if((ProtocolFrame[HIR_NUMBER_24-i]>=HIR_START_TIME_OF_LOGIC_1) && (ProtocolFrame[HIR_NUMBER_24-i]<=HIR_END_TIME_OF_LOGIC_1))
			{
				SET_BIT(received_data,i);
			}
		}
	}

	else if (DIRECTION_COMMAND==received_command)
	{
		for(i=HIR_NUMBER_0;i<HIR_NUMBER_8;i++)
		{
			/* In case of the zero bit */
			if((ProtocolFrame[HIR_NUMBER_24-i]>=HIR_START_TIME_OF_LOGIC_0) && (ProtocolFrame[HIR_NUMBER_24-i]<=HIR_END_TIME_OF_LOGIC_0))
			{
				CLEAR_BIT(received_data,i);
			}
			/* Incase of the one bit */
			else if((ProtocolFrame[HIR_NUMBER_24-i]>=HIR_START_TIME_OF_LOGIC_1) && (ProtocolFrame[HIR_NUMBER_24-i]<=HIR_END_TIME_OF_LOGIC_1))
			{
				SET_BIT(received_data,i);
			}
		}
	}

	else if (DISTANCE_COMMAND==received_command)
	{
		for(i=HIR_NUMBER_0;i<HIR_NUMBER_8;i++)
		{
			/* In case of the zero bit */
			if((ProtocolFrame[HIR_NUMBER_24-i]>=HIR_START_TIME_OF_LOGIC_0) && (ProtocolFrame[HIR_NUMBER_24-i]<=HIR_END_TIME_OF_LOGIC_0))
			{
				CLEAR_BIT(received_data,i);
			}
			/* Incase of the one bit */
			else if((ProtocolFrame[HIR_NUMBER_24-i]>=HIR_START_TIME_OF_LOGIC_1) && (ProtocolFrame[HIR_NUMBER_24-i]<=HIR_END_TIME_OF_LOGIC_1))
			{
				SET_BIT(received_data,i);
			}
		}
	}

	/********************************************/

	/* Disable the Timer */
	SYSTICK_voidCtrlIntState(SYSTICK_DISABLE_EXCEPTION_REQUEST);
}






void IR_RECEIVER_INIT(void)
{

	SYSTICK_voidInit();
	SYSTICK_voidSetCallBack(GetData);

	MGPIO_SetMode(IR_RECEIVER_PORT,IR_RECEIVER_PIN,INPUT_RESET_STATE);
	MGPIO_SetInputPinMode(IR_RECEIVER_PORT,IR_RECEIVER_PIN,PULL_UP);

	MNVIC_VoidEnbleInterrupt(EXTINT_EXTI15_10_POSITION);
	MEXTI_voidInterruptSetPort(IR_RECEIVER_EXTI_LINE,IR_RECEIVER_EXTI_PORT);
	MEXTI_voidInterruptTrigger(IR_RECEIVER_EXTI_LINE,IR_RECEIVER_EXTI_TRIG);
	MEXTI_voidSetCallBack(IR_RECEIVER_EXTI_LINE,GetFrame);
	MEXTI_voidInterruptEnableDisable(IR_RECEIVER_EXTI_LINE,EXTI_ENABLE);
}


#endif







