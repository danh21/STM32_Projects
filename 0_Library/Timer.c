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
 * Version 1.1.0: Add PWM mode and software delay
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
	pTIM->CR1 &= ~(TIM_CR1_DIR);	// Counter used as up counter
}



void Software_delay(uint32_t time)
{
	for (uint32_t i = 0; i < time; i++)
		for (uint32_t j = 0; j < 1500; j++);
}



void Timer_delay_ms(TIM_TypeDef *pTIM, uint32_t ms)
{
	pTIM->CNT = 0;
	while (pTIM->CNT < ms);
}



void PWM_init(PWM_ctrl_t *pCtrl)
{
	TIM_TypeDef *TIM = pCtrl->pTIM;
	uint8_t *channel = &pCtrl->channel;
	GPIO_TypeDef *port;
	int *pin = &pCtrl->pin;

	// enable port clock and select GPIO port
	if (TIM == TIM1 || TIM == TIM9)
	{
		pCtrl->pPort = GPIOE;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	}
	else if (((TIM == TIM3) && (*channel == 1 || *channel == 2)) || (TIM == TIM2) || (TIM == TIM5) || (TIM == TIM13) || (TIM == TIM14))
	{
		pCtrl->pPort = GPIOA;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
	else if (((TIM == TIM3) && (*channel == 3 || *channel == 4)) || (TIM == TIM10) || (TIM == TIM11) || (TIM == TIM12))
	{
		pCtrl->pPort = GPIOB;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	}
	else if (TIM == TIM4)
	{
		pCtrl->pPort = GPIOD;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	}
	else if (TIM == TIM6 || TIM == TIM7)
	{
		// no support PWM
		return;
	}
	else if (TIM == TIM8)
	{
		pCtrl->pPort = GPIOC;
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	}
	else return;

	// enable timer clock and select GPIO pin
	*pin = -1;
	if (TIM == TIM1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
		if (*channel == 1)
			*pin = 9;
		else if (*channel == 2)
			*pin = 11;
		else if (*channel == 3)
			*pin = 13;
		else if (*channel == 4)
			*pin = 14;
	}
	else if (TIM == TIM2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		if (*channel >= 1 && *channel <= 4)
			*pin = *channel - 1;
	}
	else if (TIM == TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		if (*channel == 1 || *channel == 2)
			*pin = *channel + 5;
		else if (*channel == 3 || *channel == 4)
			*pin = *channel - 3;
	}
	else if (TIM == TIM4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		if (*channel >= 1 && *channel <= 4)
			*pin = *channel + 11;
	}
	else if (TIM == TIM5)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
		if (*channel >= 1 && *channel <= 4)
			*pin = *channel - 1;
	}
	else if (TIM == TIM8)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
		if (*channel >= 1 && *channel <= 4)
			*pin = *channel + 5;
	}
	else if (TIM == TIM9)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
		if (*channel == 1 || *channel == 2)
			*pin = *channel + 4;
	}
	else if (TIM == TIM10)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
		if (*channel == 1)
			*pin = 8;
	}
	else if (TIM == TIM11)
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
		if (*channel == 1)
			*pin = 9;
	}
	else if (TIM == TIM12)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
		if (*channel == 1 || *channel == 2)
			*pin = *channel + 13;
	}
	else if (TIM == TIM13)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
		if (*channel == 1)
			*pin = 6;
	}
	else if (TIM == TIM14)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
		if (*channel == 1)
			*pin = 7;
	}

	if (*pin == -1)									// invalid channel
		return;

	port = pCtrl->pPort;
	port->MODER |= (1 << (*pin * 2));				// output mode

	TIM->ARR = AutoReload;							// auto reload value
	TIM->CR1 |= TIM_CR1_ARPE; 						// to enable Auto Reload

	TIM->PSC = 15;									// set prescaler

	TIM->CCMR1 |= (1<<5) | (1<<6);					// use PWM mode-1
	TIM->CCMR1 &= ~(1<<4);
	TIM->CCMR1 |= TIM_CCMR1_OC1PE;					// Preload register on TIMx_CCR1 enabled

	TIM->EGR |= TIM_EGR_UG;							// Reinitialize the counter and generates an update of the registers

	TIM->CCER |= TIM_CCER_CC1E;						// OC1 output on the related pin
	TIM->CCER &= ~TIM_CCER_CC1P;					// output polarity active High

	TIM->BDTR |= TIM_BDTR_BKP | TIM_BDTR_MOE;		// Break input BRK is active high & OC and OCN outputs are enabled

	TIM->CR1 |= TIM_CR1_CEN; 						// Counter enable

	while (!(TIM->SR & TIM_SR_UIF));				// This bit is set by hardware when the registers are updated

	TIM->CNT = 0;									// initial value of Counter
}



void PWM_generate_auto(PWM_ctrl_t *pCtrl)
{
	TIM_TypeDef *TIM = pCtrl->pTIM;
	GPIO_TypeDef *port = pCtrl->pPort;
	int pin = pCtrl->pin;

	for (int i = 100; i <= AutoReload; i += 5)
	{
		TIM->CCR1 = i;
		while ((TIM->CNT) < (TIM->CCR1))
			port->ODR |= (1<<pin);
		port->ODR &= ~(1<<pin);
		Software_delay(2);
	}
}
