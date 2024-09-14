/*
 * ADC.h
 *
 *  Created on: Mar 11, 2024
 *      Author: danh21
 *
 *      				REVISION HISTORY
 * Version 1.0: Config for ADC1/2/3
 */

#ifndef ADC_H_
#define ADC_H_



/*
 * Initialize ADC
 * */
void ADC_Init(ADC_TypeDef *pADC, uint32_t channel)
{
	/* enable ADC clock */
	if (pADC == ADC1)
	{
		RCC->APB2ENR |= (1<<8);		// enable ADC1 clock
	}
	else if (pADC == ADC2)
	{
		RCC->APB2ENR |= (1<<9);		// enable ADC2 clock
	}
	else if (pADC == ADC3)
	{
		RCC->APB2ENR |= (1<<10);	// enable ADC3 clock
	}

	/* init analog mode */
	if ( (0 <= channel && channel <= 3) || ((pADC == ADC1 || pADC == ADC2) && (4 <= channel && channel <= 7)) )
	{
		RCC->AHB1ENR |= (1<<0);					// enable GPIOA clock
		GPIOA->MODER |= (3<<(channel*2));
	}
	else if ((pADC == ADC1 || pADC == ADC2) && (8 <= channel && channel <= 9))
	{
		RCC->AHB1ENR |= (1<<1);					// enable GPIOB clock
		GPIOB->MODER |= (3<<((channel-8)*2));
	}
	else if ( (10 <= channel && channel <= 13) || ((pADC == ADC1 || pADC == ADC2) && (14 <= channel && channel <= 15)) )
	{
		RCC->AHB1ENR |= (1<<2);					// enable GPIOC clock
		GPIOC->MODER |= (3<<((channel-10)*2));
	}
	else 										// ADC3
	{
		RCC->AHB1ENR |= (1<<5);					// enable GPIOF clock
		if (4 <= channel && channel <= 8)
			GPIOC->MODER |= (3<<((channel+2)*2));
		else if (channel == 9)
			GPIOC->MODER |= (3<<(3*2));
		else if (14 <= channel && channel <= 15)
			GPIOC->MODER |= (3<<((channel-10)*2));
	}

	ADC->CCR &= ~(31<<0);  		// independent mode
	ADC->CCR &= ~(3<<16);  		// PCLK2 divided by 2
	ADC->CCR &= ~(3<<14);  		// disable DMA
	ADC->CCR &= ~(15<<8);  		// delay between 2 sampling phases

//	pADC->CR1 |= (1<<24);		// resolution 10-bit, default is 12-bit

	pADC->CR2 |= (1<<0);		// enable ADC
	pADC->CR2 |= (1<<1);		// continuous conversion mode
	pADC->CR2 |= (15<<24);		// external event to trigger start of conversion is EXTI line11
	pADC->CR2 &= ~(1<<11);		// data alignment right

	pADC->SQR1 &= ~(15<<20);	// 1 conversion in the regular channel conversion sequence
	pADC->SQR3 |= (channel<<0);	// channel is assigned to 1st conversion in regular sequence
}



/*
 * Start ADC by polling
 * */
void ADC_Start_Polling(ADC_TypeDef *pADC, int channel)
{
	pADC->CR2 &= ~(1<<10);				// The EOC bit is set at the end of each sequence of regular conversions. Overrun detection is enabled only if DMA=1
	pADC->CR2 |= (1<<30);				// start regular conversion
	while ((pADC->SR & (1<<4)) == 0);	// wait until conversion starts
}



/*
 * Read ADC value
 * */
uint32_t ADC_Read(ADC_TypeDef *pADC)
{
	return pADC->DR;
}



/*
 * End ADC operation
 * */
void ADC_End(ADC_TypeDef *pADC)
{
	pADC->CR2 |= (1<<10); 		// bit is set at the end of each regular conversion.
	pADC->CR2 &= ~(1<<0);		// disable adc
}



/*
 * Start ADC by interrupt
 * */
void ADC_Start_IT(ADC_TypeDef *pADC)
{
	pADC->CR2 |= (1<<30);		// start regular conversion
	pADC->SR &= ~(1<<1);		// reset EOC bit
	pADC->CR1 |= (1<<5);		// enable interrupt when bit EOC is set

	SCB->AIRCR &= (7<<8);		// choose priority group
	NVIC->IP[18] |= (1<<4);		// set priority is 1
	NVIC->ISER[0] |= (1<<18);	// Interrupt Set Enable
}



/* Handler for Interrupt */
void ADC_IRQHandler(void);

#endif /* ADC_H_ */
