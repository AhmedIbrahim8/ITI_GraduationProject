/********************************************************/
/*		HIR frame generator	based on NEC protocol		*/
/********************************************************/

/*		functions declaration 		*/
void HIR_SEND_START_BIT(void);
void HIR_HIGH_BIT(void);
void HIR_LOW_BIT(void);
void IR_SNED_FRAME(u8 address, u8 data);
/********************************************************/

/*		functions definition		*/
// this function sends start bit according to NEC protocol which is 9ms high then 4.5ms low
void HIR_SEND_START_BIT(void)
{
	TIMER_Start(TIMER2_SELECTION);
	MSYSTICK_voidDelayms(9);
	TIMER_Stop(TIMER2_SELECTION);
	MSYSTICK_voidDelayms(4.5);
}

// this function sends high bit according to NEC protocol which is 560us high then 1687us low
void HIR_HIGH_BIT(void)
{
	TIMER_Start(TIMER2_SELECTION);
	MSYSTICK_voidDelayMs(560);
	TIMER_Stop(TIMER2_SELECTION);
	MSYSTICK_voidDelayMs(1687);
}

// this function sends low bit according to NEC protocol which is 560us high then 560us low
void HIR_LOW_BIT(void)
{
	TIMER_Start(TIMER2_SELECTION);
	MSYSTICK_voidDelayMs(560);
	TIMER_Stop(TIMER2_SELECTION);
	MSYSTICK_voidDelayMs(560);
}

// this function is responsible for sending the whole frame of NEC protocol
void IR_SNED_FRAME(u8 address, u8 data)
{
	u8 address_inverse = 0, data_inverse = 0;
	// start bit
	HIR_SEND_START_BIT();

	// address sent
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(address, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();

		if (i == 0)
		{
			break;
		}
	}

	// address inverse sent
	address_inverse = (~address);
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(address_inverse, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();
		if (i == 0)
		{
			break;
		}
	}

	// data sent
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(data, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();
		if (i == 0)
		{
			break;
		}
	}

	// data inverse sent
	data_inverse = (~data);
	for (u8 i = 7; i >= 0; i--)
	{
		(GET_BIT(data_inverse, i) == 0) ? HIR_LOW_BIT() : HIR_HIGH_BIT();
		if (i == 0)
		{
			break;
		}
	}

	TIMER_Stop(TIMER2_SELECTION);
}

/********************************************************/
/********************************************************/
/********************************************************/
/********************************************************/
/*		simple program to send frame over IR transmitter		*/
int main()
{
	// RCC initialization
	MRCC_INIT();
	MRCC_ENABLE_PERIPHERAL(RCC_APB1, RCC_APB1_TIM2);
	MRCC_ENABLE_PERIPHERAL(RCC_AHB1, RCC_AHB1_GPIOAEN);

	// systick initialization
	MSYSTICK_voidInit();

	// set the pin that is responsible for PWM generation with 38KHZ
	MGPIO_SetMode(PORTA, PIN3, ALT_FUNC);
	MGPIO_PinAlternateFunction(PORTA, PIN3, AF1);

	// timer initialization
	TIMER_Init(&Timer_configuration);
	TIMER_SetPrescaler(TIMER2_SELECTION, 14);
	TIMER_SetARR(TIMER2_SELECTION, 27);
	TIMER_SetCompareValue(TIMER2_SELECTION, TIMER_CHANNEL_4, 13);

	while (1)
	{
		IR_SNED_FRAME(0, 5);
		MSYSTICK_voidDelayms(2000);
	}
	return 0;
}
