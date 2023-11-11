/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCM_Interface.h                                                       */
/*  Description  :   Interface File of the DCM  Driver                                     */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   31/10/2023                                                            */
/*******************************************************************************************/

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_


/********************************************************************************************/
/************************************* Included Files ***************************************/
/********************************************************************************************/
#include "DCM_Config.h"

#include "GPT_Interface.h"


/*******************************************************************************************/
/************************************* Motor Macro *****************************************/
/*******************************************************************************************/
#define    DCM_RIGHT                            0
#define    DCM_LEFT                             1

/*******************************************************************************************/
/************************************* TypeDefs ********************************************/
/*******************************************************************************************/
typedef    u8                    DCM_PortType;
typedef    u8                    DCM_PinType;
typedef    u8                    DCM_Index;

typedef struct{
	TIMER_IDType Speed_TimerType;
	TIMER_ChannelType Speed_ChannelType;
	DCM_PortType Speed_Port_ID;
	DCM_PinType  Speed_Pin_ID;
	DCM_PortType IN1_Port_ID;
	DCM_PinType  IN1_Pin_ID;
	DCM_PortType IN2_Port_ID;
	DCM_PinType  IN2_Pin_ID;

}DCM_ConfigType;


typedef enum{
	DCM_FORWARD,DCM_REVERSE
}DCM_DirectionType;

/********************************************************************************************/
/************************************* Extern Configuration *********************************/
/********************************************************************************************/
extern DCM_ConfigType Configuration[NUMBER_OF_DC_MOTOR];

/********************************************************************************************/
/************************************** APIs Proto-Types ************************************/
/********************************************************************************************/
void DCM_Init(DCM_ConfigType *Config);

void DCM_Rotate(DCM_Index DCM_Number,u8 Duty_Cycle,DCM_DirectionType Direction);

void DCM_Stop(DCM_Index DCM_Number);


void App_CarMoveForward(u8 Speed);
void App_CarMoveReverse(u8 Speed);
void App_CarMoveRight(u8 Speed);
void App_CarMoveLeft(u8 Speed);
void App_CarMoveAround(u8 Speed);


void App_CarStop(void);







#endif /* DCM_INTERFACE_H_ */
