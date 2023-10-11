/*********************************************************************/
/*************************** Included Files **************************/
/*********************************************************************/
#include "bootloader.h"

/*********************************************************************/
/************************ Static APIs Prototypes *********************/
/*********************************************************************/



/*********************************************************************/
/********************** Global Variables Definitions *****************/
/*********************************************************************/



/*********************************************************************/
/*********************** Static APIs Definitions *********************/
/*********************************************************************/

/* This function used by bootloader to send information to the user
	 about the bootloader state 
*/
void BL_Print_Message(char *format, ...)
{
	/* Message variable to buffer the message the bootloader 
	   wants to print to the user 
	*/
	char Message[100]={0};
	/* Special Defined Data Type */
	va_list args;
	/* Make the args variable points to the first 
	   parameter of the function (BL_Print_Message)
	*/
	va_start(args,format);
	/* To put the debug information  sent by the bootloader 
	   into the Message Variable in string shape
	*/
	vsprintf(Message,format,args);
	
	/* This # used to select between different communication protocols 
	   to debug 
	Ex : we can send the dubug information through CAN or SPI or I2C so,
       we need to make this function configurable 	
	*/
	/* In case of UART is selected as debug communication protocol */
#if BL_DEBUG_METHOD == BL_ENABLE_UART_DEBUG_MESSAGE
	/* Send the Debug information through the bootloader debug uart */
	HAL_UART_Transmit(BL_DEBUG_UART,(uint8_t *)Message,sizeof(Message),HAL_MAX_DELAY);

/* In case of CAN is selected as debug communication protocol */
#elif BL_DEBUG_METHOD == BL_ENABLE_CAN_DEBUG_MESSAGE
/* start code */

/* end code   */

/* In case of SPI is selected as debug communication protocol */
#elif BL_DEBUG_METHOD == BL_ENABLE_SPI_DEBUG_MESSAGE
/* start code */

/* end code   */

/* In case of I2C is selected as debug communication protocol */
#elif BL_DEBUG_METHOD == BL_ENABLE_I2C_DEBUG_MESSAGE
/* start code */

/* end code   */

#endif
	/* clean up the initialized object */
	va_end(args);
}