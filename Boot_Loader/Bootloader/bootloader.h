#ifndef BOOTLOADER_H
#define BOOTLOADER_H

/*********************************************************************/
/*************************** Included Files **************************/
/*********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "usart.h"

#include "crc.h"

/*********************************************************************/
/*************************** Macors Declaration **********************/
/*********************************************************************/

/* UART used for the debug information      */
#define    BL_DEBUG_UART                      &huart2
/* UART usedd for get command from the user */
#define    BL_HOST_COMMUNICATION_UART         &huart1

#define    DEBUG_INFO_DISABLE                   0
#define    DEBUG_INFO_ENABLE                    1
#define    BL_DEBUG_ENABLE                    DEBUG_INFO_DISABLE


/* CRC engine used */
#define    CRC_ENGINE_OBJ                     &hcrc

/* Macros for the communication protocols that can be used in the debug */
#define    BL_ENABLE_UART_DEBUG_MESSAGE       0x00
#define    BL_ENABLE_CAN_DEBUG_MESSAGE        0x01
#define    BL_ENABLE_SPI_DEBUG_MESSAGE        0x02
#define    BL_ENABLE_I2C_DEBUG_MESSAGE        0x03
/* The used communication Protocol in the debug */
#define    BL_DEBUG_METHOD                    BL_ENABLE_UART_DEBUG_MESSAGE

#define    BL_HOST_BUFFER_RX_LENGTH               200

/* CBL => Custom bootloader */
#define    CBL_GET_VER_CMD                            0x10
#define    CBL_GET_HELP_CMD                           0x11
#define    CBL_GET_CID_CMD                            0x12
#define    CBL_GET_RDP_STATUS_CMD                     0x13
#define    CBL_GO_TO_ADDR_CMD                         0x14
#define    CBL_FLASH_ERASE_CMD                        0x15
#define    CBL_MEM_WRITE_CMD                          0x16
#define    CBL_EN_R_W_PROTECT_CMD                     0x17
#define    CBL_MEM_READ_CMD                           0x18
#define    CBL_READ_SECTOR_STATUS_CMD                 0x19
#define    CBL_OTP_READ_CMD                           0x20 
#define    CBL_CHANGE_ROP_LEVEL_CMD                   0x21

/* #s for bootloader Versions */
#define  CBL_VENDOR_ID                  100
#define  CBL_SW_MAJOR_VERSION            1
#define  CBL_SW_MINOR_VERSION            1
#define  CBL_SW_PATCH_VERSION            0

#define  CRC_TYPE_SIZE_BYTE              4

#define  CRC_VERIFICATION_FAILED         0x00
#define  CRC_VERIFICATION_PASSED         0x01

#define  CBL_SEND_NACK                   0xAB
#define  CBL_SEND_ACK                    0xCD

#define  ADDRESS_IS_INVALID              0x00
#define  ADDRESS_IS_VALID                0x01


#define  STM32F401_FLASH_SIZE             (256*1024)
#define  STM32F401_SRAM1_SIZE             (64*1024)

#define  STM32F401_FLASH_END              (FLASH_BASE + STM32F401_FLASH_SIZE)

#define  STM32F401_SRAM1_END              (SRAM1_BASE  + STM32F401_SRAM1_SIZE)


#define  INVALID_SECTOR_NUMBER             0x00
#define  VALID_SECTOR_NUMBER               0x01

#define  UNSUCCESSFUL_ERASE                0x02
#define  SUCCESSFUL_ERASE                  0x03

/* Max Number Of Sectors in MCU = STM32F401CCU6 */
#define  CBL_FLASH_MAX_SECTOR_NUMBER       6
#define  CBL_FLASH_MASS_ERASE              0xFF

#define  HAL_SUCCESSFUL_ERASE              0xFFFFFFFFU


#define  FLASH_PAYLOAD_WRITE_FAILED        0x00
#define  FLASH_PAYLOAD_WRITE_PASSED        0x01

#define  FLASH_LOCK_WRITE_FAILED           0x00
#define  FLASH_LOCK_WRITE_PASSED           0x01


/* # define for flash sector 1 */
#define FLASH_SECTOR1_BASE_ADDRESS       0x08004000U

#define FLASH_SECTOR2_BASE_ADDRESS       0x08008000U
#define FLASH_SECTOR2_BASE_ADDRESS_4     0x08008004U


#define    ROP_LEVEL_READ_INVALID         0x00 
#define    ROP_LEVEL_READ_VALID           0x01

#define    ROP_LEVEL_CHANGE_INVALID       0x00 
#define    ROP_LEVEL_CHANGE_VALID         0x01


#define    CBL_ROP_LEVEL_0                0
#define    CBL_ROP_LEVEL_1                1
#define    CBL_ROP_LEVEL_2                2

/*********************************************************************/
/*********************** Data Types Declaration **********************/
/*********************************************************************/

typedef enum{
	BL_NACK=0,
	BL_OK
}BL_Status;

/* Typedef to branch to the app code */
typedef void (*pMainApp) (void);

typedef void (*Jump_Ptr) (void);
/*********************************************************************/
/*************************** APIs Proto-Types ************************/
/*********************************************************************/

/* 	This Function is used by the bootloader to send a dubg information
    to the host which is PC to tell him what is going inside the bootloader 
*/
void BL_Print_Message(char *format, ...);

/* This Function used to fetch the command packet sent by the host 
As Example: 
   1- command packet to send the version of the bootloader 
   2- command packet to erase the memory segment of specified sector                
*/
BL_Status BL_UART_Fetch_Host_Command(void);



#endif
