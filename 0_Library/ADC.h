/**
 ******************************************************************************
 * @file           : ADC.h
 * @author         : Danh Phan
 * @brief          : Library to interact to ADC
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
#ifndef ADC_H_
#define ADC_H_


// Include libraries
#include <stm32f407xx.h>
#include <stdio.h>


// Macroes


// Prototypes
/**
  * @brief  Initialize ADC
  * @param  pADC: pointer to ADC instance
  * @param  channel: ADC channel
  * @retval None
  */
void ADC_Init(ADC_TypeDef *pADC, uint32_t channel);


/**
  * @brief  Start ADC by polling conversion
  * @param  pADC: pointer to ADC instance
  * @param  channel: ADC channel
  * @retval None
  */
void ADC_Start_Polling(ADC_TypeDef *pADC, uint32_t channel);


/**
  * @brief  Start ADC by polling conversion
  * @param  pADC: pointer to ADC instance
  * @param  channel: ADC channel
  * @retval None
  */
void ADC_Start_Polling(ADC_TypeDef *pADC, uint32_t channel);


/**
  * @brief  Read ADC value
  * @param  pADC: pointer to ADC instance
  * @retval received data
  */
uint32_t ADC_Read(ADC_TypeDef *pADC);


/**
  * @brief  Stop ADC conversion
  * @param  pADC: pointer to ADC instance
  * @retval None
  */
void ADC_End(ADC_TypeDef *pADC);


/**
  * @brief  Start ADC by interrupt
  * @param  pADC: pointer to ADC instance
  * @retval None
  */
void ADC_Start_IT(ADC_TypeDef *pADC);


/**
  * @brief  IRQ handler
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void);


#endif /* ADC_H_ */
