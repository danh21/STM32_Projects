/**
 ******************************************************************************
 * @file           : main.c
 * @author         : danh21
 * @brief          : Investigate operation of Interrupt in STM32
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
 * Version 1.0.0: initial release
 ******************************************************************************
 */

/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"
#include "Button.h"
#include "Led.h"



/* CONFIG */
GPIO_TypeDef* pGPIO = GPIOA;	// built-in button on board is PA0
uint8_t pin_btn = 0;
user_led led = LD4;				// user led (LD3 / LD4 / LD5 / LD6)



/* PROTOTYPE */



/* MAIN */
int main()
{
	SystemClock_config();
	Button_init_exti(pGPIO, pin_btn);
	LED_init(led);

	while(1)
	{

	}
}


void EXTI0_IRQHandler(void)
{
	toggle_led(led);
	EXTI->PR |= (1 << pin_btn);
}
