/*******************************************************************************************/
/*  Module       :   GPIO                                                                  */
/*  File Name    :   MGPIO_Program.c                                                       */
/*  Description  :   Source File of the GPIO Driver                                        */
/*  Author       :   Ahmed Ibrahim                                                         */
/*  Date         :   10/09/2023                                                            */
/*******************************************************************************************/

/*******************************************************************************************/
/*********************************** GPIO introduction *************************************/
/*******************************************************************************************/
/* Each general-purpose I/O port has four 32-bit configuration registers:            */
/*  1-  GPIOx_MODER                                                                  */
/*  2-  GPIOx_OTYPER                                                                 */
/*  3-  GPIOx_OSPEEDR                                                                */
/*  4-  GPIOx_PUPDR, two 32-bit data registers:                                      */
/*  5-  GPIOx_IDR                                                                    */
/*  6-  GPIOx_ODR, a 32-bit set/reset register:                                      */
/*  7-  GPIOx_BSRR, a 32-bit locking  register:                                      */
/*  8-  GPIOx_LCKR, and two 32-bit alternate function selection register:            */
/*  9-  GPIOx_AFRH                                                                   */
/*  10- GPIOx_AFRL                                                                       */


/***********************************************************************************************/
/********************************** GPIO main features *****************************************/
/***********************************************************************************************/
/* • Up to 16 I/Os under control                                                                */
/* • Output states: push-pull or open drain + pull-up/down                                      */
/* • Output data from output data register (GPIOx_ODR) or peripheral (alternate function        */
/*   output)                                                                                    */
/* • Speed selection for each I/O                                                               */
/* • Input states: floating, pull-up/down, analog                                               */
/* • Input data to input data register (GPIOx_IDR) or peripheral (alternate function input)     */
/* • Bit set and reset register (GPIOx_BSRR) for bitwise write access to GPIOx_ODR              */
/* • Locking mechanism (GPIOx_LCKR) provided to freeze the I/O configuration                    */
/* • Analog function                                                                            */
/* • Alternate function input/output selection registers (at most 16 AFs per I/O)               */
/* • Fast toggle capable of changing every two clock cycles                                     */
/* • Highly flexible pin multiplexing allows the use of I/O pins as GPIOs or as one of several  */
/*   peripheral functions                                                                       */


/*******************************************************************************************/
/********************************** GPIO functional description ****************************/
/*******************************************************************************************/
/* Subject to the specific hardware characteristics of each I/O port listed in the datasheet, each  */
/* port bit of the general-purpose I/O (GPIO) ports can be individually configured by software in   */
/* several modes:                                                                                   */
/*  • Input floating                                                                                */
/*  • Input pull-up                                                                                 */
/*  • Input-pull-down                                                                               */
/*  • Analog                                                                                        */
/*  • Output open-drain with pull-up or pull-down capability                                        */
/*  • Output push-pull with pull-up or pull-down capability                                         */
/*  • Alternate function push-pull with pull-up or pull-down capability                             */
/*  • Alternate function open-drain with pull-up or pull-down capability                            */
/* Each I/O port bit is freely programmable, however the I/O port registers have to be              */
/* accessed as 32-bit words, half-words or bytes. The purpose of the GPIOx_BSRR register is         */
/* to allow atomic read/modify accesses to any of the GPIO registers. In this way, there is no      */
/* risk of an IRQ occurring between the read and the modify access.                              */






/*******************************************************************************************/
/*********************************** Included  Files ***************************************/
/*******************************************************************************************/
/* Standard Types File */
#include "STD_Types.h"
/* Bit Math File */
#include "BIT_MATH.h"

/* RCC Specified Header Files */
#include "MGPIO_Interface.h"
#include "MGPIO_Config.h"
#include "MGPIO_Private.h"

/********************************************************************************************/
/************************************** APIs Definition *************************************/
/********************************************************************************************/

/* This Function is responsible :
 *  Setting the mode of the pin
 *  These bits are written by software to configure the I/O direction mode.
      00: Input (reset state)
      01: General purpose output mode
      10: Alternate function mode
      11: Analog mode                                                                      */
void MGPIO_SetMode(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,u8 Copy_u8PinMode)
{
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
	/* Check for the debug pins because we can't change the logic of those bits */
	if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
	{
		/* Do No thing */
	}
	else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
	{
		/* Do No thing */
	}
	else
	{
		/* Switch Case for the port index to decide which port will be accessed */
		switch(Copy_u8PortIndex)
		{
		/* case of PORTA */
		case PORTA:
			/* Reference Manual Page 158                */
			/* Here we want to access the MODE register */
			/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
			GPIOA->MODER = ( GPIOA->MODER &~(GPIO_MODE_MASK<<(Copy_u8PinIndex*2)) ) | (Copy_u8PinMode << (Copy_u8PinIndex*2));
			break;
			/* case of PORTB */
		case PORTB:
			/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
			GPIOB->MODER = ( GPIOB->MODER &~(GPIO_MODE_MASK<<(Copy_u8PinIndex*2)) ) | (Copy_u8PinMode << (Copy_u8PinIndex*2));
			break;
			/* case of PORTC */
		case PORTC:
			/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
			GPIOC->MODER = ( GPIOC->MODER &~(GPIO_MODE_MASK<<(Copy_u8PinIndex*2)) ) | (Copy_u8PinMode << (Copy_u8PinIndex*2));
			break;
		default:
			break;
		}
	}
}


/* This Function is responsible :                                                               */
/*  Set Output Pin Mode:                                                                        */
/*      - PUSH PULL or OPEN DRAIN                                                               */
/*      - Speed Type                                                                            */
/* For the output pin type (OTYPER Register):                                                   */
/*  These bits are written by software to configure the output type of the I/O port.            */
/*    0: Output push-pull (reset state)                                                         */
/*    1: Output open-drain                                                                      */
/* For the output speed type (OSPEEDR Register):                                                */
/*  These bits are written by software to configure the I/O output speed.                       */
/*    00: Low speed                                                                             */
/*    01: Medium speed                                                                          */
/*    10: High speed                                                                            */
/*    11: Very high speed                                                                       */
void MGPIO_SetOutputPinMode(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,u8 Copy_u8OutputType,u8 Copy_u8Speed)
{
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
	/* Check for the debug pins because we can't change the logic of those bits */
	if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
	{
		/* Do No thing */
	}
	else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
	{
		/* Do No thing */
	}
	else
	{
		/* Switch Case for the port index to decide which port will be accessed */
		switch(Copy_u8PortIndex)
		{
		/* Reference Manual Page 158,159                    */
		/* Here we want to access the :                     */
		/*                      - Output Type               */
		/*                      - Output Speed Type         */
		case PORTA:
			GPIOA->OTYPER = ( GPIOA->OTYPER &~(GPIO_OUTPUT_TYPE_MASK<<(Copy_u8PinIndex)) ) \
			              | (Copy_u8OutputType << (Copy_u8PinIndex));
			/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
			GPIOA->OSPEEDR = ( GPIOA->OSPEEDR &~(GPIO_OUTPUT_SPEED_TYPE_MASK<<(Copy_u8PinIndex*2)) ) \
					       | (Copy_u8Speed << (Copy_u8PinIndex*2));
			break;
		case PORTB:
			GPIOB->OTYPER = ( GPIOB->OTYPER &~(GPIO_OUTPUT_TYPE_MASK<<(Copy_u8PinIndex)) ) \
			              | (Copy_u8OutputType << (Copy_u8PinIndex));
			/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
			GPIOB->OSPEEDR = ( GPIOB->OSPEEDR &~(GPIO_OUTPUT_SPEED_TYPE_MASK<<(Copy_u8PinIndex*2)) ) \
					       | (Copy_u8Speed << (Copy_u8PinIndex*2));
			break;
		case PORTC:
			GPIOC->OTYPER = ( GPIOC->OTYPER &~(GPIO_OUTPUT_TYPE_MASK<<(Copy_u8PinIndex)) ) \
			              | (Copy_u8OutputType << (Copy_u8PinIndex));
			/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
			GPIOC->OSPEEDR = ( GPIOC->OSPEEDR &~(GPIO_OUTPUT_SPEED_TYPE_MASK<<(Copy_u8PinIndex*2)) ) \
					       | (Copy_u8Speed << (Copy_u8PinIndex*2));
			break;
		default:
			break;
		}
	}
}



/* This Function is responsible :                                                               */
/*  Set Input Pin Mode:                                                                         */
/*      -  PULL UP                                                                              */
/*      -  PULL DOWN                                                                            */
/*      -  NO PULL UP , NO PULL DOWN                                                            */
/* For the output pin type (PUPDR Register):                                                    */
/* These bits are written by software to configure the I/O pull-up or pull-down                 */
/*   00: No pull-up, pull-down                                                                  */
/*   01: Pull-up                                                                                */
/*   10: Pull-down                                                                              */
/*   11: Reserved                                                                               */

void MGPIO_SetInputPinMode(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,u8 Copy_u8InputType)
{
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
		/* Check for the debug pins because we can't change the logic of those bits */
		if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
		{
			/* Do No thing */
		}
		else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
		{
			/* Do No thing */
		}
		else
		{
			/* Switch Case for the port index to decide which port will be accessed */
			switch(Copy_u8PortIndex)
			{
			/* case of PORTA */
			case PORTA:
				/* Reference Manual Page 159,160                        */
				/* Here we want to access the PULL UP DOWN Register     */
				/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
				GPIOA->PUPDR = ( GPIOA->PUPDR &~(GPIO_PULL_UP_DOWN__MASK<<(Copy_u8PinIndex*2)) ) \
				             | (Copy_u8InputType << (Copy_u8PinIndex*2));
				break;
			case PORTB:
				/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
				GPIOB->PUPDR = ( GPIOB->PUPDR &~(GPIO_PULL_UP_DOWN__MASK<<(Copy_u8PinIndex*2)) ) \
				             | (Copy_u8InputType << (Copy_u8PinIndex*2));
				break;
			case PORTC:
				/* Each pin has 2-bit to be programmed that's why we multiply by 2 */
				GPIOC->PUPDR = ( GPIOC->PUPDR &~(GPIO_PULL_UP_DOWN__MASK<<(Copy_u8PinIndex*2)) ) \
				             | (Copy_u8InputType << (Copy_u8PinIndex*2));
				break;
			default:
				break;
			}
		}
}


/* This Function is responsible :                                                               */
/*                     Get the pin value                                                        */
void MGPIO_GetPinValue(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,u8 *Copy_pu8Data)
{
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
			/* Check for the debug pins because we can't change the logic of those bits */
			if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
			{
				/* Do No thing */
			}
			else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
			{
				/* Do No thing */
			}
			else
			{
				/* Switch Case for the port index to decide which port will be accessed */
				switch(Copy_u8PortIndex)
				{
				/* case of PORTA */
				case PORTA:
					/* Reference Manual Page     160                        */
					/* *Copy_pu8Data = GET_BIT(GPIOA->IDR,Copy_u8PinIndex   */
					*Copy_pu8Data = GET_BIT(GPIOA->IDR,Copy_u8PinIndex);
					break;
				case PORTB:
					*Copy_pu8Data = GET_BIT(GPIOB->IDR,Copy_u8PinIndex);
					break;
				case PORTC:
					*Copy_pu8Data = GET_BIT(GPIOC->IDR,Copy_u8PinIndex);
					break;
				default:
					break;
				}
			}
}




/* This Function is responsible :                                                               */
/*                     Set the pin value (LEVEL_LOW,LEVEL_HIGH)                                 */
void MGPIO_SetPinValue(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,u8 Copy_u8Value)
{
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
	/* Check for the debug pins because we can't change the logic of those bits */
	if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
	{
		/* Do No thing */
	}
	else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
	{
		/* Do No thing */
	}
	else
	{
		/* Switch Case for the port index to decide which port will be accessed */
		switch(Copy_u8PortIndex)
		{
		/* Reference Manual Page 158,159                    */

		case PORTA:
			GPIOA->ODR = ( GPIOA->ODR &~(GPIO_OUTPUT_DATA_MASK<<(Copy_u8PinIndex)) ) | (Copy_u8Value << (Copy_u8PinIndex));
			break;
		case PORTB:
			GPIOB->ODR = ( GPIOB->ODR &~(GPIO_OUTPUT_DATA_MASK<<(Copy_u8PinIndex)) ) | (Copy_u8Value << (Copy_u8PinIndex));
			break;
		case PORTC:
			GPIOC->ODR = ( GPIOC->ODR &~(GPIO_OUTPUT_DATA_MASK<<(Copy_u8PinIndex)) ) | (Copy_u8Value << (Copy_u8PinIndex));
			break;
		default:
			break;
		}
}
}







/* This Function is responsible :                                                               */
/*                     Set the Port value                                                       */
void MGPIO_SetPortValue(u8 Copy_u8PortIndex,u32 Copy_u32Value)
{
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
	/* Check for the debug pins because we can't change the logic of those bits */

	/* Switch Case for the port index to decide which port will be accessed */
	switch(Copy_u8PortIndex)
	{
	/* Reference Manual Page 158,159                    */

	case PORTA:
		GPIOA->ODR = (GPIOA->ODR & 0x0000E000) | (Copy_u32Value & 0xFFFF1FFF);
		break;
	case PORTB:
		GPIOB->ODR = (GPIOB->ODR & 0x0000000C) | (Copy_u32Value & 0xFFFFFFF3);
		break;
	case PORTC:
		GPIOC->ODR = Copy_u32Value;
		break;
	default:
		break;
	}

}






















/* This Function is used with atomic instruction feature to set the pin value */
void MGPIO_SetResetValue(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,u8 Copy_u8SetOrReset)
{
	    /* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
		/* Check for the debug pins because we can't change the logic of those bits */
		if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
		{
			/* Do No thing */
		}
		else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
		{
			/* Do No thing */
		}
		else
		{
			/* Switch Case for the port index to decide which port will be accessed */
			switch(Copy_u8PortIndex)
			{
			/* case of PORTA */
			case PORTA:
				/* Set : Use the low 16 bits in the register */
				if( Copy_u8SetOrReset == OUTPUT_SET )
				{
					GPIOA->BSRR = (GPIOA->BSRR &~(1<<Copy_u8PinIndex)) | (1<<Copy_u8PinIndex);
				}
				/* Reset : Use the high 16 bits in the register */
				else if( Copy_u8SetOrReset == OUTPUT_RESET )
				{
					/* Increment by 16 to access the high 16bits in the register */
					Copy_u8PinIndex = Copy_u8PinIndex +16;
					GPIOA->BSRR = (GPIOA->BSRR &~(1<<Copy_u8PinIndex)) | (1<<Copy_u8PinIndex);
				}
				break;
			/* case of PORTB */
			case PORTB:
				/* Set : Use the low 16 bits in the register */
				if( Copy_u8SetOrReset == OUTPUT_SET )
				{
					GPIOB->BSRR = (GPIOB->BSRR &~(1<<Copy_u8PinIndex)) | (1<<Copy_u8PinIndex);
				}
				/* Reset : Use the high 16 bits in the register */
				else if( Copy_u8SetOrReset == OUTPUT_RESET )
				{
					/* Increment by 16 to access the high 16bits in the register */
					Copy_u8PinIndex = Copy_u8PinIndex +16;
					GPIOB->BSRR = (GPIOB->BSRR &~(1<<Copy_u8PinIndex)) | (1<<Copy_u8PinIndex);
				}
				break;
			/* case of PORTC */
			case PORTC:
				/* Set : Use the low 16 bits in the register */
				if( Copy_u8SetOrReset == OUTPUT_SET )
				{
					GPIOC->BSRR = (GPIOC->BSRR &~(1<<Copy_u8PinIndex)) | (1<<Copy_u8PinIndex);
				}
				/* Reset : Use the high 16 bits in the register */
				else if( Copy_u8SetOrReset == OUTPUT_RESET )
				{
					/* Increment by 16 to access the high 16bits in the register */
					Copy_u8PinIndex = Copy_u8PinIndex +16;
					GPIOC->BSRR = (GPIOC->BSRR &~(1<<Copy_u8PinIndex)) | (1<<Copy_u8PinIndex);
				}
				break;
			default:
				break;

			}
		}
}















void MGPIO_SetAlternativeFuncPin(u8 Copy_u8PortIndex,u8 Copy_u8PinIndex,GPIO_Alterantive  Copy_enuAlternativeChoice){
	/* Reference Manual Page 148 (8.3.1 General-purpose I/O (GPIO))             */
			/* Check for the debug pins because we can't change the logic of those bits */
	if( (Copy_u8PortIndex==PORTA) && ( Copy_u8PinIndex == PIN13 || Copy_u8PinIndex == PIN14 || Copy_u8PinIndex == PIN15))
	{
		/* Do No thing */
	}
	else if((Copy_u8PortIndex==PORTB) && ( Copy_u8PinIndex == PIN3 || Copy_u8PinIndex == PIN4 ))
	{
		/* Do No thing */
	}
	else
	{
		switch (Copy_u8PortIndex) {
		case PORTA:
			if(Copy_u8PinIndex<=7)
			{
				GPIOA->AFRL &=~(ALTERNATIVE_MASK<<(Copy_u8PinIndex*4));
				GPIOA->AFRL |=(Copy_enuAlternativeChoice<<(Copy_u8PinIndex*4));
			}
			else
			{
				GPIOA->AFRH &=~(ALTERNATIVE_MASK<<((Copy_u8PinIndex-8)*4));
				GPIOA->AFRH |=(Copy_enuAlternativeChoice<<((Copy_u8PinIndex-8)*4));
			}
			break;
		case PORTB:
			if(Copy_u8PinIndex<=7)
			{
				GPIOB->AFRL &=~(ALTERNATIVE_MASK<<(Copy_u8PinIndex*4));
				GPIOB->AFRL |=(Copy_enuAlternativeChoice<<(Copy_u8PinIndex*4));
			}
			else
			{
				GPIOB->AFRH &=~(ALTERNATIVE_MASK<<((Copy_u8PinIndex-8)*4));
				GPIOB->AFRH |=(Copy_enuAlternativeChoice<<((Copy_u8PinIndex-8)*4));
			}
			break;
		case PORTC:
			if(Copy_u8PinIndex<=7)
			{
				GPIOC->AFRL &=~(ALTERNATIVE_MASK<<(Copy_u8PinIndex*4));
				GPIOC->AFRL |=(Copy_enuAlternativeChoice<<(Copy_u8PinIndex*4));
			}
			else
			{
				GPIOC->AFRH &=~(ALTERNATIVE_MASK<<((Copy_u8PinIndex-8)*4));
				GPIOC->AFRH |=(Copy_enuAlternativeChoice<<((Copy_u8PinIndex-8)*4));
			}
			break;
		default:
			break;
		}
	}
}
