/*********************************************************************/
/*************************** Included Files **************************/
/*********************************************************************/
#include "bootloader.h"

/*********************************************************************/
/************************ Static APIs Prototypes *********************/
/*********************************************************************/
static void Bootloader_Get_Version(uint8_t *Host_Buffer);

static void Bootloader_Get_Help(uint8_t *Host_Buffer);

static void Bootloader_Get_Chip_Identification_Number(uint8_t *Host_Buffer);

static void Bootloader_Read_Protection_Level(uint8_t *Host_Buffer);

static void Bootloader_Jump_To_Address(uint8_t *Host_Buffer);

static void Bootloader_Erase_Flash(uint8_t *Host_Buffer);

static void Bootloader_Memory_Write(uint8_t *Host_Buffer);

static void Bootloader_Enable_RW_Protection(uint8_t *Host_Buffer);

static void Bootloader_Memory_Read(uint8_t *Host_Buffer);

static void Bootloader_Get_Sector_Protection_Status(uint8_t *Host_Buffer);

static void Bootloader_Read_OTP(uint8_t *Host_Buffer);

static void Bootloader_Disable_RW_Protection(uint8_t *Host_Buffer);
/*********************************************************************/
/********************** Global Variables Definitions *****************/
/*********************************************************************/

/* This array used to receive the command packet from the Host */
static uint8_t BL_Host_Buffer[BL_HOST_BUFFER_RX_LENGTH];


/*********************************************************************/
/*********************** Static APIs Definitions *********************/
/*********************************************************************/

/* This Function used to fetch the command packet sent by the host 
As Example: 
   1- command packet to send the version of the bootloader 
   2- command packet to erase the memory segment of specified sector                
*/
BL_Status BL_UART_Fetch_Host_Command(void)
{
	/* Local Variable used to return the status of the bootloader 
	   Incase the command is supported by the bootloader, the variable will be BL_OK
	*/
	BL_Status Status = BL_NACK;
	/* This variable to receive the status of the UART Trasmit function 
	   incase of timeout errot or hal error or hal ok    
	*/
	HAL_StatusTypeDef HAL_Status = HAL_ERROR;
	/* Variable to store the command length inside it */
	uint8_t Data_Length =0;
	/* This function used to clear the buffer once the function is called again
	It takes :  1- The variable we want to update its value
	            2- The value to be updated into the variable 
	            3- The length of the variable 
	*/
	memset(BL_Host_Buffer,0,BL_HOST_BUFFER_RX_LENGTH);
	/* Command Fromat : Command Length(1 Byte) + Command Code(1 Byte) + Details(N Bytes) + CRC (4 Bytes)*/
	/* First : Receive from the Host(PC) only one byte to specify the number of bytes 
	           that the bootloader will be receive from the host 
	           Bootloader wants to know the number of bytes that will be receive from the Host 
	           the command length is stored at the first element of the (BL_Host_Buffer) variable 
	*/
	HAL_Status = HAL_UART_Receive(BL_HOST_COMMUNICATION_UART,BL_Host_Buffer,1, HAL_MAX_DELAY);
	/* Check on the HAL_Status if it is not equal HAL_OK , then an error happened */
	if(HAL_Status != HAL_OK)
		{
			/* The sataus of this function is not ok */
			Status = BL_NACK;
		}
	else
		{
			/* Store the first element of the buffer which indicate the command length into the 
				 Data_Length variable 
			 */
			Data_Length = BL_Host_Buffer[0];
			/* Send to the host what the bootloader has recevied for a debug information */
			BL_Print_Message("Command Length = %d is Received \r\n",Data_Length);
			/* Recevie Data Bytes based on the Data length received by the bootloader sent by the host */
			HAL_Status = HAL_UART_Receive(BL_HOST_COMMUNICATION_UART,&(BL_Host_Buffer[1]),Data_Length, HAL_MAX_DELAY);
			/* Check on the HAL Status */
			if(HAL_Status != HAL_OK){
			  	/* The sataus of this function is not ok */
			    Status = BL_NACK;
			}
			/* Incase the HAL_Status is ok */
			else{
				/* Here, we will switch on the value of the second element of the buffer which indicates
				   the command code of what the host wants from the bootloader 
				*/
				switch(BL_Host_Buffer[1]){
					/* Incase the host wants the version of the bootloader */
					case CBL_GET_VER_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_GET_VER_CMD(0x%x) Command is Received  \r\n",CBL_GET_VER_CMD);
					  /* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for get the bootloader version */
					  Bootloader_Get_Version(BL_Host_Buffer);
					  Status = BL_OK;
						break;
					/* Incase the host wants the help of the bootloader */
					case CBL_GET_HELP_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_GET_HELP_CMD(0x%x) Command is Received  \r\n",CBL_GET_HELP_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for get the bootloader help */
					  Bootloader_Get_Help(BL_Host_Buffer);
						Status = BL_OK;
					  break;
					/* Incase the host wants  */
					case CBL_GET_CID_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_GET_CID_CMD(0x%x) Command is Received  \r\n",CBL_GET_CID_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for get the bootloader chip indentification number  */
					  Bootloader_Get_Chip_Identification_Number(BL_Host_Buffer);
						Status = BL_OK;
					  break;
					case CBL_GET_RDP_STATUS_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_GET_RDP_STATUS_CMD(0x%x) Command is Received  \r\n",CBL_GET_RDP_STATUS_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for reading the protection level  */
					  Bootloader_Read_Protection_Level(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_GO_TO_ADDR_CMD:
				  	/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_GO_TO_ADDR_CMD(0x%x) Command is Received  \r\n",CBL_GO_TO_ADDR_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for jumping to an address   */
					  Bootloader_Jump_To_Address(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_FLASH_ERASE_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_FLASH_ERASE_CMD(0x%x) Command is Received  \r\n",CBL_FLASH_ERASE_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for erasing the flash   */
					  Bootloader_Erase_Flash(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_MEM_WRITE_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_MEM_WRITE_CMD(0x%x) Command is Received  \r\n",CBL_MEM_WRITE_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for writing to the memory   */
					  Bootloader_Memory_Write(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_EN_R_W_PROTECT_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_EN_R_W_PROTECT_CMD(0x%x) Command is Received  \r\n",CBL_EN_R_W_PROTECT_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for enabling RW Protection  */
					  Bootloader_Enable_RW_Protection(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_MEM_READ_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_MEM_READ_CMD(0x%x) Command is Received  \r\n",CBL_MEM_READ_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for reading from the memory  */
					  Bootloader_Memory_Read(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_READ_SECTOR_STATUS_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_READ_SECTOR_STATUS_CMD(0x%x) Command is Received  \r\n",CBL_READ_SECTOR_STATUS_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for reading the sector status  */
					  Bootloader_Get_Sector_Protection_Status(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_OTP_READ_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_OTP_READ_CMD(0x%x) Command is Received  \r\n",CBL_OTP_READ_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for reading the OTP  */
					  Bootloader_Read_OTP(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_DIS_R_W_PROTECT_CMD:
						/* Send to the host what the bootloader has recevied for a debug information */
						BL_Print_Message("CBL_DIS_R_W_PROTECT_CMD(0x%x) Command is Received  \r\n",CBL_DIS_R_W_PROTECT_CMD);
						/* Send to the host a debug information */
					  BL_Print_Message("Bootloader starts processing the command   \r\n");
					  /* Call the static function that responsible for Disabling the RW Protection  */
					  Bootloader_Disable_RW_Protection(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					/* Incase the command code is not supported in the bootloader */
					default:
						/* Send to the host a debug information tells him that the coomand code 
               is not supported 
   					*/
						BL_Print_Message("Invalid Command Code Received From the Host !! \r\n");
						Status = BL_NACK;
					  break;
					
					
				}
			
			}
		}

	
	return Status;
}




/* 	This Function is used by the bootloader to send a dubg information
    to the host which is PC to tell him what is going inside the bootloader 
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





/* Function Used by Bootloader to send the bootloader version to the host */
static void Bootloader_Get_Version(uint8_t *Host_Buffer)
{
}

static void Bootloader_Get_Help(uint8_t *Host_Buffer)
{
}

static void Bootloader_Get_Chip_Identification_Number(uint8_t *Host_Buffer)
{
}

static void Bootloader_Read_Protection_Level(uint8_t *Host_Buffer)
{
}

static void Bootloader_Jump_To_Address(uint8_t *Host_Buffer)
{
}

static void Bootloader_Erase_Flash(uint8_t *Host_Buffer)
{
}

static void Bootloader_Memory_Write(uint8_t *Host_Buffer)
{
}

static void Bootloader_Enable_RW_Protection(uint8_t *Host_Buffer)
{
}

static void Bootloader_Memory_Read(uint8_t *Host_Buffer)
{
}

static void Bootloader_Get_Sector_Protection_Status(uint8_t *Host_Buffer)
{
}

static void Bootloader_Read_OTP(uint8_t *Host_Buffer)
{
}

static void Bootloader_Disable_RW_Protection(uint8_t *Host_Buffer)
{
}
