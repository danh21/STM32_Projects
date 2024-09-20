/*
 * Button.h
 *
 * Created on: Sep 20, 2024
 * Author: danh21
 *							REVISION HISTORY
 * Version 1.0: Config 1 user button
 */

#ifndef BUTTON_H_
#define BUTTON_H_



/* Libraries */
#include <stdbool.h>



/* Data types */
typedef enum {
	pull_down,
	pull_up
} GPIO_pull;



/* APIs */

// Initialize port of button
void Btn_init(GPIO_TypeDef* port)
{
	if (port == GPIOA)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// IO port A clock enable
	else if (port == GPIOB)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	// IO port B clock enable
	else if (port == GPIOC)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	// IO port C clock enable
	else if (port == GPIOD)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	// IO port D clock enable
	else if (port == GPIOE)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;	// IO port E clock enable
}


// Check whether button is pressed or not
_Bool btn_isPressed (GPIO_TypeDef* port, uint8_t pin, GPIO_pull pull)
{
	if (pull == pull_down)
		return ((port->IDR & (1<<pin)) == 1);
	else
		return ((port->IDR & (1<<pin)) == 0);
}


// Wait until button is released
void waitUntil_btn_isReleased(GPIO_TypeDef* port, uint8_t pin, GPIO_pull pull)
{
	while (btn_isPressed (port, pin, pull));
}



#endif /* BUTTON_H_ */
