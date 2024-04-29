/*
 * Timer.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Danh21
 */

#ifndef TIMER_H_
#define TIMER_H_



const int f_PCLK = 16000000;

#define T_timer		0.001		// ms
#define AutoReload	65535		// Auto-reload value



/*
 * Initialize Timer
 * */
void Timer_init(TIM_TypeDef *TIM)
{
	uint32_t F_timer, prescaler;

	// F_timer = f_PCLK / (PSC + 1)
	F_timer = 1 / T_timer;
	prescaler = f_PCLK / F_timer - 1;

	if (TIM == TIM1)
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; 	// TIM1 clock enable

	TIM->PSC |= prescaler;

	TIM->ARR = AutoReload;

	TIM->CR1 |= TIM_CR1_CEN;					// Counter enable
	TIM->CR1 &= ~(TIM_CR1_DIR);					// Counter used as up counter
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
