/**
 ******************************************************************************
 * @file           : SystemClock.c
 * @author         : Danh Phan
 * @brief          : Library to interact to system clock of MCU
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
 * Version 1.1.0: Add SystemClock_config_MCO1 function
 ******************************************************************************
 */


// Include libraries
#include "SystemClock.h"


// Variables
uint32_t SystemCoreClock = 16000000;
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};


// APIs
void SystemClock_config(void)
{
	RCC->CR |= RCC_CR_HSION;				// enable HSI
	while (!(RCC->CR & RCC_CR_HSIRDY));		// see that HSI is ready or not

	// Power regulator
	PWR->CR |= PWR_CR_VOS;

	// Flash latency setup
	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	// HSI oscillator used as system clock
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
}


uint32_t SystemClock_get_HCLK_freq(void)
{
  return SystemCoreClock;
}


uint32_t SystemClock_get_PCLK1_freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
  return (SystemClock_get_HCLK_freq() >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)>> RCC_CFGR_PPRE1_Pos]);
}


uint32_t SystemClock_get_PCLK2_freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency ---------------------------*/
  return (SystemClock_get_HCLK_freq()>> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2)>> RCC_CFGR_PPRE2_Pos]);
}


void SystemClock_config_MCO1(void)
{
	RCC->CFGR &= ~(RCC_CFGR_MCO1);				// select HSI as clock source
	RCC->CFGR |= (6 << RCC_CFGR_MCO1PRE_Pos);	// prescaler div by 4
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		// Enable the peripheral clock for GPIOA peripheral
	GPIOA->MODER |= GPIO_MODER_MODER8_1;		// alternate func
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL8);		// AF0 - MCO1
}
