/**
 ******************************************************************************
 * @file           : Timer.h
 * @author         : Danh Phan
 * @brief          : Library to interact to Timer
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
#ifndef TIMER_H_
#define TIMER_H_


// Include libraries
#include <stm32f407xx.h>
#include "SystemClock.h"


// Macroes
#define T_timer		0.001		// expect 1ms
#define AutoReload	65535		// Auto-reload value


// Prototypes
/**
  * @brief  Initialize Timer
  * @param  pTIM: pointer to timer instance
  * @retval None
  */
void Timer_init(TIM_TypeDef *pTIM);


/**
  * @brief  delay by ms
  * @param  pTIM: pointer to timer instance
  * @param  ms: delay by milisecond
  * @retval None
  */
void Timer_delay_ms(TIM_TypeDef *pTIM, int ms);


#endif /* TIMER_H_ */
