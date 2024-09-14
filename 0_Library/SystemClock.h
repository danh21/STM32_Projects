/*
 * SystemClock.h
 *
 * Created on: Apr 17, 2024
 * Author: Danh21
 *
 *      			REVISION HISTORY
 * Version 1.0: Init default config by SystemClock_config()
 * Version 1.1: Add APIs returning frequency of HCLK, PCLK1, PCLK2
 */

#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_



/*
 * GLOBAL VARS
 * */
uint32_t SystemCoreClock = 16000000;
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};



/*
 * Initialize default system clock
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



/*
 * Returns the HCLK frequency
 */
uint32_t Get_HCLK_freq(void)
{
  return SystemCoreClock;
}



/*
 * Returns the PCLK1 frequency
 */
uint32_t Get_PCLK1_freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
  return (Get_HCLK_freq() >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)>> RCC_CFGR_PPRE1_Pos]);
}



/*
 * Returns the PCLK2 frequency
 */
uint32_t Get_PCLK2_freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency ---------------------------*/
  return (Get_HCLK_freq()>> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2)>> RCC_CFGR_PPRE2_Pos]);
}



#endif /* SYSTEMCLOCK_H_ */
