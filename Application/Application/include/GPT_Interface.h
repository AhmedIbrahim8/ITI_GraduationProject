/*******************************************************************************************/
/*  Module       :   GPT                                                                   */
/*  File Name    :   GPT_Interface.h                                                       */
/*  Description  :   Interface File of the GPT  Driver                                     */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   10/10/2023                                                            */
/*******************************************************************************************/

#ifndef GPT_INTERFACE_H_
#define GPT_INTERFACE_H_


#include "STD_Types.h"





/********************************************************************************************/
/************************************* Typedefs ********************************************/
/********************************************************************************************/
typedef enum{
	TIMER2_SELECTION,TIMER5_SELECTION,TIMER3_SELECTION,TIMER4_SELECTION
}TIMER_IDType;



typedef enum{
	TIMER_CHANNEL_DISABLE,
	TIMER_CHANNEL_ENABLE
}TIMER_ChannelEnableType;

typedef enum{
	TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_DISABLED,
	TIMER_UPDATE_EVENT_ENABLED_INTERRUPT_FLAG_ENABLED
}TIMER_UpdateEventInterruptType;



typedef enum{
	TIMER_CHANNEL_1=1,
	TIMER_CHANNEL_2,
	TIMER_CHANNEL_3,
	TIMER_CHANNEL_4,
	TIMER_ALL_CHANNELS,
	TIMER_NO_CHANNELS
}TIMER_ChannelType;


typedef enum{
	TIMER_UPDATE_INTERRUPT,
	TIMER_COMAPRE_1_INTERRUPT,
	TIMER_COMAPRE_2_INTERRUPT,
	TIMER_COMAPRE_3_INTERRUPT,
	TIMER_COMAPRE_4_INTERRUPT,
	TIMER_TRIGGER_INTERRUPT=6,
}TIMER_InterryptType;

typedef enum{
	TIMER_FROZEN ,
	TIMER_SET_CHANNEL_ACTIVE_ON_MATCH,
	TIMER_SET_CHANNEL_INACTIVE_ON_MATCH,
	TIMER_SET_CHANNEL_TOGGLE_ON_MATCH,
	TIMER_FORCE_INACTIVE_OCxREF_LOW,
	TIMER_FORCE_ACTIVE_OCxREF_HIGH,
	TIMER_PWM_MODE_1,
	TIMER_PWM_MODE_2
}TIMER_OutputCompareModeType;



typedef enum{
	COUNT_UP,COUNT_DOWN
}TIMER_CountModeType;

typedef  u32 TIMER_AutoReloadType;

typedef  u16 TIMER_PrescalerType;

typedef enum{
	TIMER_INPUT_CAPTURE,
	TIMER_OUTPUT_COMPARE,
	TIMER_PWM,
	TIMER_ONE_PULSE_MODE
}TIMER_ModeType;


typedef enum{
	TIMER_ARR_NOT_BUFFERED,
	TIMER_ARR_BUFFERED
}TIMER_AutoReloadPreloadType;


typedef enum{
	TIMER_EGDE_ALIGNED_MODE,
	TIMER_CENTER_ALIGNED_MODE_1,
	TIMER_CENTER_ALIGNED_MODE_2,
	TIMER_CENTER_ALIGNED_MODE_3
}TIMER_CenterAlignedMode;


typedef enum{
	ACTIVE_HIGH,
	ACTIVE_LOW
}TIMER_ChannelOutputActiveType;

typedef enum{
	TIMER_NO_STOP,
	TIMER_ONE_PULSE

}TIMER_OnePulseType;

typedef u32 TIMER_OutputCompareValue;











typedef struct{
	TIMER_IDType timer_id;
	TIMER_UpdateEventInterruptType UEV_INT_Type;
	TIMER_AutoReloadPreloadType PreloadType;
	TIMER_CenterAlignedMode AlignedType;
	TIMER_CountModeType CountMode;
}TIMER_configType;




#define       CHANNEL1_MASK           0xFFFFFF00
#define       CHANNEL2_MASK           0xFFFF00FF
#define       CHANNEL3_MASK           0xFFFFFF00
#define       CHANNEL4_MASK           0xFFFF00FF





/********************************************************************************************/
/************************************* Extern Configuration *********************************/
/********************************************************************************************/
extern TIMER_configType Timer2_configuration;
extern TIMER_configType Timer5_configuration;












void TIMER_Init(TIMER_configType *Configuration);

void TIMER_VoidSetCallBack(TIMER_IDType Timer_Number,void (*ptr)(void));

void TIMER_SetPrescaler(TIMER_IDType Timer_Number , TIMER_PrescalerType prescaler);

void TIMER_SetCompareValue(TIMER_IDType Timer_Number, TIMER_ChannelType ChannelID , TIMER_OutputCompareValue ComapreValue);


void TIMER_SetARR(TIMER_IDType Timer_Number , TIMER_AutoReloadType AutoReloadValue);

void TIMER_ClearTimerCount(TIMER_IDType Timer_Number);


void TIMER_SetDutyCycle(TIMER_IDType Timer_Number, TIMER_ChannelType ChannelID ,u8 DutyCycle);



void TIMER_Start_OneShot(TIMER_IDType Timer_Number);


void TIMER_Start_Continuous(TIMER_IDType Timer_Number,TIMER_ChannelType ChannelID);


void TIMER_DelayUS(TIMER_IDType Timer_Number,u32 Delay_Value);


void TIMER_EnableInterrupt(TIMER_IDType Timer_Number,TIMER_InterryptType InterruptID);

void TIMER_DisableInterrupt(TIMER_IDType Timer_Number,TIMER_InterryptType InterruptID);


void TIMER_ChannelInit(TIMER_IDType Timer_Number,
		               TIMER_ChannelType ChannelID,
					   TIMER_OutputCompareModeType Mode,
					   TIMER_ChannelOutputActiveType ActiveType,
					   TIMER_ChannelEnableType ChannelType);


void TIMER_Stop(TIMER_IDType Timer_Number,TIMER_ChannelType ChannelID);






void TIMER_DelayUS(TIMER_IDType Timer_Number,u32 Delay_Value);



void TIMER_DelayMS(TIMER_IDType Timer_Number,u32 Delay_Value);




/* Function to return the time elapsed in micro-seconds*/
u32 TIMER_u32GetElapsedTime(TIMER_IDType Timer_Number);

/* Function to return the time remaining in micro-seconds*/
u32 TIMER_u32GetRemainingTime(TIMER_IDType Timer_Number);













#endif /* GPT_INTERFACE_H_ */
