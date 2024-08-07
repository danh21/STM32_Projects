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
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "Timer.h"
#include "SystemClock.h"



/* MACROES */
#define led_on 		GPIOD->ODR |= 1<<13
#define led_off		GPIOD->ODR &= ~(1<<13)
#define led_is_off	(GPIOD->ODR & 1<<13) == 0
#define toggle_led 	led_is_off ? led_on : (led_off)



/* PROTOTYPE */
void GPIO_init(void);



/* MAIN */
int main()
{
	SystemClock_config();
	GPIO_init();
	Timer1_init();

	while(1)
	{
		toggle_led;
		Timer1_delay_ms(500);
	}
}



/* APIs */
void GPIO_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	// IO port D clock enable
	GPIOD->MODER |= GPIO_MODER_MODER13_0;	// General purpose output mode
}
