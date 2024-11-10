/**
 ******************************************************************************
 * @file           : Button.c
 * @author         : Danh Phan
 * @brief          : Library to interact to Button
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 *							REVISION HISTORY
 * Version 1.0.0: Initial release
 ******************************************************************************
 */


// Include libraries
#include "Button.h"


// APIs
void Btn_init(GPIO_TypeDef* pPort)
{
	if (pPort == GPIOA)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	// IO port A clock enable
	else if (pPort == GPIOB)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	// IO port B clock enable
	else if (pPort == GPIOC)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	// IO port C clock enable
	else if (pPort == GPIOD)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	// IO port D clock enable
	else if (pPort == GPIOE)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;	// IO port E clock enable
}


_Bool btn_isPressed (GPIO_TypeDef* pPort, uint8_t pin, GPIO_pull pull)
{
	if (pull == pull_down)
		return ((pPort->IDR & (1<<pin)) == 1);
	else
		return ((pPort->IDR & (1<<pin)) == 0);
}


void waitUntil_btn_isReleased(GPIO_TypeDef* pPort, uint8_t pin, GPIO_pull pull)
{
	while (btn_isPressed (pPort, pin, pull));
}
