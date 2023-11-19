/*******************************************************************************************/
/*  Module       :   GPT                                                                   */
/*  File Name    :   GPT_Program.c                                                         */
/*  Description  :   Source File of the GPT  Driver                                        */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   10/10/2023                                                            */
/*******************************************************************************************/



/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"

/* GPT Specified Header Files */
#include "../include/GPT_Private.h"
#include "../include/GPT_Interface.h"
#include "../include/GPT_Config.h"



#define   F_APB1_MHZ               16

/* global variable for Input Capture TIM1 CH1 */
volatile u16 Global_u16Tim1Ch1InputCaptures[2] ={0};
volatile u8  Global_u8Tim1Ch1Counter =1;



static void (*Timer_Call_Back[4])(void)={NULL_PTR};



/*
 * @brief   this function is called in timer 2 interrupt
 * @retval  no return
 */
void TIM2_IRQHandler(void){
	if(Timer_Call_Back[0]!=NULL_PTR){
		Timer_Call_Back[0]();
	}
	else{
		/* Do No Thing */
	}
	CLEAR_BIT(TIMER2->SR,UIF);
	CLEAR_BIT(TIMER2->SR,CC1IF);
	CLEAR_BIT(TIMER2->SR,CC2IF);
	CLEAR_BIT(TIMER2->SR,CC3IF);
	CLEAR_BIT(TIMER2->SR,CC4IF);
}


/*
 * @brief   this function is called in timer 3 interrupt
 * @retval  no return
 */
void TIM3_IRQHandler(void){
	if(Timer_Call_Back[1]!=NULL_PTR){
		Timer_Call_Back[1]();
	}
	else{
		/* Do No Thing */
	}
	CLEAR_BIT(TIMER3->SR,UIF);
	CLEAR_BIT(TIMER3->SR,CC1IF);
	CLEAR_BIT(TIMER3->SR,CC2IF);
	CLEAR_BIT(TIMER3->SR,CC3IF);
	CLEAR_BIT(TIMER3->SR,CC4IF);
}



/*
 * @brief   this function is called in timer 4 interrupt
 * @retval  no return
 */
void TIM4_IRQHandler(void){
	if(Timer_Call_Back[2]!=NULL_PTR){
		Timer_Call_Back[2]();
	}
	else{
		/* Do No Thing */
	}
	CLEAR_BIT(TIMER4->SR,UIF);
	CLEAR_BIT(TIMER4->SR,CC1IF);
	CLEAR_BIT(TIMER4->SR,CC2IF);
	CLEAR_BIT(TIMER4->SR,CC3IF);
	CLEAR_BIT(TIMER4->SR,CC4IF);
}



/*
 * @brief   this function is called in timer 5 interrupt
 * @retval  no return
 */
void TIM5_IRQHandler(void){
	if(Timer_Call_Back[3]!=NULL_PTR){
		Timer_Call_Back[3]();
	}
	else{
		/* Do No Thing */
	}
	CLEAR_BIT(TIMER5->SR,UIF);
	CLEAR_BIT(TIMER5->SR,CC1IF);
	CLEAR_BIT(TIMER5->SR,CC2IF);
	CLEAR_BIT(TIMER5->SR,CC3IF);
	CLEAR_BIT(TIMER5->SR,CC4IF);
}



/*
 * @brief   this function is used to call a function when interrupts happens
 * @para 	Timer_Number of type @TIMER_IDType
 * @para    ptr is a pointer to function to be called
 * @retval  no return
 */
void TIMER_VoidSetCallBack(TIMER_IDType Timer_Number,void (*ptr)(void)){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		Timer_Call_Back[0]=ptr;
		break;
	case TIMER3_SELECTION:
		Timer_Call_Back[1]=ptr;
		break;
	case TIMER4_SELECTION:
		Timer_Call_Back[2]=ptr;
		break;
	case TIMER5_SELECTION:
		Timer_Call_Back[3]=ptr;
		break;
	}
}




/*
 * @brief   this function is used to delay in  microseconds
 * @para 	Timer_Number of type @TIMER_IDType
 * @para    Delay_Value of type @u32
 * @retval  no return
 */
void TIMER_DelayUS(TIMER_IDType Timer_Number,u32 Delay_Value){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		TIMER_SetPrescaler(TIMER2_SELECTION, 15);
		TIMER_SetARR(TIMER2_SELECTION, Delay_Value);
		TIMER_ClearTimerCount(TIMER2_SELECTION);
		CLEAR_BIT(TIMER2->SR,UIF);
		TIMER_Start_OneShot(TIMER2_SELECTION);
		while(GET_BIT(TIMER2->SR,UIF)==0);
		CLEAR_BIT(TIMER2->SR,UIF);
		break;
	case TIMER3_SELECTION:
		TIMER_SetPrescaler(TIMER3_SELECTION, 15);
		TIMER_SetARR(TIMER3_SELECTION, Delay_Value);
		TIMER_ClearTimerCount(TIMER3_SELECTION);
		CLEAR_BIT(TIMER3->SR,UIF);
		TIMER_Start_OneShot(TIMER3_SELECTION);
		while(GET_BIT(TIMER3->SR,UIF)==0);
		CLEAR_BIT(TIMER3->SR,UIF);
		break;
	case TIMER4_SELECTION:
		TIMER_SetPrescaler(TIMER4_SELECTION, 15);
		TIMER_SetARR(TIMER4_SELECTION, Delay_Value);
		TIMER_ClearTimerCount(TIMER4_SELECTION);
		CLEAR_BIT(TIMER4->SR,UIF);
		TIMER_Start_OneShot(TIMER4_SELECTION);
		while(GET_BIT(TIMER4->SR,UIF)==0);
		CLEAR_BIT(TIMER4->SR,UIF);
		break;
	case TIMER5_SELECTION:
		TIMER_SetPrescaler(TIMER5_SELECTION, 15);
		TIMER_SetARR(TIMER5_SELECTION, Delay_Value);
		TIMER_ClearTimerCount(TIMER5_SELECTION);
		CLEAR_BIT(TIMER5->SR,UIF);
		TIMER_Start_OneShot(TIMER5_SELECTION);
		while(GET_BIT(TIMER5->SR,UIF)==0);
		CLEAR_BIT(TIMER5->SR,UIF);
		break;
	}

}




/*
 * @brief   this function is used to delay in milliseconds
 * @para 	Timer_Number of type @TIMER_IDType
 * @para    Delay_Value of type @u32
 * @retval  no return
 */
void TIMER_DelayMS(TIMER_IDType Timer_Number,u32 Delay_Value){
	u32 counter = 0;
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		for(counter = 0;counter < Delay_Value;counter++){
			TIMER_DelayUS(TIMER2_SELECTION,1000);
		}
		break;
	case TIMER3_SELECTION:
		for(counter = 0;counter < Delay_Value;counter++){
			TIMER_DelayUS(TIMER3_SELECTION,1000);
		}
		break;
	case TIMER4_SELECTION:
		for(counter = 0;counter < Delay_Value;counter++){
			TIMER_DelayUS(TIMER4_SELECTION,1000);
		}
		break;
	case TIMER5_SELECTION:
		for(counter = 0;counter < Delay_Value;counter++){
			TIMER_DelayUS(TIMER5_SELECTION,1000);
		}
		break;
	}

}




/*
 * @brief   this function is used to get the remaining time in microseconds
 * @para 	Timer_Number of type @TIMER_IDType
 * @retval  u32 -->time in microseconds
 */
u32 TIMER_u32GetRemaingTime(TIMER_IDType Timer_Number)
{
	u32 elapsed_time=0;
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		elapsed_time = (TIMER2->ARR - TIMER2->CNT)*((TIMER2->PSC+1)/F_APB1_MHZ);
		break;
	case TIMER3_SELECTION:
		elapsed_time = (TIMER3->ARR - TIMER3->CNT)*((TIMER3->PSC+1)/F_APB1_MHZ);
		break;
	case TIMER4_SELECTION:
		elapsed_time = (TIMER4->ARR - TIMER4->CNT)*((TIMER4->PSC+1)/F_APB1_MHZ);
		break;
	case TIMER5_SELECTION:
		elapsed_time =  (TIMER5->ARR - TIMER5->CNT)*((TIMER5->PSC+1)/F_APB1_MHZ);
		break;
	}

	return elapsed_time;
}





/*
 * @brief   this function is used to get the elapsed time in microseconds
 * @para 	Timer_Number of type @TIMER_IDType
 * @retval  u32 -->time in microseconds
 */
u32 TIMER_u32GetElapsedTime(TIMER_IDType Timer_Number)
{
	u32 Remaining_time=0;
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		Remaining_time = (TIMER2->CNT)*((TIMER2->PSC+1)/F_APB1_MHZ);
		break;
	case TIMER3_SELECTION:
		Remaining_time = (TIMER3->CNT)*((TIMER3->PSC+1)/F_APB1_MHZ);
		break;
	case TIMER4_SELECTION:
		Remaining_time = (TIMER4->CNT)*((TIMER4->PSC+1)/F_APB1_MHZ);
		break;
	case TIMER5_SELECTION:
		Remaining_time = (TIMER5->CNT)*((TIMER5->PSC+1)/F_APB1_MHZ);
		break;
	}

	return Remaining_time;
}










/*
 * @brief   this function is used to initialize the timer channel
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	ChannelID of type @TIMER_ChannelType
 * @para 	Mode of type @TIMER_OutputCompareModeType
 * @para 	ActiveType of type @TIMER_ChannelOutputActiveType
 * @para 	ChannelType of type @TIMER_ChannelEnableType
 * @retval  no return
 */
void TIMER_ChannelInit(TIMER_IDType Timer_Number,
		               TIMER_ChannelType ChannelID,
					   TIMER_OutputCompareModeType Mode,
					   TIMER_ChannelOutputActiveType ActiveType,
					   TIMER_ChannelEnableType ChannelType){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			/* Adjust the output compare Channel Mode */
			TIMER2->CCMR1 = (TIMER2->CCMR1 & CHANNEL1_MASK)|(Mode <<OC1M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER2->CCMR1,OC1PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER2->CCER , CC1P);
			}
			else{
				SET_BIT(TIMER2->CCER , CC1P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER2->CCER , CC1E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER2->CCER , CC1E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_2:
			/* Adjust the output compare Channel Mode */
			TIMER2->CCMR1 = (TIMER2->CCMR1 & CHANNEL2_MASK)|(Mode <<OC2M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER2->CCMR1,OC2PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER2->CCER , CC2P);
			}
			else{
				SET_BIT(TIMER2->CCER , CC2P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER2->CCER , CC2E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER2->CCER , CC2E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_3:
			/* Adjust the output compare Channel Mode */
			TIMER2->CCMR2 = (TIMER2->CCMR2 & CHANNEL3_MASK)|(Mode <<OC3M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER2->CCMR2,OC3PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER2->CCER , CC3P);
			}
			else{
				SET_BIT(TIMER2->CCER , CC3P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER2->CCER , CC3E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER2->CCER , CC3E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_4:
			/* Adjust the output compare Channel Mode */
			TIMER2->CCMR2 = (TIMER2->CCMR2 & CHANNEL4_MASK)|(Mode <<OC4M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER2->CCMR2,OC4PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER2->CCER , CC4P);
			}
			else{
				SET_BIT(TIMER2->CCER , CC4P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER2->CCER , CC4E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER2->CCER , CC4E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_ALL_CHANNELS:
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;
	case TIMER3_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			/* Adjust the output compare Channel Mode */
			TIMER3->CCMR1 = (TIMER3->CCMR1 & CHANNEL1_MASK)|(Mode <<OC1M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER3->CCMR1,OC1PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER3->CCER , CC1P);
			}
			else{
				SET_BIT(TIMER3->CCER , CC1P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER3->CCER , CC1E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER3->CCER , CC1E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_2:
			/* Adjust the output compare Channel Mode */
			TIMER3->CCMR1 = (TIMER3->CCMR1 & CHANNEL2_MASK)|(Mode <<OC2M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER3->CCMR1,OC2PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER3->CCER , CC2P);
			}
			else{
				SET_BIT(TIMER3->CCER , CC2P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER3->CCER , CC2E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER3->CCER , CC2E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_3:
			/* Adjust the output compare Channel Mode */
			TIMER3->CCMR2 = (TIMER3->CCMR2 & CHANNEL3_MASK)|(Mode <<OC3M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER3->CCMR2,OC3PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER3->CCER , CC3P);
			}
			else{
				SET_BIT(TIMER3->CCER , CC3P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER3->CCER , CC3E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER3->CCER , CC3E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_4:
			/* Adjust the output compare Channel Mode */
			TIMER3->CCMR2 = (TIMER3->CCMR2 & CHANNEL4_MASK)|(Mode <<OC4M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER3->CCMR2,OC4PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER3->CCER , CC4P);
			}
			else{
				SET_BIT(TIMER3->CCER , CC4P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER3->CCER , CC4E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER3->CCER , CC4E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_ALL_CHANNELS:
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;
	case TIMER4_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			/* Adjust the output compare Channel Mode */
			TIMER4->CCMR1 = (TIMER4->CCMR1 & CHANNEL1_MASK)|(Mode <<OC1M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER4->CCMR1,OC1PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER4->CCER , CC1P);
			}
			else{
				SET_BIT(TIMER4->CCER , CC1P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER4->CCER , CC1E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER4->CCER , CC1E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_2:
			/* Adjust the output compare Channel Mode */
			TIMER4->CCMR1 = (TIMER4->CCMR1 & CHANNEL2_MASK)|(Mode <<OC2M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER4->CCMR1,OC2PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER4->CCER , CC2P);
			}
			else{
				SET_BIT(TIMER4->CCER , CC2P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER4->CCER , CC2E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER4->CCER , CC2E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_3:
			/* Adjust the output compare Channel Mode */
			TIMER4->CCMR2 = (TIMER4->CCMR2 & CHANNEL3_MASK)|(Mode <<OC3M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER3->CCMR2,OC3PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER4->CCER , CC3P);
			}
			else{
				SET_BIT(TIMER4->CCER , CC3P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER4->CCER , CC3E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER4->CCER , CC3E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_4:
			/* Adjust the output compare Channel Mode */
			TIMER4->CCMR2 = (TIMER4->CCMR2 & CHANNEL4_MASK)|(Mode <<OC4M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER4->CCMR2,OC4PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER4->CCER , CC4P);
			}
			else{
				SET_BIT(TIMER4->CCER , CC4P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER4->CCER , CC4E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER4->CCER , CC4E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_ALL_CHANNELS:
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;
	case TIMER5_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			/* Adjust the output compare Channel Mode */
			TIMER5->CCMR1 = (TIMER5->CCMR1 & CHANNEL1_MASK)|(Mode <<OC1M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER5->CCMR1,OC1PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER5->CCER , CC1P);
			}
			else{
				SET_BIT(TIMER5->CCER , CC1P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER5->CCER , CC1E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER5->CCER , CC1E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_2:
			/* Adjust the output compare Channel Mode */
			TIMER5->CCMR1 = (TIMER5->CCMR1 & CHANNEL2_MASK)|(Mode <<OC2M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER5->CCMR1,OC2PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER5->CCER , CC2P);
			}
			else{
				SET_BIT(TIMER5->CCER , CC2P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER5->CCER , CC2E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER5->CCER , CC2E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_3:
			/* Adjust the output compare Channel Mode */
			TIMER5->CCMR2 = (TIMER5->CCMR2 & CHANNEL3_MASK)|(Mode <<OC3M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER5->CCMR2,OC3PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER5->CCER , CC3P);
			}
			else{
				SET_BIT(TIMER5->CCER , CC3P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER5->CCER , CC3E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER5->CCER , CC3E);
			}
			else{
				/* Do Nothing */
			}
			break;
		case TIMER_CHANNEL_4:
			/* Adjust the output compare Channel Mode */
			TIMER5->CCMR2 = (TIMER5->CCMR2 & CHANNEL4_MASK)|(Mode <<OC4M0);
			/* Clear OC1PE Bit */
			CLEAR_BIT(TIMER5->CCMR2,OC4PE);
			/* Adjust the polarity
			 * Active High   0
			 * Active Low    1
			 *  */
			if(ActiveType == ACTIVE_HIGH){
				CLEAR_BIT(TIMER5->CCER , CC4P);
			}
			else{
				SET_BIT(TIMER5->CCER , CC4P);
			}


			if(ChannelType==TIMER_CHANNEL_ENABLE){
				/* Set the channel to be active to output the desired signal */
				SET_BIT(TIMER5->CCER , CC4E);
			}
			else if(ChannelType==TIMER_CHANNEL_DISABLE){
				/* Clear the channel to be deactivated to output the desired signal */
				CLEAR_BIT(TIMER5->CCER , CC4E);
			}
			else{
				/* Do Nothing */
			}
		break;
		case TIMER_ALL_CHANNELS:
			break;
		case TIMER_NO_CHANNELS:
			break;
	}

}
}




/*
 * @brief   this function initializes the timer
 * @para 	Configuration of type @TIMER_configType
 * @retval  no return
 */
void TIMER_Init(TIMER_configType *Configuration){
	/* Adjust the slave mode selection */
	/* Use the internal clock */


	if(Configuration->timer_id == TIMER2_SELECTION){
		TIMER2->SMCR = 0;
		TIMER2->CR1 = (Configuration->PreloadType    << ARPE)\
				|(Configuration->AlignedType         << CMS0)\
				|(Configuration->CountMode           << DIR );

		CLEAR_BIT(TIMER2->CR1,CEN);

		/* Adjust the interrupt and update event */
		if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED){
			/* Update event enabled & interrupt flag disabled */
			SET_BIT(TIMER2->CR1,URS);
			CLEAR_BIT(TIMER2->CR1,UDIS);
		}
		else if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_ENABLED){
			/* Update event enabled & interrupt flag Enabled */
			CLEAR_BIT(TIMER2->CR1,URS);
			CLEAR_BIT(TIMER2->CR1,UDIS);
		}

		/* Set UG Bit */
		SET_BIT(TIMER2->EGR,UG);

	}
	else if(Configuration->timer_id == TIMER5_SELECTION){
		TIMER5->SMCR = 0;
		TIMER5->CR1 = (Configuration->PreloadType    << ARPE)\
				|(Configuration->AlignedType         << CMS0)\
				|(Configuration->CountMode           << DIR );

		/* Adjust the interrupt and update event */
		if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED){
			/* Update event enabled & interrupt flag disabled */
			SET_BIT(TIMER5->CR1,URS);
			CLEAR_BIT(TIMER5->CR1,UDIS);
		}
		else if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_ENABLED){
			/* Update event enabled & interrupt flag Enabled */
			CLEAR_BIT(TIMER5->CR1,URS);
			CLEAR_BIT(TIMER5->CR1,UDIS);
		}

		/* Set UG Bit */
		SET_BIT(TIMER5->EGR,UG);

	}
	else if(Configuration->timer_id == TIMER3_SELECTION){
		TIMER3->SMCR = 0;
		TIMER3->CR1 = (Configuration->PreloadType    << ARPE)\
				|(Configuration->AlignedType         << CMS0)\
				|(Configuration->CountMode           << DIR );

		/* Adjust the interrupt and update event */
		if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED){
			/* Update event enabled & interrupt flag disabled */
			SET_BIT(TIMER3->CR1,URS);
			CLEAR_BIT(TIMER3->CR1,UDIS);
		}
		else if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_ENABLED){
			/* Update event enabled & interrupt flag Enabled */
			CLEAR_BIT(TIMER3->CR1,URS);
			CLEAR_BIT(TIMER3->CR1,UDIS);
		}

		/* Set UG Bit */
		SET_BIT(TIMER3->EGR,UG);


	}
	else if(Configuration->timer_id == TIMER4_SELECTION){
		TIMER4->SMCR = 0;
		TIMER4->CR1 = (Configuration->PreloadType    << ARPE)\
				|(Configuration->AlignedType         << CMS0)\
				|(Configuration->CountMode           << DIR );

		/* Adjust the interrupt and update event */
		if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED){
			/* Update event enabled & interrupt flag disabled */
			SET_BIT(TIMER4->CR1,URS);
			CLEAR_BIT(TIMER4->CR1,UDIS);
		}
		else if(Configuration->UEV_INT_Type == TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_ENABLED){
			/* Update event enabled & interrupt flag Enabled */
			CLEAR_BIT(TIMER4->CR1,URS);
			CLEAR_BIT(TIMER4->CR1,UDIS);
		}

		/* Set UG Bit */
		SET_BIT(TIMER4->EGR,UG);

	}


}




/*
 * @brief   this function start the timer counts one time only
 * @para 	Timer_Number of type @TIMER_IDType
 * @retval  no return
 */
void TIMER_Start_OneShot(TIMER_IDType Timer_Number){
	/* Here, after one shot, it will stop the timer
	 * Clearing the CEN Bit in CR1 Register
	 *  */

	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		SET_BIT(TIMER2->CR1,OPM);
		SET_BIT(TIMER2->CR1,CEN);
		break;
	case TIMER3_SELECTION:
		SET_BIT(TIMER3->CR1,OPM);
		SET_BIT(TIMER3->CR1,CEN);
		break;
	case TIMER4_SELECTION:
		SET_BIT(TIMER4->CR1,OPM);
		SET_BIT(TIMER4->CR1,CEN);
		break;
	case TIMER5_SELECTION:
		SET_BIT(TIMER5->CR1,OPM);
		SET_BIT(TIMER5->CR1,CEN);
		break;
	}

}



/*
 * @brief   this function start the timer counts continuously
 * @para 	Timer_Number of type @TIMER_IDType
 * @retval  no return
 */
void TIMER_Start_Continuous(TIMER_IDType Timer_Number,TIMER_ChannelType ChannelID){
	/* Here, It will continuously output a PWM Signal */

	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		CLEAR_BIT(TIMER2->CR1,OPM);
		/* Enable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			SET_BIT(TIMER2->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			SET_BIT(TIMER2->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			SET_BIT(TIMER2->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			SET_BIT(TIMER2->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			SET_BIT(TIMER2->CCER , CC1E);
			SET_BIT(TIMER2->CCER , CC2E);
			SET_BIT(TIMER2->CCER , CC3E);
			SET_BIT(TIMER2->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}
		/* Enable Timer 2 */
		SET_BIT(TIMER2->CR1,CEN);

		break;
	case TIMER3_SELECTION:
		CLEAR_BIT(TIMER3->CR1,OPM);
		/* Enable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			SET_BIT(TIMER3->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			SET_BIT(TIMER3->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			SET_BIT(TIMER3->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			SET_BIT(TIMER3->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			SET_BIT(TIMER3->CCER , CC1E);
			SET_BIT(TIMER3->CCER , CC2E);
			SET_BIT(TIMER3->CCER , CC3E);
			SET_BIT(TIMER3->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}

		SET_BIT(TIMER3->CR1,CEN);
		break;
	case TIMER4_SELECTION:
		CLEAR_BIT(TIMER4->CR1,OPM);
		/* Enable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			SET_BIT(TIMER4->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			SET_BIT(TIMER4->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			SET_BIT(TIMER4->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			SET_BIT(TIMER4->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			SET_BIT(TIMER4->CCER , CC1E);
			SET_BIT(TIMER4->CCER , CC2E);
			SET_BIT(TIMER4->CCER , CC3E);
			SET_BIT(TIMER4->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}
		SET_BIT(TIMER4->CR1,CEN);
		break;
	case TIMER5_SELECTION:
		CLEAR_BIT(TIMER5->CR1,OPM);
		/* Enable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			SET_BIT(TIMER5->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			SET_BIT(TIMER5->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			SET_BIT(TIMER5->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			SET_BIT(TIMER5->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			SET_BIT(TIMER5->CCER , CC1E);
			SET_BIT(TIMER5->CCER , CC2E);
			SET_BIT(TIMER5->CCER , CC3E);
			SET_BIT(TIMER5->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}
		SET_BIT(TIMER5->CR1,CEN);
		break;
	}

}






/*
 * @brief   this function enables the interrupt of timer
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	InterruptID of type @TIMER_InterryptType
 * @retval  no return
 */
void TIMER_EnableInterrupt(TIMER_IDType Timer_Number,TIMER_InterryptType InterruptID){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			SET_BIT(TIMER2->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			SET_BIT(TIMER2->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			SET_BIT(TIMER2->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			SET_BIT(TIMER2->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			SET_BIT(TIMER2->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			SET_BIT(TIMER2->DIER,TIE);
			break;
		}
		break;
	case TIMER3_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			SET_BIT(TIMER3->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			SET_BIT(TIMER3->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			SET_BIT(TIMER3->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			SET_BIT(TIMER3->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			SET_BIT(TIMER3->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			SET_BIT(TIMER3->DIER,TIE);
			break;
		}
		break;
	case TIMER4_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			SET_BIT(TIMER4->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			SET_BIT(TIMER4->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			SET_BIT(TIMER4->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			SET_BIT(TIMER4->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			SET_BIT(TIMER4->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			SET_BIT(TIMER4->DIER,TIE);
			break;
		}
		break;
	case TIMER5_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			SET_BIT(TIMER5->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			SET_BIT(TIMER5->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			SET_BIT(TIMER5->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			SET_BIT(TIMER5->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			SET_BIT(TIMER5->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			SET_BIT(TIMER5->DIER,TIE);
			break;
		}
			break;
	}
}





/*
 * @brief   this function disables the interrupt of timer
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	InterruptID of type @TIMER_InterryptType
 * @retval  no return
 */
void TIMER_DisableInterrupt(TIMER_IDType Timer_Number,TIMER_InterryptType InterruptID){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			CLEAR_BIT(TIMER2->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			CLEAR_BIT(TIMER2->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			CLEAR_BIT(TIMER2->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			CLEAR_BIT(TIMER2->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			CLEAR_BIT(TIMER2->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			CLEAR_BIT(TIMER2->DIER,TIE);
			break;
		}
		break;
	case TIMER3_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			CLEAR_BIT(TIMER3->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			CLEAR_BIT(TIMER3->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			CLEAR_BIT(TIMER3->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			CLEAR_BIT(TIMER3->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			CLEAR_BIT(TIMER3->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			CLEAR_BIT(TIMER3->DIER,TIE);
			break;
		}
		break;
	case TIMER4_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			CLEAR_BIT(TIMER4->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			CLEAR_BIT(TIMER4->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			CLEAR_BIT(TIMER4->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			CLEAR_BIT(TIMER4->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			CLEAR_BIT(TIMER4->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			CLEAR_BIT(TIMER4->DIER,TIE);
			break;
		}
		break;
	case TIMER5_SELECTION:
		switch(InterruptID){
		case TIMER_UPDATE_INTERRUPT:
			CLEAR_BIT(TIMER5->DIER,UIE);
			break;
		case TIMER_COMAPRE_1_INTERRUPT:
			CLEAR_BIT(TIMER5->DIER,CC1IE);
			break;
		case TIMER_COMAPRE_2_INTERRUPT:
			CLEAR_BIT(TIMER5->DIER,CC2IE);
			break;
		case TIMER_COMAPRE_3_INTERRUPT:
			CLEAR_BIT(TIMER5->DIER,CC3IE);
			break;
		case TIMER_COMAPRE_4_INTERRUPT:
			CLEAR_BIT(TIMER5->DIER,CC4IE);
			break;
		case TIMER_TRIGGER_INTERRUPT:
			CLEAR_BIT(TIMER5->DIER,TIE);
			break;
		}
			break;
	}
}






/*
 * @brief   this function stops the timer
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	InterruptID of type @TIMER_InterryptType
 * @retval  no return
 */
void TIMER_Stop(TIMER_IDType Timer_Number,TIMER_ChannelType ChannelID){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		CLEAR_BIT(TIMER2->CR1,CEN);
		/* Disable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			CLEAR_BIT(TIMER2->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			CLEAR_BIT(TIMER2->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			CLEAR_BIT(TIMER2->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			CLEAR_BIT(TIMER2->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			CLEAR_BIT(TIMER2->CCER , CC1E);
			CLEAR_BIT(TIMER2->CCER , CC2E);
			CLEAR_BIT(TIMER2->CCER , CC3E);
			CLEAR_BIT(TIMER2->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}

		break;
	case TIMER3_SELECTION:
		CLEAR_BIT(TIMER3->CR1,CEN);
		/* Disable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			CLEAR_BIT(TIMER3->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			CLEAR_BIT(TIMER3->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			CLEAR_BIT(TIMER3->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			CLEAR_BIT(TIMER3->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			CLEAR_BIT(TIMER3->CCER , CC1E);
			CLEAR_BIT(TIMER3->CCER , CC2E);
			CLEAR_BIT(TIMER3->CCER , CC3E);
			CLEAR_BIT(TIMER3->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}
		break;
	case TIMER4_SELECTION:
		CLEAR_BIT(TIMER4->CR1,CEN);
		/* Disable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			CLEAR_BIT(TIMER4->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			CLEAR_BIT(TIMER4->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			CLEAR_BIT(TIMER4->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			CLEAR_BIT(TIMER4->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			CLEAR_BIT(TIMER4->CCER , CC1E);
			CLEAR_BIT(TIMER4->CCER , CC2E);
			CLEAR_BIT(TIMER4->CCER , CC3E);
			CLEAR_BIT(TIMER4->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}
		break;
	case TIMER5_SELECTION:
		CLEAR_BIT(TIMER5->CR1,CEN);
		/* Disable Channels */
		/* Disable Channels */
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			CLEAR_BIT(TIMER5->CCER , CC1E);
			break;
		case TIMER_CHANNEL_2:
			CLEAR_BIT(TIMER5->CCER , CC2E);
			break;
		case TIMER_CHANNEL_3:
			CLEAR_BIT(TIMER5->CCER , CC3E);
			break;
		case TIMER_CHANNEL_4:
			CLEAR_BIT(TIMER5->CCER , CC4E);
			break;
		case TIMER_ALL_CHANNELS:
			CLEAR_BIT(TIMER5->CCER , CC1E);
			CLEAR_BIT(TIMER5->CCER , CC2E);
			CLEAR_BIT(TIMER5->CCER , CC3E);
			CLEAR_BIT(TIMER5->CCER , CC4E);
			break;
		case TIMER_NO_CHANNELS:

			break;
		}
		break;
	}
}





/*
 * @brief   this function sets the timer prescalar
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	prescaler of type @TIMER_PrescalerType
 * @retval  no return
 */
void TIMER_SetPrescaler(TIMER_IDType Timer_Number , TIMER_PrescalerType prescaler){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		TIMER2->PSC = prescaler;
		break;
	case TIMER3_SELECTION:
		TIMER3->PSC = prescaler;
		break;
	case TIMER4_SELECTION:
		TIMER4->PSC = prescaler;
		break;
	case TIMER5_SELECTION:
		TIMER5->PSC = prescaler;
		break;
	}

}




/*
 * @brief   this function sets the compare match value
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	ChannelID of type @TIMER_ChannelType
 * @para 	ComapreValue of type @TIMER_OutputCompareValue
 * @retval  no return
 */
void TIMER_SetCompareValue(TIMER_IDType Timer_Number, TIMER_ChannelType ChannelID , TIMER_OutputCompareValue ComapreValue){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			TIMER2->CCR1 = ComapreValue;
			break;
		case TIMER_CHANNEL_2:
			TIMER2->CCR2 = ComapreValue;
			break;
		case TIMER_CHANNEL_3:
			TIMER2->CCR3 = ComapreValue;
			break;
		case TIMER_CHANNEL_4:
			TIMER2->CCR4 = ComapreValue;
			break;
		case TIMER_ALL_CHANNELS:
			TIMER2->CCR1 = ComapreValue;
			TIMER2->CCR2 = ComapreValue;
			TIMER2->CCR3 = ComapreValue;
			TIMER2->CCR4 = ComapreValue;
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;

	case TIMER3_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			TIMER3->CCR1 = ComapreValue;
			break;
		case TIMER_CHANNEL_2:
			TIMER3->CCR2 = ComapreValue;
			break;
		case TIMER_CHANNEL_3:
			TIMER3->CCR3 = ComapreValue;
			break;
		case TIMER_CHANNEL_4:
			TIMER3->CCR4 = ComapreValue;
			break;
		case TIMER_ALL_CHANNELS:
			TIMER3->CCR1 = ComapreValue;
			TIMER3->CCR2 = ComapreValue;
			TIMER3->CCR3 = ComapreValue;
			TIMER3->CCR4 = ComapreValue;
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;

	case TIMER4_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			TIMER4->CCR1 = ComapreValue;
			break;
		case TIMER_CHANNEL_2:
			TIMER4->CCR2 = ComapreValue;
			break;
		case TIMER_CHANNEL_3:
			TIMER4->CCR3 = ComapreValue;
			break;
		case TIMER_CHANNEL_4:
			TIMER4->CCR4 = ComapreValue;
			break;
		case TIMER_ALL_CHANNELS:
			TIMER4->CCR1 = ComapreValue;
			TIMER4->CCR2 = ComapreValue;
			TIMER4->CCR3 = ComapreValue;
			TIMER4->CCR4 = ComapreValue;
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;

	case TIMER5_SELECTION:
		switch(ChannelID){
		case TIMER_CHANNEL_1:
			TIMER5->CCR1 = ComapreValue;
			break;
		case TIMER_CHANNEL_2:
			TIMER5->CCR2 = ComapreValue;
			break;
		case TIMER_CHANNEL_3:
			TIMER5->CCR3 = ComapreValue;
			break;
		case TIMER_CHANNEL_4:
			TIMER5->CCR4 = ComapreValue;
			break;
		case TIMER_ALL_CHANNELS:
			TIMER5->CCR1 = ComapreValue;
			TIMER5->CCR2 = ComapreValue;
			TIMER5->CCR3 = ComapreValue;
			TIMER5->CCR4 = ComapreValue;
			break;
		case TIMER_NO_CHANNELS:
			break;
		}
		break;
	}
}




/*
 * @brief   this function sets auto reload register in timer
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	AutoReloadValue of type @TIMER_AutoReloadType
 * @retval  no return
 */
void TIMER_SetARR(TIMER_IDType Timer_Number , TIMER_AutoReloadType AutoReloadValue){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		TIMER2->ARR = AutoReloadValue;
		break;
	case TIMER3_SELECTION:
		TIMER3->ARR = AutoReloadValue;
		break;
	case TIMER4_SELECTION:
		TIMER4->ARR = AutoReloadValue;
		break;
	case TIMER5_SELECTION:
		TIMER5->ARR = AutoReloadValue;
		break;
	}

}






/*
 * @brief   this function sets the clear time
 * @para 	Timer_Number of type @TIMER_IDType
 * @retval  no return
 */
void TIMER_ClearTimerCount(TIMER_IDType Timer_Number){
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		TIMER2->CNT = 0;
		break;
	case TIMER3_SELECTION:
		TIMER3->CNT = 0;
		break;
	case TIMER4_SELECTION:
		TIMER4->CNT = 0;
		break;
	case TIMER5_SELECTION:
		TIMER5->CNT = 0;
		break;
	}

}




/*
 * @brief   this function sets the duty cycle for timer
 * @para 	Timer_Number of type @TIMER_IDType
 * @para 	ChannelID of type @TIMER_ChannelType
 * @para 	DutyCycle of type @u8
 * @retval  no return
 */
void TIMER_SetDutyCycle(TIMER_IDType Timer_Number, TIMER_ChannelType ChannelID ,u8 DutyCycle){
	u32 TimerOnValue =0;
	switch(Timer_Number)
	{
	case TIMER2_SELECTION:
		TimerOnValue = (((TIMER2->ARR+1) * (u32)DutyCycle)/100)-1;
		break;
	case TIMER3_SELECTION:
		TimerOnValue = (((TIMER3->ARR+1) * (u32)DutyCycle)/100)-1;
		break;
	case TIMER4_SELECTION:
		TimerOnValue = (((TIMER4->ARR+1) * (u32)DutyCycle)/100)-1;
		break;
	case TIMER5_SELECTION:
		TimerOnValue = (((TIMER5->ARR+1) * (u32)DutyCycle)/100)-1;
		break;
	}
	TIMER_SetCompareValue(Timer_Number, ChannelID,  TimerOnValue);
}









/*
 * @brief   this function initializes the ICU mode in Timer
 * @retval  no return
 */
void voidICU_Init(void)
{


		TIM1->PSC = TIM1_PRESCALER -1;		// Set the prescaler
		TIM1->ARR = 0xFFFF;					// set ARR for max value
		TIM1->CNT = 0 ;						// Clear counter

		/* capture is done ---> CH1 is rising edge and CH2 is falling edge */
		TIM1->CCER &=  ~0x2;
		TIM1->CCER |=  0x20;

	TIM1->CCMR1 = 0x0201; /*Enable Filter*/

		/* configure the timer slave mode with TI1FP1 as reset signal */
		TIM1->SMCR = 0x54;

		/* Capture enable for CH1 & CH2 */
		TIM1->CCER |=  0x11;
		/* counter enable */
		TIM1->CR1  |= 0x1;
		/* interrupt enable for CH1 & CH2 */
		TIM1->DIER  |= 0x2;

} // end of function





/*
 * @brief   this function measures the on time to get the duty cycle
 * @retval  no return
 */
f32 f32MeasureTon(void)
{

	volatile f32 Local_f32TimeOn =0;


		Local_f32TimeOn = Global_u16Tim1Ch1InputCaptures[1];

	return Local_f32TimeOn;
}





/*
 * @brief   this function measures period of signal
 * @retval  no return
 */
f32 f32MeasureTotalTime(void)
{

	volatile f32 Local_f32TotalTime =0;

		Local_f32TotalTime = Global_u16Tim1Ch1InputCaptures[0];

	return Local_f32TotalTime;
}




/*
 * @brief   this function measures the freqency of signal
 * @retval  no return
 */
f32 f32MeasureFrequncy(void) {

	volatile f32 Local_f32Frequncy = 0;

	Local_f32Frequncy = (1000000UL) / Global_u16Tim1Ch1InputCaptures[0];


	return Local_f32Frequncy;
}





/*
 * @brief   this function measures the duty cycle
 * @retval  no return
 */
f32 f32MeasureDutyCycle(void) {

	volatile f32 Local_f32DutyCycle = 0;

	Local_f32DutyCycle = (float) ((Global_u16Tim1Ch1InputCaptures[1] / Global_u16Tim1Ch1InputCaptures[0]) * 100.0);

	return Local_f32DutyCycle;
}




/*
 * @brief   this function is called when ICU interrupt happens
 * @retval  no return
 */
void TIM1_CC_IRQHandler(void)
{

		if(1 == Global_u8Tim1Ch1Counter)
		{
			Global_u16Tim1Ch1InputCaptures[0] = TIM1->CCR1 ;
			Global_u8Tim1Ch1Counter++;
		}
		else if(2 == Global_u8Tim1Ch1Counter)
		{
			Global_u16Tim1Ch1InputCaptures[1] = TIM1->CCR2;
		Global_u16Tim1Ch1InputCaptures[1] = Global_u16Tim1Ch1InputCaptures[1]
				+ 2;
			Global_u8Tim1Ch1Counter = 1;
		}


}

