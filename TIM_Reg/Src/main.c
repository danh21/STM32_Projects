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
 * Version 1.0.0: blink led periodically using upcounting mode
 * Version 1.0.1: refactor code, separate .c and .h files
 ******************************************************************************
 */

/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"
#include "Led.h"
#include "Timer.h"



/* CONFIG */
user_led led = LD4;				// user led (LD3 / LD4 / LD5 / LD6)
TIM_TypeDef *TIM = TIM1;



/* MAIN */
int main()
{
	SystemClock_config();
	LED_init(led);
	Timer_init(TIM);

	while(1)
	{
		toggle_led(led);
		Timer_delay_ms(TIM, 500);
	}
}
