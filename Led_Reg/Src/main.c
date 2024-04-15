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
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>



/* MACROES */
#define led_on 	GPIOD->ODR |= (1<<13)
#define led_off	GPIOD->ODR &= ~(1<<13)



/* PROTOTYPE */
void SystemClock_config();
void GPIO_init(void);
void delay(int a);



/* MAIN */
int main()
{
	SystemClock_config();
	GPIO_init();

	while(1)
	{
		led_on;
		delay(10000);
		led_off;
		delay(10000);
	}
}



/* APIs */
void SystemClock_config()
{
	RCC->AHB1ENR |= (1<<3);		// enable IO Port D clock
}

void GPIO_init(void)
{
	GPIOD->MODER |= (1<<26);	// output mode for PD13
}

void delay(int a)
{
	for (int i = 0; i < a; i++)
		for (int j = 0; j < 123; j++);
}
