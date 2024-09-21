/*
 * Led.h
 *
 * Created on: Aug 26, 2024
 * Author: danh21
 *							REVISION HISTORY
 * Version 1.0: Config 4 user leds
 * Version 1.1: Add control led by BSRR register
 *
 */

#ifndef LED_H_
#define LED_H_



/* Data types */

// Define user LEDs
typedef enum {
	LD3 = 13,
	LD4 = 12,
	LD5 = 14,
	LD6 = 15
} user_led;

// Define register controls LEDs
#define GPIOx_ODR 0
#define GPIOx_BSRR 1
#define LED_ctrl_reg GPIOx_BSRR		// select reg to control led (GPIOx_ODR / GPIOx_BSRR)



/* Macros */
#if LED_ctrl_reg == GPIOx_ODR
	#define led_on(x) 		GPIOD->ODR |= 1<<x
	#define led_off(x)		GPIOD->ODR &= ~(1<<x)
#elif LED_ctrl_reg == GPIOx_BSRR
	#define led_on(x) 		GPIOD->BSRR |= 1<<x
	#define led_off(x)		GPIOD->BSRR |= 1<<(x+16)
#endif

#define led_is_off(x)	(GPIOD->ODR & 1<<x) == 0
#define toggle_led(x) 	led_is_off(x) ? led_on(x) : (led_off(x))



/*
 * Init LED
 * */
void LED_init(user_led LD)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	// IO port D clock enable

	// set general purpose output mode
	switch (LD)
	{
		case LD3:
			GPIOD->MODER |= GPIO_MODER_MODER13_0;
	 		break;
		case LD4:
			GPIOD->MODER |= GPIO_MODER_MODER12_0;
			break;
		case LD5:
			GPIOD->MODER |= GPIO_MODER_MODER14_0;
			break;
		case LD6:
			GPIOD->MODER |= GPIO_MODER_MODER15_0;
			break;
		default:
			break;
	}
}



#endif /* LED_H_ */
