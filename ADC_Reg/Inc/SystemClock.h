/*
 * SystemClock.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Danh21
 */

#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_



/*
 * Initialize system clock
 * */
void SystemClock_config()
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



#endif /* SYSTEMCLOCK_H_ */
