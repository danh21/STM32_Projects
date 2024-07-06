/*
 * ADC.h
 *
 *  Created on: Mar 11, 2024
 *      Author: danh21
 */

#ifndef ADC_H_
#define ADC_H_



void ADC1_Init()
{
	RCC->APB2ENR |= (1<<8);		// enable ADC1 clock

	ADC->CCR &= ~(3<<16);  		 // PCLK2 divided by 2

	ADC1->CR1 |= (1<<24);		// resolution 10-bit
	//	ADC1->CR1 |= (1<<5);		// Enable interrupt mode for EOC

	ADC1->CR2 |= (1<<0);		// adc enable respectively
	ADC1->CR2 |= (1<<1);		// continuous conversion mode
	ADC1->CR2 |= (1<<10);		// EOC after each conversion
	ADC1->CR2 &= ~(1<<11);		// data alignment right

	ADC1->SMPR2 &= ~(7<<3);		// 3 clock cycle polling, 1th channel
}



void ADC1_Start_Polling(int channel)
{
	ADC1->SQR3 |= (channel<<0);		// polling for 1 channel, keep 1 channel in the sequence at a time
	ADC1->CR2 |= (1<<30);			// start regular conversion
	while (!(ADC1->SR & (1<<1)));	// wait for EOC flag to set
}



uint32_t ADC1_Read()
{
	return ADC1->DR;
}



void ADC1_End()
{
	ADC1->CR2 &= ~(1<<0);		// disable adc
}



#endif /* ADC_H_ */
