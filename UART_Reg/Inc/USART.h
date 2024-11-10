/**
 ******************************************************************************
 * @file           : USART.h
 * @author         : Danh Phan
 * @brief          : Library to interact to USART
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
#ifndef USART_H_
#define USART_H_


// Include libraries
#include <stm32f407xx.h>
#include "SystemClock.h"


// Macroes
#define baudrate 115200


// Prototypes
/**
  * @brief  Initialize UART
  * @param  pUSART: pointer to USART instance
  * @retval None
  */
void USART_init(USART_TypeDef *pUSART);


/**
  * @brief  transmit data
  * @param  pUSART: pointer to USART instance
  * @param  pData: pointer to data
  * @retval None
  */
void USART_transmit(USART_TypeDef *pUSART, char *pData);


#endif /* USART_H_ */
