/*******************************************************************************************/
/*  Module       :   Ultrasonic                                                            */
/*  File Name    :   Ultrasonic_Interface.h                                                */
/*  Description  :   Interface File of the Ultrasonic  Driver                              */
/*  Author       :   Mahmoud Salah                                                         */
/*  Date         :   01/11/2023                                                            */
/*******************************************************************************************/

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

void Ultrsonic_Init(void);
void Ultrsonic_Trigger(void);

float UltrasonicCalculateDistance(void);



#endif /* ULTRASONIC_INTERFACE_H_ */
