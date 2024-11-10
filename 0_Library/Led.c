/**
 ******************************************************************************
 * @file           : Led.c
 * @author         : Danh Phan
 * @brief          : Library to interact to Led
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
#include "Led.h"


// APIs
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
