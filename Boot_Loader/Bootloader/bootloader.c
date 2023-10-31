/*********************************************************************/
/*************************** Included Files **************************/
/*********************************************************************/
#include "bootloader.h"

/*********************************************************************/
/************************ Static APIs Prototypes *********************/
/*********************************************************************/
static uint8_t Flash_Memory_Write_Payload(uint8_t *Host_Payload,uint32_t Payload_Start_Address, uint32_t Payload_Len);

static uint8_t CBL_STM32F401_Get_RDP_Level();

static uint8_t Perform_Flash_Erase(uint8_t Sector_Number,uint8_t Number_Of_Sectors);

static void Bootloader_Jump_To_App_Code();

static uint8_t Host_Jump_Address_Verification(uint32_t Jump_Address);

static void Bootloader_Send_Data_To_Host(uint8_t *Host_Buffer,uint32_t Data_Len);

static void Bootloader_Send_ACK(uint8_t Replay_Len);

static void Bootloader_Send_NACK();

static uint8_t Bootloader_CRC_Verify(uint8_t *pData,uint32_t Data_Len,uint32_t Host_CRC);

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

static void Bootloader_Change_Read_Protection_Level(uint8_t *Host_Buffer);
/*********************************************************************/
/********************** Global Variables Definitions *****************/
/*********************************************************************/

/* This array used to receive the command packet from the Host */
static uint8_t BL_Host_Buffer[BL_HOST_BUFFER_RX_LENGTH];

static uint8_t Bootloader_Supported_CMDs[12]= {
	CBL_GET_VER_CMD,                           
  CBL_GET_HELP_CMD,                           
  CBL_GET_CID_CMD,                            
  CBL_GET_RDP_STATUS_CMD,                     
  CBL_GO_TO_ADDR_CMD,                         
  CBL_FLASH_ERASE_CMD,                        
  CBL_MEM_WRITE_CMD,                          
  CBL_EN_R_W_PROTECT_CMD,                     
  CBL_MEM_READ_CMD,                           
  CBL_READ_SECTOR_STATUS_CMD,                 
  CBL_OTP_READ_CMD,                            
  CBL_CHANGE_ROP_LEVEL_CMD                    
};

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

			/* Recevie Data Bytes based on the Data length received by the bootloader sent by the host */
			HAL_Status = HAL_UART_Receive(BL_HOST_COMMUNICATION_UART,&BL_Host_Buffer[1],Data_Length, HAL_MAX_DELAY);
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
			BL_Print_Message("Command Length = %d is Received \r\n",Data_Length);
  		BL_Print_Message("Command Packed is Received \r\n");
#endif 
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
					  /* Call the static function that responsible for get the bootloader version */
					  Bootloader_Get_Version(BL_Host_Buffer);				  
					  Status = BL_OK;
						break;
					/* Incase the host wants the help of the bootloader */
					case CBL_GET_HELP_CMD:
					  /* Call the static function that responsible for get the bootloader help */
					  Bootloader_Get_Help(BL_Host_Buffer);
						Status = BL_OK;
					  break;
					/* Incase the host wants  */
					case CBL_GET_CID_CMD:
					  /* Call the static function that responsible for get the bootloader chip indentification number  */
					  Bootloader_Get_Chip_Identification_Number(BL_Host_Buffer);
						Status = BL_OK;
					  break;
					/* Incase Host wants to read the protection level of  the flash memory 
					- Level 0 : 0xAA
					- Level 1 : Any value except 0xAA and 0xCC 
					- Level 2 : 0xCC
					*/
					case CBL_GET_RDP_STATUS_CMD:
					  /* Call the static function that responsible for reading the protection level  */
					  Bootloader_Read_Protection_Level(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_GO_TO_ADDR_CMD:
					  /* Call the static function that responsible for jumping to an address   */
					  Bootloader_Jump_To_Address(BL_Host_Buffer);
				 // Bootloader_Jump_To_App_Code();
					  Status = BL_OK;
					  break;
					case CBL_FLASH_ERASE_CMD:
					  /* Call the static function that responsible for erasing the flash   */
					  Bootloader_Erase_Flash(BL_Host_Buffer);
					  Status = BL_OK;
					  break;
					case CBL_MEM_WRITE_CMD:
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
					case CBL_CHANGE_ROP_LEVEL_CMD:
					  /* Call the static function that responsible for Disabling the RW Protection  */
					  Bootloader_Change_Read_Protection_Level(BL_Host_Buffer);
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


static uint8_t Bootloader_CRC_Verify(uint8_t *pData,uint32_t Data_Len,uint32_t Host_CRC)
{
	/* Local variable to store the CRC Status */
	uint8_t CRC_Status = CRC_VERIFICATION_FAILED;
	/* Local variable to store the CRC Calculated by CRC Peripheral of MCU */
	uint32_t MCU_CRC_Calculated=0;
	/* Local Variable used as a counter to loop into the length of the data */
	uint8_t Data_Counter=0;
	/* Data buffer sent by the CRC */
	uint32_t Data_Buffer = 0;
	/* Calculate the CRC Value */
	for(Data_Counter=0;Data_Counter < Data_Len;Data_Counter++){
		Data_Buffer = (uint32_t)pData[Data_Counter];
	  /* Call the function of CRC Peripheral to calculate the CRC Value */
	  MCU_CRC_Calculated = HAL_CRC_Accumulate(CRC_ENGINE_OBJ, &Data_Buffer, 1);
		
	}
	
  /* Reset the CRC Calculation Unit 
	   Reset the CRC Data Register because we use the CRC Accumulation which means 
	   that using the last value of CRC Register to calculate the next element and so on...
	*/
	__HAL_CRC_DR_RESET(CRC_ENGINE_OBJ);
	
	/* If HOST_CRC is equal to the Calculated CRC , we send CRC Passed */
	if(Host_CRC == MCU_CRC_Calculated ){
		CRC_Status = CRC_VERIFICATION_PASSED;
	}
	/* If HOST_CRC is not equal to the Calculated CRC , we send CRC failed */
	else{
		CRC_Status = CRC_VERIFICATION_FAILED;
	}
	return CRC_Status;
}


/* Function used to send ACK to the host with the replied length message */
static void Bootloader_Send_ACK(uint8_t Replay_Len){
	uint8_t Ack_Value[2]={CBL_SEND_ACK,Replay_Len};
	
	HAL_UART_Transmit(BL_HOST_COMMUNICATION_UART,(uint8_t *)Ack_Value,2,HAL_MAX_DELAY);
	
}

/* Function used to send NACK to the host */
static void Bootloader_Send_NACK(){
	uint8_t Ack_Value = CBL_SEND_NACK;
	HAL_UART_Transmit(BL_HOST_COMMUNICATION_UART,&Ack_Value,1,HAL_MAX_DELAY);
}


/* Function used to send data to the host
*/
static void Bootloader_Send_Data_To_Host(uint8_t *Host_Buffer,uint32_t Data_Len){
	HAL_UART_Transmit(BL_HOST_COMMUNICATION_UART,(uint8_t *)Host_Buffer,Data_Len,HAL_MAX_DELAY);
}






/* Function Used by Bootloader to send the bootloader version to the host */
static void Bootloader_Get_Version(uint8_t *Host_Buffer)
{
	/* Array for the : 
	  1- Bootloader Vendor ID 
	  2- Bootloader Major Version
	  3- Bootloader Minor Version
	  4- Bootloader Patch Version
	*/
	uint8_t BL_Version[4]={CBL_VENDOR_ID,\
	                       CBL_SW_MAJOR_VERSION,\
	                       CBL_SW_MINOR_VERSION,\
	                       CBL_SW_PATCH_VERSION};
	/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	/* Send to the host what the bootloader has recevied for a debug information */
	BL_Print_Message("CBL_GET_VER_CMD(0x%x) Command is Received  \r\n",CBL_GET_VER_CMD);
	/* Send to the host a debug information */
	BL_Print_Message("Bootloader starts processing the command   \r\n");									 
#endif												 
	/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_ACK(4);
		/* Send the reply packet to the user */
		Bootloader_Send_Data_To_Host((uint8_t *)BL_Version,4);
		/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
  	BL_Print_Message("Bootloader Version is sent and = %d.%d.%d    \r\n",BL_Version[1],BL_Version[2],BL_Version[3]);
#endif	
	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}
 Bootloader_Jump_To_App_Code();
}

static void Bootloader_Get_Help(uint8_t *Host_Buffer)
{
	/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	/* Send to the host what the bootloader has recevied for a debug information */
	BL_Print_Message("CBL_GET_HELP_CMD(0x%x) Command is Received  \r\n",CBL_GET_HELP_CMD);
	/* Send to the host a debug information */
	BL_Print_Message("Bootloader starts processing the command   \r\n");									 
#endif												 
	/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_ACK(12);
		/* Send the reply packet to the user */
		Bootloader_Send_Data_To_Host((uint8_t *)Bootloader_Supported_CMDs,12);
		
		
		/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Bootloader Supported Commands is sent    \r\n");
#endif	
	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}
}

/* Function responsible for get the DEVICE ID Code */
static void Bootloader_Get_Chip_Identification_Number(uint8_t *Host_Buffer)
{
	/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
	/* Variable to store MCU Identification ID Number */
	uint16_t MCU_Identification_Number = 0;
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	/* Send to the host what the bootloader has recevied for a debug information */
	BL_Print_Message("CBL_GET_CID_CMD(0x%x) Command is Received  \r\n",CBL_GET_CID_CMD);
	/* Send to the host a debug information */
	BL_Print_Message("Bootloader starts processing the command   \r\n");									 
#endif
		/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif
		/* Get Chip Identification Number */
		/* We want the first 12 bit so, we anding with mask as shown below */
		MCU_Identification_Number = (uint16_t)((DBGMCU->IDCODE) & 0x00000FFF);
		
		/*Send the ack with the length of the message to the host */
		Bootloader_Send_ACK(2);
		/* Send the reply packet to the user */
		Bootloader_Send_Data_To_Host((uint8_t *)&MCU_Identification_Number,2);		
		/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Bootloader Chip Identification Number is sent and = 0x%x   \r\n",MCU_Identification_Number);
#endif	
	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}
}











static uint8_t Host_Jump_Address_Verification(uint32_t Jump_Address){
		/* Vaiable to store the status of the address verification */
	uint8_t Address_Verification=ADDRESS_IS_INVALID;
	
	/* Check Address between range of flash OR between range of sram  */
	if( ((Jump_Address >= FLASH_BASE) && (Jump_Address <= STM32F401_FLASH_END)) || \
      ((Jump_Address >= SRAM1_BASE) && (Jump_Address <= STM32F401_SRAM1_END))		)
	    {
				/* Address is valid */
			Address_Verification = ADDRESS_IS_VALID;
			
			}
	else{
		    /* Address is invalid */
		  Address_Verification=ADDRESS_IS_INVALID;
			}
	
	return Address_Verification;

}








static void Bootloader_Jump_To_Address(uint8_t *Host_Buffer)
{
		/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
	/* Variable to store the jumping address from the host packet */
	uint32_t HOST_Jump_Address=0;
	/* Vaiable to store the status of the address verification */
	uint8_t Address_Verification=ADDRESS_IS_INVALID;
	/* Variable to store the pointer to the jumping address */
	Jump_Ptr Jump_Address = (void *)0; 
	
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	/* Send to the host what the bootloader has recevied for a debug information */
	BL_Print_Message("CBL_GO_TO_ADDR_CMD(0x%x) Command is Received  \r\n",CBL_GO_TO_ADDR_CMD);
	/* Send to the host a debug information */
	BL_Print_Message("Bootloader starts processing the command   \r\n");								 
#endif
		/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif
		/*Send the ack with the length of the message to the host */
		Bootloader_Send_ACK(1);
		/* Extract the jumping address  */
		HOST_Jump_Address = *((uint32_t *)&Host_Buffer[2]);
		/* Address Verification (Must ensure that address between the range of MCU Memory) */
		Address_Verification = Host_Jump_Address_Verification(HOST_Jump_Address);
		/* Send the reply packet to the user */
		Bootloader_Send_Data_To_Host((uint8_t *)&Address_Verification,1);	
		/* Check the address verification */
		if(Address_Verification == ADDRESS_IS_VALID){
					/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Address is valid. Jumping to Address = 0x%x   \r\n",HOST_Jump_Address);
#endif
			
			/* Store the jump address into pointer to fuction 
			1 : because of the T-Bit 
			*/
			Jump_Address = (Jump_Ptr)(HOST_Jump_Address+1);
			/* Branch to the Address  */
			Jump_Address();
		}
		else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Address is 0x%x is not valid   \r\n",HOST_Jump_Address);
#endif
		}
	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}
}


static void Bootloader_Jump_To_App_Code(){
	
	/* Local Variable to store the main stack pointer MSP of the 
	   App code   
	*/
	uint32_t MSP_Value = *((volatile uint32_t *)FLASH_SECTOR1_BASE_ADDRESS);
	/* Local Variable to store the address of the reset handler of
     the App code 
	*/
	uint32_t MainAppAddr = *((volatile uint32_t *)(FLASH_SECTOR1_BASE_ADDRESS+4));
	/* Local variable of type pointer to function and 
	   store the address of the reset handler of the code
	   inside that variable
	*/
	pMainApp App_ResetHandlerAddress = (pMainApp)MainAppAddr;
	
	/* Before call the reset handler, we need to initialize the MSP so, we
	   will call the CMSIS Function to set the MSP value
	*/
	__set_MSP(MSP_Value);
	
	/* Deinitializtion of the Modules used by the bootloader */
	
	/* Resets the RCC clock configuration to the default reset state */
	HAL_RCC_DeInit();
	
	/* Call the reset handler of the application code */
	App_ResetHandlerAddress();
}





static uint8_t CBL_STM32F401_Get_RDP_Level(){
	
	FLASH_OBProgramInitTypeDef FLASH_OBProgram;
	
	
	
	HAL_FLASHEx_OBGetConfig(&FLASH_OBProgram);
	
	
	
	
	return (uint8_t)(FLASH_OBProgram.RDPLevel);
}




static void Bootloader_Read_Protection_Level(uint8_t *Host_Buffer)
{
	/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
	/* Variable to store RDP Level Value */
	uint8_t RDP_Level = 0;
	
	uint8_t RDP_Level_Error_Status = ROP_LEVEL_READ_INVALID;
	
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		/* Send to the host what the bootloader has recevied for a debug information */
		BL_Print_Message("CBL_GET_RDP_STATUS_CMD(0x%x) Command is Received  \r\n",CBL_GET_RDP_STATUS_CMD);
		/* Send to the host a debug information */
		BL_Print_Message("Bootloader starts processing the command (Read Flash Protection Level)  \r\n");							 
#endif
		/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif
		/*Send the ack with the length of the message to the host */
		Bootloader_Send_ACK(1);
		
		/* Read RDP Level */
		RDP_Level = CBL_STM32F401_Get_RDP_Level();
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("Sending Protection Level .......... \r\n");
#endif
		Bootloader_Send_Data_To_Host((uint8_t *)&RDP_Level,1);

		}

	
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}
}



/* Function responsible for performing erasing flash and return :
   - SUCCESSFUL_ERASE                 
           OR
   - UNSUCCESSFUL_ERASE
*/
static uint8_t Perform_Flash_Erase(uint8_t Sector_Number,uint8_t Number_Of_Sectors){
	uint8_t Sector_Validity_Status = INVALID_SECTOR_NUMBER;
	
	/* Configuration of the Flash erase */
	FLASH_EraseInitTypeDef pEraseInit;
	
	/* Remaining Sectors */
	uint8_t Remaining_Sectors = 0;
	
	/* Variable to receive the value from the flash erase function */
	HAL_StatusTypeDef  HAL_Status = HAL_ERROR;
	
	uint32_t SectorError=0;
	
	/* Incase Number of sectors greater than MCU Provided Sector then, Can't perform Erase */
	if(Number_Of_Sectors > CBL_FLASH_MAX_SECTOR_NUMBER){
		Sector_Validity_Status = INVALID_SECTOR_NUMBER;
	}
	else{
		if( (Sector_Number <= (CBL_FLASH_MAX_SECTOR_NUMBER - 1)) || (CBL_FLASH_MASS_ERASE==Sector_Number) ){
			/* Incase of Mass Erase */
			if( CBL_FLASH_MASS_ERASE==Sector_Number ){
				/* Configure the Flash Erasing Type*/
				pEraseInit.TypeErase =FLASH_TYPEERASE_MASSERASE;  /* Flash Mass Erase Activation */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("Mass Easing ..................... \r\n");
#endif	
			}
			/* Sectors Erase Only */
			else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("Sectors Easing ..................... \r\n");
#endif					
				Remaining_Sectors = CBL_FLASH_MAX_SECTOR_NUMBER - Sector_Number;
				/* Incase user enters sector number + number of sectors greater thean MCU Maximum Sectors */
				if(Number_Of_Sectors > Remaining_Sectors){
					Number_Of_Sectors = Remaining_Sectors;
				}
				else{
				/* Do No Thing */
				}
				
			  /* Configure the Flash Erasing Type */
				pEraseInit.TypeErase =FLASH_TYPEERASE_SECTORS;	  /* Flash Sector Erase Activation */
				pEraseInit.Sector = Sector_Number;                /* Initial Flash sector to erase when mass erase is disabled */   
				pEraseInit.NbSectors = Number_Of_Sectors;         /* Number of sectors to be erased  */
			}
		/* STM32F401CC has only one bank */
		pEraseInit.Banks = FLASH_BANK_1 ;
		pEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3 ;     /*!< Device operating range: 2.7V to 3.6V                */
		
	  /* Unlock Flash Control Register */
		HAL_Status = HAL_FLASH_Unlock();
		/* Call the  erase Function */
		HAL_Status = HAL_FLASHEx_Erase(&pEraseInit, &SectorError );
		/* Check the status of the HAL_Status */
		if(HAL_SUCCESSFUL_ERASE == SectorError){
			Sector_Validity_Status = SUCCESSFUL_ERASE;
		}
		else{
			Sector_Validity_Status = UNSUCCESSFUL_ERASE;
		}
		/* Lock Flash Control Register */
		HAL_Status = HAL_FLASH_Lock();
		
		}
		else{
			Sector_Validity_Status = UNSUCCESSFUL_ERASE;
		}
		
	}
	
	return Sector_Validity_Status;
}



static void Bootloader_Erase_Flash(uint8_t *Host_Buffer)
{
	/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
	
	/* Variable to stroe the erase status */
	uint8_t Erase_Status = 0;
	
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	/* Send to the host what the bootloader has recevied for a debug information */
	BL_Print_Message("CBL_FLASH_ERASE_CMD(0x%x) Command is Received  \r\n",CBL_FLASH_ERASE_CMD);
	/* Send to the host a debug information */
	BL_Print_Message("Bootloader starts processing the command   \r\n");								 
#endif												 
	/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif
		/*Send the ack with the length of the message to the host */
		Bootloader_Send_ACK(1);
		
		/* Perform Flash Erase  */
		Erase_Status = Perform_Flash_Erase(Host_Buffer[2],Host_Buffer[3]);
    /* Incase Erase Flash is not done and Passed  */
		if(SUCCESSFUL_ERASE == Erase_Status){
			Bootloader_Send_Data_To_Host((uint8_t *)&Erase_Status,1);
	  /* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("FLASH Erase is Passed \r\n");
#endif	
		}
		/* Incase Erase Flash is done and Failed */
    else{
			Bootloader_Send_Data_To_Host((uint8_t *)&Erase_Status,1);
		/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("FLASH Erase is Failed \r\n ");
#endif	
		}		

		

	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}	
	
}

static uint8_t Flash_Memory_Write_Payload(uint8_t *Host_Payload,uint32_t Payload_Start_Address, uint32_t Payload_Len){
	/* Local Variable to store the status */
	HAL_StatusTypeDef HAL_Status = HAL_ERROR;
	
	/* Local Variable to store the status of the flash write 
	   - FLASH_PAYLOAD_WRITE_FAILED
	   - FLASH_PAYLOAD_WRITE_PASSED
	*/
	uint8_t Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_FAILED;
	
	/* Local Variable to loop for the payload length */
	uint16_t Payload_Counter = 0;
	
	/* Unlock Flash Control Register */
	HAL_Status = HAL_FLASH_Unlock();
	
	/* Check the status */
	if(HAL_Status != HAL_OK){
		/* Failed in unlocking the flash control register  */
		Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_FAILED;
	}
	/* Successed in unlocking the flash control register  */
	else{ /* start of else  */
		/* Loop to the payload length */
		for(Payload_Counter = 0;Payload_Counter<Payload_Len;Payload_Counter++){ /* Start for loop */
			/* Call the flash to program the memory */
			/* HAL_FLASH_Program Function will : 
		          1- Program byte by byte 
		          2- Program from a specified memory address and will be incremented each iteration 
		          3- Program till payload length is reached out 
			*/
			HAL_Status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,\
																		 Payload_Start_Address+Payload_Counter,\
																		 Host_Payload[Payload_Counter]);
			/* Incase program the memory didn't done */
			if(HAL_Status != HAL_OK){ /* Start if condition */
				/* Flash status is faild to program the memory */
				Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_FAILED;
				break;
				}/* End if condition */
			else{/* Start of else */
				Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_PASSED;
			}/* End of else */
		
		} /* End for loop */
	
	}/* End of else */
	

	/* Check the HAL_Status and payload status */
	if((FLASH_PAYLOAD_WRITE_PASSED == Flash_Payload_Write_Status)  && (HAL_OK == HAL_Status)){/* Start if condition */
			/* Lock Flash Control Register */
			HAL_Status = HAL_FLASH_Lock();
			/* Check the HAL_Status */
		  if(HAL_Status != HAL_OK){/* Start if condition */
				Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_FAILED;
			}/*End if condition */
			else{ /* Start else */
				Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_PASSED;
			}/* End else */
			
	}/* End if condition */
	else{ /* Start of else */
			Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_FAILED;
	}/* End of else */
	
	

	
	return Flash_Payload_Write_Status;
}


static void Bootloader_Memory_Write(uint8_t *Host_Buffer)
{
	/* Variable represnt the command packet length */
	uint16_t Host_CMD_Packet_Len =0;
	/* Variable represnt the Host CRC */
  uint32_t Host_CRC32 =0;
	/* Variable to store the start address to be write to */
	uint32_t HOST_Address = 0;
	/* Variable to store the Payload length */
	uint8_t Payload_Len = 0;
	/* Variable to store address verification status */
	uint8_t Address_Verification = ADDRESS_IS_INVALID;
	/* Local Variable to store the status of the flash write 
	   - FLASH_PAYLOAD_WRITE_FAILED
	   - FLASH_PAYLOAD_WRITE_PASSED
	*/
	uint8_t Flash_Payload_Write_Status = FLASH_PAYLOAD_WRITE_FAILED;
	
	
  /* Extract the CRC32 and Packet Length sent by the Host */
	Host_CMD_Packet_Len = Host_Buffer[0]+1;										 
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
  /* Send to the host what the bootloader has recevied for a debug information */
	BL_Print_Message("CBL_MEM_WRITE_CMD(0x%x) Command is Received  \r\n",CBL_MEM_WRITE_CMD);
	/* Send to the host a debug information */
	BL_Print_Message("Bootloader starts processing the command   \r\n");								 
#endif		
		/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0],Host_CMD_Packet_Len - CRC_TYPE_SIZE_BYTE,Host_CRC32)){
/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and equal to the CRC sent by the Host \r\n");
#endif

		/*Send the ack with the length of the message to the host */
		Bootloader_Send_ACK(1);
		
		/* Extract start address to be write to */
	  HOST_Address = *((uint32_t *)(&Host_Buffer[2]));
	  /* Extract Payload length */
	  Payload_Len = Host_Buffer[6];
		
		/* Check the address valid or not valid by the MCU(STM32F401CCU6) */
		Address_Verification = Host_Jump_Address_Verification(HOST_Address);
		/* Check the status of the address verification */
		/* if address is valid by MCU (STM32F401CCU6)*/
		if(ADDRESS_IS_VALID == Address_Verification){
			Flash_Payload_Write_Status = Flash_Memory_Write_Payload((uint8_t *)&Host_Buffer[7],HOST_Address,Payload_Len);
			/* Check the Flash_Payload_Write_Status */
			if(FLASH_PAYLOAD_WRITE_PASSED == Flash_Payload_Write_Status){/* Start if condition */
				/* Send the reply packet to the user */
				/* Payload write passed */
				Bootloader_Send_Data_To_Host((uint8_t *)&Flash_Payload_Write_Status,1);	
			/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Payload write passed \r\n");
#endif				
				
			}/* End if condition */
			else{ /* Start else */	
				/* Send the reply packet to the user */
				/* Payload write Failed */
				Bootloader_Send_Data_To_Host((uint8_t *)&Flash_Payload_Write_Status,1);
				/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Payload write Failed \r\n");
#endif	
			}/* End else */
		}
		else{
			/* Send the reply packet to the user */
			/* Address is not valid by MCU (STM32F401CCU6)*/
			Bootloader_Send_Data_To_Host((uint8_t *)&Address_Verification,1);		
			/* Debug Information */
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
 		BL_Print_Message("Address_Verification is not valid by MCU (STM32F401CCU6)\r\n");
#endif	
		}
		

	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC calculation is done and not equal to the CRC sent by the Host \r\n");
#endif
		Bootloader_Send_NACK();
	}
//	Bootloader_Jump_To_App_Code();
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




static uint8_t Change_ROP_Level(uint32_t ROP_Level){
	HAL_StatusTypeDef HAL_Status = HAL_ERROR;
	FLASH_OBProgramInitTypeDef FLASH_OBProgramInit;
	uint8_t ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
	
	/* Unlock the FLASH Option Control Registers access */
	HAL_Status = HAL_FLASH_OB_Unlock();
	if(HAL_Status != HAL_OK){
		ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	BL_Print_Message("Failed -> Unlock the FLASH Option Control Registers access \r\n");
#endif
	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("Passed -> Unlock the FLASH Option Control Registers access \r\n");
#endif
		FLASH_OBProgramInit.OptionType = OPTIONBYTE_RDP; /* RDP option byte configuration */
		FLASH_OBProgramInit.Banks = FLASH_BANK_1;
		FLASH_OBProgramInit.RDPLevel = ROP_Level;
		/* Program option bytes */
		HAL_Status = HAL_FLASHEx_OBProgram(&FLASH_OBProgramInit);
		if(HAL_Status != HAL_OK){
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
			BL_Print_Message("Failed -> Program option bytes \r\n");
#endif
			HAL_Status = HAL_FLASH_OB_Lock();
			ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
		}
		else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
			BL_Print_Message("Passed -> Program option bytes \r\n");
#endif
			/* Launch the option byte loading */
			HAL_Status = HAL_FLASH_OB_Launch();
			if(HAL_Status != HAL_OK){
				ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
			}
			else{
				/* Lock the FLASH Option Control Registers access */
				HAL_Status = HAL_FLASH_OB_Lock();
				if(HAL_Status != HAL_OK){
					ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
				}
				else{
					ROP_Level_Status = ROP_LEVEL_CHANGE_VALID;
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
					BL_Print_Message("Passed -> Program ROP to Level : 0x%X \r\n", ROP_Level);
#endif
				}
			}
		}
	}
	return ROP_Level_Status;
}


static void Bootloader_Change_Read_Protection_Level(uint8_t *Host_Buffer)
{
	uint16_t Host_CMD_Packet_Len = 0;
  uint32_t Host_CRC32 = 0;
	uint8_t ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
	uint8_t Host_ROP_Level = 0;
	
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
	BL_Print_Message("Change read protection level of the user flash \r\n");
#endif
	/* Extract the CRC32 and packet length sent by the HOST */
	Host_CMD_Packet_Len = Host_Buffer[0] + 1;
	Host_CRC32 = *((uint32_t *)((Host_Buffer + Host_CMD_Packet_Len) - CRC_TYPE_SIZE_BYTE));	
/* CRC Verification */
	if(CRC_VERIFICATION_PASSED == Bootloader_CRC_Verify((uint8_t *)&Host_Buffer[0] , Host_CMD_Packet_Len - 4, Host_CRC32)){
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC Verification Passed \r\n");
#endif
		Bootloader_Send_ACK(1);
		/* Request change the Read Out Protection Level */
		Host_ROP_Level = Host_Buffer[2];
		/* Warning: When enabling read protection level 2, it s no more possible to go back to level 1 or 0 */
		if((CBL_ROP_LEVEL_2 == Host_ROP_Level) || (OB_RDP_LEVEL_2 == Host_ROP_Level)){
			ROP_Level_Status = ROP_LEVEL_CHANGE_INVALID;
		}
		else{
			if(CBL_ROP_LEVEL_0 == Host_ROP_Level){ 
				Host_ROP_Level = 0xAA; 
			}
			else if(CBL_ROP_LEVEL_1 == Host_ROP_Level){ 
				Host_ROP_Level = 0x55; 
			}
			ROP_Level_Status = Change_ROP_Level(Host_ROP_Level);
		}
		Bootloader_Send_Data_To_Host((uint8_t *)&ROP_Level_Status, 1);
	}
	else{
#if (BL_DEBUG_ENABLE == DEBUG_INFO_ENABLE)
		BL_Print_Message("CRC Verification Failed \r\n");
#endif
		Bootloader_Send_NACK();
	}
}
