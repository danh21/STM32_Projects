/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Danh21
 * @brief          : Main program body
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
 * Version 1.0: blink led by periodically using ODR
 * Version 1.1: blink led by periodically using BSRR
 * Version 1.2: blink led by periodically using counter up timer
 *
 * Version 2.0: toggle led by button using polling technique
 *
 * Version 3.0: blink led by periodically using counter up timer; apply Led.h lib
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"
#include "Timer.h"
#include "Led.h"



/* CONFIG */
TIM_TypeDef *TIM = TIM8;
user_led led = LD3;
uint32_t your_delay = 1000;



/* MAIN */
int main()
{
	SystemClock_config();
	LED_init(led);
	Timer_init(TIM);

	while(1)
	{
		toggle_led(led);
		Timer_delay_ms(TIM, your_delay);
	}
}
