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
 * Version 1.0: read ADC by polling and send to console by UART
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "Timer.h"
#include "SystemClock.h"
#include "ADC.h"
#include "USART.h"



/* VARS */
TIM_TypeDef *pTIM = TIM1;
ADC_TypeDef *pADC = ADC1;
USART_TypeDef *pUSART = USART2;

uint32_t ADC_data = 0;
char result[20];



/* PROTOTYPES */
void GPIO_init();



/* MACROES */
#define send_data(x) 	USART_transmit(pUSART, x);
#define delay_ms(x)		Timer_delay_ms(pTIM, x)



/* MAIN */
int main()
{
	SystemClock_config();
	GPIO_init();
	Timer_init(pTIM);
	ADC_Init(pADC);
	USART_init(pUSART);

	while(1)
	{
		ADC_Start_Polling(pADC, 1);
		ADC_data = ADC_Read(pADC);
		sprintf(result, "adc value = %d\n", ADC_data);

		send_data(result);
		delay_ms(1000);
	}
}



/* Initializing GPIO */
void GPIO_init(void)
{
	GPIOA->MODER |= (3<<2);				// analog for PA1
	GPIOA->OSPEEDR |= (2<<2);			// high speed for PA1
}
