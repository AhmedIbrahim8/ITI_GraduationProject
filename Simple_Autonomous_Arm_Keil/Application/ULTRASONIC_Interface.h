/*
 * ULTRASONIC_Interface.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Omar Abouzaid
 */

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_
#include "STD_Types.h"

/*Initialization the Ultrasonic */
void UltraSonic_Init(void);


/*Send pulse on the Trig pin */
void UltraSonic_Send_Pulse(void);


/*Measure the Distance*/
u32 UltraSonic_Measure_Distance(void);


#endif /* ULTRASONIC_INTERFACE_H_ */
