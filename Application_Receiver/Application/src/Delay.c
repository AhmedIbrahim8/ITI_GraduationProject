/*
 * Delay.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Omar Abouzaid
 */

/* Standard Types File */
#include "../include/STD_Types.h"
/* Bit Math File */
#include "../include/BIT_MATH.h"
#include "../include/Delay.h"

void delay_us(u32 microseconds) {
    // Assuming a 16MHz system clock
    microseconds = microseconds * 16;
    while (microseconds--) {
        __asm__("NOP");
    }
}
