#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/MGPIO_Interface.h"

#include "../include/MRCC_Interface.h"






void delay_us(u32 microseconds) {
    // Assuming a 16MHz system clock
    microseconds = microseconds * 16;
    while (microseconds--) {
        __asm__("nop");
    }
}


void ultra_init(void)
{
  // Configure trigger pin as output
	MGPIO_SetMode(PORTB,PIN0,GENRAL_PURPOSE_OUTPUT_MODE);

	MGPIO_SetOutputPinMode(PORTB,PIN0,OUTPUT_PUSH_PULL,OUTPUT_LOW_SPEED_TYPE);

	MGPIO_SetPinValue(PORTB,PIN0,0);

    // Configure echo pin as input
	MGPIO_SetMode(PORTA,PIN8,INPUT_RESET_STATE);

	MGPIO_SetInputPinMode(PORTA,PIN8,PULL_DOWN);


}

void send_pulse(void) {
    // Set trigger pin high for 10 microseconds to generate a pulse


	MGPIO_SetPinValue(PORTB,PIN0,1);
	delay_us(10);
	MGPIO_SetPinValue(PORTB,PIN0,0);

}

u32 measure_distance(void) {
    // Wait for the echo pin to go high
	volatile u8 Copy_pu8Data=0;


	while(Copy_pu8Data==0){
		MGPIO_GetPinValue(PORTA,PIN8,&Copy_pu8Data);
	}

    // Start timer
    volatile u32 start_time = 0;
    while(Copy_pu8Data==1){
        start_time++;
        delay_us(1);
        MGPIO_GetPinValue(PORTA,PIN8,&Copy_pu8Data);
    }
    // Calculate distance in centimeters
    volatile u32 distance = (start_time * 0.0343 * 10.7);
    return distance;



}
















/**********************************************************/
/*********************** Global Variables *****************/
/**********************************************************/


int main(){
	volatile u32 distance = 0;
	MRCC_Init();
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	ultra_init();





	while(1){
		send_pulse();
		distance = measure_distance();
		send_pulse();
		distance = measure_distance();

	}
	return 0;
}
