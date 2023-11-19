/*
 * LINE_FOLLOWER_INTERFACE.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Misra
 */

#ifndef LINE_FOLLOWER_INTERFACE_H_
#define LINE_FOLLOWER_INTERFACE_H_



/*		global variables		*/
extern u8 line_follower_flag_right;
extern u8 line_follower_flag_left;



void line_follower_init();

void RIGHT_LED_INT_ENABLE(void);
void MIDDLE_LED_INT_ENABLE(void);
void LEFT_LED_INT_ENABLE(void);

void RIGHT_LED_INT_DISABLE(void);
void MIDDLE_LED_INT_DISABLE(void);
void LEFT_LED_INT_DISABLE(void);
#endif /* LINE_FOLLOWER_INTERFACE_H_ */
