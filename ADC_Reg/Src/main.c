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
 * Version 1.1: read ADC by interrupt and send to console by UART
 * 		ref: https://www.youtube.com/watch?v=q8XSsTDAUiM
 ******************************************************************************
 */
/* LIBRARIES */
#include <stdint.h>
#include <stm32f407xx.h>
#include "Timer.h"
#include "SystemClock.h"
#include "USART.h"
#include "ADC.h"



/* GLOBAL VARS */
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

int _write(int file, char *ptr, int len)
{
	for (int DataIdx = 0; DataIdx < len; DataIdx++)
		ITM_SendChar(*ptr++);
	return len;
}



/* MAIN */
int main()
{
	SystemClock_config();
	GPIO_Init();
	Timer_init(pTIM);
	USART_init(pUSART);
	ADC_Init(pADC);

	ADC_Start_IT(pADC);

	while(1)
	{

	}
}



/* Initializing GPIO */
void GPIO_Init(void)
{
	RCC->AHB1ENR |= (1<<0);		// enable GPIOA clock
	GPIOA->MODER |= (3<<2);		// analog for PA1
	GPIOA->OSPEEDR |= (2<<2);	// high speed for PA1
}



void ADC_IRQHandler(void)
{
	uint32_t ADC_data = ADC_Read(ADC1);
//	printf("The value of ADC is %ld\n", ADC_data);
	sprintf(result, "adc value = %d\n", ADC_data);
	send_data(result);
	delay_ms(1000);
	ADC1->SR &= ~(1<<1);								// reset EOC bit
}
