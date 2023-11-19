/*
 * Servo_Interface.h
 *
 *  Created on: Oct 31, 2023
 *      Author: Omar Abouzaid
 */

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

typedef enum
{
	SERVO_DIRECTION_RIGHT=0,
	SERVO_DIRECTION_FORWARD,
	SERVO_DIRECTION_LEFT
}Servo_Direction;


/*Servo initilization*/
void Servo_Init(void);

/*set direction of Servo motor*/
void SERVO_SET_DIRECTION (Servo_Direction Copy_u8_direction);
#endif /* SERVO_INTERFACE_H_ */



