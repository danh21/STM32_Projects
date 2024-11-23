/**
 ******************************************************************************
 * @file           : main.c
 * @author         : danh21
 * @brief          : Investigate operation of PWM in STM32
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
 * Version 1.0.0: Initial release, adjust the brightness of led
 ******************************************************************************
 */

/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "SystemClock.h"
#include "Led.h"
#include "Timer.h"



/* CONFIG */
PWM_ctrl_t PWM_instance = {
	.pTIM = TIM1,			// Timer
	.channel = 2			// PWM Generation channel
};



/* MAIN */
int main()
{
	SystemClock_config();
	PWM_init(&PWM_instance);

	while(1)
	{
		PWM_generate_auto(&PWM_instance);
	}
}
