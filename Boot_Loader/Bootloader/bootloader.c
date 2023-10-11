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
	/* Send the Debug information through the bootloader debug uart */
	HAL_UART_Transmit(BL_DEBUG_UART,(uint8_t *)Message,sizeof(Message),HAL_MAX_DELAY);
	/* clean up the initialized object */
	va_end(args);
}