/*
 * Timer.h
 *
 * Created on: Apr 17, 2024
 * Author: danh21
 *
 *      			REVISION HISTORY
 * Version 1.0: Init and create delay by TIM1
 * Version 2.0: Init and create delay by any TIM
 */
#include "SystemClock.h"

#ifndef TIMER_H_
#define TIMER_H_



/* MACRO */
#define T_timer		0.001		// expect 1ms
#define AutoReload	65535		// Auto-reload value



/*
 * Initialize Timer
 * */
void Timer_init(TIM_TypeDef *TIM)
{
	uint32_t F_timer, prescaler, f_CLK;

	// get frequency of CLK
	if (TIM == TIM1 || TIM == TIM8 || TIM == TIM9 || TIM == TIM10 || TIM == TIM11)
		f_CLK = Get_PCLK2_freq();
	else if (TIM == TIM2 || TIM == TIM3 || TIM == TIM4 || TIM == TIM5 || TIM == TIM6 || TIM == TIM7 || TIM == TIM12 || TIM == TIM13 || TIM == TIM14)
		f_CLK = Get_PCLK1_freq();

	// TIM clock enable
	if (TIM == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (TIM == TIM8)
		RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	else if (TIM == TIM9)
		RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	else if (TIM == TIM10)
		RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	else if (TIM == TIM11)
		RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
	else if (TIM == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (TIM == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (TIM == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	else if (TIM == TIM5)
		RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	else if (TIM == TIM6)
		RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	else if (TIM == TIM7)
		RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	else if (TIM == TIM12)
		RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
	else if (TIM == TIM13)
		RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
	else if (TIM == TIM14)
		RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

	// F_timer = f_CLK / (PSC + 1)
	F_timer = 1 / T_timer;
	prescaler = f_CLK / F_timer - 1;

	TIM->PSC |= prescaler;
	TIM->ARR = AutoReload;

	TIM->CR1 |= TIM_CR1_CEN;		// Counter enable
	TIM->CR1 &= ~(TIM_CR1_DIR);		// Counter used as up counter
}



/*
 * delay by ms
 * */
void Timer_delay_ms(TIM_TypeDef *TIM, int ms)
{
	TIM->CNT = 0;
	while (TIM->CNT < ms);
}



#endif /* TIMER_H_ */
