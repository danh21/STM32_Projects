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
 * Version 1.0.0: read ADC by polling and send to console by UART
 * Version 1.1.0: read ADC by interrupt and send to console by UART
 * Version 1.2.0: can use channel 0 - 15 of ADC1/2/3 to read ADC
 * Version 1.2.1: refactor code, separate .c and .h files
 *
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
ADC_TypeDef *pADC = ADC3;
USART_TypeDef *pUSART = USART6;
uint32_t adc_channel = 11;

uint32_t ADC_data = 0;
char result[20];



/* MACROES */
#define send_data(x) 	USART_transmit(pUSART, x);
#define delay_ms(x)		Timer_delay_ms(pTIM, x)



/* MAIN */
int main()
{
	SystemClock_config();
	ADC_Init(pADC, adc_channel);
	Timer_init(pTIM);
	USART_init(pUSART);

	ADC_Start_IT(pADC);

	while(1)
	{

	}
}



/* ADC ISR */
void ADC_IRQHandler(void)
{
	uint32_t ADC_data = ADC_Read(pADC);
	sprintf(result, "adc value = %ld\n", ADC_data);
	send_data(result);
	delay_ms(1000);
	pADC->SR &= ~(1<<1);		// reset EOC bit
}
