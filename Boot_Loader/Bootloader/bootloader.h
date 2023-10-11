#ifndef BOOTLOADER_H
#define BOOTLOADER_H

/*********************************************************************/
/*************************** Included Files **************************/
/*********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "usart.h"


/*********************************************************************/
/*************************** Macors Declaration **********************/
/*********************************************************************/
#define    BL_DEBUG_UART                      &huart2

#define    BL_ENABLE_UART_DEBUG_MESSAGE       0x00
#define    BL_ENABLE_CAN_DEBUG_MESSAGE        0x01
#define    BL_ENABLE_SPI_DEBUG_MESSAGE        0x02
#define    BL_ENABLE_I2C_DEBUG_MESSAGE        0x03

#define    BL_DEBUG_METHOD                    BL_ENABLE_UART_DEBUG_MESSAGE
/*********************************************************************/
/*************************** APIs Proto-Types ************************/
/*********************************************************************/
void BL_Print_Message(char *format, ...);


/*********************************************************************/
/*********************** Data Types Declaration **********************/
/*********************************************************************/
#endif
