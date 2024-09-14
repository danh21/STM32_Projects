/*
 * Led.h
 *
 * Created on: Aug 26, 2024
 * Author: Danh21
 *							REVISION HISTORY
 * Version 1.0: Config 4 user leds
 */

#ifndef LED_H_
#define LED_H_



/* Define user LEDs */
typedef enum {
	LD3 = 13,
	LD4 = 12,
	LD5 = 14,
	LD6 = 15
} user_led;



/* Macros */
#define led_on(x) 		GPIOD->ODR |= 1<<x
#define led_off(x)		GPIOD->ODR &= ~(1<<x)
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
