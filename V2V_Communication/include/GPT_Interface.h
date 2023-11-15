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
/************************************** Types Declaration ***********************************/
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

/********************************************************************************************/
/************************************** #s used in the Module *******************************/
/********************************************************************************************/


#define       CHANNEL1_MASK           0xFFFFFF00
#define       CHANNEL2_MASK           0xFFFF00FF
#define       CHANNEL3_MASK           0xFFFFFF00
#define       CHANNEL4_MASK           0xFFFF00FF





/********************************************************************************************/
/************************************* Extern Configuration *********************************/
/********************************************************************************************/
extern TIMER_configType Timer2_configuration;

extern TIMER_configType Timer3_configuration;

extern TIMER_configType Timer5_configuration;

extern TIMER_configType Timer4_configuration;









/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/

/* FUNCTION      : TIMER_Init                                      */
/* INPUT         : Configuration of the Timer Selection            */
/* OUTPUT        : No Return                                       */
/* Description   : The First Function needed to be called for the  */
/*                 initialization of the timer                     */
void TIMER_Init(TIMER_configType *Configuration);



/* FUNCTION      : TIMER_VoidSetCallBack                                    */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Pointer to the function that will be called          */
/* OUTPUT        : No Return                                                */
/* Description   : Function to set the call back if an interrupt happened   */
void TIMER_VoidSetCallBack(TIMER_IDType Timer_Number,void (*ptr)(void));



/* FUNCTION      : TIMER_SetPrescaler                                       */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Pre-scaler Value                                     */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Adjust the pre-scaler of a given Timer       */
void TIMER_SetPrescaler(TIMER_IDType Timer_Number , TIMER_PrescalerType prescaler);


/* FUNCTION      : TIMER_SetCompareValue                                    */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Channel Index                                        */
/*                 3 - Compare Value Index                                  */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Adjust the Compare Value of a given Timer    */
/*                 and given Channel                                        */
void TIMER_SetCompareValue(TIMER_IDType Timer_Number, TIMER_ChannelType ChannelID , TIMER_OutputCompareValue ComapreValue);




/* FUNCTION      : TIMER_SetARR                                             */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Auto Reload Register Value                           */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Adjust the Auto Reload Register Value  of a  */
/*                 a given Timer                                            */
void TIMER_SetARR(TIMER_IDType Timer_Number , TIMER_AutoReloadType AutoReloadValue);




/* FUNCTION      : TIMER_ClearTimerCount                                    */
/* INPUT         : 1 - Timer Index                                          */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Clear the Counter register of a given Timer  */
void TIMER_ClearTimerCount(TIMER_IDType Timer_Number);




/* FUNCTION      : TIMER_SetDutyCycle                                       */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Channel Index                                        */
/*                 3 - DutyCycle                                            */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Adjust the Duty Cycle of a given Timer       */
/*                 and given Channel                                        */
void TIMER_SetDutyCycle(TIMER_IDType Timer_Number, TIMER_ChannelType ChannelID ,u8 DutyCycle);





/* FUNCTION      : TIMER_Start_OneShot                                      */
/* INPUT         : Timer Index                                              */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Start the timer only once                    */
void TIMER_Start_OneShot(TIMER_IDType Timer_Number);



/* FUNCTION      : TIMER_Start_Continuous                                    */
/* INPUT         : 1 - Timer Index                                           */
/*                 2 - Channel Index                                         */
/* OUTPUT        : No Return                                                 */
/* Description   : Function to Start the timer Continuously of a given timer */
/*                 and a given Channel or no channel or All channels         */
void TIMER_Start_Continuous(TIMER_IDType Timer_Number,TIMER_ChannelType ChannelID);




/* FUNCTION      : TIMER_EnableInterrupt                                     */
/* INPUT         : 1 - Timer Index                                           */
/*                 2 - Interrupt Type                                        */
/* OUTPUT        : No Return                                                 */
/* Description   : Function to Enable the Interrupt for a given Timer and a  */
/*                 given Interrupt Type                                      */
void TIMER_EnableInterrupt(TIMER_IDType Timer_Number,TIMER_InterryptType InterruptID);




/* FUNCTION      : TIMER_DisableInterrupt                                     */
/* INPUT         : 1 - Timer Index                                            */
/*                 2 - Interrupt Type                                         */
/* OUTPUT        : No Return                                                  */
/* Description   : Function to Disable the Interrupt for a given Timer and a  */
/*                 given Interrupt Type                                       */
void TIMER_DisableInterrupt(TIMER_IDType Timer_Number,TIMER_InterryptType InterruptID);





/* FUNCTION      : TIMER_ChannelInit                                          */
/* INPUT         : 1 - Timer Index                                            */
/*                 2 - Channel Index                                          */
/*                 3 - Mode of the Channel                                    */
/*                 4 - Channel Active Type (Active High or Active Low)        */
/*                 5 - Channel Running Type (ON or OFF)                       */
/* OUTPUT        : No Return                                                  */
/* Description   : Function to initializating the Channel                     */
void TIMER_ChannelInit(TIMER_IDType Timer_Number,
		               TIMER_ChannelType ChannelID,
					   TIMER_OutputCompareModeType Mode,
					   TIMER_ChannelOutputActiveType ActiveType,
					   TIMER_ChannelEnableType ChannelType);





/* FUNCTION      : TIMER_Stop                                               */
/* INPUT         : Timer Index                                              */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Stop the timer                               */
void TIMER_Stop(TIMER_IDType Timer_Number,TIMER_ChannelType ChannelID);





/* FUNCTION      : TIMER_DelayUS                                            */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Delay Value in Micro-seconds                         */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Delay in Micro-seconds                       */
void TIMER_DelayUS(TIMER_IDType Timer_Number,u32 Delay_Value);


/* FUNCTION      : TIMER_DelayMS                                            */
/* INPUT         : 1 - Timer Index                                          */
/*                 2 - Delay Value in Milli-seconds                         */
/* OUTPUT        : No Return                                                */
/* Description   : Function to Delay in Milli-seconds                       */
void TIMER_DelayMS(TIMER_IDType Timer_Number,u32 Delay_Value);




/* Function to return the time elapsed in micro-seconds*/
u32 TIMER_u32GetElapsedTime(TIMER_IDType Timer_Number);

/* Function to return the time remaining in micro-seconds*/
u32 TIMER_u32GetRemainingTime(TIMER_IDType Timer_Number);





void voidICU_Init(void);
f32 f32MeasureTon(void);
f32 f32MeasureTotalTime(void);
f32 f32MeasureFrequncy(void);
f32 f32MeasureDutyCycle(void);








#endif /* GPT_INTERFACE_H_ */
