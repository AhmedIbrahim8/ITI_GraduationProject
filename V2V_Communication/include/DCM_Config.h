/*******************************************************************************************/
/*  Module       :   DCM                                                                   */
/*  File Name    :   DCM_Config.h                                                          */
/*  Description  :   Interface File of the DCM  Driver                                     */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   31/10/2023                                                            */
/*******************************************************************************************/

#ifndef DCM_CONFIG_H_
#define DCM_CONFIG_H_

#define   NUMBER_OF_DC_MOTOR                     2


#define   DCM_1_SPEED_PORT_ID                          PORTA
#define   DCM_1_SPEED_PIN_ID                           PIN0
#define   DCM_1_SPEED_TIMER                            TIMER2_SELECTION
#define   DCM_1_SPEED_CHANNEL                          TIMER_CHANNEL_1

#define   DCM_1_IN1_PORT_ID                            PORTA
#define   DCM_1_IN1_PIN_ID                             PIN4
#define   DCM_1_IN2_PORT_ID                            PORTA
#define   DCM_1_IN2_PIN_ID                             PIN5




#define   DCM_2_SPEED_PORT_ID                          PORTA
#define   DCM_2_SPEED_PIN_ID                           PIN1
#define   DCM_2_SPEED_TIMER                            TIMER2_SELECTION
#define   DCM_2_SPEED_CHANNEL                          TIMER_CHANNEL_2

#define   DCM_2_IN1_PORT_ID                            PORTA
#define   DCM_2_IN1_PIN_ID                             PIN6
#define   DCM_2_IN2_PORT_ID                            PORTA
#define   DCM_2_IN2_PIN_ID                             PIN7

#endif /* DCM_CONFIG_H_ */
