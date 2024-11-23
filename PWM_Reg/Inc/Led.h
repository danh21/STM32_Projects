/**
 ******************************************************************************
 * @file           : Led.h
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
#ifndef LED_H_
#define LED_H_

// Include libraries
#include <stm32f407xx.h>



// Macroes

// Define register controls LEDs
#define GPIOx_ODR 0
#define GPIOx_BSRR 1
#define LED_ctrl_reg GPIOx_ODR		// select reg to control led (GPIOx_ODR / GPIOx_BSRR)



// Define action to LEDs
#if LED_ctrl_reg == GPIOx_ODR
	#define led_on(x) 		GPIOD->ODR |= 1<<x
	#define led_off(x)		GPIOD->ODR &= ~(1<<x)
#elif LED_ctrl_reg == GPIOx_BSRR
	#define led_on(x) 		GPIOD->BSRR |= 1<<x
	#define led_off(x)		GPIOD->BSRR |= 1<<(x+16)
#endif

#define led_is_off(x)	(GPIOD->ODR & 1<<x) == 0
#define toggle_led(x) 	led_is_off(x) ? led_on(x) : (led_off(x))



// Data types
// Define user LEDs
typedef enum {
	LD3 = 13,
	LD4 = 12,
	LD5 = 14,
	LD6 = 15
} user_led;



// Prototypes
/**
  * @brief  Initialize LED
  * @param  LD: built-in led on board
  * @retval None
  */
void LED_init(user_led LD);



#endif /* LED_H_ */
