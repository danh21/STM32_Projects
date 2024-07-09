/*
 * ADC.h
 *
 *  Created on: Mar 11, 2024
 *      Author: danh21
 */

#ifndef ADC_H_
#define ADC_H_



void ADC_Init(ADC_TypeDef *pADC)
{
	if (pADC == ADC1)
	{
		RCC->APB2ENR |= (1<<8);	// enable ADC1 clock
	}

	RCC->AHB1ENR |= (1<<0);		// enable GPIOA clock

	ADC->CCR &= ~(3<<16);  		// PCLK2 divided by 2

//	pADC->CR1 |= (1<<24);		// resolution 10-bit
	//	pADC->CR1 |= (1<<5);	// Enable interrupt mode for EOC

	pADC->CR2 |= (1<<0);		// adc enable respectively
	pADC->CR2 |= (1<<1);		// continuous conversion mode
	pADC->CR2 |= (1<<10);		// EOC after each conversion
	pADC->CR2 &= ~(1<<11);		// data alignment right

	pADC->SMPR2 &= ~(7<<3);		// 3 clock cycle polling
}



void ADC_Start_Polling(ADC_TypeDef *pADC, int channel)
{
	pADC->SQR3 |= (channel<<0);			// polling for 1 channel, keep 1 channel in the sequence at a time
	pADC->CR2 &= ~(1<<10);				// The EOC bit is set at the end of each sequence of regular conversions. Overrun detection is enabled only if DMA=1
	pADC->CR2 |= (1<<30);				// start regular conversion
	while ((pADC->SR & (1<<4)) == 0);	// wait until conversion starts
}



uint32_t ADC_Read(ADC_TypeDef *pADC)
{
	return pADC->DR;
}



void ADC_End(ADC_TypeDef *pADC)
{
	pADC->CR2 |= (1<<10); 		//bit is set at the end of each regular conversion.
	pADC->CR2 &= ~(1<<0);		// disable adc
}



#endif /* ADC_H_ */