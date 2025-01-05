/**
 ******************************************************************************
 * @file           : main.c
 * @author         : danh21
 * @brief          : Investigate operation of system clock in STM32
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
 * Version 1.0.0: initial release, measure clock frequency using MCO1 pin
 ******************************************************************************
 */

/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"



/* CONFIG */
uint8_t div_prescaler = 4;



/* PROTOTYPE */



/* MAIN */
int main()
{
	SystemClock_config_HSI();
	SystemClock_config_MCO1(div_prescaler);

	while(1)
	{

	}
}
