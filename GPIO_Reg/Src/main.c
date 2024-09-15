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
 * Version 1.0: blink led periodically using ODR register
 *
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"
#include "Led.h"



/* CONFIG */
user_led led = LD3;			// user led (LD3 / LD4 / LD5 / LD6)
#define yourDelay 10000		// stuff delay



/* MAIN */
int main()
{
	SystemClock_config();
	LED_init(led);

	while(1)
	{
		toggle_led(led);
		delay(yourDelay);
	}
}



/* stuff delay, not precise */
void delay(int a)
{
	for (int i = 0; i < a; i++)
		for (int j = 0; j < 123; j++);
}
