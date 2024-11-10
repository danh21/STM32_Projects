/**
 ******************************************************************************
 * @file           : main.c
 * @author         : danh21
 * @brief          : Investigate operation of GPIO in STM32
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
 * Version 1.0.0: blink led periodically using ODR register
 * Version 1.1.0: blink led periodically using BSRR register
 *
 * Version 2.0.0: toggle led by pressing button using polling technique
 * Version 2.0.1: refactor code, separate .c and .h files
 ******************************************************************************
 */

/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"
#include "Led.h"
#include "Button.h"



/* CONFIG */
user_led led = LD4;				// user led (LD3 / LD4 / LD5 / LD6)
//#define yourDelay 10000			// stuff delay

#define port_btn GPIOA			// built-in button on board is PA0
#define pin_bn 0
#define pull_btn pull_up		// pull-down resistor



/* PROTOTYPE */
void delay(int a);



/* MAIN */
int main()
{
	SystemClock_config();
	LED_init(led);
	Btn_init(port_btn);

	while(1)
	{
		if (btn_isPressed(port_btn, pin_bn, pull_btn))
		{
			waitUntil_btn_isReleased(port_btn, pin_bn, pull_btn);
			toggle_led(led);
		}
	}
}



/* stuff delay, not precise */
void delay(int a)
{
	for (int i = 0; i < a; i++)
		for (int j = 0; j < 123; j++);
}
