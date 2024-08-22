/*
 * USART.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Danh21
 */

#ifndef USART_H_
#define USART_H_

#define f_PCLK 		16000000
#define baudrate 	115200



/* Initializing UART */
void USART_init(USART_TypeDef *USART)
{
	uint32_t USART_DIV, DIV_Mantissa, DIV_Fraction;

	if (USART == USART2)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;		// IO port A clock enable

		GPIOD->MODER |= (2<<10);					// alternate function for PD5
		GPIOD->AFR[0] |= (7<<20);					// USART2 mode for PA2
		/*
		 * PD5 - USART2 TX
		 * */

		RCC->APB1ENR |= RCC_APB1ENR_USART2EN; 		// USART2 clock enable
	}

	USART->CR1 |= USART_CR1_TE; 					// transmit enable
	USART->CR1 |= USART_CR1_UE;						// USART enable

	USART_DIV = f_PCLK / (baudrate * 16);
	DIV_Mantissa = USART_DIV;
	DIV_Fraction = (USART_DIV - DIV_Mantissa) * 16;
	USART->BRR |= (DIV_Mantissa<<4) | (DIV_Fraction);	// set baudrate
}



/* transmit data */
void USART_transmit(USART_TypeDef *USART, char *p)
{
	while (*p != '\0')
	{
		USART->DR = *p;											// load data
		while ((USART->SR & USART_SR_TC_Msk) != USART_SR_TC);	// wait until Transmission is complete
		p++;
	}
}

#endif /* USART_H_ */
