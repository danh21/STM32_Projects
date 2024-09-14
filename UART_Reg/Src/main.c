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
 * Version 1.0: transmit data by UART
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "Timer.h"
#include "SystemClock.h"
#include "USART.h"



/* VARS */
USART_TypeDef *USART = USART6;
TIM_TypeDef *TIM = TIM1;



/* MACROES */
#define send_data(x) 	USART_transmit(USART, x);
#define delay_ms(x)		Timer_delay_ms(TIM, x)



/* MAIN */
int main()
{
	SystemClock_config();
	Timer_init(TIM);
	USART_init(USART);

	while(1)
	{
		send_data("hello world\n");
		delay_ms(1000);
	}
}
