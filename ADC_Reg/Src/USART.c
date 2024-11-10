/**
 ******************************************************************************
 * @file           : USART.c
 * @author         : Danh Phan
 * @brief          : Library to interact to USART
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
#include "USART.h"


// APIs
void USART_init(USART_TypeDef *pUSART)
{
	uint32_t USART_DIV, DIV_Mantissa, DIV_Fraction, f_CLK;

	// get frequency of CLK
	if (pUSART == USART2 || pUSART == USART3 || pUSART == UART4 || pUSART == UART5)
		f_CLK = Get_PCLK1_freq();
	else if (pUSART == USART1 || pUSART == USART6)
		f_CLK = Get_PCLK2_freq();
	else
		return;

	// IO port clock enable
	if (pUSART == USART1)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;		// IO port B clock enable
	else if (pUSART == USART2 || pUSART == USART3)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;		// IO port D clock enable
	else if (pUSART == UART4 || pUSART == UART5 || pUSART == USART6)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;		// IO port C clock enable

	// pUSART setting
	if (pUSART == USART1)
	{
		GPIOB->MODER |= GPIO_MODER_MODER6_1;		// alternate function for PB6
		GPIOB->AFR[0] |= (7<<24);					// USART1 mode for PB6
		/*
		 * PB6 - USART1_TX
		 * */

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 		// USART1 clock enable
	}
	else if (pUSART == USART2)
	{
		GPIOD->MODER |= GPIO_MODER_MODER5_1;		// alternate function for PD5
		GPIOD->AFR[0] |= (7<<20);					// USART2 mode for PD5
		/*
		 * PD5 - USART2_TX
		 * */

		RCC->APB1ENR |= RCC_APB1ENR_USART2EN; 		// USART2 clock enable
	}
	else if (pUSART == USART3)
	{
		GPIOD->MODER |= GPIO_MODER_MODER8_1;		// alternate function for PD8
		GPIOD->AFR[1] |= (7<<0);					// USART3 mode for PD8
		/*
		 * PD8 - USART3_TX
		 * */

		RCC->APB1ENR |= RCC_APB1ENR_USART3EN; 		// USART3 clock enable
	}
	else if (pUSART == UART4)
	{
		GPIOC->MODER |= GPIO_MODER_MODER10_1;		// alternate function for PC10
		GPIOC->AFR[1] |= GPIO_AFRH_AFSEL10_3;		// UART4 mode for PC10
		/*
		 * PC10 - UART4_TX
		 * */

		RCC->APB1ENR |= RCC_APB1ENR_UART4EN; 		// UART4 clock enable
	}
	else if (pUSART == UART5)
	{
		GPIOC->MODER |= GPIO_MODER_MODER12_1;		// alternate function for PC12
		GPIOC->AFR[1] |= GPIO_AFRH_AFSEL12_3;		// UART5 mode for PC12
		/*
		 * PC12 - UART5_TX
		 * */

		RCC->APB1ENR |= RCC_APB1ENR_UART5EN; 		// UART5 clock enable
	}
	else if (pUSART == USART6)
	{
		GPIOC->MODER |= GPIO_MODER_MODER6_1;		// alternate function for PC6
		GPIOC->AFR[0] |= GPIO_AFRL_AFSEL6_3;		// USART6 mode for PC6
		/*
		 * PC6 - USART6_TX
		 * */

		RCC->APB2ENR |= RCC_APB2ENR_USART6EN; 		// USART6 clock enable
	}

	// pUSART setting
	pUSART->CR1 |= USART_CR1_TE; 					// transmit enable
	pUSART->CR1 |= USART_CR1_UE;					// pUSART enable

	USART_DIV = f_CLK / (baudrate * 16);
	DIV_Mantissa = USART_DIV;
	DIV_Fraction = (USART_DIV - DIV_Mantissa) * 16;
	pUSART->BRR |= (DIV_Mantissa<<4) | (DIV_Fraction);	// set baudrate
}


void USART_transmit(USART_TypeDef *pUSART, char *pData)
{
	while (*pData != '\0')
	{
		pUSART->DR = *pData;									// load data
		while ((pUSART->SR & USART_SR_TC_Msk) != USART_SR_TC);	// wait until Transmission is complete
		pData++;
	}
}
