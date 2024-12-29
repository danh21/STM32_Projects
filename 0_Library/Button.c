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
 * Version 1.1.0: Modify format name of functions, add Button_init_exti function
 ******************************************************************************
 */


// Include libraries
#include "Button.h"


// APIs
void Button_init(GPIO_TypeDef* pPort)
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


_Bool Button_isPressed (GPIO_TypeDef* pPort, uint8_t pin, GPIO_pull pull)
{
	if (pull == pull_down)
		return ((pPort->IDR & (1<<pin)) == 1);
	else
		return ((pPort->IDR & (1<<pin)) == 0);
}


void Button_waitUntil_isReleased(GPIO_TypeDef* pPort, uint8_t pin, GPIO_pull pull)
{
	while (Button_isPressed (pPort, pin, pull));
}


void Button_init_exti(GPIO_TypeDef* pPort, uint8_t pin)
{
	uint8_t cfg;
	Button_init(pPort);

	if (pPort == GPIOA)
		cfg = 0;
	else if (pPort == GPIOB)
		cfg = 1;
	else if (pPort == GPIOC)
		cfg = 2;
	else if (pPort == GPIOD)
		cfg = 3;
	else if (pPort == GPIOE)
		cfg = 4;

	if (pin >= 0 && pin <= 3)
		SYSCFG->EXTICR[0] |= (cfg << (pin*4));
	else if (pin >= 4 && pin <= 7)
		SYSCFG->EXTICR[1] |= (cfg << ((pin-4)*4));
	else if (pin >= 8 && pin <= 11)
		SYSCFG->EXTICR[2] |= (cfg << ((pin-8)*4));
	else if (pin >= 12 && pin <= 15)
		SYSCFG->EXTICR[3] |= (cfg << ((pin-12)*4));

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	EXTI->RTSR |= (1 << pin);		// rising edge
	EXTI->IMR |= (1 << pin);		// disable mask

	if (pin >= 0 && pin <= 4)
		NVIC_EnableIRQ(0+6);
	else if (pin >= 5 && pin <= 9)
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	else if (pin >= 10 && pin <= 15)
		NVIC_EnableIRQ(EXTI15_10_IRQn);
}
