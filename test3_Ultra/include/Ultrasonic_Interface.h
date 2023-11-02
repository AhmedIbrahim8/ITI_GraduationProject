/*
 * Ultrasonic_Interface.h
 *
 *  Created on: Oct 31, 2023
 *      Author: PC
 */

#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

void Ultrsonic_Init(void);
void Ultrsonic_Trigger(void);

float UltrasonicCalculateDistance(void);



#endif /* ULTRASONIC_INTERFACE_H_ */
