/**
 ******************************************************************************
 * @file           : Timer.c
 * @author         : Danh Phan
 * @brief          : Library to interact to Timer
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
#include "Timer.h"


// APIs
void Timer_init(TIM_TypeDef *pTIM)
{
	uint32_t F_timer, prescaler, f_CLK;

	// get frequency of CLK
	if (pTIM == TIM1 || pTIM == TIM8 || pTIM == TIM9 || pTIM == TIM10 || pTIM == TIM11)
		f_CLK = Get_PCLK2_freq();
	else if (pTIM == TIM2 || pTIM == TIM3 || pTIM == TIM4 || pTIM == TIM5 || pTIM == TIM6 || pTIM == TIM7 || pTIM == TIM12 || pTIM == TIM13 || pTIM == TIM14)
		f_CLK = Get_PCLK1_freq();

	// pTIM clock enable
	if (pTIM == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (pTIM == TIM8)
		RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	else if (pTIM == TIM9)
		RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	else if (pTIM == TIM10)
		RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	else if (pTIM == TIM11)
		RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
	else if (pTIM == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (pTIM == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (pTIM == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	else if (pTIM == TIM5)
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	else if (pTIM == TIM6)
		RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	else if (pTIM == TIM7)
		RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	else if (pTIM == TIM12)
		RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
	else if (pTIM == TIM13)
		RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
	else if (pTIM == TIM14)
		RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

	// F_timer = f_CLK / (PSC + 1)
	F_timer = 1 / T_timer;
	prescaler = f_CLK / F_timer - 1;

	pTIM->PSC |= prescaler;
	pTIM->ARR = AutoReload;

	pTIM->CR1 |= TIM_CR1_CEN;		// Counter enable
	pTIM->CR1 &= ~(TIM_CR1_DIR);		// Counter used as up counter
}


void Timer_delay_ms(TIM_TypeDef *pTIM, int ms)
{
	pTIM->CNT = 0;
	while (pTIM->CNT < ms);
}
